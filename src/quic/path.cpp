
#include <quic/path.hpp>
#include <quic/IDatagramTransport.hpp>

#include <backend/string.hpp>
#include <backend/primitives.hpp>

namespace Constellation {

String Path::toString() const
{
  if (transport == nullptr) {
    return TEXT("invalidPath");
  } else {
    return transport->toString(context);
  }
}

bool Path::isValid() const
{
  if (transport == nullptr) {
    return false;
  } else {
    return transport->isValid(context);
  }
}

size_t Path::hashCode() const
{
  if (transport == nullptr) {
    return 0;
  } else {
    return transport->getHashCode(context);
  }
}
bool Path::operator==(const Path &right) const
{
  if (transport == nullptr) {
    return right.transport == nullptr;
      
  } else {
    return transport->areEqual(context, right.context);
  }
}

bool Path::operator != (const Path &right) const { return !(*this == right); }
}// namespace Constellation