#ifndef EDITMODEINFO_H
#define EDITMODEINFO_H

#include "core_global.h"

#include <QIcon>
#include <QString>

class CORE_EXPORT EditModeInfo
{
public:
    virtual ~EditModeInfo() = default;

    virtual QString getTitle() = 0;
    virtual QString getDescription() = 0;
    virtual QIcon getIcon() = 0;
};

#endif // EDITMODEINFO_H
