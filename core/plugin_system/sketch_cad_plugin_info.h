#ifndef SKETCHCADPLUGININFO_H
#define SKETCHCADPLUGININFO_H

#include "core_global.h"

#include <QtPlugin>
#include <QString>

class CORE_EXPORT SketchCADPluginInfo
{
public:
    virtual ~SketchCADPluginInfo() = default;

    // Functional information
    virtual int getVersion() const = 0;
    virtual QString getNamespace() const = 0;
    virtual QString getName() const = 0;
    QString getFullName() const { return this->getNamespace() + "::" + this->getName(); }

    // Descriptional information
    virtual QString getAuthor() const = 0;
    virtual QString getAuthorEmail() const = 0;
    virtual QString getTitle() const = 0;
    virtual QString getDescription() const = 0; /* getDescription() may return HTML text */
};

#endif // SKETCHCADPLUGININFO_H
