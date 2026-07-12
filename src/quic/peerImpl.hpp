#pragma once
#include <backend/vector.hpp>
#include <quic/connectOptions.hpp>
#include <quic/remotePeer.hpp>

namespace Constellation {
class IDatagramTransport;
class QuicPeerImpl
{
public:
  QuicPeerImpl(Vector<const IDatagramTransport *> transports) : _transports(transports) {}
  QuicRemotePeer connect(const ConnectOptions &options);

private:
  Vector<const IDatagramTransport *> _transports;
};
}// namespace Constellation