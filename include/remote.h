#pragma once

#include <address.h>
#include <vars.h>
#include <network.h>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/*template<typename Lambda>
bool Func1(int Arg1, Lambda Arg2){ // or Lambda&&, which is usually better
  if(Arg1 > 0){
    return Arg2(Arg1);
  } else {
    return false; // remember, all control paths must return a value
  }
}*/

class Remote{
    public:
        Remote::Remote(Address remoteAddress);
        void open_connection();
        void close_connection();
        std::string RemoteAddrStr();
        std::size_t id(std::size_t offset = 0);
        void send(std::string msg);
        std::string recv();
        bool ping();

        // Depends on sucsessful connection
        std::string command(std::string msg);
        std::vector<Remote> get_successors();
        Remote successor();
        Remote predecessor();
        Remote find_successor(std::size_t id);
        Remote closest_preceding_finger(std::size_t id);
        void notify(Remote node);
    private:
        bool connected;
        Address address;
        std::string lastMessageSent;

        //struct sockaddr_in address;
        int socket = 0, valread;
        std::size_t BUFFER_SIZE;
};