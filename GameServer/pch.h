#pragma onece

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")		// 디버그 모드일 때 참조하는 lib
#else
#pragma comment(lib, "Release\\ServerCore.lib")		// 릴리즈 모드일 때 참조하는 lib
#endif

#include "CorePch.h"