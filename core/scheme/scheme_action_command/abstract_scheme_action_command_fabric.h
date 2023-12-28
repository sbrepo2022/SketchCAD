#ifndef ABSTRACTACTIONCOMMANDFABRIC_H
#define ABSTRACTACTIONCOMMANDFABRIC_H

#include "core_global.h"
#include "scheme/scheme_action_command/abstract_scheme_action_command.h"
#include <memory>
#include <vector>
#include <string>

class CORE_EXPORT AbstractSchemeActionCommandFabric
{
public:
    virtual ~AbstractSchemeActionCommandFabric() = default;
    virtual std::shared_ptr<AbstractSchemeActionCommand> getSchemeActionCommandFabric(const std::vector<std::string> &args) = 0;
    virtual std::vector<std::pair<std::string, std::string>> getArgsDescriptions() = 0;
    virtual std::string getHelpText() = 0;
};

#endif // ABSTRACTACTIONCOMMANDFABRIC_H
