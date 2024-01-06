#ifndef SCENESCHEMEVIEWMODEL_H
#define SCENESCHEMEVIEWMODEL_H

#include "scene_scheme_view_module_lib_global.h"

#include "scheme/scheme_model/abstract_scheme_view_model.h"
#include "abstract_primitive_scene_view_item.h"
#include "scheme_graphics_scene.h"

#include <QGraphicsScene>
#include <QPointer>

#include <memory>


class SCENE_SCHEME_VIEW_MODULE_LIB_EXPORT SceneSchemeViewModelPluginInfo : public SketchCADPluginInfo
{
    virtual int getVersion() const override { return 1; }
    virtual QString getNamespace() const override { return "scad_default"; }
    virtual QString getName() const override { return "SceneSchemeViewModelPlugin"; }

    virtual std::optional<QJsonObject> getDefaultSettings() const override
    {
        return std::nullopt;
    }

    // Descriptional information
    virtual QString getAuthor() const override { return "Sergey Borisov"; }
    virtual QString getAuthorEmail() const override { return "borisov123.sergey@yandex.ru"; }
    virtual QString getTitle() const override { return "Scene scheme view model"; }
    virtual QString getDescription() const override { return "Every scheme has its own scene view model with primitive graphics items."; }
};

class SCENE_SCHEME_VIEW_MODULE_LIB_EXPORT SceneSchemeViewModel : public AbstractSchemeViewModel
{
    Q_OBJECT

private:
    QPointer<SchemeGraphicsScene> scene;
    std::list<AbstractPrimitiveSceneViewItem*> scene_primitive_view_items;

public:
    SceneSchemeViewModel();
    ~SceneSchemeViewModel();
    QGraphicsScene* getScene() const;
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<SceneSchemeViewModelPluginInfo>(); }

public slots:
    virtual void attachPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive) override;
    virtual void detachPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive) override;

    void onSchemeEventOccured(const std::shared_ptr<SchemeEvent> &scheme_event, QGraphicsItem *graphics_item);
};
#endif // SCENESCHEMEVIEWMODEL_H
