#ifndef __PROCESS_H__
#define __PROCESS_H__
typedef struct _MODULE_INFO
{
	std::wstring ModuleName;
	PVOID BaseAddress;
	size_t Size;
}MODULE_INFO, *PMODULE_INFO;

typedef struct _PROCESS_INFO
{
	HWND hWnd;
	DWORD ProceeID;
	HANDLE hProcess;
	std::wstring ProcessName;
	PVOID BaseAddress;
	size_t Size;
	std::map<const wchar_t *, MODULE_INFO> moudle_list;

}PROCESS_INFO, *PPROCESS_INFO;

class Process
{
public:
	PROCESS_INFO process_info;

	bool process_hacker(LPCWSTR window_class, LPCWSTR window_name)
	{
		HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
		MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };
		MODULE_INFO module_info;
		this->process_info.hWnd = FindWindow(window_class, window_name);
		if (this->process_info.hWnd == NULL)
		{
			print_string("窗口未找到  Error Code - <%d>", RED, GetLastError());
			return false;
		}
		GetWindowThreadProcessId(this->process_info.hWnd, &this->process_info.ProceeID);
		if (!this->process_info.hWnd)
		{
			print_string("获取进程ID失败 Error Code - <%d>", RED, GetLastError());
			return false;
		}
		this->process_info.hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, this->process_info.ProceeID);
		if (!this->process_info.hWnd)
		{
			print_string("打开进程ID失败 Error Code - <%d>", RED, GetLastError());
			return false;
		}
		
		hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->process_info.ProceeID); 
		if (hModuleSnap == INVALID_HANDLE_VALUE)
		{
			print_string("创建模块快照失败 Error Code - <%d>", RED, GetLastError());
			return false;
		}
		Module32First(hModuleSnap, &me32);
		do {
			module_info.BaseAddress = me32.modBaseAddr;
			module_info.ModuleName = me32.szModule;
			module_info.Size = me32.modBaseSize;
			print_wstring(L"%s %x %d",YELLOW, me32.szModule, me32.modBaseAddr, me32.modBaseSize);
			process_info.moudle_list[me32.szModule] = module_info;
		} while (Module32Next(hModuleSnap, &me32));
		CloseHandle(hModuleSnap);
		/*print_string("process_hacker success!!!");
		print_wstring(L"BaseAddress %x", RED, this->process_info.moudle_list[a].BaseAddress);
		print_wstring(L"ModuleName %s", RED, this->process_info.moudle_list[a].ModuleName);
		print_wstring(L"Size %d", RED, this->process_info.moudle_list[a].Size);*/

		print_string("process_info.moudle_list.size() %d",RED, process_info.moudle_list.size());

		return true;
	}

	std::vector<byte> read_bytes(DWORD_PTR base_address, size_t size)
	{
		byte* buffer = new byte[size];
		std::vector<byte> bytes;
		if (ReadProcessMemory(process_info.hProcess, (LPCVOID)base_address, buffer, size, NULL)) {
			for (size_t i = 0; i < size; i++)
				bytes[i] = buffer[i];
		}
		delete[]buffer;
		return bytes;
	}

	bool write_bytes(DWORD_PTR base_address, std::vector<byte> bytes)
	{
		size_t size = bytes.size();
		byte* buffer = new byte[size];
		bool result = false;
		for (size_t i = 0; i < size; i++)
			buffer[i] = bytes[i];
		result = WriteProcessMemory(process_info.hProcess, (LPVOID)base_address, buffer, size, NULL);
		delete[]buffer;
		return result;
	}

	std::wstring read_wstring(DWORD_PTR base_address, size_t length)
	{
		wchar_t *buffer = new wchar_t[length];
		std::wstring wstr;
		if (ReadProcessMemory(process_info.hProcess, (LPCVOID)base_address, buffer, length, NULL)) {
			wstr.resize(length);
			wstr = buffer;
		}
		delete[] buffer;
		return wstr;
	}

	std::string read_string(DWORD_PTR base_address, size_t length)
	{
		char *buffer = new char[length];
		std::string str;
		if (ReadProcessMemory(process_info.hProcess, (LPCVOID)base_address, buffer, length, NULL)) {
			str.resize(length);
			str = buffer;
		}
		delete[] buffer;
		return str;
	}

	template<typename T>
	T read_memory(DWORD_PTR base_address)
	{
		T value = T();
		ReadProcessMemory(process_info.hProcess, (LPCVOID)base_address, &value, sizeof(T), NULL);
		return value;
	}

	template<typename T>
	bool write_memory(DWORD_PTR base_address, T value)
	{
		return WriteProcessMemory(process_info.hProcess, (LPVOID)base_address, &value, sizeof(T), NULL);
	}

	template<typename T>
	T read_memory_offset(DWORD_PTR base_address, std::vector<DWORD> offset)
	{
		DWORD ofset_address = this->read_memory<DWORD>(base_address);
		T value;
		for (size_t i = 0; i < offset.size(); i++)
		{
			if (ofset_address > 0)
			{
				if ((i + 1) < offset.size())
				{
					ofset_address = this->read_memory<DWORD>(ofset_address + offset[i]);
				}
				else {
					value = this->read_memory<T>(ofset_address + offset[i]);
				}
			}
		}
		return value;
	}

	template<typename T>
	bool write_memory_offset(DWORD_PTR base_address, std::vector<DWORD> offset, T value)
	{
		DWORD ofset_address = this->read_memory<DWORD>(base_address);
		bool result = false;
		for (size_t i = 0; i < offset.size(); i++)
		{
			if (ofset_address)
			{
				if ((i + 1) < offset.size())
				{
					ofset_address = this->read_memory<DWORD>(ofset_address + offset[i]);
				}
				else {
					result = this->write_memory<T>(ofset_address + offset[i], value);
				}
			}
		}
		return result;
	}
};

#endif // !__PROCESS_H__






