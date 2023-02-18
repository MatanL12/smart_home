#include <iostream>

#include "threads_act_event_handler.hpp"

namespace threads {
HandlerAct::HandlerAct(PtrTCPClient a_client, std::shared_ptr<smart_home::EventsPublisher> a_eventPublisher, std::shared_ptr<smart_home::ProxyEventsPublisher> a_eventPublisherProxy, std::shared_ptr<smart_home::AgentManager> a_agentManager, smart_home::InterfaceProtocol const& a_protocol, std::vector<unsigned char> const& a_recvBytesVec)
: m_client(std::move(a_client))
, m_eventPublisher(a_eventPublisher)
, m_eventPublisherProxy(a_eventPublisherProxy)
, m_agentManager(a_agentManager)
, m_protocol(a_protocol)
, m_recvBytesVec(a_recvBytesVec)
{
}

void HandlerAct::Act()
{
    auto unpackedVec = m_protocol.UnPack(m_recvBytesVec);
    
    smart_home::Event event = m_agentManager->GetEvent(unpackedVec, m_eventPublisherProxy);

    m_eventPublisher->SubmitNotify(event, m_eventPublisherProxy);
}

}//threads