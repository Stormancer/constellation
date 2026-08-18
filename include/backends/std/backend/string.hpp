#pragma once
#include <quic/quic_export.hpp>

#include <string>

#define TEXT(x) L##x

namespace Constellation
{
	using String = std::wstring;

	template<typename T> String toString(T value) { return std::to_wstring(value); }


}