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
			const size_t 文件数目 = Files.getNumberOfElements();
			ArrayFactory 数组工厂;
			buffer_ptr_t<int64_t> 指针缓冲 = 数组工厂.createBuffer<int64_t>(文件数目);
			LARGE_INTEGER NewFilePointer;
			for (size_t F = 0; F < 文件数目; ++F)
			{
				SetFilePointerEx(HANDLE(uint64_t(Files[F])), DistanceToMove, &NewFilePointer, MoveMethod);
				指针缓冲[F] = NewFilePointer.QuadPart;
			}
			outputs[0] = 数组工厂.createArrayFromBuffer({ 文件数目,1 }, std::move(指针缓冲));
			break;
		}
		case 2:
		{
			const size_t 文件数目 = Files.getNumberOfElements();
			ArrayFactory 数组工厂;
			buffer_ptr_t<bool> 结果缓冲 = 数组工厂.createBuffer<bool>(文件数目);
			buffer_ptr_t<int64_t> 指针缓冲 = 数组工厂.createBuffer<int64_t>(文件数目);
			LARGE_INTEGER NewFilePointer;
			for (size_t F = 0; F < 文件数目; ++F)
			{
				结果缓冲[F] = SetFilePointerEx(HANDLE(uint64_t(Files[F])), DistanceToMove, &NewFilePointer, MoveMethod);
				指针缓冲[F] = NewFilePointer.QuadPart;
			}
			outputs[0] = 数组工厂.createArrayFromBuffer({ 文件数目,1 }, std::move(指针缓冲));
			outputs[1] = 数组工厂.createArrayFromBuffer({ 文件数目,1 }, std::move(结果缓冲));
			break;
		}
		case 3:
		{
			const size_t 文件数目 = Files.getNumberOfElements();
			ArrayFactory 数组工厂;
			buffer_ptr_t<bool> 结果缓冲 = 数组工厂.createBuffer<bool>(文件数目);
			buffer_ptr_t<int64_t> 指针缓冲 = 数组工厂.createBuffer<int64_t>(文件数目);
			buffer_ptr_t<uint32_t> 错误缓冲 = 数组工厂.createBuffer<uint32_t>(文件数目);
			LARGE_INTEGER NewFilePointer;
			for (size_t F = 0; F < 文件数目; ++F)
			{
				结果缓冲[F] = SetFilePointerEx(HANDLE(uint64_t(Files[F])), DistanceToMove, &NewFilePointer, MoveMethod);
				错误缓冲[F] = GetLastError();
				指针缓冲[F] = NewFilePointer.QuadPart;
			}
			outputs[0] = 数组工厂.createArrayFromBuffer({ 文件数目,1 }, std::move(指针缓冲));
			outputs[1] = 数组工厂.createArrayFromBuffer({ 文件数目,1 }, std::move(结果缓冲));
			outputs[2] = 数组工厂.createArrayFromBuffer({ 文件数目,1 }, std::move(错误缓冲));
			break;
		}
		}
	}
};