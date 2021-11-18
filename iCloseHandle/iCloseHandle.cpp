#include "mex.hpp"
#include "mexAdapter.hpp"
#include <windows.h>
using namespace matlab::data;
class MexFunction : public matlab::mex::Function {
public:
	void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
		const TypedArray<uint64_t> Object = std::move(inputs[0]);
		switch (outputs.size())
		{
		case 0:
			for (uint64_t O : Object)
				CloseHandle(HANDLE(O));
			break;
		case 1: {
			const size_t �����Ŀ = Object.getNumberOfElements();
			ArrayFactory ���鹤��;
			buffer_ptr_t<bool> ���ػ��� = ���鹤��.createBuffer<bool>(�����Ŀ);
			for (size_t a = 0; a < �����Ŀ; ++a)
				���ػ���[a] = CloseHandle(HANDLE(uint64_t(Object[a])));
			outputs[0] = ���鹤��.createArrayFromBuffer({ �����Ŀ,1 }, std::move(���ػ���));
			break; }
		case 2: {
			const size_t �����Ŀ = Object.getNumberOfElements();
			ArrayFactory ���鹤��;
			buffer_ptr_t<bool> ���ػ��� = ���鹤��.createBuffer<bool>(�����Ŀ);
			buffer_ptr_t<uint32_t> ���󻺳� = ���鹤��.createBuffer<uint32_t>(�����Ŀ);
			for (size_t a = 0; a < �����Ŀ; ++a)
			{
				���ػ���[a] = CloseHandle(HANDLE(uint64_t(Object[a])));
				���󻺳�[a] = GetLastError();
			}
			outputs[0] = ���鹤��.createArrayFromBuffer({ �����Ŀ,1 }, std::move(���ػ���));
			outputs[1] = ���鹤��.createArrayFromBuffer({ �����Ŀ,1 }, std::move(���󻺳�));
			break; }
		}
	}
};