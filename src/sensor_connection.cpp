/******************************************************************************
 * Helper library for writing the solver client interface to an Owl aggregator.
 *****************************************************************************/

#include "sensor_connection.hpp"

#include <iostream>
#include <algorithm>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>

#include <owl/simple_sockets.hpp>
#include <owl/sensor_aggregator_protocol.hpp>

bool SensorConnection::reconnect() {
  //See if the socket needs to be connected before handhshaking
  if (not agg) {
    //Otherwise try to make a new connection
    ClientSocket agg2(AF_INET, SOCK_STREAM, 0, port, ip);
    if (not agg2) {
      std::cerr<<"SensorConnection: Failed to create socket for aggregator connection.\n";
      return false;
    }
    else {
      agg = std::move(agg2);
    }
  }

  if (agg) {
    //Try to get the handshake message
    {
      std::vector<unsigned char> handshake = sensor_aggregator::makeHandshakeMsg();

      //Send the handshake message
      agg.send(handshake);
      std::vector<unsigned char> raw_message(handshake.size());
      size_t length = agg.receive(raw_message);

      //Check if the handshake message failed
      if (not (length == handshake.size() and
            std::equal(handshake.begin(), handshake.end(), raw_message.begin()) )) {
        //Quit on failure - what we are trying to connect to is not a proper server.
        std::cerr<<"SensorConnection: Failure during handshake with aggregator - aborting.\n";
        //Destroy the socket connection
        ClientSocket empty_connection(AF_INET, SOCK_STREAM, 0, 0, "");
        agg = std::move(empty_connection);
      }
      else {
        std::cerr<<"SensorConnection: Connected to the GRAIL aggregation server.\n";
      }
    }
  } else {
    std::cerr<<"SensorConnection: Failed to connect to the GRAIL aggregation server.\n";
    return false;
  }
  return true;
}

SensorConnection::SensorConnection(std::string& ip, int port) : agg(AF_INET, SOCK_STREAM, 0, port, ip) {
  //Store these values so that we can reconnect later
  this->ip = ip;
  this->port = port;

  //Do the protocol handshake.
  reconnect();
}

SensorConnection::~SensorConnection() {
  ;
}

SensorConnection::operator bool() const {
  ///Simply mirror the state of the socket
  if (this->agg) {
    return true;
  }
  else {
    return false;
  }
}

void SensorConnection::send(SampleData& sd) {
  agg.send(sensor_aggregator::makeSampleMsg(sd));
}

