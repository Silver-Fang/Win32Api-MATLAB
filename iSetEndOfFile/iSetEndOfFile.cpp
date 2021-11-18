#include "mex.hpp"
#include "mexAdapter.hpp"
#include <windows.h>
using namespace matlab::data;
class MexFunction : public matlab::mex::Function {
public:
	void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
		const TypedArray<uint64_t> Files = std::move(inputs[0]);
		switch (outputs.size())
		{
		case 0:
			for (uint64_t F : Files)
				SetEndOfFile(HANDLE(F));
			break;
		case 1:
		{
			const size_t �ļ���Ŀ = Files.getNumberOfElements();
			ArrayFactory ���鹤��;
			buffer_ptr_t<bool> ������� = ���鹤��.createBuffer<bool>(�ļ���Ŀ);
			for (size_t F = 0; F < �ļ���Ŀ; ++F)
				�������[F] = SetEndOfFile(HANDLE(uint64_t(Files[F])));
			outputs[0] = ���鹤��.createArrayFromBuffer({ �ļ���Ŀ,1 }, std::move(�������));
			break;
		}
		case 2:
		{
			const size_t �ļ���Ŀ = Files.getNumberOfElements();
			ArrayFactory ���鹤��;
			buffer_ptr_t<bool> ������� = ���鹤��.createBuffer<bool>(�ļ���Ŀ);
			buffer_ptr_t<uint32_t> ���󻺳� = ���鹤��.createBuffer<uint32_t>(�ļ���Ŀ);
			for (size_t F = 0; F < �ļ���Ŀ; ++F)
			{
				�������[F] = SetEndOfFile(HANDLE(uint64_t(Files[F])));
				���󻺳�[F] = GetLastError();
			}
			outputs[0] = ���鹤��.createArrayFromBuffer({ �ļ���Ŀ,1 }, std::move(�������));
			outputs[1] = ���鹤��.createArrayFromBuffer({ �ļ���Ŀ,1 }, std::move(���󻺳�));
			break;
		}
		}
	}
};