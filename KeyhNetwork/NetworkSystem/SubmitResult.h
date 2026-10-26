#pragma once
#include "NetworkTypes.h"

namespace keyh
{
	enum class SubmitStatus : uint8
	{
		None,
		Accepted,
		Rejected
	};

	struct SubmitResult
	{
	public:
		inline bool isAccepted() const { return _status == SubmitStatus::Accepted; }

	public:
		static SubmitResult sucess();
		static SubmitResult reject(IoErrorCode error, int nativeError = 0);

	private:
		SubmitStatus _status = SubmitStatus::None;
		IoErrorGroup _errorGroup;
	};
}

