classdef ShellFileOperations < uint32
    %用作ShellAPI.SHFileOperation的Func参数。
	%这些旗帜不能组合使用
    enumeration
		%将 From 中指定的文件移动到 To 中指定的位置。
        FO_MOVE (0x0001)
		%将 From 成员中指定的文件复制到 To 成员中指定的位置。
        FO_COPY (0x0002)
		%删除 From 中指定的文件。
        FO_DELETE (0x0003)
		%重命名 From 中指定的文件。您不能使用此标志通过单个函数调用重命名多个文件。请改用 FO_MOVE。
        FO_RENAME (0x0004)
    end
end