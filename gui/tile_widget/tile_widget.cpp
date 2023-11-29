#include "tile_widget.h"
#include "ui_tile_widget.h"

#include <QDebug>
#include <QSplitter>

TileWidget::TileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TileWidget)
{
    this->ui->setupUi(this);
    connect(this->ui->split_horizontal, &QPushButton::clicked, this, &TileWidget::onSplitHorizontal);
    connect(this->ui->split_vertical, &QPushButton::clicked, this, &TileWidget::onSplitVertical);
    connect(this->ui->close_panel, &QPushButton::clicked, this, &TileWidget::onClosePanel);
    connect(this, &TileWidget::closePanel, this, &TileWidget::onClosePanel, Qt::QueuedConnection);
    connect(this->ui->tile_type_combo_box, &QComboBox::currentIndexChanged, this, &TileWidget::onTileViewTypeIndexChanged);
}


TileWidget::~TileWidget()
{
    delete ui;
}


void TileWidget::init(const std::shared_ptr<TileViewDispatcher> &tile_view_dispatcher)
{
    this->tile_view_dispatcher = tile_view_dispatcher;
    connect(this, &TileWidget::tileWidgetAwaitTileView, this->tile_view_dispatcher.get(), &TileViewDispatcher::onTileWidgetAwaitTileView);
    connect(this->tile_view_dispatcher.get(), &TileViewDispatcher::tileViewCreated, this, &TileWidget::onTileViewCreated);

    std::unordered_map<ID, std::shared_ptr<TileViewInfo>> tiles_info = this->tile_view_dispatcher->getLoadedTileViewsInfo();
    for (auto& tile_info : tiles_info)
    {
        std::shared_ptr<TileViewInfo> info_obj = tile_info.second;
        this->ui->tile_type_combo_box->addItem(info_obj->getIcon(), info_obj->getTitle(), QVariant(tile_info.first));
    }

    if (tiles_info.size() > 0)
    {
        emit tileWidgetAwaitTileView(this->getId(), tiles_info.begin()->first);
    }
}


void TileWidget::resizeEvent(QResizeEvent *event) {
    if ((event->size().width() != event->oldSize().width() && event->size().width() == 0) ||
        (event->size().height() != event->oldSize().height() && event->size().height() == 0)) {

        emit this->closePanel();
    }
    QWidget::resizeEvent(event);
}


void TileWidget::onSplitHorizontal()
{
    QWidget *parent_widget = this->parentWidget();
    if (!parent_widget) return;

    // If top widget is splitter with same orientation, add new widget to splitter
    if (QSplitter *parent_splitter = qobject_cast<QSplitter*>(parent_widget))
    {
        if (parent_splitter->orientation() == Qt::Horizontal)
        {
            TileWidget *new_widget = new TileWidget(nullptr);
            new_widget->init(this->tile_view_dispatcher);
            int index = parent_splitter->indexOf(this);
            parent_splitter->insertWidget(index + 1, new_widget);
            return;
        }
    }

    // Otherwise, we need to create new splitter
    QSplitter *new_splitter = new QSplitter(Qt::Horizontal, parent_widget);
    TileWidget *new_widget = new TileWidget(new_splitter);
    new_widget->init(this->tile_view_dispatcher);

    QWidget *splitter_container = new QWidget();
    QVBoxLayout *container_layout = new QVBoxLayout(splitter_container);
    container_layout->addWidget(new_splitter);
    container_layout->setContentsMargins(0, 0, 0, 0);

    if (QSplitter *parent_splitter = qobject_cast<QSplitter*>(parent_widget))
    {
        int index = parent_splitter->indexOf(this);
        parent_splitter->replaceWidget(index, splitter_container);
    }
    else if (QLayout *layout = parent_widget->layout())
    {
        layout->removeWidget(this);
        layout->addWidget(splitter_container);
    }

    new_splitter->addWidget(this);
    new_splitter->addWidget(new_widget);
}


void TileWidget::onSplitVertical()
{
    QWidget *parent_widget = this->parentWidget();
    if (!parent_widget) return;

    // If top widget is splitter with same orientation, add new widget to splitter
    if (QSplitter *parent_splitter = qobject_cast<QSplitter*>(parent_widget))
    {
        if (parent_splitter->orientation() == Qt::Vertical)
        {
            TileWidget *new_widget = new TileWidget(nullptr);
            new_widget->init(this->tile_view_dispatcher);
            int index = parent_splitter->indexOf(this);
            parent_splitter->insertWidget(index + 1, new_widget);
            return;
        }
    }

    // Otherwise, we need to create new splitter
    QSplitter *new_splitter = new QSplitter(Qt::Vertical, parent_widget);
    TileWidget *new_widget = new TileWidget(new_splitter);
    new_widget->init(this->tile_view_dispatcher);

    QWidget *splitter_container = new QWidget();
    QVBoxLayout *container_layout = new QVBoxLayout(splitter_container);
    container_layout->addWidget(new_splitter);
    container_layout->setContentsMargins(0, 0, 0, 0);

    if (QSplitter *parent_splitter = qobject_cast<QSplitter*>(parent_widget))
    {
        int index = parent_splitter->indexOf(this);
        parent_splitter->replaceWidget(index, splitter_container);
    }
    else if (QLayout *layout = parent_widget->layout())
    {
        layout->removeWidget(this);
        layout->addWidget(splitter_container);
    }

    new_splitter->addWidget(this);
    new_splitter->addWidget(new_widget);
}


void TileWidget::onClosePanel()
{
    QWidget *parent_widget = this->parentWidget();
    if (!parent_widget) return;

    if (QSplitter *parent_splitter = qobject_cast<QSplitter*>(parent_widget))
    {
        if (parent_splitter->count() > 2)
        {
            this->setParent(nullptr);
            this->deleteLater();
            return;
        }

        if (parent_splitter->count() == 2)
        {
            int index = parent_splitter->indexOf(this);
            int other_index = 1 - index;
            QWidget *other_widget = parent_splitter->widget(other_index);
            other_widget->setParent(nullptr);

            QWidget *splitter_container = this->parentWidget()->parentWidget();
            QWidget *parent_for_splitter_container = splitter_container->parentWidget();
            if (parent_for_splitter_container != nullptr)
            {
                if (QSplitter *splitter_to_insert = qobject_cast<QSplitter*>(parent_for_splitter_container))
                {
                    int index = splitter_to_insert->indexOf(splitter_container);
                    splitter_to_insert->replaceWidget(index, other_widget);
                    splitter_container->deleteLater();
                }
                else if (QLayout *layout = parent_for_splitter_container->layout())
                {
                    layout->removeWidget(splitter_container);
                    layout->addWidget(other_widget);
                    splitter_container->deleteLater();
                }
            }
        }
    }
}


void TileWidget::onTileViewTypeIndexChanged(int index)
{
    emit tileWidgetAwaitTileView(this->getId(), this->ui->tile_type_combo_box->itemData(index).toInt());
}


void TileWidget::onTileViewCreated(ID tile_widget_id, AbstractTileView* tile_view)
{
    // Check tile_widget_id
    if (tile_widget_id != this->getId())
        return;

    if (! this->ui->content_widget)
        return;

    QLayout *layout = this->ui->content_widget->layout();
    if (!layout)
        return;

    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget *widget = item->widget()) {
            widget->setParent(nullptr);
            widget->deleteLater();
        }
    }

    // Setup tile_view
    layout->addWidget(tile_view);
}
