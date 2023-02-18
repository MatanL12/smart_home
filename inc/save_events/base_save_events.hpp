#ifndef BASE_SAVE_EVENTS_HPP
#define BASE_SAVE_EVENTS_HPP

#include <mutex>
#include "interface_save_events.hpp"

namespace smart_home
{

class BaseSaveEvents :public InterfaceSaveEvents
{
public:
    ~BaseSaveEvents() = default;

    virtual void Save(std::vector<std::pair<std::string, std::string>> const& a_data) = 0;

protected:
    BaseSaveEvents() = default;
    BaseSaveEvents(BaseSaveEvents const& a_other) = default;
    BaseSaveEvents& operator=(BaseSaveEvents const& a_other) = default;

protected:
    std::mutex m_mtx;
};



} // namespace smart_home

#endif /* BASE_SAVE_EVENTS_HPP */