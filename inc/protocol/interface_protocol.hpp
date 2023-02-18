#ifndef INTERFACE_PROTOCOL_HPP
#define INTERFACE_PROTOCOL_HPP

#include <vector>       // vector 
#include <string>       // string 
#include <chrono>       //system_clock 

namespace smart_home 
{
class InterfaceProtocol 
{
public:
    InterfaceProtocol() = default;
    InterfaceProtocol(InterfaceProtocol const& a_other) = default;
    InterfaceProtocol& operator=(InterfaceProtocol const& a_other) = default;
    ~InterfaceProtocol() = default;

    virtual std::vector<unsigned char> Pack(std::string const& a_deviceID, std::chrono::system_clock::time_point const& a_timeStamp, std::vector<std::string> const& a_payload) const = 0; 
    virtual size_t UnPackSize(std::vector<unsigned char>& a_packedBuffer) const = 0; 
    virtual std::vector<std::string> UnPack(std::vector<unsigned char>& a_packedBuffer) const = 0; 

};
}//smart_home

#endif /* INTERFACE_PROTOCOL_HPP */ 