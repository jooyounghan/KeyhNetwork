#pragma once

namespace keyh
{
	class IIoBuffer
	{
	public:
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
}

#include "IoBuffer.hpp"