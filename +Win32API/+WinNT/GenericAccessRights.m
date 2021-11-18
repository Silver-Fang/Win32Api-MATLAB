classdef GenericAccessRights<Win32API.Internal.CombinableFlagU32
    %通用访问权限，用作FileAPI.CreateFile的DesiredAccess参数。详见 https://docs.microsoft.com/en-us/windows/win32/secauthz/generic-access-rights
    %可以用按位或（|）组合使用这些旗帜。
    enumeration
        GENERIC_READ (0x80000000)
        GENERIC_WRITE (0x40000000)
        GENERIC_EXECUTE (0x20000000)
        GENERIC_ALL (0x10000000)
	end
end