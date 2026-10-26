#include "IoBuffer.h"
#pragma once

namespace keyh
{
	template<size_t Size>
	IoBuffer<Size>::IoBuffer(IoBufferPooler<Size>* owner)
		: _owner(owner)
	{
	}

	template<size_t Size>
	void IoBuffer<Size>::release()
	{
		_owner->release(this);
	}
}