#pragma once
#include "NetworkTypes.h"
#include "Socket.h"

namespace keyh
{
	class Socket;

	class SocketRegistry
	{
	public:
		SocketID	registerSocketTcp();
		SocketID	registerSocketUdp();

	private:
		SocketID	registerSocket(Socket&& socket);

	public:
		void			unregisterSocket(SocketID socket);

	public:
		const Socket*	getSocket(SocketID socket) const;

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

