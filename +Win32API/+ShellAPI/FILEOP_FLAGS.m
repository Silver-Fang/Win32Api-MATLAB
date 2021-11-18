classdef FILEOP_FLAGS<Win32API.Internal.CombinableFlagU16
	%用作ShellAPI.SHFileOperation的Flags参数，详见SHFileOperation文档
	%可以用按位或（|）组合使用这些旗帜。
	enumeration
		%当且仅当To参数指定了多个目标时才使用该旗帜。To参数只有一个时指定该旗帜可能产生意外结果。
		FOF_MULTIDESTFILES (0x0001) %The pTo member specifies multiple destination files (one for each source file in pFrom) rather than one directory where all source files are to be deposited.
		FOF_CONFIRMMOUSE (0x0002)
		FOF_SILENT (0x0004) % don't display progress UI (confirm prompts may be displayed still)
		%如果目标名称中已存在具有目标名称的文件，则在移动、复制或重命名操作中为正在操作的文件指定新名称。
		FOF_RENAMEONCOLLISION (0x0008) % automatically rename the source files to avoid the collisions
		FOF_NOCONFIRMATION (0x0010) % don't display confirmation UI, assume "yes" for cases that can be bypassed, "no" for those that can not
		%该旗帜必须与FOF_RENAMEONCOLLISION组合使用，可以返回被重命名文件操作前后的文件名映射
		FOF_WANTMAPPINGHANDLE (0x0020) % Fill in SHFILEOPSTRUCT.hNameMappings. Must be freed using SHFreeNameMappings
		%指定该旗帜可以将删除的文件移动到回收站。对于移动和复制操作也支持撤销，但是被覆盖的文件无法恢复。
		FOF_ALLOWUNDO (0x0040) % enable undo including Recycle behavior
		FOF_FILESONLY (0x0080) % only operate on the files (non folders), both files and folders are assumed without this
		FOF_SIMPLEPROGRESS (0x0100) % means don't show names of files
		FOF_NOCONFIRMMKDIR (0x0200) % don't dispplay confirmatino UI before making any needed directories, assume "Yes" in these cases
		FOF_NOERRORUI (0x0400) % don't put up error UI, other UI may be displayed, progress, confirmations
		FOF_NOCOPYSECURITYATTRIBS (0x0800) % dont copy file security attributes (ACLs)
		FOF_NORECURSION (0x1000) % don't recurse into directories for operations that would recurse
		FOF_NO_CONNECTED_ELEMENTS (0x2000) % don't operate on connected elements ("xxx_files" folders that go with .htm files)
		FOF_WANTNUKEWARNING (0x4000) % during delete operation, warn if object is being permanently destroyed instead of recycling (partially overrides FOF_NOCONFIRMATION)
		FOF_NORECURSEREPARSE (0x8000) % deprecated; the operations engine always does the right thing on FolderLink objects (symlinks, reparse points, folder shortcuts)
		FOF_NO_UI (0x0614) % don't display any UI at all
	end
end