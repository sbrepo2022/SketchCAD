#include "primitive_view_items_manager.h"

PrimitiveViewItemsManager::PrimitiveViewItemsManager()
{

}

void PrimitiveViewItemsManager::addPrimitiveViewItem(std::unique_ptr<AbstractPrimitiveViewItem> &&primitive_view_item)
{
    this->primitive_view_items.emplace_back(std::move(primitive_view_item));
}


void PrimitiveViewItemsManager::updatePrimitiveViewItems()
{
    for (auto& view_item : this->primitive_view_items)
    {
        view_item->onLinkedPrimitiveUpdated();
    }
}


std::vector<AbstractPrimitiveViewItem*> PrimitiveViewItemsManager::getPrimitiveViewItemsByName(const QString &full_name) const
{
    std::vector<AbstractPrimitiveViewItem*> result;
    for (size_t i = 0; i < this->primitive_view_items.size(); i++)
    {
        AbstractPrimitiveViewItem* ptr = this->primitive_view_items[i].get();
        if (ptr->getPluginInfo()->getFullName() == full_name)
        {
            result.push_back(ptr);
        }
    }

    return result;
}
