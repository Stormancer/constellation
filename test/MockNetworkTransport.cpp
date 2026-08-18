#include "MockNetworkTransport.hpp"
#include <backend/memory.hpp>
#include <backend/string.hpp>
#include <backend/primitives.hpp>
#include <quic/path.hpp>
#include <utility>



struct EndpointContext : public Constellation::Shareable<EndpointContext>
{
  explicit EndpointContext(int address) : address(address) {}
  int address;
};

Constellation::Path MockNetworkTransport::getPath(int destinationId) const
{
  auto endpointIt = _endpoints.find(destinationId);
  if (endpointIt == _endpoints.end()) {
    auto result = Constellation::makeShared<EndpointContext>(destinationId);


    _endpoints.emplace(destinationId, result);
    return Constellation::Path{ this, result };
  }
  return Constellation::Path{ this, endpointIt->second };
}

Constellation::String MockNetworkTransport::toString(Constellation::SharedPtr<const void> context) const
{
  auto ctx = Constellation::CastShared<const EndpointContext>(context);
  return TEXT("mockTransport://") + Constellation::toString(ctx->address);
}

bool MockNetworkTransport::isValid(Constellation::SharedPtr<const void> context) const
{
  return context != nullptr;
}

Constellation::size_t MockNetworkTransport::getHashCode(Constellation::SharedPtr<const void> context) const
{
  auto ctx = Constellation::CastShared<const EndpointContext>(std::move(context));
  return 0;
}

bool MockNetworkTransport::areEqual(Constellation::SharedPtr<const void> left,  Constellation::SharedPtr<const void> right) const  // NOLINT(bugprone-easily-swappable-parameters)
{
  auto leftCtx = Constellation::CastShared<const EndpointContext>(left);
  auto rightCtx = Constellation::CastShared<const EndpointContext>(right);
  return leftCtx->address == rightCtx->address;
}
