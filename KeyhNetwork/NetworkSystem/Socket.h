#pragma once
#include "NetworkTypes.h"

namespace keyh
{
	class Socket
	{
	public:
		Socket() = default;
		explicit Socket(NativeSocket socket);

	public:
		Socket(const Socket&) = delete;
		Socket& operator=(const Socket&) = delete;

	public:
		Socket(Socket&& other) noexcept;
		Socket& operator=(Socket&& other) noexcept;

	public:
		inline NativeSocket	getNativeSocket() const { return _socket; }
		inline bool			isValid() const { return _socket != kInvalidSocket; }

	public:
		void reset();

	private:
		NativeSocket _socket = kInvalidSocket;
	};

}

#pragma region FNV1aHash Specializations
namespace keyh
{
	DECLARE_FNV1A_HASH_SPECIALIZATION(Socket);
}
#pragma endregion
