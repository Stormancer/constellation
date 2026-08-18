#pragma once
#include <quic/IDatagramTransport.hpp>
#include <quic/path.hpp>
#include <backend/map.hpp>
#include <backend/memory.hpp>
#include <backend/primitives.hpp>

struct EndpointContext;

class MockNetworkTransport : public Constellation::IDatagramTransport
{
public:
 
  Constellation::Path getPath(int destinationId) const;


  // Inherited via IDatagramTransport
  Constellation::String toString(Constellation::SharedPtr<const void> context) const override;
  bool isValid(Constellation::SharedPtr<const void> context) const override;
  Constellation::size_t getHashCode(Constellation::SharedPtr<const void> context) const override;
  bool areEqual(Constellation::SharedPtr<const void> left, Constellation::SharedPtr<const void> right) const override;

private:
  mutable Constellation::Map<int, Constellation::SharedPtr<EndpointContext>> _endpoints; 
};

