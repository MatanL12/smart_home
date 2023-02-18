#ifndef SAVE_E_DB_HPP
#define SAVE_EVENTS_DB_HPP

#include <unordered_map>
#include <string>
#include <memory>

#include "base_save_events.hpp"
#include "mysql_connection.h"

namespace smart_home
{

class SaveEventsDB : public BaseSaveEvents
{
public:
    SaveEventsDB(sql::Connection* a_dbConnection, std::string const& a_tableName);
    SaveEventsDB(SaveEventsDB const& a_other) = delete;
    SaveEventsDB& operator=(SaveEventsDB const& a_other) = delete;
    ~SaveEventsDB() = default;

    virtual void Save(std::vector<std::pair<std::string, std::string>> const& a_data) override;
    
private:
    sql::Connection* m_dbConnection;
    std::string m_tableName;
};

} // namespace smart_home

#endif /* SAVE_EVENTS_DB_HPP */