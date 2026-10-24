#pragma once
namespace keyh
{
	template<size_t Size>
	class IoBuffer
	{
	private:
		StaticArray<byte, Size> _buffer;
	};

	template<size_t Size>
	class IoBufferPooler
	{
	public:
		IoBufferPooler() = default;
		~IoBufferPooler() = default;

	public:
		IoBuffer<Size>*		acquire();
		void				release(IoBuffer<Size>* buffer);
	};
}

