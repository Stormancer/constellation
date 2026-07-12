#pragma once
namespace Constellation {
enum class QuicStateIdentifier {
  /*
   * https://www.rfc-editor.org/info/rfc9000/#name-closing-connection-state
   */
  Closing,

  /*
  * https://www.rfc-editor.org/info/rfc9000/#name-draining-connection-state
  */
  Draining
};
struct QuicState
{
};
}// namespace Constellation