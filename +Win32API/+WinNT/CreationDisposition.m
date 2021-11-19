classdef CreationDisposition < uint32
    %创建倾向，用作FileAPI.CreateFile的CreationDisposition参数，详见CreateFile文档
    %这些旗帜不能组合使用
    enumeration
		% 创建一个新文件，仅当它不存在时。
		% 如果指定的文件存在，该函数将失败并且最后一个错误代码被设置为 ERROR_FILE_EXISTS (80)。如果指定的文件不存在并且是可写位置的有效路径，则会创建一个新文件。
		CREATE_NEW (1)
		% 总是创建一个新文件。
		% 如果指定的文件存在且可写，则该函数覆盖该文件，该函数成功，并将最后一个错误代码设置为 ERROR_ALREADY_EXISTS (183)。如果指定的文件不存在并且是有效路径，则创建一个新文件，函数成功，并且最后一个错误代码设置为零。
        CREATE_ALWAYS (2)
		% 打开文件或设备，仅当它存在时。
		% 如果指定的文件或设备不存在，该函数将失败并且最后一个错误代码设置为 ERROR_FILE_NOT_FOUND (2)。
        OPEN_EXISTING (3)
		% 总是打开一个文件。
		% 如果指定的文件存在，则函数成功，最后一个错误代码设置为 ERROR_ALREADY_EXISTS (183)。如果指定的文件不存在并且是可写位置的有效路径，则该函数会创建一个文件并将最后一个错误代码设置为零。
        OPEN_ALWAYS (4)
		% 打开一个文件并截断​​它，使其大小为零字节，仅当它存在时。
		% 如果指定的文件不存在，该函数将失败并且最后一个错误代码被设置为 ERROR_FILE_NOT_FOUND (2)。调用进程必须打开文件，并将 GENERIC_WRITE 位设置为 DesiredAccess 参数的一部分。
        TRUNCATE_EXISTING (5)
	end
end