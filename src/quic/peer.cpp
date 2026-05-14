#include <quic/peer.hpp>
#include <backend/string.hpp>
#include <backend/primitives.hpp>
#include <async/task.hpp>
#include <quic/remotePeer.hpp>

namespace Constellation
{

	class QuicPeerImpl
	{
        public:
          Task<QuicRemotePeer> connect(String &hostname, uint16 port);
	};

	
	Task<QuicRemotePeer> QuicPeer::connect(String& hostname, uint16 port) 
	{ 
		return _impl->connect(hostname, port);
	}
 }