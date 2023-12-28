#ifndef SCENE_SCHEME_TILE_VIEW_H
#define SCENE_SCHEME_TILE_VIEW_H

#include "scene_scheme_tile_view_global.h"
#include "plugin_system/plugins_types/tile_view_plugin.h"
#include "tile_view/abstract_tile_view_fabric.h"

#include <memory>


class SCENE_SCHEME_TILE_VIEW_EXPORT SceneSchemeTileViewInfo : public TileViewInfo
{
    virtual QString getTitle() { return "Scheme"; }
    virtual QString getDescription() { return "Scheme editing"; }
    virtual QIcon getIcon() { return QIcon(":/resources/scheme.png"); }
};




class SCENE_SCHEME_TILE_VIEW_EXPORT SceneSchemeTileViewPluginInfo : public SketchCADPluginInfo
{
    virtual int getVersion() const override { return 1; }
    virtual QString getNamespace() const override { return "scad_default"; }
    virtual QString getName() const override { return "SceneSchemeTileViewPlugin"; }

    virtual std::optional<QJsonObject> getDefaultSettings() const override
    {
        return std::nullopt;
    }

    // Descriptional information
    virtual QString getAuthor() const override { return "Sergey Borisov"; }
    virtual QString getAuthorEmail() const override { return "borisov123.sergey@yandex.ru"; }
    virtual QString getTitle() const override { return "Scene scheme tile view"; }
    virtual QString getDescription() const override { return "Main view for scene scheme observation and editing."; }
};




QT_BEGIN_NAMESPACE
namespace Ui { class SceneSchemeTileView; }
QT_END_NAMESPACE

class SCENE_SCHEME_TILE_VIEW_EXPORT SceneSchemeTileView : public AbstractTileView
{
    Q_OBJECT

private:
    Ui::SceneSchemeTileView *ui;

public:
    explicit SceneSchemeTileView(QWidget *parent = nullptr);

};




class SCENE_SCHEME_TILE_VIEW_EXPORT SceneSchemeTileViewFabric : public AbstractTileViewFabric
{
    Q_OBJECT

public:
    virtual AbstractTileView* createTileView() override { return new SceneSchemeTileView; }

    virtual std::shared_ptr<TileViewInfo> getTileViewInfo() const override { return std::make_shared<SceneSchemeTileViewInfo>(); }
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<SceneSchemeTileViewPluginInfo>(); }
};




class SCENE_SCHEME_TILE_VIEW_EXPORT SceneSchemeTileViewPlugin : public QObject, public TileViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "scad_basic::AbstractSketchCADPlugin/1.0")
    Q_INTERFACES(AbstractSketchCADPlugin)

public:
    virtual AbstractTileViewFabric* getTileViewFabric() const override { return new SceneSchemeTileViewFabric(); }
    virtual std::shared_ptr<TileViewInfo> getTileViewInfo() const override { return std::make_shared<SceneSchemeTileViewInfo>(); }
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<SceneSchemeTileViewPluginInfo>(); }

};

#endif // SCENE_SCHEME_TILE_VIEW_H
