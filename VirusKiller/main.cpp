// VirusKiller.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

// 热键响应
VOID Keypress(MSG *msg)
{
	switch (msg->wParam)
	{
	case VK_F1:
		/*printf("VK_F1\n");*/
		print_wstring(process.read_wstring(0x0093B018, 100).c_str());
		break;
	case VK_F2:
		print_string(process.read_string(0x0093B018, 100).c_str());
		//printf("VK_F2\n");
		break;
	case VK_F3:
		printf("VK_F3\n");
		break;
	case VK_F4:
		printf("VK_F4\n");
		break;
	case VK_F5:
		printf("VK_F5\n");
		break;
	case VK_F6:
		printf("VK_F6\n");
	case VK_F7:
		printf("VK_F7\n");
		break;
	case VK_F8:
		printf("VK_F8\n");
		break;
	case VK_F9:
		printf("VK_F9\n");
		break;
	case VK_F10:
		printf("VK_F10\n");
		break;
	case VK_F11:
		printf("VK_F11\n");
		break;
	case VK_F12:
		printf("VK_F12\n");
		break;
	case VK_HOME:
		//printf("VK_HOME\n");
		process.process_hacker(L"YodaoMainWndClass",L"网易有道词典");
		break;
	case VK_END:
		// 删除热键
		DelHotKey(VK_F1);
		DelHotKey(VK_F2);
		DelHotKey(VK_F3);
		DelHotKey(VK_F4);
		DelHotKey(VK_F5);
		DelHotKey(VK_F6);
		DelHotKey(VK_F7);
		DelHotKey(VK_F8);
		DelHotKey(VK_F9);
		DelHotKey(VK_F10);
		DelHotKey(VK_F11);
		DelHotKey(VK_F12);
		DelHotKey(VK_HOME);
		DelHotKey(VK_END);

		exit(0);
		break;
	default:
		break;
	}
}

// 
void ThreadMessage(MSG *msg)
{

}

int main()
{
	window_initialize();
	// 关闭窗口关闭按钮
	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_GRAYED);
	// 注册热键
	RegHotKey(VK_F1);
	RegHotKey(VK_F2);
	RegHotKey(VK_F3);
	RegHotKey(VK_F4);
	RegHotKey(VK_F5);
	RegHotKey(VK_F6);
	RegHotKey(VK_F7);
	RegHotKey(VK_F8);
	RegHotKey(VK_F9);
	RegHotKey(VK_F10);
	RegHotKey(VK_F11);
	RegHotKey(VK_F12);
	RegHotKey(VK_HOME);
	RegHotKey(VK_END);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		switch (msg.message)
		{
		case WM_HOTKEY:
			Keypress(&msg);
			break;
		case MY_MESSAGE_ID:
			ThreadMessage(&msg);
			break;
		default:
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

