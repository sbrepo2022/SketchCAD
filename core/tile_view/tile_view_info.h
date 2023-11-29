#ifndef TILEVIEWINFO_H
#define TILEVIEWINFO_H

#include "core_global.h"

#include <QIcon>
#include <QString>

class CORE_EXPORT TileViewInfo
{
public:
    virtual ~TileViewInfo() = default;

    virtual QString getTitle() = 0;
    virtual QString getDescription() = 0;
    virtual QIcon getIcon() = 0;
};

#endif // TILEVIEWINFO_H
