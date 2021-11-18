为MATLAB环境提供方便的Win32 API调用接口

本项目的发布版本号遵循[语义化版本](https://semver.org/lang/zh-CN/)规范。开发者认为这是一个优秀的规范，并向每一位开发者推荐遵守此规范。
# 目录
本包中所有函数均在命名空间+Win32API下，使用前需import。使用命名空间是一个好习惯，可以有效防止命名冲突，避免编码时不必要的代码提示干扰。
```MATLAB
import Win32API.*
```
[CloseHandle](#CloseHandle) 关闭一个打开的对象句柄。

[+FileAPI](#FileAPI)
- [CreateFile](#CreateFile) 创建或打开文件或 I/O 设备。
- [ReadFile](#ReadFile) 从指定的文件或输入/输出 (I/O) 设备读取数据。如果设备支持，读取发生在文件指针指定的位置。
- [SetEndOfFile](#SetEndOfFile) 将指定文件的物理文件大小设置为文件指针的当前位置。
- [SetFilePointer](#SetFilePointer) 移动指定文件的文件指针。
- [WriteFile](#WriteFile) 将数据写入指定的文件或输入/输出 (I/O) 设备。

[+ShellAPI](#ShellAPI)
- [SHFileOperation](#SHFileOperation) 复制、移动、重命名或删除文件系统对象。
# CloseHandle
关闭一个打开的对象句柄。
## 输入参数
Object(:,1)WinNT.HANDLE，必需，打开对象的有效句柄。该参数已向量化，可以同时关闭多个句柄。
## 返回值
Succeed(:,1)logical，关闭是否成功。

ErrorCodes(:,1)SystemErrorCodes，每个句柄返回的错误代码。
# +FileAPI
## CreateFile
创建或打开文件或 I/O 设备。

最常用的 I/O 设备如下：文件、文件流、目录、物理磁盘、卷、控制台缓冲区、磁带驱动器、通信资源、邮槽和管道。该函数返回一个句柄，该句柄可用于根据文件或设备以及指定的标志和属性为各种类型的 I/O 访问文件或设备。
```MATLAB
import Win32API.WinNT.*
[Handles,ErrorCodes1]=Win32API.FileAPI.CreateFile(...
string(1:10),...%在当前文件夹下创建名为1~10的10个文件
GenericAccessRights.GENERIC_READ|GenericAccessRights.GENERIC_WRITE,...%具有读写权限
FileShareMode.FILE_SHARE_READ|FileShareMode.FILE_SHARE_WRITE,...%并且允许后来者读写
0,...%暂不支持设置特殊的安全属性，必须为0
CreationDisposition.OPEN_ALWAYS...%若文件存在，则打开；若不存在，则创建
)%其它参数保持默认
%关闭这些文件
[Succeed,ErrorCodes2]=Win32API.CloseHandle(Handles)
```
使用Win32API相比于内置fopen，可以使用更多Windows平台限定的功能。例如直接设定文件结尾的位置（EOF）以扩展或截断文件，而无需重写整个文件——内置函数则不支持此种操作。
### 必需参数
FileName(:,1)string，要创建或打开的文件或设备的名称。您可以在此名称中使用正斜杠 (/) 或反斜杠 (\\)。该参数已向量化，可以同时打开多个文件。
### 可选参数
DesiredAccess(1,1)WinNT.GenericAccessRights=WinNT.GenericAccessRights.GENERIC_READ|WinNT.GenericAccessRights.GENERIC_WRITE，请求的对文件或设备的访问，可以概括为读、写、两者或两者都不是。

ShareMode(1,1)WinNT.FileShareMode=WinNT.FileShareMode.FILE_SHARE_READ，请求的文件或设备的共享模式，可以是读、写、两者、删除、所有这些或无。对属性或扩展属性的访问请求不受此标志的影响。

SecurityAttributes(1,1)uint64=uint64(0)，指向 SECURITY_ATTRIBUTES 结构的指针，该结构包含两个独立但相关的数据成员：一个可选的安全描述符，以及一个确定返回的句柄是否可以被子进程继承的布尔值。此参数可以为 NULL。如果此参数为 NULL，则 CreateFile 返回的句柄不能由应用程序可能创建的任何子进程继承，并且与返回的句柄关联的文件或设备将获得默认安全描述符。

CreationDisposition(1,1)WinNT.CreationDisposition=WinNT.CreationDisposition.OPEN_ALWAYS，对存在或不存在的文件或设备采取的操作。对于文件以外的设备，此参数通常设置为 OPEN_EXISTING。

FlagsAndAttributes(1,1)WinNT.FlagsAndAttributes=WinNT.FlagsAndAttributes.FILE_ATTRIBUTE_NORMAL，文件或设备属性和标志，FILE_ATTRIBUTE_NORMAL 是文件最常见的默认值。此参数可以包括可用文件属性 (FILE_ATTRIBUTE_*) 的任意组合。所有其他文件属性覆盖 FILE_ATTRIBUTE_NORMAL。此参数还可以包含用于控制文件或设备缓存行为、访问模式和其他特殊用途标志的标志 (FILE_FLAG_) 组合。这些与任何 FILE_ATTRIBUTE_ 值结合。通过指定 SECURITY_SQOS_PRESENT 标志，此参数还可以包含安全服务质量 (SQOS) 信息。

TemplateFile(1,1)WinNT.HANDLE=WinNT.HANDLE(uint64(0))，具有 GENERIC_READ 访问权限的模板文件的有效句柄。模板文件为正在创建的文件提供文件属性和扩展属性。此参数可以为 NULL。打开现有文件时，CreateFile 会忽略此参数。
### 返回值
Handles(:,1)WinNT.HANDLE，打开的文件句柄。文件操作结束后，应当调用CloseHandle关闭这个句柄。如果操作失败，将返回INVALID_HADNLE_VALUE=WinNT.HANDLE(intmax('uint64'))。

ErrorCodes(:,1)SystemErrorCodes，创建每个文件产生的错误代码
### 已知问题
无法对 OneDrive For Business 上已存在的文件执行 具有 GENERIC_ALL 权限的 OPEN_ALWAYS 操作，将返回 ERROR_ACCESS_DENIED 错误
## ReadFile
从指定的文件或输入/输出 (I/O) 设备读取数据。如果设备支持，读取发生在文件指针指定的位置。

不同于内置fread，本函数仅能读出uint8列向量。您可以使用typecast将读入数据转换为其它数据类型。
```MATLAB
import Win32API.FileAPI.*
%假设当前目录存在一个100字节的test.txt文件
Handle=CreateFile('test.txt');
Buffer=ReadFile(Handle,80)
%返回Buffer，一个(80,1)uint8数组，为文件的前80字节
[Buffer,Succeed,ErrorCode]=ReadFile(Handle,80)
%虽然要求读80字节，但是上次读取后文件指针已经移动到80位置，后面只剩20字节可读，返回Buffer长度20。但是函数仍然执行成功且不返回错误代码。
Win32API.CloseHandle(Handle);
```
### 输入参数
File(1,1)WinNT.HANDLE，设备句柄（例如，文件、文件流、物理磁盘、卷、控制台缓冲区、磁带驱动器、套接字、通信资源、邮槽或管道）。 File 参数必须以读取访问权限创建。

NumberOfBytesToRead(1,1)uint32，要读取的最大字节数。
### 返回值
Buffer(:,1)uint8，从文件或设备读取的数据。

Succeed(1,1)logical，函数执行是否成功。

ErrorCode(1,1)SystemErrorCodes，返回的错误代码。
## SetEndOfFile
将指定文件的物理文件大小设置为文件指针的当前位置。

物理文件大小也称为文件结尾。 SetEndOfFile 函数可用于截断或扩展文件。
```MATLAB
import Win32API.FileAPI.*
Handle=CreateFile('test.txt');
SetFilePointer(Handle,100);
SetEndOfFile(Handle);
Win32API.CloseHandle(Handle);
%上述代码创建一个大小为100的文件。该文件的内容未初始化，不一定是全零。
```
该函数为Windows平台限定。相比之下，内置的文件操作函数不支持对文件进行直接截断或扩展，只能通过追加、重写的方式执行，效率低下。
### 输入参数
File(:,1)WinNT.HANDLE，要扩展或截断的文件的句柄。必须使用 GENERIC_WRITE 访问权限创建文件句柄。该参数已向量化，可以同时操作多个文件。
### 返回值
Succeed(:,1)logical，每个文件的操作执行是否成功。

ErrorCode(:,1)SystemErrorCodes，每个文件返回的错误代码
## SetFilePointer
移动指定文件的文件指针。

不能将 SetFilePointer 函数与非搜索设备（如管道或通信设备）的句柄一起使用。

请注意，不同于内置 fseek 函数，将文件指针设置为超出文件末尾的位置并不是错误。在您调用 SetEndOfFile 或 WriteFile 函数之前，文件的大小不会增加。写操作将文件的大小增加到文件指针位置加上写入的缓冲区的大小，中间字节未初始化。

您可以使用 SetFilePointer 来确定文件的长度。为此，请对 MoveMethod 使用 FILE_END 并寻找位置0。返回的文件偏移量是文件的长度。但是，这种做法可能会产生意想不到的副作用，例如无法保存当前文件指针以便程序可以返回到该位置。

作为内置 ftell 函数的对标，您也可以使用 SetFilePointer 查询当前文件指针位置。为此，请指定 FILE_CURRENT 的移动方法和0距离。
```MATLAB
import Win32API.FileAPI.*
import Win32API.MoveMethod
Handle=CreateFile('test.txt');
CurrentPosition=SetFilePointer(Handle)
%上述代码将返回文件指针当前位置
CurrentPosition=SetFilePointer(Handle,0,MoveMethod.FILE_END)
%上述代码将返回文件大小
[CurrentPosition,Succeed,ErrorCode]=SetFilePointer(Handle,-1,MoveMethod.FILE_BEGIN)
%上述操作将失败，因为文件指针移动到了起点之前，返回错误代码
Win32API.CloseHandle(Handle);
```
### 输入参数
File(:,1)WinNT.HANDLE，必需，文件的句柄。必须使用 GENERIC_READ 或 GENERIC_WRITE 访问权限创建文件句柄。该参数已向量化，可以同时操作多个文件。

DistanceToMove(1,1)int64=int64(0)，可选，移动文件指针的字节数。正值将指针在文件中向前移动，负值将文件指针向后移动。

MoveMethod(1,1)MoveMethod=MoveMethod.FILE_CURRENT，可选，文件指针移动的起点。
### 返回值
NewFilePointer(:,1)int64，每个文件移动后的文件指针偏移。

Succeed(:,1)logical，每个文件的操作是否成功。

ErrorCode(:,1)SystemErrorCodes，每个文件返回的错误代码。
## WriteFile
将数据写入指定的文件或输入/输出 (I/O) 设备。

不同于内置fwrite，本函数仅能写入uint8字节数组。
```MATLAB
import Win32API.FileAPI.*
Handle=CreateFile('test.txt');
%向文件写入100个随机字节
WriteFile(Handle,randi([0 255],100,1));
%生成100个随机字节，但只写前50个
[Succeed,NumberOfBytesWritten,ErrorCode]=WriteFile(Handle,randi([0 255],100,1),50)
%randi返回double类型数值，但本函数一律将其转换为uint8类型写入，因此不能用本函数直接写入超过一个字节的非ASCII字符，需要调用方自行获取字符串对应的编码字节流
Win32API.CloseHandle(Handle);
```
### 输入参数
File(1,1)WinNT.HANDLE，必需，文件或 I/O 设备（例如，文件、文件流、物理磁盘、卷、控制台缓冲区、磁带驱动器、套接字、通信资源、邮槽或管道）的句柄。 必须是使用写访问权创建的。

Buffer(:,1)uint8，必需，要写入文件或设备的数据。输入其它类型数值，将被强制转换为uint8类型，可能造成信息丢失。输入非ASCII字符也将被截断成单字节。调用方应当负责用typecast等方法将数据转换为原始字节数组再交给本函数。

NumberOfBytesToWrite(1,1)uint32=uint32(numel(Buffer))，可选，要写入文件或设备的字节数。零值指定空写操作。空写操作的行为取决于底层文件系统或通信技术。
### 返回值
Succeed(1,1)logical，写入操作是否成功。

NumberOfBytesWritten(1,1)uint32，写入的字节数。

ErrorCode(1,1)SystemErrorCodes，返回的错误代码。
# +ShellAPI
## SHFileOperation
复制、移动、重命名或删除文件系统对象。

相比于内置的copyfile、movefile、delete，调用Win32API可以实现更多Windows平台特定的功能。最常用的例子是，指定FOF_MULTIDESTFILES旗帜可以一次性将文件复制、移动到多个不同位置；指定FOF_ALLOWUNDO旗帜，执行操作后可以在Windows文件资源管理器的上下文菜单中撤销操作，删除文件移动到回收站等。
```MATLAB
import Win32API.ShellAPI.*
Flags=FILEOP_FLAGS.FOF_ALLOWUNDO|FILEOP_FLAGS.FOF_MULTIDESTFILES;
%%
%本函数可用两种语法调用。将参数存入一个结构体，或者用名称值参数
FileOp.Func=ShellFileOperations.FO_COPY;
%假设当前目录下存在名为1~10的10个文件
FileOp.From=string(1:10);
%FileOp中未指定的参数也可以用名称值参数补充。FileOp中已经指定的参数，如果在名称值参数中再次指定，将以FileOp中的参数为准。
ErrorCode = SHFileOperation(FileOp,To=string(11:20),Flags=Flags)
%上述操作将会把上述1~10文件复制为11~20
%%
ErrorCode = SHFileOperation(Func=ShellFileOperations.FO_MOVE,From=string(1:10),To=string(11:20),Flags=Flags)
%上述操作将会把文件1~10重命名为11~20。如果文件11~20已经存在，将会弹出对话框，询问用户是否覆盖。注意，被覆盖的文件无法恢复，即使允许撤销也一样。
%%
ErrorCode = SHFileOperation(Func=ShellFileOperations.FO_DELETE,From=string(11:15),Flags=Flags)
%上述操作将文件11~15移动到回收站，可以撤销
%%
ErrorCode = SHFileOperation(Func=ShellFileOperations.FO_RENAME,From='16',To='21')
%上述操作将文件16重命名为21。注意，重命名仅支持字符串标量，但可以使用通配符实现多文件操作。此外也可以使用MOVE实现重命名。
```
### 可选参数
FileOp(1,1)struct，可以以结构体字段的形式指定下述名称值参数。在此结构体中已经指定的参数，将会忽略名称值形式的指定值。
名称值参数

hwnd(1,1)HWND=HWND，对话框的窗口句柄，用于显示有关文件操作状态的信息。通常无需手动指定该参数。

Func(1,1)ShellFileOperations，一个值，指示要执行的操作。

From(:,1)string，一个或多个源文件名。标准的 MS-DOS 通配符，例如“*”，只允许出现在文件名位置。在字符串的其他地方使用通配符将导致不可预测的结果。

To(:,1)string，目标文件或目录名称。不允许使用通配符。它们的使用将导致不可预测的结果。对于删除操作，不得指定该参数。

Flags(1,1)FILEOP_FLAGS=FILEOP_FLAGS.FOF_ALLOWUNDO，控制文件操作的标志。可以使用按位或（|）组合使用多个旗帜。常用组合如FILEOP_FLAGS.FOF_ALLOWUNDO|FILEOP_FLAGS.FOF_MULTIDESTFILES，允许操作后撤销，并且含有多个目标。
### 返回值
ErrorCode(1,1)SystemErrorCode，返回错误代码

AnyOperationsAborted(1,1)logical，如果任何文件操作在完成之前中止，则为 true；否则，为 false。用户可以通过 UI 手动中止操作，或者如果设置了 FOF_NOERRORUI 或 FOF_NOCONFIRMATION 标志，则系统可以静默中止操作。

SHNameMapping(:,1)struct，包含重命名文件的旧名称和新名称的名称映射对象。仅当 Flags 包含 FOF_WANTMAPPINGHANDLE|FOF_RENAMEONCOLLISION 旗帜时才返回此值，否则为空结构体。

ProgressTitle(1,:)char，进度对话框的标题。仅当 Flags 包含 FOF_SIMPLEPROGRESS 旗帜时才返回此值，否则为空字符向量。
### 已知问题
SHNameMapping返回值可能不像文档中解释的那样工作，请务必进行实际测试。