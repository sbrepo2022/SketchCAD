#ifndef SCHEMETILEVIEW_H
#define SCHEMETILEVIEW_H

#include "scheme_tile_view_global.h"
#include "plugin_system/plugins_types/tile_view_plugin.h"
#include "tile_view/abstract_tile_view_fabric.h"

#include <memory>


class SCHEMETILEVIEW_EXPORT SchemeTileViewInfo : public TileViewInfo
{
    virtual QString getTitle() { return "Scheme"; }
    virtual QString getDescription() { return "Scheme editing"; }
    virtual QIcon getIcon() { return QIcon(":/resources/scheme.png"); }
};




class SCHEMETILEVIEW_EXPORT SchemeTileViewPluginInfo : public SketchCADPluginInfo
{
    virtual int getVersion() const override { return 1; }
    virtual QString getNamespace() const override { return "scad_default"; }
    virtual QString getName() const override { return "SchemeTileViewPlugin"; }

    virtual std::optional<QJsonObject> getDefaultSettings() const override
    {
        return std::nullopt;
    }

    // Descriptional information
    virtual QString getAuthor() const override { return "Sergey Borisov"; }
    virtual QString getAuthorEmail() const override { return "borisov123.sergey@yandex.ru"; }
    virtual QString getTitle() const override { return "Scheme tile view"; }
    virtual QString getDescription() const override { return "Main view for scheme observation and editing."; }
};




QT_BEGIN_NAMESPACE
namespace Ui { class SchemeTileView; }
QT_END_NAMESPACE

class SCHEMETILEVIEW_EXPORT SchemeTileView : public AbstractTileView
{
    Q_OBJECT

private:
    Ui::SchemeTileView *ui;

public:
    explicit SchemeTileView(QWidget *parent = nullptr);

};




class SCHEMETILEVIEW_EXPORT SchemeTileViewFabric : public AbstractTileViewFabric
{
    Q_OBJECT

public:
    virtual AbstractTileView* createTileView() override { return new SchemeTileView; }

    virtual std::shared_ptr<TileViewInfo> getTileViewInfo() const override { return std::make_shared<SchemeTileViewInfo>(); }
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<SchemeTileViewPluginInfo>(); }
};




class SCHEMETILEVIEW_EXPORT SchemeTileViewPlugin : public QObject, public TileViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "scad_basic::AbstractSketchCADPlugin/1.0")
    Q_INTERFACES(AbstractSketchCADPlugin)

public:
    virtual AbstractTileViewFabric* getTileViewFabric() const override { return new SchemeTileViewFabric(); }
    virtual std::shared_ptr<TileViewInfo> getTileViewInfo() const override { return std::make_shared<SchemeTileViewInfo>(); }
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<SchemeTileViewPluginInfo>(); }

};

#endif // SCHEMETILEVIEW_H
