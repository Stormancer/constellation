#pragma once
#include <backend/primitives.hpp>
#include <backend/span.hpp>
#include <protocol.hpp>

namespace Constellation {
struct PaddingFrames
{
  size_t length;
  size_t getLength() { return length; }

  bool tryWrite(Span<byte> buffer)
  {
    if (buffer.size() < length) { return false; }

    memset(buffer.data(), 0, length);
    return true;
  }
}
}// namespace Constellation