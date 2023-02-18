#include <fstream>
#include "mysql_connection.h"
#include <cppconn/driver.h>

#include "server_app.hpp"
#include "interface_save_events.hpp"
#include "save_events_ostream.hpp"
#include "save_events_db.hpp"
#include "smart_home_protocol.hpp"

int main() 
{
    using namespace smart_home;
    
    std::ifstream stream("config.txt");
    
    size_t numOfThreads = 4;

    std::ofstream log("../log/log.txt");
    SaveEventsOstream saveStream{log};
    SmartHomeProtocol protocol{};
    ServerApp serverApp{"127.0.0.1", 8080, stream, saveStream, numOfThreads, protocol};
    
    serverApp.Run();

    return 0;
}