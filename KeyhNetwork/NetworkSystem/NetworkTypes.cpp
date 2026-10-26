#include "NetworkSystemPch.h"
#include "NetworkTypes.h"

namespace keyh
{
	uint64 SocketID::encode(SocketID socketId)
	{
		return (static_cast<uint64>(socketId._generation) << 32) | socketId._index;
	}

	IoErrorGroup::IoErrorGroup()
		: _error(IoErrorCode::None), _nativeError(0) 
	{}

	IoErrorGroup::IoErrorGroup(IoErrorCode error, int nativeError)
		: _error(error), _nativeError(nativeError)
	{}
}
