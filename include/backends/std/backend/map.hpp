#pragma once
#include <unordered_map>

namespace Constellation {
template<typename TKey, typename TValue> using Map = std::unordered_map<TKey, TValue>;
}// namespace Constellation