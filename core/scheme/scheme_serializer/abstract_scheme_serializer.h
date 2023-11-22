#ifndef ABSTRACTSCHEMESERIALIZER_H
#define ABSTRACTSCHEMESERIALIZER_H

#include "core_global.h"
#include "scheme/scheme_model/scheme_model.h"
#include "primitive/primitive_model/primitive_plain_data.h"

#include <istream>

class CORE_EXPORT AbstractSchemeSerializer
{
public:
    void loadSchemeFromStream(std::istream &in, SchemeModel &scheme_model);
    void saveSchemeToStream(std::ostream &out, const SchemeModel &scheme_model);

protected:
    virtual std::vector<PrimitivePlainData> loadPlainDataFromStream(std::istream &in) = 0;
    virtual void savePlainDataToStream(std::ostream &out, const std::vector<PrimitivePlainData> &plain_data_objects) = 0;
};

#endif // ABSTRACTSCHEMESERIALIZER_H
