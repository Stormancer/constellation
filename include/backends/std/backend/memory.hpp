#pragma once
#include <memory>
namespace Constellation
{
	template<typename T>
	using SharedPtr = std::shared_ptr<T>;
}