#ifndef SERVER_APP_HPP
#define SERVER_APP_HPP

#include <chrono> //system_clock
#include <string>
#include <memory>

#include "tcp_selector.hpp"
#include "tcp_server_socket.hpp"
#include "tcp_acceptor.hpp"
#include "interface_save_events.hpp"
#include "interface_protocol.hpp"

namespace smart_home 
{
class ServerApp 
{
public:
    ServerApp(std::string const& a_ip, size_t a_port, std::ifstream& a_configStream, InterfaceSaveEvents& a_logStream, size_t a_numOfThreads, InterfaceProtocol const& a_protocol);
    ServerApp(ServerApp const& a_other) = delete;
    ServerApp& operator=(ServerApp const& a_other) = delete;
    ~ServerApp() = default;

    void Run();
    void Shutdown();

private:
    net::TCPServerSocket m_server;
    std::unique_ptr<net::Handler> m_handler;
    std::unique_ptr<net::Acceptor> m_acceptor;
    net::Selector m_selector;
};
}//smart_home

#endif /* SERVER_APP_HPP */