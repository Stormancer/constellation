#pragma once
#include <quic/peer.hpp>

namespace Constellation
{
	class QuicPeerBuilder
	{
        public:
          /*
		  * Creates a new Quic peer using this configuration builder.
		  */
          QuicPeer create() const;
	};
}