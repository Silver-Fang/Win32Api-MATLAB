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
		const size_t �ļ���Ŀ = FileName.getNumberOfElements();
		ArrayFactory ���鹤��;
		buffer_ptr_t<uint64_t> ���ػ��� = ���鹤��.createBuffer<uint64_t>(�ļ���Ŀ);
		if (outputs.size() > 1)
		{
			buffer_ptr_t<uint32_t> ���󻺳� = ���鹤��.createBuffer<uint32_t>(�ļ���Ŀ);
			for (size_t a = 0; a < �ļ���Ŀ; ++a)
			{
				���ػ���[a] = uint64_t(CreateFileW(LPCWSTR(String(FileName[a]).c_str()), DesiredAccess, ShareMode, SecurityAttributes, CreationDisposition, FlagsAndAttributes, TemplateFile));
				���󻺳�[a] = GetLastError();
			}
			outputs[1] = ���鹤��.createArrayFromBuffer({ �ļ���Ŀ,1 }, std::move(���󻺳�));
		}
		else
			for (size_t a = 0; a < �ļ���Ŀ; ++a)
				���ػ���[a] = uint64_t(CreateFileW(LPCWSTR(String(FileName[a]).c_str()), DesiredAccess, ShareMode, SecurityAttributes, CreationDisposition, FlagsAndAttributes, TemplateFile));
		outputs[0] = ���鹤��.createArrayFromBuffer({ �ļ���Ŀ,1 }, std::move(���ػ���));
	}
};