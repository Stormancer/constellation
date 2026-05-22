#pragma once
#include <quic/quic_export.hpp>

#include <quic/peer.hpp>

namespace Constellation
{
	QUIC_EXPORT class QuicPeerBuilder
	{
        public:
          /*
		  * Creates a new Quic peer using this configuration builder.
		  */
          QuicPeer create() const;
	};
}