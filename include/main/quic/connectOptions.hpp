#pragma once

#include <quic/quic_export.hpp>
#include <backend/vector.hpp>
#include <quic/path.hpp>
#include <quic/connectionId.hpp>

namespace Constellation {
QUIC_EXPORT struct ConnectOptions
{
  /*
  * Network paths to the remote peer.
  */
  Vector<Path> paths;
};
}// namespace Constellation