#pragma once
#include "IoBuffer.h"

namespace keyh
{
	template<size_t Size>
	class IoBufferPooler
	{
	public:
		friend class IoBuffer<Size>;
		using Buffer = IoBuffer<Size>;
		struct Config
		{
			size_t _initialCount;
			size_t _maxCount;
		};

	public:
		explicit IoBufferPooler(Config config);

	public:
		IoBufferPooler(const IoBufferPooler&) = delete;
		IoBufferPooler& operator=(const IoBufferPooler&) = delete;

		IoBufferPooler(IoBufferPooler&&) = delete;
		IoBufferPooler& operator=(IoBufferPooler&&) = delete;

	private:
		struct Slot
		{
			Buffer	_buffer;
			Slot* _nextFree = nullptr;
			bool	_isLeased = false;

			explicit Slot(IoBufferPooler* owner);
		};

	private:
		Slot* createSlot();
		void	pushFree(Slot* slot);
		Slot* popFree();

	public:
		Buffer* acquire();

	private:
		void	release(Buffer* buffer);

	private:
		size_t _maxCount;

	private:
		OwnerVector<Slot>		_slots;
		HashMap<Buffer*, Slot*>	_lookup;
		Slot* _freeHead = nullptr;

	};
}

#include "IoBufferPool.hpp"

