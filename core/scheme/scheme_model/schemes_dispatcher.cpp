#include "schemes_dispatcher.h"

SchemesDispatcher::SchemesDispatcher() :
    QObject{nullptr},
    current_scheme_id(0)
{

}


ID SchemesDispatcher::createScheme()
{
    auto new_scheme = std::make_shared<SchemeModel>();
    ID id = new_scheme->getId();
    this->schemes.insert(std::make_pair(id, new_scheme));

    connect(new_scheme.get(), &SchemeModel::schemeEventOccured, this, &SchemesDispatcher::onSchemeEventOccured);
    connect(new_scheme.get(), &SchemeModel::recalculateConstraints, this, &SchemesDispatcher::onRecalculateConstraints);

    if (schemes.size() == 1){
        this->setCurrentSchemeID(id);
    }

    return id;
}


void SchemesDispatcher::removeScheme(ID id)
{
    this->schemes.erase(id);

    if (schemes.size() == 0){
        this->setCurrentSchemeID(0);
    }
}


std::shared_ptr<SchemeModel> SchemesDispatcher::getScheme(ID id)
{
    auto it = this->schemes.find(id);
    if (it == this->schemes.end())
        return nullptr;

    return it->second;
}


ID SchemesDispatcher::getCurrentSchemeID()
{
    auto it = this->schemes.find(this->current_scheme_id);
    if (it == this->schemes.end())
        return 0;

    return this->current_scheme_id;
}


void SchemesDispatcher::setCurrentSchemeID(ID id)
{
    auto it = this->schemes.find(id);
    if (it != this->schemes.end())
        id = 0;

    this->current_scheme_id = id;
    emit this->currentSchemeIDChanged(id);
}


void SchemesDispatcher::loadSchemeFromStream(std::istream &in, AbstractSchemeSerializer &scheme_serializer, ID id)
{
    ID cur_id = id == 0 ? this->current_scheme_id : id;

    std::shared_ptr<SchemeModel> scheme = this->getScheme(cur_id);
    if (scheme != nullptr)
    {
        scheme_serializer.loadSchemeFromStream(in, *scheme);
    }
}


void SchemesDispatcher::saveSchemeToStream(std::ostream &out, AbstractSchemeSerializer &scheme_serializer, ID id)
{
    ID cur_id = id == 0 ? this->current_scheme_id : id;

    std::shared_ptr<SchemeModel> scheme = this->getScheme(cur_id);
    if (scheme != nullptr)
    {
        scheme_serializer.saveSchemeToStream(out, *scheme);
    }
}


void SchemesDispatcher::onDoAction(const std::shared_ptr<AbstractSchemeActionCommand> &command)
{
    std::shared_ptr<SchemeModel> scheme = this->getScheme(this->getCurrentSchemeID());
    scheme->onDoAction(command);
}


void SchemesDispatcher::onUndoLastAction()
{
    std::shared_ptr<SchemeModel> scheme = this->getScheme(this->getCurrentSchemeID());
    scheme->onUndoLastAction();
}


void SchemesDispatcher::onRedoLastAction()
{
    std::shared_ptr<SchemeModel> scheme = this->getScheme(this->getCurrentSchemeID());
    scheme->onRedoLastAction();
}


void SchemesDispatcher::onSchemeEventOccured(const SchemeEvent &scheme_event, const SchemeModel &scheme_model)
{
    if (scheme_model.getId() == this->getCurrentSchemeID())
        emit this->schemeEventOccured(scheme_event, scheme_model);
}


void SchemesDispatcher::onRecalculateConstraints(const SchemeModel &scheme_model)
{
    if (scheme_model.getId() == this->getCurrentSchemeID())
        emit this->recalculateConstraints(scheme_model);
}
