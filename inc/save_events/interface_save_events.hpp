#ifndef SAVE_Events_INTERFACE_HPP
#define SAVE_Events_INTERFACE_HPP

#include <vector>
#include <string>

namespace smart_home
{

class InterfaceSaveEvents
{
public:
    ~InterfaceSaveEvents() = default;

    virtual void Save(std::vector<std::pair<std::string, std::string>> const& a_data) = 0;

protected:
    InterfaceSaveEvents() = default;
    InterfaceSaveEvents(InterfaceSaveEvents const& a_other) = default;
    InterfaceSaveEvents& operator=(InterfaceSaveEvents const& a_other) = default;

};



} // namespace smart_home




#endif /* SAVE_Events_INTERFACE_HPP */