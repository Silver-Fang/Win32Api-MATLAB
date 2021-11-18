#include "mex.hpp"
#include "mexAdapter.hpp"
#include <windows.h>
using namespace matlab::data;
class MexFunction : public matlab::mex::Function {
public:
	void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
		const HANDLE File = HANDLE(uint64_t(TypedArray<uint64_t>(std::move(inputs[0]))[0]));
		const LPCVOID Buffer = TypedArray<uint8_t>(std::move(inputs[1])).release().release();
		const DWORD NumberOfBytesToWrite = TypedArray<uint32_t>(std::move(inputs[2]))[0];
		ArrayFactory 数组工厂;
		DWORD NumberOfBytesWritten;
		switch (outputs.size())
		{
		case 0:
			WriteFile(File, Buffer, NumberOfBytesToWrite, &NumberOfBytesWritten, NULL);
			break;
		case 1:
			outputs[0] = 数组工厂.createScalar<bool>(WriteFile(File, Buffer, NumberOfBytesToWrite, &NumberOfBytesWritten, NULL));
			break;
		case 2:
			outputs[0] = 数组工厂.createScalar<bool>(WriteFile(File, Buffer, NumberOfBytesToWrite, &NumberOfBytesWritten, NULL));
			outputs[1] = 数组工厂.createScalar<uint32_t>(NumberOfBytesWritten);
			break;
		case 3:
			outputs[0] = 数组工厂.createScalar<bool>(WriteFile(File, Buffer, NumberOfBytesToWrite, &NumberOfBytesWritten, NULL));
			outputs[2] = 数组工厂.createScalar<uint32_t>(GetLastError());
			outputs[1] = 数组工厂.createScalar<uint32_t>(NumberOfBytesWritten);
			break;
		}
	}
};