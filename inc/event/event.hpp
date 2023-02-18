#ifndef EVENT_HPP
#define EVENT_HPP

#include <chrono> //system_clock
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>

#include "location.hpp"
#include "interface_save_events.hpp"

namespace smart_home 
{
struct Event 
{
public:
    void Print(InterfaceSaveEvents& a_logger) const;

    std::string timestamp;
    std::string eType;
    Location location;
    std::vector<std::string> payload;
};
}//smart_home

#include "event.hxx"

#endif /* EVENT_HPP */