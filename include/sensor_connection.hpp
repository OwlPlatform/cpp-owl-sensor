/******************************************************************************
 * Helper library for writing the solver client interface to an Owl aggregator.
 *****************************************************************************/

#ifndef __OWL_SENSOR_CONNECTION__
#define __OWL_SENSOR_CONNECTION__

#include <string>
#include <vector>

#include <owl/simple_sockets.hpp>
#include <owl/sensor_aggregator_protocol.hpp>

//TODO In the future C++11 support for regex should be used over these POSIX
//regex c headers.
#include <sys/types.h>
#include <regex.h>

/**
 * Maintain a sensor connection to an Owl aggregator.
 */
class SensorConnection {
  private:
    ClientSocket agg;
    std::string ip;
    int port;
  public:
    bool reconnect();
    SensorConnection(std::string& ip, int port);
    ~SensorConnection();

    ///Evalute to true if connected, false otherwise.
    explicit operator bool() const;

    ///Sends the given sample. Throws a std::runtime_error upon failure.
    void send(SampleData& sd);
};


#endif


