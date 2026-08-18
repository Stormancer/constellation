#include <peerImpl.hpp>
#include <quic/connectOptions.hpp>
#include <quic/peer.hpp>
#include <quic/remotePeer.hpp>


namespace Constellation {


QuicRemotePeer QuicPeer::connect(const ConnectOptions &options) { return _impl->connect(options); }


QuicPeerImpl::QuicPeerImpl(Vector<const IDatagramTransport *> transports) : _transports(transports) 
{

}

QuicRemotePeer QuicPeerImpl::connect(const ConnectOptions &options) 
{
	_connections
}
}// namespace Constellation