#include "notifier_events.hpp"

namespace smart_home 
{

NotifierEvents::NotifierEvents(InterfaceSaveEvents& a_logStream, size_t a_numOfThreads)
: m_threadsPool(std::make_shared<threads::ThreadPool>(a_numOfThreads))
, m_logStream(a_logStream)
{
}

NotifierEvents::~NotifierEvents()
{
    // m_threadsPool->ShutDown();
}

void NotifierEvents::SubmitNotify(Event const& a_event, std::vector<PtrAgent> const& a_distributionList, PtrProxy a_ptrProxyEventsPublisher)
{
    auto eventPtr = std::make_shared<Event>(a_event);
    m_threadsPool->AddTask(std::unique_ptr<threads::AbstractAct> {new NotifyAct{eventPtr, a_distributionList, a_ptrProxyEventsPublisher, m_threadsPool, m_logStream}});
}


NotifierEvents::NotifyAct::NotifyAct(PtrEvent a_eventPtr, std::vector<PtrAgent> const& a_distributionList, PtrProxy a_proxyPtr, PtrThreadsPool a_threadsPool, InterfaceSaveEvents& a_logStream)
: m_eventPtr(a_eventPtr)
, m_distributionList(a_distributionList)
, m_proxyPtr(a_proxyPtr)
, m_threadsPool(a_threadsPool)
, m_logStream(a_logStream)
{
}


void NotifierEvents::NotifyAct::Act()
{   
    if(m_distributionList.size() > 0) {
        std::vector<std::string> dataVec {m_eventPtr->eType};

        for(auto & e : m_eventPtr->payload) {
            dataVec.push_back(e);
        }

        for (auto const& agent : m_distributionList) {
            // agent->Act(dataVec, m_proxyPtr);
            m_threadsPool->AddTask(std::unique_ptr<threads::AbstractAct> {new InformAgentAct{m_eventPtr, agent, dataVec, m_proxyPtr}});
        }
        m_eventPtr->Print(m_logStream);
    }
    
}

NotifierEvents::InformAgentAct::InformAgentAct(PtrEvent a_eventPtr, PtrAgent a_agentsPtr, std::vector<std::string> const& a_eventData, PtrProxy a_proxyPtr)
// : m_eventPtr(a_eventPtr)
: m_agentsPtr(a_agentsPtr)
, m_eventData(a_eventData)
, m_proxyPtr(a_proxyPtr)
{
}

void NotifierEvents::InformAgentAct::Act()
{
    m_agentsPtr->Act(m_eventData, m_proxyPtr);
}

} //smart_home