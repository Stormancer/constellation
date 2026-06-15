#pragma once
#include <vector>

namespace Constellation {
template<typename T> class Vector
{
public:
  void add(T &item) { _data.push_back(item); }

private:
  std::vector<T> _data;
};
}// namespace Constellation