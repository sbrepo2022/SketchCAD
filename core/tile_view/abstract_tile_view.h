#ifndef ABSTRACTTILEVIEW_H
#define ABSTRACTTILEVIEW_H

#include "core_global.h"
#include "scheme/scheme_model/scheme_model.h"
#include "edit_mode/abstract_edit_mode.h"
#include "primitive/selectable_model_component/selectable_model_components_keeper.h"

#include <QWidget>

class CORE_EXPORT AbstractTileView : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractTileView(QWidget *parent = nullptr);


public slots:
    virtual void onCurrentSchemeChanged(const std::shared_ptr<SchemeModel> &scheme)
    {
        Q_UNUSED(scheme)
    }

    virtual void onCurrentEditModeChanged(const std::shared_ptr<AbstractEditMode> &edit_mode)
    {
        Q_UNUSED(edit_mode)
    }

    virtual void onObjectSelected(SelectableModelComponentsKeeper *selectable_model_components_keeper)
    {
        Q_UNUSED(selectable_model_components_keeper)
    }
};

#endif // ABSTRACTTILEVIEW_H
