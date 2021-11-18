classdef FileShareMode<Win32API.Internal.CombinableFlagU32
    %文件共享模式，用作FileAPI.CreateFile的DesiredMode参数，详见CreateFile文档
    %可以用按位或（|）组合使用这些旗帜。
    enumeration
        FILE_SHARE_NONE(0x00000000)
        FILE_SHARE_READ(0x00000001)
        FILE_SHARE_WRITE(0x00000002)
        FILE_SHARE_DELETE(0x00000004)
	end
end