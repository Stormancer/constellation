#include <quic/peerBuilder.hpp>
#include <quic/peer.hpp>
#include <backend/memory.hpp>
#include <peerImpl.hpp>

namespace Constellation {
QuicPeer QuicPeerBuilder::create() const 
{
  auto peerImpl = makeShared<QuicPeerImpl>(transports);
  return { peerImpl };
}
}// namespace Constellation