#pragma once

#include "NetworkTypes.h"

namespace keyh
{
	class IoBuffer;

	//class INetworkIoEngine
	//{
	//public:
	//	virtual ~INetworkIoEngine() = default;

	//public:
	//	virtual bool registerSocket(
	//		SocketID socket
	//	) = 0;

	//	virtual bool submitReceive(
	//		IoOperation& operation
	//		, IoBuffer& buffer
	//	) = 0;

	//	virtual bool submitSend(
	//		IoOperation& operation
	//		, IoBuffer& buffer
	//	) = 0;

	//private:
	//	virtual bool submitOperation(
	//		IoOperation& operation
	//	) = 0;

	//public:
	//	virtual size_t poll(
	//		IoCompletion* completions
	//		, size_t completionCount
	//		, int timeoutMilliseconds
	//	) = 0;

	//	virtual void shutdown() = 0;
	//};

}
