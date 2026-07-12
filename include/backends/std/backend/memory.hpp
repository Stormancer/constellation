#pragma once
#include <memory>
namespace Constellation {
template<typename T> using SharedPtr = std::shared_ptr<T>;
template<typename T> using UniquePtr = std::unique_ptr<T>;
template<typename T> using WeakPtr = std::weak_ptr<T>;

template<typename T, typename... TArgs> SharedPtr<T> makeShared(TArgs... args) { return std::make_shared<T>(args...); }
}// namespace Constellation