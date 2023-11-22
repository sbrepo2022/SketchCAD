#ifndef ABSTRACTSCHEMEACTIONCOMMAND_H
#define ABSTRACTSCHEMEACTIONCOMMAND_H

#include "core_global.h"


class SchemeModel;

class CORE_EXPORT AbstractSchemeActionCommand
{
private:
    bool sequence_with_previous;

public:
    AbstractSchemeActionCommand();
    AbstractSchemeActionCommand(bool sequence_with_previous);
    virtual ~AbstractSchemeActionCommand();

    bool isSequenceWithPrevious() const { return sequence_with_previous; }

    virtual void doAction(const SchemeModel &scheme_model) = 0;
    virtual void undoAction(const SchemeModel &scheme_model) = 0;
    virtual void redoAction(const SchemeModel &scheme_model) = 0;
};

#endif // ABSTRACTSCHEMEACTIONCOMMAND_H
