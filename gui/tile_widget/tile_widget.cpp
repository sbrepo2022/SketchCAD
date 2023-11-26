#include "tile_widget.h"
#include "ui_tile_widget.h"

#include <QDebug>
#include <QSplitter>

TileWidget::TileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TileWidget)
{
    this->ui->setupUi(this);
    connect(this->ui->split_horizontal, &QPushButton::clicked, this, &TileWidget::splitHorizontal);
    connect(this->ui->split_vertical, &QPushButton::clicked, this, &TileWidget::splitVertical);
    connect(this->ui->close_panel, &QPushButton::clicked, this, &TileWidget::closePanel);
}


TileWidget::~TileWidget()
{
    delete ui;
}


void TileWidget::splitHorizontal()
{
    QWidget *parent_widget = this->parentWidget();
    if (!parent_widget) return;

    // If top widget is splitter with same orientation, add new widget to splitter
    if (QSplitter *parent_splitter = qobject_cast<QSplitter*>(parent_widget))
    {
        if (parent_splitter->orientation() == Qt::Horizontal)
        {
            QWidget *new_widget = new TileWidget(nullptr);
            parent_splitter->addWidget(new_widget);
            return;
        }
    }

    // Otherwise, we need to create new splitter
    QSplitter *new_splitter = new QSplitter(Qt::Horizontal, parent_widget);
    QWidget *new_widget = new TileWidget(new_splitter);

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


void TileWidget::splitVertical()
{
    QWidget *parent_widget = this->parentWidget();
    if (!parent_widget) return;

    // If top widget is splitter with same orientation, add new widget to splitter
    if (QSplitter *parent_splitter = qobject_cast<QSplitter*>(parent_widget))
    {
        if (parent_splitter->orientation() == Qt::Vertical)
        {
            QWidget *new_widget = new TileWidget(nullptr);
            parent_splitter->addWidget(new_widget);
            return;
        }
    }

    // Otherwise, we need to create new splitter
    QSplitter *new_splitter = new QSplitter(Qt::Vertical, parent_widget);
    QWidget *new_widget = new TileWidget(new_splitter);

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


void TileWidget::closePanel()
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
