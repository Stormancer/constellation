#pragma once
#include <backend/primitives.hpp>
#include <backend/span.hpp>

namespace Stormancer {
namespace BinaryPrimitives {
  bool tryReadUint16BigEndian(Span<const byte> buffer, uint16 &result);
  bool tryWriteUint16BigEndian(Span<byte> buffer, uint16 data);
  bool tryReadUint16LittleEndian(Span<const byte> buffer, uint16 &result);
  bool tryWriteUint16LittleEndian(Span<byte> buffer, uint16 result);

  bool tryReadUint64LittleEndian(Span<const byte> buffer, uint64 &result);
  bool tryWriteUint64LittleEndian(Span<byte> buffer, uint64 value);
}// namespace BinaryPrimitives
}// namespace Stormancer