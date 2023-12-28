#include "scene_scheme_tile_view.h"
#include "ui_scene_scheme_tile_view.h"


SceneSchemeTileView::SceneSchemeTileView(QWidget *parent) :
    AbstractTileView(parent),
    ui(new Ui::SceneSchemeTileView)
{
    ui->setupUi(this);
}
