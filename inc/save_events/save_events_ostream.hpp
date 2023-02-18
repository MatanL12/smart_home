#ifndef SAVE_EVENTS_OSTREAM_HPP
#define SAVE_EVENTS_OSTREAM_HPP

#include <vector>
#include <string>
#include <ostream>

#include "base_save_events.hpp"

namespace smart_home
{

class SaveEventsOstream : public BaseSaveEvents
{
public:
    SaveEventsOstream(std::ostream& a_stream);
    SaveEventsOstream(SaveEventsOstream const& a_other) = delete;
    SaveEventsOstream& operator=(SaveEventsOstream const& a_other) = delete;
    ~SaveEventsOstream() = default;

    virtual void Save(std::vector<std::pair<std::string, std::string>> const& a_data) override;
    
private:
    std::ostream& m_stream;

};

} // namespace smart_home

#endif /* SAVE_EVENTS_OSTREAM_HPP */