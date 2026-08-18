#pragma once
#include <backend/memory.hpp>
#include <backend/string.hpp>
#include <quic/quic_export.hpp>

namespace Constellation {
class IDatagramTransport
{
public:
  virtual String toString(SharedPtr<const void> context) const = 0;


  virtual bool isValid(SharedPtr<const void> context) const = 0;

  /// <summary>
  /// Gets an hash code of the path.
  /// </summary>
  /// <returns></returns>
  virtual size_t getHashCode(SharedPtr<const void> context) const = 0;

  virtual bool areEqual(SharedPtr<const void> left, SharedPtr<const void> right) const = 0;
};
}// namespace Constellation