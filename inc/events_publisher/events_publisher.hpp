#ifndef EVENTS_PUBLISHER_HPP
#define EVENTS_PUBLISHER_HPP

#include <vector>
#include <memory>

#include "location.hpp"
#include "event.hpp"
#include "agent_interface.hpp"
#include "threads_concurrent_hash_table.hpp"
#include "threads_abstract_act.hpp"
#include "threads_thread_pool.hpp"
#include "events_publisher_interface.hpp"
#include "notifier_events.hpp"

namespace smart_home 
{

namespace details
{

struct HashFunc {
    std::size_t operator()(const std::pair<std::string, Location>& a_key) const
    {
        return std::hash<std::string>()(a_key.first);
    }
};

} // namespace details

class EventsPublisher : public IEventsPublisher
{
public:
    EventsPublisher(InterfaceSaveEvents& a_logStream ,size_t a_numOfThreads = 1);
    EventsPublisher(EventsPublisher const& a_other) = default;
    EventsPublisher& operator=(EventsPublisher const& a_other) = default;
    ~EventsPublisher();

    void Register(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr) override;
    void Unregister(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr) override;
    void SubmitNotify(Event const& a_event, std::shared_ptr<IEventsPublisher> a_proxy) override;

private:
    using PtrProxy = std::shared_ptr<IEventsPublisher>;
    using EventData = std::pair<std::string, Location>;
    using PtrAgent = std::shared_ptr<IAgent>;
    using EventAgentsMap = threads::ConcurrentHashTable<EventData, std::vector<PtrAgent>, details::HashFunc>;
    using PtrEventAgentsMap = std::shared_ptr<EventAgentsMap>;
    using PtrNotifierEvents = std::unique_ptr<NotifierEvents>;

    void eraseAgentFromDistributionList(std::vector<PtrAgent>& a_distributionList, PtrAgent a_agentPtr);

private:
    PtrEventAgentsMap m_eventAgentsMapPtr;
    InterfaceSaveEvents& m_logStream;
    PtrNotifierEvents m_notifierEvents;
};

} //smart_home

#endif /* EVENTS_PUBLISHER_HPP */