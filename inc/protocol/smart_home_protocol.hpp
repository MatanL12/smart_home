#ifndef SMART_HOME_PROTOCOL_HPP
#define SMART_HOME_PROTOCOL_HPP

#include "interface_protocol.hpp"

namespace smart_home 
{
class SmartHomeProtocol : public InterfaceProtocol
{
public:
    SmartHomeProtocol() = default;
    SmartHomeProtocol(SmartHomeProtocol const& a_other) = default;
    SmartHomeProtocol& operator=(SmartHomeProtocol const& a_other) = default;
    ~SmartHomeProtocol() = default;

    std::vector<unsigned char> Pack(std::string const& a_deviceID, std::chrono::system_clock::time_point const& a_timeStamp, std::vector<std::string> const& a_payload) const override; 
    size_t UnPackSize(std::vector<unsigned char>& a_packedBuffer) const override; 
    std::vector<std::string> UnPack(std::vector<unsigned char>& a_packedBuffer) const override; 

};
}//smart_home

#endif /* SMART_HOME_PROTOCOL_HPP */ 