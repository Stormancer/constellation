#pragma once
#include "tls/tlsContext.hpp"

#include "backend/memory.hpp"

namespace Constellation {
class QuicContext
{
public:
  UniquePtr<TlsContext> tls;

};

}// namespace Constellation