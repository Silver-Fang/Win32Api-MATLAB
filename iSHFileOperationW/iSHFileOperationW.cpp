#include "mex.hpp"
#include "mexAdapter.hpp"
#include <windows.h>
using namespace matlab::data;
class MexFunction : public matlab::mex::Function {
private:
	PCZZWSTR 字符串拼接(const Array& rhs)
	{
		const StringArray 所有字符串(rhs);
		const size_t 字符串数目 = 所有字符串.getNumberOfElements();
		if (字符串数目)
		{
			size_t* const 字符串长度 = new size_t[字符串数目];
			std::u16string* const 转换字符串 = new std::u16string[字符串数目];
			size_t 总长度 = 0;
			for (size_t a = 0; a < 字符串数目; ++a)
			{
				转换字符串[a] = String(std::move(所有字符串[a]));
				总长度 += 字符串长度[a] = 转换字符串[a].length() + 1;
			}
			wchar_t* const 返回值 = new wchar_t[总长度 + 1];
			size_t 起点 = 0;
			for (size_t a = 0; a < 字符串数目; ++a)
			{
				wmemcpy(返回值 + 起点, (const wchar_t*)转换字符串[a].c_str(), 字符串长度[a]);
				起点 += 字符串长度[a];
			}
			返回值[起点] = 0;
			delete[] 字符串长度;
			delete[] 转换字符串;
			return 返回值;
		}
		else
			return NULL;
	}
	struct HANDLETOMAPPINGS
	{
		UINT              uNumberOfMappings;  // Number of mappings in the array.
		LPSHNAMEMAPPINGW   lpSHNameMapping;    // Pointer to the array of mappings.
	};
public:
	void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
		SHFILEOPSTRUCTW 操作{ .hwnd = HWND(size_t(TypedArray<uint64_t>(std::move(inputs[0]))[0])),.wFunc = TypedArray<uint32_t>(std::move(inputs[1]))[0],.pFrom = 字符串拼接(inputs[2]),.pTo = 字符串拼接(inputs[3]),.fFlags = TypedArray<uint16_t>(std::move(inputs[4]))[0] };
		ArrayFactory 数组工厂;
		outputs[0] = 数组工厂.createScalar(SHFileOperationW(&操作));
		outputs[1] = 数组工厂.createScalar(bool(操作.fAnyOperationsAborted));
		if (操作.fFlags & (FOF_WANTMAPPINGHANDLE|FOF_RENAMEONCOLLISION))
		{
			const HANDLETOMAPPINGS* const 映射句柄 = (HANDLETOMAPPINGS*)操作.hNameMappings;
			if (映射句柄)
			{
				const UINT 映射数目 = 映射句柄->uNumberOfMappings;
				StructArray 名称映射 = 数组工厂.createStructArray({ 映射数目,1 }, { "OldPath","NewPath" });
				LPSHNAMEMAPPINGW 映射条目 = 映射句柄->lpSHNameMapping;
				for (UINT a = 0; a < 映射数目; ++a, ++映射条目)
				{
					名称映射[a]["OldPath"] = 数组工厂.createCharArray((char16_t*)映射条目->pszOldPath);
					名称映射[a]["NewPath"] = 数组工厂.createCharArray((char16_t*)映射条目->pszNewPath);
				}
				outputs[2] = 名称映射;
				SHFreeNameMappings((HANDLE)映射句柄);
			}
			else
				outputs[2] = 数组工厂.createStructArray({ 0,1 }, { "OldPath","NewPath" });
		}
		else
			outputs[2] = 数组工厂.createStructArray({ 0,1 }, { "OldPath","NewPath" });
		if (操作.fFlags & FOF_SIMPLEPROGRESS)
			if (操作.lpszProgressTitle)
				outputs[3] = 数组工厂.createCharArray((char16_t*)操作.lpszProgressTitle);
			else
				outputs[3] = 数组工厂.createCharArray("");
		else
			outputs[3] = 数组工厂.createCharArray("");
		
	}
};