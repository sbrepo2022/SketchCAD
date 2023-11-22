#ifndef SELECTABLEMODELCOMPONENTSKEEPER_H
#define SELECTABLEMODELCOMPONENTSKEEPER_H

#include "core_global.h"
#include "primitive/selectable_model_component/selectable_model_component.h"
#include "scheme/scheme_action_command/abstract_scheme_action_command.h"

#include <QObject>
#include <memory>
#include <vector>

class CORE_EXPORT SelectableModelComponentsKeeper : public QObject
{
    Q_OBJECT

private:
    std::unordered_map<QString, std::unique_ptr<SelectableModelComponent>> selectable_model_components;

public:
    explicit SelectableModelComponentsKeeper(QObject *parent = nullptr);
    ~SelectableModelComponentsKeeper();

    void addComponent(std::unique_ptr<SelectableModelComponent> &&component);

    template<class T>
    std::vector<T*> getComponentsByType() const
    {
        std::vector<T*> result;
        for (auto it = this->selectable_model_components.begin(); it != this->selectable_model_components.end(); ++it)
        {
            T* ptr = dynamic_cast<T*>(it->second.get());
            if (ptr != nullptr)
            {
                result.push_back(ptr);
            }
        }
        return result;
    }

    SelectableModelComponent* getComponentByName(const QString &full_name) const;

signals:
    void doAction(const std::shared_ptr<AbstractSchemeActionCommand> &command);
};

#endif // SELECTABLEMODELCOMPONENTSKEEPER_H
