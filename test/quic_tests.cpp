#include <catch2/catch_test_macros.hpp>

#include <quic/peerBuilder.hpp>
#include <quic/connectOptions.hpp>
#include <MockNetworkTransport.hpp>

TEST_CASE("Create a peer using a builder.", "[quic]")
{
  using namespace Constellation;

  MockChannel channel;
  const auto* transport1 = channel.createTransport(0);
  

  QuicPeerBuilder builder;
  
  builder.addTransport(transport1);

  auto peer = builder.create();
}

TEST_CASE("Connect quic peers.", "[quic]")
{
  using namespace Constellation;

  MockChannel channel;
  const auto *transport1 = channel.createTransport(0);
  const auto *transport2 = channel.createTransport(1);


  QuicPeerBuilder builder;
  builder.addTransport(transport1);
  auto peer1 = builder.create();

  builder = QuicPeerBuilder();
  builder.addTransport(transport2);
  auto peer2 = builder.create();

  ConnectOptions connectOpt;
  connectOpt.paths.add(transport2->getPath(0));
  peer2.connect(connectOpt);

}
