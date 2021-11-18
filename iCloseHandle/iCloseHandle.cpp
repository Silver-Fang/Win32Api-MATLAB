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
			const size_t 句柄数目 = Object.getNumberOfElements();
			ArrayFactory 数组工厂;
			buffer_ptr_t<bool> 返回缓冲 = 数组工厂.createBuffer<bool>(句柄数目);
			for (size_t a = 0; a < 句柄数目; ++a)
				返回缓冲[a] = CloseHandle(HANDLE(uint64_t(Object[a])));
			outputs[0] = 数组工厂.createArrayFromBuffer({ 句柄数目,1 }, std::move(返回缓冲));
			break; }
		case 2: {
			const size_t 句柄数目 = Object.getNumberOfElements();
			ArrayFactory 数组工厂;
			buffer_ptr_t<bool> 返回缓冲 = 数组工厂.createBuffer<bool>(句柄数目);
			buffer_ptr_t<uint32_t> 错误缓冲 = 数组工厂.createBuffer<uint32_t>(句柄数目);
			for (size_t a = 0; a < 句柄数目; ++a)
			{
				返回缓冲[a] = CloseHandle(HANDLE(uint64_t(Object[a])));
				错误缓冲[a] = GetLastError();
			}
			outputs[0] = 数组工厂.createArrayFromBuffer({ 句柄数目,1 }, std::move(返回缓冲));
			outputs[1] = 数组工厂.createArrayFromBuffer({ 句柄数目,1 }, std::move(错误缓冲));
			break; }
		}
	}
};