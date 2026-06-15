#include <catch2/catch_test_macros.hpp>

#include <quic/peerBuilder.hpp>
#include <MockNetworkTransport.hpp>

TEST_CASE("Create a peer using a builder.", "[quic]")
{
  using namespace Constellation;

  QuicPeerBuilder builder;
  MockNetworkTransport transport;
  builder.addTransport(&transport);

  auto peer = builder.create();
}
