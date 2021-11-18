classdef HANDLE<uint64
	%此类本质上就是uint64，主要用于防止错误的数值作为句柄被意外传入Win32 API，可能造成意外结果。
	%一般不应手动建立此类对象，而应用FileAPI.CreateFile获取
	methods
		function obj = HANDLE(Address)
			arguments
				Address=uint64(0)
			end
			obj@uint64(Address);
			if ~isa(Address,'uint64')
				error('尝试用非uint64类型的值建立句柄对象');
			end
		end
	end
end