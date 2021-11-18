#include "mex.hpp"
#include "mexAdapter.hpp"
#include <windows.h>
using namespace matlab::data;
class MexFunction : public matlab::mex::Function {
private:
	PCZZWSTR �ַ���ƴ��(const Array& rhs)
	{
		const StringArray �����ַ���(rhs);
		const size_t �ַ�����Ŀ = �����ַ���.getNumberOfElements();
		if (�ַ�����Ŀ)
		{
			size_t* const �ַ������� = new size_t[�ַ�����Ŀ];
			std::u16string* const ת���ַ��� = new std::u16string[�ַ�����Ŀ];
			size_t �ܳ��� = 0;
			for (size_t a = 0; a < �ַ�����Ŀ; ++a)
			{
				ת���ַ���[a] = String(std::move(�����ַ���[a]));
				�ܳ��� += �ַ�������[a] = ת���ַ���[a].length() + 1;
			}
			wchar_t* const ����ֵ = new wchar_t[�ܳ��� + 1];
			size_t ��� = 0;
			for (size_t a = 0; a < �ַ�����Ŀ; ++a)
			{
				wmemcpy(����ֵ + ���, (const wchar_t*)ת���ַ���[a].c_str(), �ַ�������[a]);
				��� += �ַ�������[a];
			}
			����ֵ[���] = 0;
			delete[] �ַ�������;
			delete[] ת���ַ���;
			return ����ֵ;
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
		SHFILEOPSTRUCTW ����{ .hwnd = HWND(size_t(TypedArray<uint64_t>(std::move(inputs[0]))[0])),.wFunc = TypedArray<uint32_t>(std::move(inputs[1]))[0],.pFrom = �ַ���ƴ��(inputs[2]),.pTo = �ַ���ƴ��(inputs[3]),.fFlags = TypedArray<uint16_t>(std::move(inputs[4]))[0] };
		ArrayFactory ���鹤��;
		outputs[0] = ���鹤��.createScalar(SHFileOperationW(&����));
		outputs[1] = ���鹤��.createScalar(bool(����.fAnyOperationsAborted));
		if (����.fFlags & (FOF_WANTMAPPINGHANDLE|FOF_RENAMEONCOLLISION))
		{
			const HANDLETOMAPPINGS* const ӳ���� = (HANDLETOMAPPINGS*)����.hNameMappings;
			if (ӳ����)
			{
				const UINT ӳ����Ŀ = ӳ����->uNumberOfMappings;
				StructArray ����ӳ�� = ���鹤��.createStructArray({ ӳ����Ŀ,1 }, { "OldPath","NewPath" });
				LPSHNAMEMAPPINGW ӳ����Ŀ = ӳ����->lpSHNameMapping;
				for (UINT a = 0; a < ӳ����Ŀ; ++a, ++ӳ����Ŀ)
				{
					����ӳ��[a]["OldPath"] = ���鹤��.createCharArray((char16_t*)ӳ����Ŀ->pszOldPath);
					����ӳ��[a]["NewPath"] = ���鹤��.createCharArray((char16_t*)ӳ����Ŀ->pszNewPath);
				}
				outputs[2] = ����ӳ��;
				SHFreeNameMappings((HANDLE)ӳ����);
			}
			else
				outputs[2] = ���鹤��.createStructArray({ 0,1 }, { "OldPath","NewPath" });
		}
		else
			outputs[2] = ���鹤��.createStructArray({ 0,1 }, { "OldPath","NewPath" });
		if (����.fFlags & FOF_SIMPLEPROGRESS)
			if (����.lpszProgressTitle)
				outputs[3] = ���鹤��.createCharArray((char16_t*)����.lpszProgressTitle);
			else
				outputs[3] = ���鹤��.createCharArray("");
		else
			outputs[3] = ���鹤��.createCharArray("");
		
	}
};