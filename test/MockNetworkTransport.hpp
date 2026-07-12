#pragma once
#include <quic/IDatagramTransport.hpp>
#include <quic/path.hpp>
#include <backend/map.hpp>

class MockChannel;

class MockNetworkTransport : public Constellation::IDatagramTransport
{
public:
  MockNetworkTransport(MockChannel *channel) : _channel(channel) {}

  Constellation::Path getPath(int destinationId) const;

private:
  const MockChannel *_channel;
};

class MockChannel
{
public:
  const MockNetworkTransport *createTransport(int id);

  const MockNetworkTransport *getTransport(int id) const;

private:
  Constellation::Map<int, MockNetworkTransport> _transports;
};