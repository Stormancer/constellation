#pragma once
#include <memory>
#include <vector>
#include <span>
#include "stormancer/StormancerTypes.h"

namespace Stormancer
{
	/// <summary>
	/// Class providing shared ownership of a memory buffer
	/// </summary>
	STORMANCERCORE_API struct MemoryOwner
	{
		STORMANCERCORE_API MemoryOwner(const std::span<const byte>& span);
		

		std::shared_ptr <std::vector<byte>> buffer;

		
	};

	STORMANCERCORE_API struct Memory
	{
		STORMANCERCORE_API Memory(const std::span<const byte>& span);
		STORMANCERCORE_API Memory(Memory& memory);
		
		STORMANCERCORE_API  Memory slice(size_t offset);
	
		STORMANCERCORE_API std::span<const byte> getReadOnlySpan() const;
		STORMANCERCORE_API std::span<byte> getSpan() const;

	private:
		MemoryOwner _owner;
		std::span<byte> span;
	};

	/// <summary>
	/// An output sink into which binary data can be written.
	/// </summary>
	struct BufferWriter
	{
		STORMANCERCORE_API BufferWriter();

		/// <summary>
		/// returns a span to write to.
		/// </summary>
		/// <param name="size">minimum size of the returned writing buffer</param>
		/// <returns></returns>
		STORMANCERCORE_API std::span<byte> getSpan(size_t size);

		/// <summary>
		/// Notifies the the sink that data were written into the span previously returned by <see cref="BufferWriter::getSpan" />
		/// </summary>
		/// <param name="size"></param>
		STORMANCERCORE_API void advance(size_t size);


		/// <summary>
		/// Returns the current content of the sink.
		/// </summary>
		/// <returns></returns>
		STORMANCERCORE_API std::span<const byte> content();
		
		/// <summary>
		/// Short inline method to write a bytes buffer into the writer
		/// </summary>
		void write(const byte* buf,size_t len)
		{
			auto span = getSpan(len);
			std::memcpy(span.data(), buf, len);
			advance(len);
		}

		void write(const char* buf, size_t len)
		{
			write(reinterpret_cast<const byte*>(buf), len);
		}

	private:
		MemoryOwner _owner;
		size_t lockedLength = 0;
		std::span<byte> writingBuffer;
	};
}