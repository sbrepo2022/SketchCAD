#include "scene_scheme_tile_view.h"
#include "scene_scheme_view_model_lib.h"
#include "ui_scene_scheme_tile_view.h"


SceneSchemeTileView::SceneSchemeTileView(QWidget *parent) :
    AbstractTileView(parent),
    ui(new Ui::SceneSchemeTileView)
{
    ui->setupUi(this);
    ui->graphics_view->setMouseTracking(true);
}


void SceneSchemeTileView::onCurrentSchemeChanged(const std::shared_ptr<SchemeModel> &scheme)
{
    if (scheme == nullptr)
    {
        this->ui->graphics_view->setScene(nullptr);
        return;
    }

    auto scheme_graphics_scenes = scheme->getSchemeViewModelsManager()->getSchemeViewModelsByType<SceneSchemeViewModel>();

    if (scheme_graphics_scenes.size() > 0)
    {
        this->ui->graphics_view->setScene(scheme_graphics_scenes[0]->getScene());
    }
}


AbstractTileView* SceneSchemeTileViewFabric::createTileView()
{
    AbstractTileView* tile_view = new SceneSchemeTileView();
    this->makeConnections(tile_view);
    return tile_view;
}
