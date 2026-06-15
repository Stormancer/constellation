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
  /*
   * Creates a string representation of the path.
   */
  String toString();

  /*
   * Gets a boolean value indicating whether the path is valid.
   */
  bool isValid();


private:
  IDatagramTransport *transport;
  SharedPtr<void> context;
};
}// namespace Constellation