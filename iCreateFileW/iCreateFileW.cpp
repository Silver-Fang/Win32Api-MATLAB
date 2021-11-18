#include "mex.hpp"
#include "mexAdapter.hpp"
#include <windows.h>
using namespace matlab::data;
class MexFunction : public matlab::mex::Function {
public:
	void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
		const StringArray FileName = std::move(inputs[0]);
		const DWORD DesiredAccess = TypedArray<uint32_t>(std::move(inputs[1]))[0];
		const DWORD ShareMode = TypedArray<uint32_t>(std::move(inputs[2]))[0];
		const LPSECURITY_ATTRIBUTES SecurityAttributes = LPSECURITY_ATTRIBUTES(size_t(TypedArray<uint64_t>(std::move(inputs[3]))[0]));
		const DWORD CreationDisposition = TypedArray<uint32_t>(std::move(inputs[4]))[0];
		const DWORD FlagsAndAttributes = TypedArray<uint32_t>(std::move(inputs[5]))[0];
		const HANDLE TemplateFile = HANDLE(size_t(TypedArray<uint64_t>(std::move(inputs[6]))[0]));
		const size_t 文件数目 = FileName.getNumberOfElements();
		ArrayFactory 数组工厂;
		buffer_ptr_t<uint64_t> 返回缓冲 = 数组工厂.createBuffer<uint64_t>(文件数目);
		if (outputs.size() > 1)
		{
			buffer_ptr_t<uint32_t> 错误缓冲 = 数组工厂.createBuffer<uint32_t>(文件数目);
			for (size_t a = 0; a < 文件数目; ++a)
			{
				返回缓冲[a] = uint64_t(CreateFileW(LPCWSTR(String(FileName[a]).c_str()), DesiredAccess, ShareMode, SecurityAttributes, CreationDisposition, FlagsAndAttributes, TemplateFile));
				错误缓冲[a] = GetLastError();
			}
			outputs[1] = 数组工厂.createArrayFromBuffer({ 文件数目,1 }, std::move(错误缓冲));
		}
		else
			for (size_t a = 0; a < 文件数目; ++a)
				返回缓冲[a] = uint64_t(CreateFileW(LPCWSTR(String(FileName[a]).c_str()), DesiredAccess, ShareMode, SecurityAttributes, CreationDisposition, FlagsAndAttributes, TemplateFile));
		outputs[0] = 数组工厂.createArrayFromBuffer({ 文件数目,1 }, std::move(返回缓冲));
	}
};