#include <catch2/catch_test_macros.hpp>

#include <quic/peerBuilder.hpp>

TEST_CASE("Create a peer using a builder.", "[quic]")
{
  using namespace Constellation;

  QuicPeerBuilder builder;


  auto peer = builder.create();
}
