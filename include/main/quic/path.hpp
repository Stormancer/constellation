#pragma once
#include <quic/quic_export.hpp>

#include <backend/memory.hpp>
#include <backend/string.hpp>

namespace Constellation {
class IDatagramTransport;

/*
 * Represents a network path.
 */
QUIC_EXPORT class Path
{
public:
  Path(const IDatagramTransport *transport, SharedPtr<const void> context) : transport(transport), context(context) {}

  /*
   * Creates a string representation of the path.
   */
  String toString() const;

  /*
   * Gets a boolean value indicating whether the path is valid.
   */
  bool isValid() const;

  /// <summary>
  /// Gets an hash code of the path.
  /// </summary>
  /// <returns></returns>
  size_t hashCode() const; 

  /// <summary>
  /// Equality operator between 2 paths.
  /// </summary>
  /// <param name="left"></param>
  /// <param name="right"></param>
  /// <returns></returns>
  bool operator==(const Path &right) const;

  /// <summary>
  /// Inequality operator between 2 paths.
  /// </summary>
  /// <param name="left"></param>
  /// <param name="right"></param>
  /// <returns></returns>
  bool operator!=( const Path &right) const;

private:
  const IDatagramTransport *transport;
  SharedPtr<const void> context;
};
}// namespace Constellation