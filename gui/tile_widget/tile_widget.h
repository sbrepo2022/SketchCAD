#ifndef TILE_WIDGET_H
#define TILE_WIDGET_H

#include <QWidget>

namespace Ui {
class TileWidget;
}

class TileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TileWidget(QWidget *parent = nullptr);
    ~TileWidget();

private:
    Ui::TileWidget *ui;

public slots:
    void splitHorizontal();
    void splitVertical();
    void closePanel();
};

#endif // TILE_WIDGET_H
