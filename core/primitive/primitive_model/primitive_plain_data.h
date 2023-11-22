#ifndef PRIMITIVEPLAINDATA_H
#define PRIMITIVEPLAINDATA_H


#include "core_global.h"
#include "helpers/id_counter.h"

#include <QString>
#include <QVariant>
#include <string>
#include <unordered_map>
#include <vector>

class CORE_EXPORT PrimitivePlainData
{
public:
    PrimitivePlainData();

    QString primitive_type_name;
    ID primitive_id;

    std::unordered_map<QString, QVariant> primitive_properties;
};

#endif // PRIMITIVEPLAINDATA_H
