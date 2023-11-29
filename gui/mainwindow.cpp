#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tile_widget/tile_widget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tile_view_dispatcher(new TileViewDispatcher),
    edit_mode_dispatcher(new EditModeDispatcher)
{
    this->ui->setupUi(this);

    this->ui->central_tile_widget->init(this->tile_view_dispatcher);

    this->initEditModeSwitchActions();
}


MainWindow::~MainWindow()
{
    delete ui;
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
