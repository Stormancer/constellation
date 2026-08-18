#include <catch2/catch_test_macros.hpp>

#include <quic/peerBuilder.hpp>
#include <quic/connectOptions.hpp>
#include <MockNetworkTransport.hpp>

TEST_CASE("Create a peer using a builder.", "[quic]")
{
  using namespace Constellation;

  
  const MockNetworkTransport transport1;
    

  QuicPeerBuilder builder;
  
  builder.addTransport(&transport1);

  builder.create();
}

TEST_CASE("Connect quic peers.", "[quic]")
{
  using namespace Constellation;

  const MockNetworkTransport transport;



  QuicPeerBuilder builder;
  builder.addTransport(&transport);
  auto peer1 = builder.create();

  builder = QuicPeerBuilder();
  builder.addTransport(&transport);
  auto peer2 = builder.create();

  ConnectOptions connectOpt;
  connectOpt.paths.add(transport.getPath(0));
  peer2.connect(connectOpt);

}
