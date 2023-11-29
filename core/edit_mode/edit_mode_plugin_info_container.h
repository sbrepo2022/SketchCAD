#ifndef EDITMODEPLUGININFOCONTAINER_H
#define EDITMODEPLUGININFOCONTAINER_H

#include "core_global.h"
#include "edit_mode/edit_mode_info.h"


class CORE_EXPORT EditModePluginInfoContainer
{
public:
    EditModePluginInfoContainer() = default;

    virtual std::shared_ptr<EditModeInfo> getEditModeInfo() const = 0;
};

#endif // EDITMODEPLUGININFOCONTAINER_H
