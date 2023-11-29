#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tile_view/tile_view_dispatcher.h"
#include "edit_mode/edit_mode_dispatcher.h"

#include <QMainWindow>
#include <QFile>
#include <QActionGroup>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QToolBar *edit_modes_toolbar;
    QActionGroup *edit_modes_action_group;


    std::shared_ptr<TileViewDispatcher> tile_view_dispatcher;
    std::shared_ptr<EditModeDispatcher> edit_mode_dispatcher;

    void initEditModeSwitchActions();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
