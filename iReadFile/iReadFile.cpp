#include "mex.hpp"
#include "mexAdapter.hpp"
#include <windows.h>
using namespace matlab::data;
class MexFunction : public matlab::mex::Function {
public:
	void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
		const HANDLE File = HANDLE(uint64_t(TypedArray<uint64_t>(std::move(inputs[0]))[0]));
		const DWORD NumberOfBytesToRead = TypedArray<uint32_t>(std::move(inputs[1]))[0];
		ArrayFactory 数组工厂;
		buffer_ptr_t<uint8_t> 输出缓冲 = 数组工厂.createBuffer<uint8_t>(NumberOfBytesToRead);
		uint8_t* const Buffer = 输出缓冲.get();
		DWORD NumberOfBytesRead;
		switch (outputs.size())
		{
		case 0:
			ReadFile(File, Buffer, NumberOfBytesToRead, &NumberOfBytesRead, NULL);
			break;
		case 1:
			ReadFile(File, Buffer, NumberOfBytesToRead, &NumberOfBytesRead, NULL);
			outputs[0] = 数组工厂.createArrayFromBuffer({ NumberOfBytesRead,1 }, std::move(输出缓冲));
			break;
		case 2:
			outputs[1] = 数组工厂.createScalar<bool>(ReadFile(File, Buffer, NumberOfBytesToRead, &NumberOfBytesRead, NULL));
			outputs[0] = 数组工厂.createArrayFromBuffer({ NumberOfBytesRead,1 }, std::move(输出缓冲));
			break;
		case 3:
			outputs[1] = 数组工厂.createScalar<bool>(ReadFile(File, Buffer, NumberOfBytesToRead, &NumberOfBytesRead, NULL));
			outputs[2] = 数组工厂.createScalar<uint32_t>(GetLastError());
			outputs[0] = 数组工厂.createArrayFromBuffer({ NumberOfBytesRead,1 }, std::move(输出缓冲));
			break;
		}
	}
};