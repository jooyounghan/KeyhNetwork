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

	template<size_t Size>
	IoBufferPooler<Size>::Slot::Slot(IoBufferPooler* owner) 
		: _buffer(owner) 
	{
	}

	template<size_t Size>
	IoBufferPooler<Size>::IoBufferPooler(Config config)
		: _maxCount(config._maxCount)
	{
		if (config._initialCount > config._maxCount)
		{
			KEYH_ASSERT_ARGS(false , "invalid IoBufferPooler Config");
		}

		_slots.reserve(config._maxCount);
		_lookup.reserve(config._maxCount);

		for (uint32 idx = 0; idx < config._initialCount; ++idx)
		{
			Slot* slot = createSlot();
			pushFree(slot);
		}
	}

	template<size_t Size>
	IoBufferPooler<Size>::Slot* IoBufferPooler<Size>::createSlot()
	{
		Slot* slot = _slots.emplace_back(this);
		_lookup.insert(&slot->_buffer, slot);
		return slot;
	}

	template<size_t Size>
	void IoBufferPooler<Size>::pushFree(Slot* slot)
	{
		KEYH_ASSERT_DEV(slot != nullptr, "Invalid slot for IoBufferPool");
		slot->_nextFree = _freeHead;
		_freeHead = slot;
	}

	template<size_t Size>
	IoBufferPooler<Size>::Slot* IoBufferPooler<Size>::popFree()
	{
		if (_freeHead == nullptr)
		{
			KEYH_ASSERT_DEV(false, "Empty free slot for IoBufferPool");
			return nullptr;
		}

		Slot* slot = _freeHead;
		_freeHead = slot->_nextFree;
		slot->_nextFree = nullptr;
		return slot;
	}
	
	template<size_t Size>
	IoBuffer<Size>* IoBufferPooler<Size>::acquire()
	{
		Slot* slot = nullptr;
		if (_freeHead != nullptr)
		{
			slot = popFree();
		}
		else if (_slots.size() < _maxCount)
		{
			slot = createSlot();
		}
		else
		{
			KEYH_ASSERT_DEV(false, "Pool Exhaustion Occurs");
			return nullptr;
		}

		if (slot == nullptr || slot->_isLeased)
		{
			KEYH_ASSERT_DEV(false, "slot is Invalid");
			return nullptr;
		}

		slot->_isLeased = true;
		return &slot->buffer;
	}
	
	template<size_t Size>
	void IoBufferPooler<Size>::release(IoBuffer<Size>* buffer)
	{
		if (buffer == nullptr)
			return;

		typename HashMap<Buffer*, Slot*>::FindResult findResult = _lookup.find(buffer);
		if (findResult.isFound() == false)
		{
			KEYH_ASSERT_DEV(false, "Buffer Owner mismatch for release");
			return;
		}

		Slot* slot = *findResult.value();

		if (slot->_isLeased == false)
		{
			KEYH_ASSERT_DEV(false, "Double release");
			return;

		}

		slot->_isLeased = false;
		pushFree(slot);
	}
}