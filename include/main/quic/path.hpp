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
  String toString();

  /*
   * Gets a boolean value indicating whether the path is valid.
   */
  bool isValid();


private:
  const IDatagramTransport *transport;
  SharedPtr<const void> context;
};
}// namespace Constellation