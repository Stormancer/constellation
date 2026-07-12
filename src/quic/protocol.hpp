#pragma once
#include <backend/primitives.hpp>
#include <backend/span.hpp>

namespace Constellation {

struct BinaryPrimitives
{
  bool tryReadUint16BigEndian(Span<byte> buffer, uint16 &value)
  {
    if (buffer.size() < 2) return false;
  }
};
}// namespace Constellation