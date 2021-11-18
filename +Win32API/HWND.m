classdef HWND<uint64
	%此类本质上就是uint64，主要用于防止错误的数值作为句柄被意外传入Win32 API，可能造成意外结果。
	%一般不应手动建立此类对象，除非您只是需要一个空句柄作为默认值，此时直接使用WinDef.HWND即可获取空句柄。
	methods
		function obj = HWND(Handle)
			arguments
				Handle=uint64(0);
			end
			obj@uint64(Handle);
			if ~isa(Handle,'uint64')
				error('尝试用非uint64类型的值建立句柄对象');
			end
		end
	end
end