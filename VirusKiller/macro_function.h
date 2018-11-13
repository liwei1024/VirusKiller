#pragma once
#define RegHotKey(KeyCode){\
	if(RegisterHotKey(NULL, KeyCode, NULL, KeyCode) == false){\
		if (KeyCode == VK_F1)\
		{\
			printf("F1  ¼üÉèÖÃÊ§°Ü\n"); \
		}\
		else if (KeyCode == VK_F2)\
		{\
			printf("F2  ¼üÉèÖÃÊ§°Ü\n");\
		}\
		else if (KeyCode == VK_F3)\
		{\
			printf("F3  ¼üÉèÖÃÊ§°Ü\n");\
		}\
		else if (KeyCode == VK_F4)\
		{\
			printf("F4  ¼üÉèÖÃÊ§°Ü\n");\
		}\
		else if (KeyCode == VK_F5)\
		{\
			printf("F5  ¼üÉèÖÃÊ§°Ü\n");\
		}\
		else if (KeyCode == VK_F6)\
		{\
			printf("F6  ¼üÉèÖÃÊ§°Ü\n");\
		}\
		else if (KeyCode == VK_F7)\
		{\
			printf("F7  ¼üÉèÖÃÊ§°Ü\n");\
		}\
		else if (KeyCode == VK_F8)\
		{\
			printf("F8  ¼üÉèÖÃÊ§°Ü\n");\
		}\
		else if (KeyCode == VK_F9)\
		{\
			printf("F9  ¼üÉèÖÃÊ§°Ü\n");\
		}\
		else if (KeyCode == VK_F10)\
		{\
			printf("F10 ¼üÉèÖÃÊ§°Ü\n");\
		}\
		else if (KeyCode == VK_F11)\
		{\
			printf("F11 ¼üÉèÖÃÊ§°Ü\n");\
		}\
		else if (KeyCode == VK_F12)\
		{\
			printf("F12 ¼üÉèÖÃÊ§°Ü\n");\
		}\
		else if (KeyCode == VK_HOME)\
		{\
			printf("HOME ¼üÉèÖÃÊ§°Ü\n");\
		}\
		else if (KeyCode == VK_END)\
		{\
			printf("END ¼üÉèÖÃÊ§°Ü\n");\
		}\
	}\
}
#define DelHotKey(KeyCode){GlobalDeleteAtom(KeyCode);}