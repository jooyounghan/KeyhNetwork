#include "SocketRegistry.h"
#include "IoBuffer.h"
#include "IoBufferPool.h"
using namespace keyh;

int main()
{
	IoBufferPooler<4096>::Config config;
	config._initialCount = 8;
	config._maxCount = 16;

	IoBufferPooler<4096> test(config);

}