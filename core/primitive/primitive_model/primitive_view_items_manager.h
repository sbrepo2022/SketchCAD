#ifndef PRIMITIVEVIEWITEMSMANAGER_H
#define PRIMITIVEVIEWITEMSMANAGER_H

#include "core_global.h"
#include "primitive/primitive_model/abstract_primitive_view_item.h"

#include <memory>
#include <vector>

class CORE_EXPORT PrimitiveViewItemsManager
{
private:
    std::vector<std::unique_ptr<AbstractPrimitiveViewItem>> primitive_view_items;

public:
    PrimitiveViewItemsManager();

    void addPrimitiveViewItem(std::unique_ptr<AbstractPrimitiveViewItem> &&primitive_view_item);

    void updatePrimitiveViewItems();

    template<class T>
    std::vector<T*> getPrimitiveViewItemsByType() const
    {
        std::vector<T*> result;
        for (size_t i = 0; i < this->primitive_view_items.size(); i++)
        {
            T* ptr = dynamic_cast<T*>(this->primitive_view_items[i].get());
            if (ptr != nullptr)
            {
                result.push_back();
            }
        }

        return result;
    }

    std::vector<AbstractPrimitiveViewItem*> getPrimitiveViewItemsByName(const QString &full_name) const;
};

#endif // PRIMITIVEVIEWITEMSMANAGER_H
