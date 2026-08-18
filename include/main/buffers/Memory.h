#pragma once
#include <backend/memory.hpp>
#include <backend/primitives.hpp>
#include <backend/span.hpp>
#include <backend/vector.hpp>
#include <constellation/quic_export.hpp>

namespace Constellation {
/// <summary>
/// Class representing shared ownership of a memory buffer
/// </summary>
/// <remarks>
/// placeholder implementation based on a vector<byte>
/// </remarks>
QUIC_LIBRARY_EXPORT struct MemoryOwner
{
  MemoryOwner(Span<const byte> span);


  SharedPtr<Vector<byte>> buffer;
};

QUIC_LIBRARY_EXPORT struct Memory
{
  Memory(Span<const byte> span);
  Memory(Memory &memory);

  Memory slice(size_t offset);

  Span<const byte> getReadOnlySpan() const;
  Span<byte> getSpan() const;

private:
  MemoryOwner _owner;
  Span<byte> span;
};

/// <summary>
/// An output sink into which binary data can be written.
/// </summary>
QUIC_LIBRARY_EXPORT struct BufferWriter
{
  BufferWriter();

  /// <summary>
  /// returns a span to write to.
  /// </summary>
  /// <param name="size">minimum size of the returned writing buffer</param>
  /// <returns></returns>
  Span<byte> getSpan(size_t size);

  /// <summary>
  /// Notifies the the sink that data were written into the span previously returned by <see
  /// cref="BufferWriter::getSpan" />
  /// </summary>
  /// <param name="size"></param>
  void advance(size_t size);


  /// <summary>
  /// Returns the current content of the sink.
  /// </summary>
  /// <returns></returns>
  Span<const byte> content();

  /// <summary>
  /// Short inline method to write a bytes buffer into the writer
  /// </summary>
  void write(const byte *buf, size_t len)
  {
    auto span = getSpan(len);
    std::memcpy(span.data(), buf, len);
    advance(len);
  }

  void write(const char *buf, size_t len) { write(reinterpret_cast<const byte *>(buf), len); }

private:
  MemoryOwner _owner;
  size_t lockedLength = 0;
  Span<byte> writingBuffer;
};
}// namespace Stormancer