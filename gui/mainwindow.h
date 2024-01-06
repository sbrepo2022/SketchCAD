#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tile_view/tile_view_dispatcher.h"
#include "edit_mode/edit_mode_dispatcher.h"
#include "scheme/scheme_model/schemes_dispatcher.h"

#include <QMainWindow>
#include <QFile>
#include <QActionGroup>
#include <QToolBar>
#include <QTabBar>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* ui;
    QToolBar* edit_modes_toolbar;
    QActionGroup* edit_modes_action_group;
    QTabBar* schemes_tabs;


    std::shared_ptr<TileViewDispatcher> tile_view_dispatcher;
    std::shared_ptr<EditModeDispatcher> edit_mode_dispatcher;
    std::shared_ptr<SchemesDispatcher> schemes_dispatcher;

    void connectActions();
    void initEditModeSwitchActions();
    void initSchemesTabBar();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onTileViewCreated(ID tile_widget_id, AbstractTileView* tile_view);

    void onCreateScheme();
    void onCurrentSchemeChanged(const std::shared_ptr<SchemeModel> &scheme);

    void onSchemeTabIndexChanged(int tab_index);
    void onSchemeTabClodeRequested(int tab_index);
};
#endif // MAINWINDOW_H
