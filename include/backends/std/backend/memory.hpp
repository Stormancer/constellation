#pragma once
#include <memory>
namespace Constellation {
template<typename T> using SharedPtr = std::shared_ptr<T>;
template<typename T> using UniquePtr = std::unique_ptr<T>;
template<typename T> using WeakPtr = std::weak_ptr<T>;
template<typename T> using Shareable = std::enable_shared_from_this<T>;

template<typename TDest, typename TOrigin> SharedPtr<TDest> CastShared(SharedPtr<TOrigin> o)
{ return std::static_pointer_cast<TDest>(o); }

template<typename T, typename... TArgs> SharedPtr<T> makeShared(TArgs... args)
{ return std::make_shared<T>(args...); }
}// namespace Constellation