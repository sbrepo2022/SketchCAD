#ifndef SCHEMETRANSACTION_H
#define SCHEMETRANSACTION_H

#include "scheme_transaction_interface.h"

#include <memory>
#include <vector>

class CORE_EXPORT SchemeTransaction : public SchemeTransactionInterface
{
private:
    SchemeTransactionInterface *apply_to;

    std::vector<std::shared_ptr<AbstractPrimitive>> primitives_to_add;
    std::vector<std::shared_ptr<AbstractConstraint>> constraints_to_add;
    std::vector<ID> primitives_to_remove;
    std::vector<ID> primitives_to_update;

public:
    static SchemeTransaction empty() { return SchemeTransaction(nullptr); }

    SchemeTransaction(SchemeTransactionInterface *apply_to);

    void addPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive) override;
    void addConstraint(const std::shared_ptr<AbstractConstraint> &constraint) override;
    void removePrimitive(ID id) override;
    void updatePrimitives(ID id) override;

    bool applyTransaction() override;

    std::vector<std::shared_ptr<AbstractPrimitive>> getPrimitivesToAdd() { return this->primitives_to_add; }
    std::vector<std::shared_ptr<AbstractConstraint>> getConstraintsToAdd() { return this->constraints_to_add; }
    std::vector<ID> getPrimitivesToRemoveIDs() { return this->primitives_to_remove; }
    std::vector<ID> getPrimitivesToUpdateIDs() { return this->primitives_to_update; }
};

#endif // SCHEMETRANSACTION_H

/*
    Преимущества транзакций:
    1) Позволяют начать пересчет constraints один раз в момент применения транзакции
    2) Есть возможность отката транзакции в случае неудачной инициализации
    3) Позволяет временно хранить примитивы в процессе инициализации из списка id
*/
