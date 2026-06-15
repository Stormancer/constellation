#pragma once
#include <quic/quic_export.hpp>
#include <backend/primitives.hpp>
#include <backend/memory.hpp>
#include <quic/remotePeer.hpp>
#include <quic/path.hpp>

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
		  * Starts connection to a remote peer joinable through the provided path.
		  */
          QuicRemotePeer connect(const Path& path);


        private:
          QuicPeer(SharedPtr<QuicPeerImpl> impl) : _impl(impl) {}
          SharedPtr<QuicPeerImpl> _impl;
	};
}