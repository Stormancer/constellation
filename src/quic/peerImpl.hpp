#pragma once
#include <backend/vector.hpp>
#include <quic/connectOptions.hpp>
#include <quic/connectionsRepository.hpp>
#include <quic/remotePeer.hpp>

namespace Constellation {
class IDatagramTransport;
class ConnectionContext;
class QuicPeerImpl
{
public:
  explicit QuicPeerImpl(Vector<const IDatagramTransport *> transports);
  QuicRemotePeer connect(const ConnectOptions &options);

private:
 

  Vector<const IDatagramTransport *> _transports;
  ConnectionsRepository _connections;
};
}// namespace Constellation