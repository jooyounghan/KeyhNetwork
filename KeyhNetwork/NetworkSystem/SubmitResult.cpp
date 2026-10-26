#include "NetworkSystemPch.h"
#include "SubmitResult.h"

namespace keyh
{
	SubmitResult SubmitResult::sucess()
	{
		SubmitResult submitResult;
		submitResult._status = SubmitStatus::Accepted;
		return submitResult;
	}

	SubmitResult SubmitResult::reject(IoErrorCode error, int nativeError /*= 0*/)
	{
		SubmitResult submitResult;
		submitResult._status = SubmitStatus::Rejected;
		submitResult._errorGroup = IoErrorGroup(error, nativeError);
		return submitResult;
	}
}