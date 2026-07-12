#pragma once

#include <quic/quic_export.hpp>
#include <backend/primitives.hpp>
#include <backend/array.hpp>

namespace Constellation {
QUIC_EXPORT struct ConnectionId
{
  static constexpr int MAX_LENGTH = 20;

  uint8 size;
  Array<byte,MAX_LENGTH> data;
};
}// namespace Constellation