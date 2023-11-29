#ifndef SCHEMESDISPATCHER_H
#define SCHEMESDISPATCHER_H

#include "core_global.h"
#include "scheme/scheme_model/scheme_model.h"
#include "scheme/scheme_serializer/abstract_scheme_serializer.h"

#include <QObject>

#include <memory>
#include <unordered_map>


class CORE_EXPORT SchemesDispatcher : public QObject
{
    Q_OBJECT

private:
    std::unordered_map<ID, std::shared_ptr<SchemeModel>> schemes;
    ID current_scheme_id;

public:
    SchemesDispatcher();

    ID createScheme();
    void removeScheme(ID id);
    std::shared_ptr<SchemeModel> getScheme(ID id);

    ID getCurrentSchemeID();
    void setCurrentSchemeID(ID id);

    void loadSchemeFromStream(std::istream &in, AbstractSchemeSerializer &scheme_serializer, ID id = 0);
    void saveSchemeToStream(std::ostream &out, AbstractSchemeSerializer &scheme_serializer, ID id = 0);

public slots:
    // From EditModesDispatcher
    void onDoAction(const std::shared_ptr<AbstractSchemeActionCommand> &command);
    void onUndoLastAction();
    void onRedoLastAction();

    // From SchemeModel, resend signals only if they are from current scheme model
    void onSchemeEventOccured(const SchemeEvent &scheme_event, const SchemeModel &scheme_model);
    void onRecalculateConstraints(const SchemeModel &scheme_model);

signals:
    void currentSchemeChanged(const std::shared_ptr<SchemeModel> &scheme);
    void schemeEventOccured(const SchemeEvent &scheme_event, const SchemeModel &scheme_model);
    void recalculateConstraints(const SchemeModel &scheme_model);
};

#endif // SCHEMESDISPATCHER_H
