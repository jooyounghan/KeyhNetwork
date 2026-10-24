#pragma once
#include "NetworkTypes.h"
#include "Socket.h"

namespace keyh
{
	class Socket;

	class ConnectionRegistry
	{
	public:
		ConnectionID	registerConnectionTcp();
		ConnectionID	registerConnectionUdp();

	private:
		ConnectionID	registerConnection(Socket&& socket);

	public:
		void			unregisterConnection(ConnectionID connection);

	public:
		const Socket*	getSocket(ConnectionID connection) const;

	private:
		static Socket createTcpSocket();
		static Socket createUdpSocket();

	private:
		struct SocketSlot
		{
			uint32 _generation = 0;
			Socket _socket;
		};

		Vector<SocketSlot>	_slots;		
		Vector<uint32>		_freeSlots;
	};
}

