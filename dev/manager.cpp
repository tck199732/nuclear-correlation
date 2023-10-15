#include "manager.hpp"

manager::manager()
{
    this->event_reader = 0;
    this->analyses = new analysis_collection();
}

manager::~manager()
{
    if (this->event_reader) delete this->event_reader;
    for (auto& anal : *this->analyses) delete anal;
    this->analyses->clear();
    delete this->analyses;
}

int manager::process()
{
    auto evt = event_reader->return_event();

    if (!evt)
    {
        return event_reader->get_status();
    }
    for (auto& anal : *this->analyses) {
        anal->process(evt);
    }

    if (evt) delete evt;

    return 0;
}
