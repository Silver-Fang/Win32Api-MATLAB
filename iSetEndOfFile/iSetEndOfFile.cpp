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
			const size_t 文件数目 = Files.getNumberOfElements();
			ArrayFactory 数组工厂;
			buffer_ptr_t<bool> 结果缓冲 = 数组工厂.createBuffer<bool>(文件数目);
			for (size_t F = 0; F < 文件数目; ++F)
				结果缓冲[F] = SetEndOfFile(HANDLE(uint64_t(Files[F])));
			outputs[0] = 数组工厂.createArrayFromBuffer({ 文件数目,1 }, std::move(结果缓冲));
			break;
		}
		case 2:
		{
			const size_t 文件数目 = Files.getNumberOfElements();
			ArrayFactory 数组工厂;
			buffer_ptr_t<bool> 结果缓冲 = 数组工厂.createBuffer<bool>(文件数目);
			buffer_ptr_t<uint32_t> 错误缓冲 = 数组工厂.createBuffer<uint32_t>(文件数目);
			for (size_t F = 0; F < 文件数目; ++F)
			{
				结果缓冲[F] = SetEndOfFile(HANDLE(uint64_t(Files[F])));
				错误缓冲[F] = GetLastError();
			}
			outputs[0] = 数组工厂.createArrayFromBuffer({ 文件数目,1 }, std::move(结果缓冲));
			outputs[1] = 数组工厂.createArrayFromBuffer({ 文件数目,1 }, std::move(错误缓冲));
			break;
		}
		}
	}
};