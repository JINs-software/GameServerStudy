#include "pch.h"
#include <iostream>

// 윈도우즈 버전의 소켓 라이브러리
#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>
// 소켓 정적 라이브러리 링크
#pragma comment(lib, "ws2_32.lib")

int main()
{
    // 1. 윈속 라이브러리 초기화
    // 관련 정보가 wsaData에 채워짐
    WSADATA wsaData;
    if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 0;
    }

    // 2. 소켓 생성
            // ad, type, protocol
            // ad: 주소체계(ipv4/6)
            // type: TCP(SOCK_STREAM), UDP(SOCK_DGRAM)
            // protocol: 0(알아서 설정)
    SOCKET listenSock = ::socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET) {
        int32 errCode = ::WSAGetLastError();
        cout << "Socket Error Code: " << errCode << endl;
        cout << "소켓 생성 에러" << endl;
        return 0;
    }


    // 3. 연결될 주소 (클라가 접근할 주소)
    SOCKADDR_IN localAddr;
    ::memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    // 주소 변환 함수
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 알아서 설정 
    localAddr.sin_port = ::htons(7777);    // 상대쪽 포트번호 (서버에서 연 포트)
    
    //SOCKADDR _localAddr; // SOCKADDR
    //::memset(&_localAddr, 0, sizeof(_localAddr));
    //_localAddr.

    // 4. 소켓 바인딩
    if (::bind(listenSock, (SOCKADDR*)&localAddr, sizeof(localAddr)) == SOCKET_ERROR) {
        int32 errCode = ::WSAGetLastError();
        cout << "Socket Error Code: " << errCode << endl;
        cout << "소켓 바인딩 에러" << endl;
        return 0;
    }

    // 5. Listen 시작
    if (::listen(listenSock, 10)) {
                // 두번째 인자 -> 백로드: 대기열 수
        int32 errCode = ::WSAGetLastError();
        cout << "Socket Error Code: " << errCode << endl;
        cout << "소켓 리슨 에러" << endl;
        return 0;
    }

    //----------------------------------
    // 연결 붙음
    while (true) {
        SOCKADDR_IN clientAddr;
        ::memset(&clientAddr, 0, sizeof(clientAddr));
        int32 addrLen = sizeof(clientAddr);

        SOCKET connSock = ::accept(listenSock, (SOCKADDR*)&clientAddr, &addrLen);

        // 클라 입장
        char ipAddr[16];
        ::inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddr, sizeof(ipAddr));
        cout << "Client Connected IP: " << ipAddr << endl;
    }



    // 소켓 리소스 반환
    ::closesocket(listenSock);
    // 윈속 라이브러리 정리
    ::WSACleanup();
}
