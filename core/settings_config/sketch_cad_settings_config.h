#ifndef SKETCHCADSETTINGSCONFIG_H
#define SKETCHCADSETTINGSCONFIG_H

#include "core_global.h"

#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

#include <unordered_map>
#include <optional>

class CORE_EXPORT SketchCADSettingsConfig
{
// Singletone specific realization
private:
    // Private constructor and destructor
    SketchCADSettingsConfig();
    ~SketchCADSettingsConfig() {}

    // Forbiden copy and assigning
    SketchCADSettingsConfig(const SketchCADSettingsConfig&) = delete;
    SketchCADSettingsConfig& operator=(const SketchCADSettingsConfig&) = delete;

    static SketchCADSettingsConfig* instance;

public:
    // Static method for singletone instance getting
    static SketchCADSettingsConfig* getInstance() {
        if (instance == nullptr) {
            instance = new SketchCADSettingsConfig();
        }
        return instance;
    }

// Functional data and methods
private:
    QJsonObject app_settings_default;
    QJsonObject app_settings_overrided;

    std::optional<QJsonValue> getNestedValueHelper(const QJsonValue& current, const QString& key) {
        if (current.isObject()) {
            QJsonObject obj = current.toObject();
            if (obj.contains(key)) {
                return obj.value(key);
            }
        }
        return std::nullopt;
    }

    std::optional<QJsonValue> getNestedValueHelper(const QJsonValue& current, int index) {
        if (current.isArray()) {
            QJsonArray arr = current.toArray();
            if (index >= 0 && index < arr.size()) {
                return arr.at(index);
            }
        }
        return std::nullopt;
    }

    template<typename T, typename... Args>
    std::optional<QJsonValue> getNestedValueHelper(const QJsonValue& current, T first, Args... args) {
        if (auto next = getNestedValueHelper(current, first); next.has_value()) {
            return getNestedValueHelper(next.value(), args...);
        }
        return std::nullopt;
    }


public:
    static QDir getConfigDirectory();
    void readSettingsOverrided();
    void setupAppSettingsDefault();
    void setupPluginsSettingsDefault();
    void writeSettingsDefault();

    template<typename T, typename... Args>
    std::optional<QJsonValue> getNestedValue(T first, Args... args) {
        if (auto res = getNestedValueHelper(this->app_settings_overrided, first, args...))
        {
            return res;
        }
        return getNestedValueHelper(this->app_settings_default, first, args...);
    }
};

#endif // SKETCHCADSETTINGSCONFIG_H
