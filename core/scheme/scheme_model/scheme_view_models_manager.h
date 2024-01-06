#ifndef SCHEMEVIEWMODELSMANAGER_H
#define SCHEMEVIEWMODELSMANAGER_H

#include "core_global.h"
#include "scheme/scheme_model/abstract_scheme_view_model.h"
#include "scheme/scheme_event/scheme_event.h"
#include "scheme/scheme_action_command/abstract_scheme_action_command.h"
#include "primitive/primitive_model/abstract_primitive.h"

#include <QObject>

#include <memory>
#include <unordered_map>
#include <vector>

class CORE_EXPORT SchemeViewModelsManager : public QObject
{
    Q_OBJECT

private:
    std::unordered_map<QString, std::unique_ptr<AbstractSchemeViewModel>> scheme_views_models;

public:
    SchemeViewModelsManager();

    template<class T>
    std::vector<T*> getSchemeViewModelsByType() const
    {
        std::vector<T*> result;
        for (auto it = this->scheme_views_models.begin(); it != this->scheme_views_models.end(); ++it)
        {
            T* ptr = dynamic_cast<T*>(it->second.get());
            if (ptr != nullptr)
            {
                result.push_back(ptr);
            }
        }

        return result;
    }

    AbstractSchemeViewModel* getSchemeViewModelByName(const QString &full_name) const;

public slots:
    void attachPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive);
    void detachPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive);

signals:
    void schemeEventOccured(const std::shared_ptr<SchemeEvent> &scheme_event);
    void doAction(const std::shared_ptr<AbstractSchemeActionCommand> &command);
};

#endif // SCHEMEVIEWMODELSMANAGER_H
