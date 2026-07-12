#include "MockNetworkTransport.hpp"
#include <backend/memory.hpp>
#include <quic/path.hpp>
#include <quic/IDatagramTransport.hpp>

Constellation::Path MockNetworkTransport::getPath(int destinationId) const
{
  const auto *transport = _channel->getTransport(destinationId);
  const Constellation::SharedPtr<const void> ctx(transport, [](auto) {});
  return { static_cast<const IDatagramTransport *>(this), ctx };
}

const MockNetworkTransport *MockChannel::createTransport(int transportId)
{
  const MockNetworkTransport transport(this);
  _transports.emplace(transportId, transport);

  return getTransport(transportId);
}

const MockNetworkTransport *MockChannel::getTransport(int transportId) const { return &_transports.at(transportId); }
