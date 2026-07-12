#pragma once

namespace Constellation {
class QuicContext;

class QuicClientController
{
public:
  void connect(QuicContext *ctx);
};


class QuicServerController
{
};
}// namespace Constellation