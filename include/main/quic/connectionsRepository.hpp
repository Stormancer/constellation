#pragma once
#include <quic/quic_export.hpp>

#include <backend/vector.hpp>
#include <backend/memory.hpp>
#include <backend/mutex.hpp>
class ConnectionImpl;

namespace Constellation {
class ConnectionsRepository
{
	
private:
  Vector<SharedPtr<ConnectionImpl>> _connections;

  Mutex _syncRoot;
};
}// namespace Constellation