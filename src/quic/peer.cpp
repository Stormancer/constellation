#include <quic/peer.hpp>
#include <quic/path.hpp>
#include <quic/remotePeer.hpp>
#include <peerImpl.hpp>

namespace Constellation
{

	

	
	QuicRemotePeer QuicPeer::connect(const Path& path) 
	{ 
		return _impl->connect(path);
	}
 }