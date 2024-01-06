#ifndef SCHEMEMODEL_H
#define SCHEMEMODEL_H

#include "core_global.h"
#include "scheme/scheme_model/scheme_transaction/scheme_transaction.h"
#include "helpers/id_counter.h"
#include "primitive/primitive_model/abstract_primitive.h"
#include "primitive/primitive_model/abstract_constraint.h"
#include "scheme/scheme_action_command/scheme_history.h"
#include "scheme/scheme_model/scheme_view_models_manager.h"

#include <QObject>

#include <memory>
#include <unordered_map>

class CORE_EXPORT SchemeModel : public QObject, public IdCounterT<SchemeModel>, private SchemeTransactionInterface
{
    Q_OBJECT

private:
    QString scheme_name;
    mutable SchemeHistory scheme_history;
    std::unordered_map<ID, std::shared_ptr<AbstractPrimitive>> primitives;
    std::unordered_map<ID, std::shared_ptr<AbstractConstraint>> constraints;
    std::unique_ptr<SchemeViewModelsManager> scheme_view_models_manager;

    void addPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive) override;
    void addConstraint(const std::shared_ptr<AbstractConstraint> &constraint) override;
    void removePrimitive(ID id) override;
    void updatePrimitive(ID id) override;

    bool applyTransaction() override;

    friend class SchemeTransaction;

public:
    explicit SchemeModel();

    QString getSchemeName() { return this->scheme_name; }
    std::unordered_map<ID, std::shared_ptr<const AbstractPrimitive>> getPrimitives() const;
    std::unordered_map<ID, std::shared_ptr<const AbstractConstraint>> getConstraints() const;
    std::vector<ID> getPrimitivesIDs() const;
    std::vector<ID> getConstraintsIDs() const;
    std::shared_ptr<AbstractPrimitive> getPrimitive(ID id) const;
    std::shared_ptr<AbstractConstraint> getConstraint(ID id) const;

    SchemeViewModelsManager* getSchemeViewModelsManager();

    SchemeTransaction createTransaction() const;

public slots:
    void onDoAction(const std::shared_ptr<AbstractSchemeActionCommand> &command) const;
    void onUndoLastAction() const;
    void onRedoLastAction() const;

signals:
    void schemeEventOccured(const std::shared_ptr<SchemeEvent> &scheme_event, const SchemeModel &scheme_model);
    void recalculateConstraints(const SchemeModel &scheme_model);
};

#endif // SCHEMEMODEL_H
