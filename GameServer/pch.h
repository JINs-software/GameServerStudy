#pragma onece

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")		// ����� ����� �� �����ϴ� lib
#else
#pragma comment(lib, "Release\\ServerCore.lib")		// ������ ����� �� �����ϴ� lib
#endif

#include "CorePch.h"