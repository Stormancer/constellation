#pragma once
#include <span>
#include "stormancer/StormancerTypes.h"

namespace Stormancer
{
	namespace BinaryPrimitives
	{
		STORMANCERCORE_API bool tryReadUint16BigEndian(const std::span<const byte>& buffer, uint16& result);
		STORMANCERCORE_API bool tryWriteUint16BigEndian(const std::span<byte>& buffer, uint16 data);
		STORMANCERCORE_API bool  tryReadUint16LittleEndian(const std::span<const byte>& buffer, uint16& result);
		STORMANCERCORE_API bool  tryWriteUint16LittleEndian(const std::span<byte>& buffer, uint16 result);

		STORMANCERCORE_API bool tryReadUint64LittleEndian(const std::span<const byte>& buffer, uint64& result);
		STORMANCERCORE_API bool tryWriteUint64LittleEndian(const std::span<byte>& buffer, uint64 value);
	}
}