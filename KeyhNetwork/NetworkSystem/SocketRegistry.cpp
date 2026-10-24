#include "NetworkSystemPch.h"
#include "SocketRegistry.h"

namespace keyh
{
	SocketID SocketRegistry::registerSocketTcp()
	{
		return registerSocket(createTcpSocket());
	}

	SocketID SocketRegistry::registerSocketUdp()
	{
		return  registerSocket(createUdpSocket());
	}

	SocketID SocketRegistry::registerSocket(Socket&& socket)
	{
		if (_freeSlots.empty() == false)
		{
			uint32 freeIndex = _freeSlots.unsafeBack();
			_freeSlots.pop_back();

			SocketSlot& slot = _slots[freeIndex];
			slot._socket = keyh::move(socket);

			SocketID socketId;
			socketId._index = freeIndex;
			socketId._generation = slot._generation;
			return socketId;
		}

		SocketSlot slot;
		slot._generation = SocketID::kInitialGeneration;
		slot._socket = keyh::move(socket);

		SocketID socketId;
		socketId._index = static_cast<uint32>(_slots.size());
		socketId._generation = SocketID::kInitialGeneration;

		_slots.push_back(keyh::move(slot));

		return socketId;
	}


	void SocketRegistry::unregisterSocket(SocketID socket)
	{
		const uint32 index = socket._index;
		if (_slots.size() <= index)
		{
			KEYH_ASSERT_DEV(false, "Invalid socket id");
			return;
		}
		
		SocketSlot& slot = _slots[index];
		slot._generation++;
		slot._socket.reset();
		_freeSlots.push_back(index);
	}

	const Socket* SocketRegistry::getSocket(SocketID socket) const
	{
		const uint32 index = socket._index;
		if (_slots.size() <= index)
		{
			KEYH_ASSERT_DEV(false, "Invalid socket id");
			return nullptr;
		}

		const SocketSlot& slot = _slots[index];
		if (slot._generation != socket._generation)
		{
			KEYH_ASSERT_DEV(false, "Invalid socket id [generation is invalid]");
			return nullptr;
		}

		return &slot._socket;
	}

	Socket SocketRegistry::createTcpSocket()
	{
		NativeSocket nativeSocket = kInvalidSocket;
		nativeSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (nativeSocket == kInvalidSocket)
		{
			KEYH_ASSERT_DEV(false, "Failed to create socket");
			return Socket();
		}

		return Socket(nativeSocket);
	}

	Socket SocketRegistry::createUdpSocket()
	{
		NativeSocket nativeSocket = kInvalidSocket;
		nativeSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (nativeSocket == kInvalidSocket)
		{
			KEYH_ASSERT_DEV(false, "Failed to create socket");
			return Socket();
		}
		return Socket(nativeSocket);
	}
}