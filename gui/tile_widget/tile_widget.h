#ifndef TILE_WIDGET_H
#define TILE_WIDGET_H

#include "helpers/id_counter.h"
#include "tile_view/tile_view_dispatcher.h"

#include <QWidget>
#include <QResizeEvent>

namespace Ui {
class TileWidget;
}

class TileWidget : public QWidget, public IdCounterT<TileWidget>
{
    Q_OBJECT

    std::shared_ptr<TileViewDispatcher> tile_view_dispatcher;


public:
    explicit TileWidget(QWidget *parent = nullptr);
    ~TileWidget();

    void init(const std::shared_ptr<TileViewDispatcher> &tile_view_dispatcher);


private:
    Ui::TileWidget *ui;


protected:
    void resizeEvent(QResizeEvent *event) override;


public slots:
    void onSplitHorizontal();
    void onSplitVertical();
    void onClosePanel();
    void onTileViewTypeIndexChanged(int index);
    void onTileViewCreated(ID tile_widget_id, AbstractTileView* tile_view);

signals:
    void closePanel();
    void tileWidgetAwaitTileView(ID tile_widget_id, ID tile_view_fabric_id);
};

#endif // TILE_WIDGET_H
