classdef CreationDisposition < uint32
    %创建倾向，用作FileAPI.CreateFile的CreationDisposition参数，详见CreateFile文档
    %这些旗帜不能组合使用
    enumeration
        CREATE_NEW (1)
        CREATE_ALWAYS (2)
        OPEN_EXISTING (3)
        OPEN_ALWAYS (4)
        TRUNCATE_EXISTING (5)
	end
end