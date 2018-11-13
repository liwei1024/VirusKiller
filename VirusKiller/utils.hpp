#pragma once
// ��ӡ�ַ���
static void print_string(
	_In_ const char * format, 
	_In_ WORD color = CYAN,
	_In_ ...
)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	va_list argList;
	char buffer[0x1024];
	va_start(argList, color);
	vsprintf_s(buffer, format, argList);
	std::cout << buffer << std::endl;
	va_end(argList);
}
// ��ӡ���ַ���
static void print_wstring(
	_In_ const wchar_t * format, 
	_In_ WORD color = CYAN,
	_In_ ...
)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	va_list argList;
	wchar_t buffer[0x1024];
	va_start(argList, color);
	vswprintf_s(buffer, format, argList);
	std::wcout.imbue(std::locale("chs"));//��������
	std::wcout << buffer << std::endl;
	va_end(argList);
}
// ���������
static int create_random_number(
	_In_ int min,
	_In_ int max
)
{
	int random_number = 0;
	if (max > min) {
		srand((unsigned)time(NULL));
		random_number = (rand() % (min - max + 1) + max);
	}
	else {
		srand((unsigned)time(NULL));
		random_number = (rand() % (max - min + 1) + min);
	}
	return random_number;
}
// ��ȡʱ���
static DWORD get_time()
{
	return GetTickCount();//�Ӳ���ϵͳ������������elapsed���ĺ����������ķ���ֵ��DWORD��
}
// ���ڳ�ʼ��
static void window_initialize()
{
	RECT rect;
	int cx, cy;
	int width, height;
	cx = GetSystemMetrics(SM_CXFULLSCREEN);
	cy = GetSystemMetrics(SM_CYFULLSCREEN);
	HWND g_self_window_handle = GetConsoleWindow();
	GetWindowRect(g_self_window_handle, &rect);
	MoveWindow(g_self_window_handle, 0, 0, 800, 600, TRUE);
	GetWindowRect(g_self_window_handle, &rect);
	width = (rect.right - rect.left);
	height = (rect.bottom - rect.top);
	MoveWindow(g_self_window_handle, cx - width, cy - height, width, height, TRUE);

	EnableMenuItem(GetSystemMenu(g_self_window_handle, FALSE), SC_CLOSE, MF_GRAYED);

	SetConsoleTitle(_T("VirusKiller"));
	//SetLayeredWindowAttributes(g_self_window_handle, 0, 200, 3);//͸��������
}
// ɾ�������ļ�
static bool delete_self_file()
{
	//VMProtectBeginUltra("ɾ������");
	bool result = true;
	wchar_t FileName[MAX_PATH];
	memset(FileName, 0, MAX_PATH);
	//��ȡ�ļ�·��
	GetModuleFileName(NULL, FileName, MAX_PATH);
	wchar_t *NewFileName;
	NewFileName = new wchar_t[MAX_PATH];
	memset(NewFileName, 0, MAX_PATH);
	//�����ļ�����
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_NORMAL);
	//����ֱ��ɾ��
	if (DeleteFile(FileName))//��ֱ��ɾ�����
	{
		delete[] NewFileName;
		return false;
	}
	//����APIһ�������ن���
	wsprintf(NewFileName, _T("C:\\Windows\\%C\0"), FileName[0]);
	CreateDirectory(NewFileName, NULL);
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_HIDDEN);
	wsprintf(NewFileName, _T("C:\\Windows ����������\0"), FileName[0], GetTickCount());
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_NORMAL);
	DeleteFile(NewFileName);
	if (!MoveFileEx(FileName, NewFileName, MOVEFILE_REPLACE_EXISTING))
	{
		delete[] NewFileName;
		//printf("ɾ������ʧ�� Error Code\n");
		return false;//�����˾ͷ���
	}
	MoveFileEx(NewFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
	delete[] NewFileName;
	if (result == false)
	{
		printf("ɾ������ʧ�� Error Code\n");
		system("pause");
		exit(0);
	}
	//VMProtectEnd();
	return result;
}
// ��Զ��callת���ֽڼ�
static std::vector<byte> get_call_bytes(
	_In_ LPVOID call_address
)
{
	size_t call_size = 0;
	std::vector<byte> call_bytes;
	while (true)
	{
		if (
			*(byte*)((DWORD_PTR)call_address + (call_size + 0)) == 0xcc &&
			*(byte*)((DWORD_PTR)call_address + (call_size + 1)) == 0xcc &&
			*(byte*)((DWORD_PTR)call_address + (call_size + 2)) == 0xcc &&
			*(byte*)((DWORD_PTR)call_address + (call_size + 3)) == 0xcc &&
			*(byte*)((DWORD_PTR)call_address + (call_size + 4)) == 0xcc)
		{
			break;
		}
		else {
			call_bytes[call_size] = *(byte*)((DWORD_PTR)call_address + call_size);
		}
		call_size++;
	}
}

