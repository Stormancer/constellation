#include <quic/peer.hpp>
#include <quic/remotePeer.hpp>
#include <quic/connectOptions.hpp>
#include <peerImpl.hpp>

namespace Constellation
{

	

	
	QuicRemotePeer QuicPeer::connect(const ConnectOptions& options) 
	{ 
		return _impl->connect(options);
	}


	QuicRemotePeer QuicPeerImpl::connect(const ConnectOptions& options)
	{
		
	}
 }