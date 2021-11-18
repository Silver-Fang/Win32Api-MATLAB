#include "mex.hpp"
#include "mexAdapter.hpp"
#include <windows.h>
using namespace matlab::data;
class MexFunction : public matlab::mex::Function {
public:
	void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
		const TypedArray<uint64_t> Files = std::move(inputs[0]);
		const LARGE_INTEGER DistanceToMove{ .QuadPart = TypedArray<int64_t>(std::move(inputs[1]))[0] };
		const DWORD MoveMethod = TypedArray<uint32_t>(std::move(inputs[2]))[0];
		switch (outputs.size())
		{
		case 0:
			for (uint64_t F : Files)
				SetFilePointerEx(HANDLE(F), DistanceToMove, NULL, MoveMethod);
			break;
		case 1:
		{
			const size_t �ļ���Ŀ = Files.getNumberOfElements();
			ArrayFactory ���鹤��;
			buffer_ptr_t<int64_t> ָ�뻺�� = ���鹤��.createBuffer<int64_t>(�ļ���Ŀ);
			LARGE_INTEGER NewFilePointer;
			for (size_t F = 0; F < �ļ���Ŀ; ++F)
			{
				SetFilePointerEx(HANDLE(uint64_t(Files[F])), DistanceToMove, &NewFilePointer, MoveMethod);
				ָ�뻺��[F] = NewFilePointer.QuadPart;
			}
			outputs[0] = ���鹤��.createArrayFromBuffer({ �ļ���Ŀ,1 }, std::move(ָ�뻺��));
			break;
		}
		case 2:
		{
			const size_t �ļ���Ŀ = Files.getNumberOfElements();
			ArrayFactory ���鹤��;
			buffer_ptr_t<bool> ������� = ���鹤��.createBuffer<bool>(�ļ���Ŀ);
			buffer_ptr_t<int64_t> ָ�뻺�� = ���鹤��.createBuffer<int64_t>(�ļ���Ŀ);
			LARGE_INTEGER NewFilePointer;
			for (size_t F = 0; F < �ļ���Ŀ; ++F)
			{
				�������[F] = SetFilePointerEx(HANDLE(uint64_t(Files[F])), DistanceToMove, &NewFilePointer, MoveMethod);
				ָ�뻺��[F] = NewFilePointer.QuadPart;
			}
			outputs[0] = ���鹤��.createArrayFromBuffer({ �ļ���Ŀ,1 }, std::move(ָ�뻺��));
			outputs[1] = ���鹤��.createArrayFromBuffer({ �ļ���Ŀ,1 }, std::move(�������));
			break;
		}
		case 3:
		{
			const size_t �ļ���Ŀ = Files.getNumberOfElements();
			ArrayFactory ���鹤��;
			buffer_ptr_t<bool> ������� = ���鹤��.createBuffer<bool>(�ļ���Ŀ);
			buffer_ptr_t<int64_t> ָ�뻺�� = ���鹤��.createBuffer<int64_t>(�ļ���Ŀ);
			buffer_ptr_t<uint32_t> ���󻺳� = ���鹤��.createBuffer<uint32_t>(�ļ���Ŀ);
			LARGE_INTEGER NewFilePointer;
			for (size_t F = 0; F < �ļ���Ŀ; ++F)
			{
				�������[F] = SetFilePointerEx(HANDLE(uint64_t(Files[F])), DistanceToMove, &NewFilePointer, MoveMethod);
				���󻺳�[F] = GetLastError();
				ָ�뻺��[F] = NewFilePointer.QuadPart;
			}
			outputs[0] = ���鹤��.createArrayFromBuffer({ �ļ���Ŀ,1 }, std::move(ָ�뻺��));
			outputs[1] = ���鹤��.createArrayFromBuffer({ �ļ���Ŀ,1 }, std::move(�������));
			outputs[2] = ���鹤��.createArrayFromBuffer({ �ļ���Ŀ,1 }, std::move(���󻺳�));
			break;
		}
		}
	}
};