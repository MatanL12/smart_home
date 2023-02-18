#include <fstream>
#include "server_app.hpp"
#include "interface_save_events.hpp"
#include "save_events_ostream.hpp"
#include "save_events_db.hpp"
#include "smart_home_protocol.hpp"
#include "mysql_connection.h"
#include <cppconn/driver.h>

int main() 
{
    using namespace smart_home;
    
    std::ifstream stream("config.txt");
    
    size_t numOfThreads = 3;

    sql::Driver *driver;
    sql::Connection* con;
    driver = get_driver_instance();
    con = driver->connect("tcp://db:3306", "root", "password"); 
    con->setSchema("smart_home_log");
    SaveEventsDB saveStreamDB{con, "events"};
    SmartHomeProtocol protocol{};
    ServerApp serverApp{"127.0.0.1", 8080, stream, saveStreamDB, numOfThreads, protocol};
    
    serverApp.Run();

    return 0;
}