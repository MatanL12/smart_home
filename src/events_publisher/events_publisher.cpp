#include "events_publisher.hpp"

namespace smart_home 
{

namespace details 
{
using PtrAgent = std::shared_ptr<IAgent>;

struct Creator {
    Creator(PtrAgent a_ptrAgent) : m_ptrAgent(a_ptrAgent){};
    std::vector<PtrAgent> operator()() {
        return std::vector<PtrAgent>{m_ptrAgent};
    }
private:
    PtrAgent m_ptrAgent;
};

struct Updator {
    Updator(PtrAgent a_ptrAgent) : m_ptrAgent(a_ptrAgent){};
    void operator()(std::vector<PtrAgent> & a_value) {
        return a_value.push_back(m_ptrAgent);
    }
private:
    PtrAgent m_ptrAgent;
};
}

EventsPublisher::EventsPublisher(InterfaceSaveEvents& a_logStream ,size_t a_numOfThreads) 
: m_eventAgentsMapPtr(std::make_shared<EventAgentsMap>())
, m_logStream(a_logStream)
, m_notifierEvents(std::make_unique<NotifierEvents>(a_logStream, a_numOfThreads))
{
}


EventsPublisher::~EventsPublisher()
{
}


void EventsPublisher::Register(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr)
{
    EventData a_key = {a_eventType, a_location};
    m_eventAgentsMapPtr->Upsert(a_key, details::Creator{a_agentPtr}, details::Updator{a_agentPtr});
}


void EventsPublisher::eraseAgentFromDistributionList(std::vector<PtrAgent>& a_distributionList, PtrAgent a_agentPtr)
{
    std::vector<PtrAgent>::iterator it = a_distributionList.begin();
    std::vector<PtrAgent>::iterator end = a_distributionList.end();
    while(it != end) { 
        if((**it).ID() == (*a_agentPtr).ID()) { 
            a_distributionList.erase(it);
            break;
        }
        ++it;
    }
}

void EventsPublisher::Unregister(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr)
{
    EventData a_key = {a_eventType, a_location};

    std::vector<PtrAgent> distributionList = m_eventAgentsMapPtr->Get(a_key); //throwing KeyNotExistException if key not found

    eraseAgentFromDistributionList(distributionList, a_agentPtr);    
}


void EventsPublisher::SubmitNotify(Event const& a_event, std::shared_ptr<IEventsPublisher> a_proxy) 
{
    EventData a_key = {a_event.eType, a_event.location};
    std::vector<PtrAgent> distributionList {};
    try {
        distributionList = m_eventAgentsMapPtr->Get(a_key);
    }
    catch (threads::KeyNotExistException const& e) {}
    m_notifierEvents->SubmitNotify(a_event, distributionList, a_proxy);
}

}//smart_home