#pragma once
#define RegHotKey(KeyCode){\
	if(RegisterHotKey(NULL, KeyCode, NULL, KeyCode) == false){\
		if (KeyCode == VK_F1)\
		{\
			printf("F1  ������ʧ��\n"); \
		}\
		else if (KeyCode == VK_F2)\
		{\
			printf("F2  ������ʧ��\n");\
		}\
		else if (KeyCode == VK_F3)\
		{\
			printf("F3  ������ʧ��\n");\
		}\
		else if (KeyCode == VK_F4)\
		{\
			printf("F4  ������ʧ��\n");\
		}\
		else if (KeyCode == VK_F5)\
		{\
			printf("F5  ������ʧ��\n");\
		}\
		else if (KeyCode == VK_F6)\
		{\
			printf("F6  ������ʧ��\n");\
		}\
		else if (KeyCode == VK_F7)\
		{\
			printf("F7  ������ʧ��\n");\
		}\
		else if (KeyCode == VK_F8)\
		{\
			printf("F8  ������ʧ��\n");\
		}\
		else if (KeyCode == VK_F9)\
		{\
			printf("F9  ������ʧ��\n");\
		}\
		else if (KeyCode == VK_F10)\
		{\
			printf("F10 ������ʧ��\n");\
		}\
		else if (KeyCode == VK_F11)\
		{\
			printf("F11 ������ʧ��\n");\
		}\
		else if (KeyCode == VK_F12)\
		{\
			printf("F12 ������ʧ��\n");\
		}\
		else if (KeyCode == VK_HOME)\
		{\
			printf("HOME ������ʧ��\n");\
		}\
		else if (KeyCode == VK_END)\
		{\
			printf("END ������ʧ��\n");\
		}\
	}\
}
#define DelHotKey(KeyCode){GlobalDeleteAtom(KeyCode);}