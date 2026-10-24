#include "NetworkSystemPch.h"
#include "ConnectionRegistry.h"

namespace keyh
{
	ConnectionID ConnectionRegistry::registerConnectionTcp()
	{
		return registerConnection(createTcpSocket());
	}

	ConnectionID ConnectionRegistry::registerConnectionUdp()
	{
		return  registerConnection(createUdpSocket());
	}

	ConnectionID ConnectionRegistry::registerConnection(Socket&& socket)
	{
		if (_freeSlots.empty() == false)
		{
			uint32 freeIndex = _freeSlots.unsafeBack();
			_freeSlots.pop_back();

			SocketSlot& slot = _slots[freeIndex];
			slot._socket = keyh::move(socket);

			ConnectionID connection;
			connection._index = freeIndex;
			connection._generation = slot._generation;
			return connection;
		}

		SocketSlot slot;
		slot._generation = ConnectionID::kInitialGeneration;
		slot._socket = keyh::move(socket);

		ConnectionID connection;
		connection._index = static_cast<uint32>(_slots.size());
		connection._generation = ConnectionID::kInitialGeneration;

		_slots.push_back(keyh::move(slot));

		return connection;
	}


	void ConnectionRegistry::unregisterConnection(ConnectionID connection)
	{
		const uint32 index = connection._index;
		if (_slots.size() <= index)
		{
			KEYH_ASSERT_DEV(false, "Invalid connection id");
			return;
		}
		
		SocketSlot& slot = _slots[index];
		slot._generation++;
		slot._socket.reset();
		_freeSlots.push_back(index);
	}

	const Socket* ConnectionRegistry::getSocket(ConnectionID connection) const
	{
		const uint32 index = connection._index;
		if (_slots.size() <= index)
		{
			KEYH_ASSERT_DEV(false, "Invalid connection id");
			return nullptr;
		}

		const SocketSlot& slot = _slots[index];
		if (slot._generation != connection._generation)
		{
			KEYH_ASSERT_DEV(false, "Invalid connection id [generation is invalid]");
			return nullptr;
		}

		return &slot._socket;
	}

	Socket ConnectionRegistry::createTcpSocket()
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

	Socket ConnectionRegistry::createUdpSocket()
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