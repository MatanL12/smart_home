#ifndef TCP_EVENT_HANDLER_HPP
#define TCP_EVENT_HANDLER_HPP

#include "tcp_abstract_handler.hpp"
#include "agent_manager.hpp"
#include "events_publisher.hpp"
#include "proxy_events_publisher.hpp"
#include "threads_thread_pool.hpp"
#include "interface_save_events.hpp"
#include "smart_home_protocol.hpp"


namespace net {

class EventHandler : public Handler {
public:
    using Handler::Handler;
    EventHandler(std::ifstream& a_configStream, smart_home::InterfaceSaveEvents& a_logStream, size_t a_numOfThreads, smart_home::InterfaceProtocol const& a_protocol);
    ~EventHandler();

    virtual void HandlerIncoming(std::shared_ptr<TCPClientSocket>& a_client) override;

private:
    using PtrTCPClient = std::shared_ptr<net::TCPClientSocket>;
    std::vector<unsigned char> recvEntireMsg(PtrTCPClient& a_client);

private:
    std::shared_ptr<smart_home::EventsPublisher> m_eventPublisher;
    std::shared_ptr<smart_home::ProxyEventsPublisher> m_eventPublisherProxy;
    std::shared_ptr<smart_home::AgentManager> m_agentManager;
    smart_home::InterfaceProtocol const& m_protocol;
    threads::ThreadPool m_threadPool;
};

}//net

#endif /* TCP_EVENT_HANDLER_HPP */