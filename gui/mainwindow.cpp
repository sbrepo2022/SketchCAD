#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tile_widget/tile_widget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tile_view_dispatcher(new TileViewDispatcher),
    edit_mode_dispatcher(new EditModeDispatcher),
    schemes_dispatcher(new SchemesDispatcher)
{
    this->ui->setupUi(this);

    this->ui->central_tile_widget->init(this->tile_view_dispatcher);

    this->initEditModeSwitchActions();

    this->initSchemesTabBar();

    this->connectActions();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connectActions()
{
    connect(this->ui->actionCreate, &QAction::triggered, this, &MainWindow::onCreateScheme);
    connect(this->schemes_dispatcher.get(), &SchemesDispatcher::currentSchemeChanged, this, &MainWindow::onCurrentSchemeChanged);
    connect(this->tile_view_dispatcher.get(), &TileViewDispatcher::tileViewCreated, this, &MainWindow::onTileViewCreated);

    // Direct dispatchers connections
    connect(this->schemes_dispatcher.get(), &SchemesDispatcher::schemeEventOccured, this->edit_mode_dispatcher.get(), &EditModeDispatcher::onSchemeEventOccured);
}


void MainWindow::initEditModeSwitchActions()
{
    this->edit_modes_toolbar = new QToolBar(tr("Edit modes toolbar"), this);
    this->edit_modes_toolbar->setIconSize(QSize(30, 30));

    this->edit_modes_action_group = new QActionGroup(this);
    this->edit_modes_action_group->setExclusive(true);

    std::unordered_map<ID, std::shared_ptr<EditModeInfo>> edit_modes_info = this->edit_mode_dispatcher->getLoadedEditModesInfo();
    std::unordered_map<ID, std::shared_ptr<SketchCADPluginInfo>> edit_modes_plugins_info = this->edit_mode_dispatcher->getLoadedEditModesPluginsInfo();

    bool first = true;
    for (auto& edit_mode_info : edit_modes_info)
    {
        QAction *action = this->edit_modes_toolbar->addAction(edit_mode_info.second->getIcon(), edit_mode_info.second->getTitle());
        this->edit_modes_action_group->addAction(action);
        action->setCheckable(true);
        action->setData(edit_mode_info.first);
        action->setWhatsThis(edit_modes_plugins_info[edit_mode_info.first]->getDescription());
        action->setToolTip(edit_mode_info.second->getTitle());
        action->setStatusTip(edit_mode_info.second->getDescription());

        if (first)
        {
            action->setChecked(true);
            first = false;
        }
    }

    this->addToolBar(this->edit_modes_toolbar);
}


void MainWindow::initSchemesTabBar()
{
    this->schemes_tabs = new QTabBar();
    this->schemes_tabs->setExpanding(false);
    this->schemes_tabs->setTabsClosable(true);

    this->ui->centralwidget->layout()->addWidget(this->schemes_tabs);
}


void MainWindow::onTileViewCreated(ID tile_widget_id, AbstractTileView* tile_view)
{
    auto edit_mode = edit_mode_dispatcher->getEditMode(edit_mode_dispatcher->getCurrentEditModeID());
    tile_view->onCurrentEditModeChanged(edit_mode);

    auto scheme_model = schemes_dispatcher->getScheme(schemes_dispatcher->getCurrentSchemeID());
    tile_view->onCurrentSchemeChanged(scheme_model);

    // TODO: Доделать для tile_view->onObjectSelected()

    Q_UNUSED(tile_widget_id);
}


void MainWindow::onCreateScheme()
{
    int tabs_count_before_add = this->schemes_tabs->count();

    ID scheme_id = this->schemes_dispatcher->createScheme();
    std::shared_ptr<SchemeModel> scheme_model = this->schemes_dispatcher->getScheme(scheme_id);
    int tab_index = this->schemes_tabs->addTab(scheme_model->getSchemeName());
    this->schemes_tabs->setTabData(tab_index, QVariant(scheme_id));

    if (tabs_count_before_add == 0)
    {
        connect(this->schemes_tabs, &QTabBar::currentChanged, this, &MainWindow::onSchemeTabIndexChanged);
        connect(this->schemes_tabs, &QTabBar::tabCloseRequested, this, &MainWindow::onSchemeTabClodeRequested);
        this->onSchemeTabIndexChanged(tab_index);
    }
}


void MainWindow::onCurrentSchemeChanged(const std::shared_ptr<SchemeModel> &scheme)
{
    emit this->tile_view_dispatcher->currentSchemeChanged(scheme);
}


void MainWindow::onSchemeTabIndexChanged(int tab_index)
{
    ID scheme_id = this->schemes_tabs->tabData(tab_index).toUInt();
    this->schemes_dispatcher->setCurrentSchemeID(scheme_id);
}


void MainWindow::onSchemeTabClodeRequested(int tab_index)
{
    ID scheme_id = this->schemes_tabs->tabData(tab_index).toUInt();
    this->schemes_tabs->removeTab(tab_index);
    this->schemes_dispatcher->removeScheme(scheme_id);

    int tabs_count_after_remove = this->schemes_tabs->count();
    if (tabs_count_after_remove == 0)
    {
        disconnect(this->schemes_tabs, &QTabBar::currentChanged, this, &MainWindow::onSchemeTabIndexChanged);
        disconnect(this->schemes_tabs, &QTabBar::tabCloseRequested, this, &MainWindow::onSchemeTabClodeRequested);
    }
}
