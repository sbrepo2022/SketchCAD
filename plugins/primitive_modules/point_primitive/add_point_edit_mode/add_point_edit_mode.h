#ifndef ADDPOINTEDITMODE_H
#define ADDPOINTEDITMODE_H

#include "add_point_edit_mode_global.h"
#include "plugin_system/plugins_types/edit_mode_plugin.h"
#include "edit_mode/abstract_edit_mode.h"

#include <memory>


class ADDPOINTEDITMODE_EXPORT AddPointEditModeInfo : public EditModeInfo
{
    virtual QString getTitle() { return "Add point"; }
    virtual QString getDescription() { return "Add point tool"; }
    virtual QIcon getIcon() { return QIcon(":/resources/add_point.png"); }
};




class ADDPOINTEDITMODE_EXPORT AddPointEditModePluginInfo : public SketchCADPluginInfo
{
    virtual int getVersion() const override { return 1; }
    virtual QString getNamespace() const override { return "scad_default"; }
    virtual QString getName() const override { return "AddPointEditModePlugin"; }

    virtual std::optional<QJsonObject> getDefaultSettings() const override
    {
        return std::nullopt;
    }

    // Descriptional information
    virtual QString getAuthor() const override { return "Sergey Borisov"; }
    virtual QString getAuthorEmail() const override { return "borisov123.sergey@yandex.ru"; }
    virtual QString getTitle() const override { return "Add point edit mode"; }
    virtual QString getDescription() const override { return "Editing mode, the task of which is to add points to the scheme."; }
};




class ADDPOINTEDITMODE_EXPORT AddPointEditMode : public AbstractEditMode
{
    Q_OBJECT

public:
    virtual void onSchemeEventOccured(const SchemeEvent &scheme_event, const SchemeModel &scheme_model) override;

    virtual std::shared_ptr<EditModeInfo> getEditModeInfo() const override { return std::make_shared<AddPointEditModeInfo>(); }
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<AddPointEditModePluginInfo>(); }
};



class ADDPOINTEDITMODE_EXPORT AddPointEditModePlugin : public QObject, public EditModePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "scad_basic::AbstractSketchCADPlugin/1.0")
    Q_INTERFACES(AbstractSketchCADPlugin)

public:
    virtual AbstractEditMode* getEditMode() override { return new AddPointEditMode; }
    virtual std::shared_ptr<EditModeInfo> getEditModeInfo() const override { return std::make_shared<AddPointEditModeInfo>(); }
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<AddPointEditModePluginInfo>(); }

};

#endif // ADDPOINTEDITMODE_H
