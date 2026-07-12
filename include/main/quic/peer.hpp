#pragma once
#include <quic/quic_export.hpp>

#include <backend/primitives.hpp>
#include <backend/memory.hpp>


#include <quic/remotePeer.hpp>
#include <quic/connectOptions.hpp>
namespace Constellation
{
	class QuicPeerImpl;
class QuicPeerBuilder;
	/*
	* Represents a local quic peer.
	*/
	QUIC_EXPORT class QuicPeer
	{
          friend QuicPeerBuilder;
        public:

          /*
		  * Starts a connection to a remote peer.
		  */
          QuicRemotePeer connect(const ConnectOptions& options);


        private:
          QuicPeer(SharedPtr<QuicPeerImpl> impl) : _impl(impl) {}
          SharedPtr<QuicPeerImpl> _impl;
	};
}