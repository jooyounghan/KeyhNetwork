#include "NetworkSystemPch.h"
#include "Socket.h"

namespace keyh
{
	Socket::Socket(NativeSocket socket) 
		: _socket(socket) 
	{
	}

	Socket::Socket(Socket&& other) noexcept
		: _socket(other._socket)
	{
		other._socket = kInvalidSocket;
	}

	Socket& Socket::operator=(Socket&& other) noexcept
	{
		if (this != &other)
		{
			_socket = other._socket;
			other._socket = kInvalidSocket;
		}
		return *this;
	}

	void Socket::reset()
	{
		if (isValid())
		{
			closeSocket(_socket);
			_socket = kInvalidSocket;
		}
	}

}

#pragma region FNV1aHash Specializations
namespace keyh
{
	DEFINE_FNV1A_HASH_DEFAULT_SPECIALIZATION(Socket);
}
#pragma endregion