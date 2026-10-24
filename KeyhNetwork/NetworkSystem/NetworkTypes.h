#pragma once

#if defined(KEYH_PLATFORM_WINDOWS)
#include <winsock2.h>
#elif defined(KEYH_PLATFORM_POSIX)
#include <sys/socket.h>
#include <unistd.h>
#else
#error Unsupported platform for NetworkSystem
#endif

namespace keyh
{
#if defined(KEYH_PLATFORM_WINDOWS)
	using		NativeSocket = SOCKET;
	constexpr	NativeSocket kInvalidSocket = INVALID_SOCKET;
	inline		int closeSocket(NativeSocket socket) { return closesocket(socket); }
#elif defined(KEYH_PLATFORM_POSIX)
	using		NativeSocket = int;
	constexpr	NativeSocket kInvalidSocket = -1;
	inline		int closeSocket(NativeSocket socket) { return close(socket); }
#endif

	struct SocketID
	{
		uint32 _index;
		uint32 _generation = kInvalidGeneration;

		static constexpr uint32 kInvalidGeneration = 0;
		static constexpr uint32 kInitialGeneration = 1;

		inline bool isValid() const { return _generation != kInvalidGeneration; }
	};



	enum class OperationType : uint8
	{
		None,
		Send,
		Receive,
	};
}
