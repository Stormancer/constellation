#pragma once
#include <quic/quic_export.hpp>

#include <mutex>

namespace Constellation {

using Mutex = std::mutex;

/// <summary>
/// RIIA based lock mechanism, using a mutex 
/// </summary>
using Lock = std::lock_guard<std::mutex>;
}