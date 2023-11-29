#include "scheme_tile_view.h"
#include "ui_scheme_tile_view.h"


SchemeTileView::SchemeTileView(QWidget *parent) :
    AbstractTileView(parent),
    ui(new Ui::SchemeTileView)
{
    ui->setupUi(this);
}
