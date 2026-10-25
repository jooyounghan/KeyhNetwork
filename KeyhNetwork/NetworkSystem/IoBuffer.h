#pragma once

namespace keyh
{
	class IIoBuffer
	{
		virtual IBuffer*	getBuffer() = 0;
		virtual void		release() = 0;
	};

	template<size_t Size>
	class IoBufferPooler;

	template<size_t Size>
	class IoBuffer : public IIoBuffer
	{
	public:
		explicit IoBuffer(IoBufferPooler<Size>* owner);

	public:
		IoBuffer(const IoBuffer&)				= delete;
		IoBuffer& operator=(const IoBuffer&)	= delete;
		IoBuffer(IoBuffer&&)					= delete;
		IoBuffer& operator=(IoBuffer&&)			= delete;

	public:
		virtual IBuffer*	getBuffer() { return &_storage; }
		virtual void		release();

	private:
		StaticBuffer<byte, Size>	_storage;
		IoBufferPooler<Size>*		_owner;
	};

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
			Slot*	_nextFree = nullptr;
			bool	_isLeased = false;

			explicit Slot(IoBufferPooler* owner);
		};

	private:
		Slot*	createSlot();
		void	pushFree(Slot* slot);
		Slot*	popFree();

	public:
		Buffer* acquire();

	private:
		void	release(Buffer* buffer);

	private:
		size_t _maxCount;

	private:
		OwnerVector<Slot>		_slots;
		HashMap<Buffer*, Slot*>	_lookup;
		Slot*					_freeHead = nullptr;

	};
}

#include "IoBuffer.hpp"