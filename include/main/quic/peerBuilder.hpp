#pragma once
#include <quic/quic_export.hpp>

#include <backend/vector.hpp>
#include <quic/peer.hpp>

namespace Constellation {
class IDatagramTransport;

QUIC_EXPORT class QuicPeerBuilder
{
public:
  /*
   * Creates a new Quic peer using this configuration builder.
   */
  QuicPeer create() const;

  Vector<const IDatagramTransport *> transports;

  QuicPeerBuilder &addTransport(const IDatagramTransport *transport)
  {
    transports.add(transport);
    return *this;
  }
  
};
}// namespace Constellation