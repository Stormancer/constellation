#pragma once
#include <backend/vector.hpp>
#include <quic/path.hpp>
#include <quic/remotePeer.hpp>

namespace Constellation {
class IDatagramTransport;
class QuicPeerImpl
{
public:
  QuicPeerImpl(Vector<IDatagramTransport *> transports) : _transports(transports) {}
  QuicRemotePeer connect(const Path &path);

private:
  Vector<IDatagramTransport *> _transports;
};
}// namespace Constellation