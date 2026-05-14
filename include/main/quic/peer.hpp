#pragma once
#include <quic/quic_export.hpp>
#include <backend/primitives.hpp>
#include <backend/string.hpp>
#include <backend/memory.hpp>
#include <async/task.hpp>
#include <quic/remotePeer.hpp>


namespace Constellation
{
	class QuicPeerImpl;
	
	/*
	* Represents a local quic peer.
	*/
	QUIC_EXPORT class QuicPeer
	{
        public:
          Task<QuicRemotePeer> connect(String &hostname, uint16 port);


        private:
          SharedPtr<QuicPeerImpl> _impl;
	};
}