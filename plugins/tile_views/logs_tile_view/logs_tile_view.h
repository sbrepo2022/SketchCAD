#ifndef LOGSTILEVIEW_H
#define LOGSTILEVIEW_H

#include "logs_tile_view_global.h"
#include "plugin_system/plugins_types/tile_view_plugin.h"
#include "tile_view/abstract_tile_view_fabric.h"
#include "logs_keeper/sketch_cad_logs_keeper.h"

#include <memory>


class LOGS_TILE_VIEW_EXPORT LogsTileViewInfo : public TileViewInfo
{
    virtual QString getTitle() { return "Logs"; }
    virtual QString getDescription() { return "Logs output"; }
    virtual QIcon getIcon() { return QIcon(":/resources/log.png"); }
};




class LOGS_TILE_VIEW_EXPORT LogsTileViewPluginInfo : public SketchCADPluginInfo
{
    virtual int getVersion() const override { return 1; }
    virtual QString getNamespace() const override { return "scad_default"; }
    virtual QString getName() const override { return "LogsTileViewPlugin"; }

    virtual std::optional<QJsonObject> getDefaultSettings() const override
    {
        return std::nullopt;
    }

    // Descriptional information
    virtual QString getAuthor() const override { return "Sergey Borisov"; }
    virtual QString getAuthorEmail() const override { return "borisov123.sergey@yandex.ru"; }
    virtual QString getTitle() const override { return "Logs tile view"; }
    virtual QString getDescription() const override { return "Tile view for logs output."; }
};




QT_BEGIN_NAMESPACE
namespace Ui { class LogsTileView; }
QT_END_NAMESPACE

class LOGS_TILE_VIEW_EXPORT LogsTileView : public AbstractTileView
{
    Q_OBJECT

private:
    Ui::LogsTileView *ui;

public:
    explicit LogsTileView(QWidget *parent = nullptr);

public slots:
    void onNewLogMessage(const LogMessage &log_message);
};




class LOGS_TILE_VIEW_EXPORT LogsTileViewFabric : public AbstractTileViewFabric
{
    Q_OBJECT

public:
    virtual AbstractTileView* createTileView() override { return new LogsTileView; }

    virtual std::shared_ptr<TileViewInfo> getTileViewInfo() const override { return std::make_shared<LogsTileViewInfo>(); }
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<LogsTileViewPluginInfo>(); }
};




class LOGS_TILE_VIEW_EXPORT LogsTileViewPlugin : public QObject, public TileViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "scad_basic::AbstractSketchCADPlugin/1.0")
    Q_INTERFACES(AbstractSketchCADPlugin)

public:
    virtual AbstractTileViewFabric* getTileViewFabric() const override { return new LogsTileViewFabric(); }
    virtual std::shared_ptr<TileViewInfo> getTileViewInfo() const override { return std::make_shared<LogsTileViewInfo>(); }
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<LogsTileViewPluginInfo>(); }

};

#endif // LOGSTILEVIEW_H
