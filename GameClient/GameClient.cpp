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

    unsigned long temp = 0x12345678;
    // cf) 인텔 시스템, Little Endian: 78 56 34 12


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
    SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        int32 errCode = ::WSAGetLastError();
        cout << "Socket Error Code: " << errCode << endl;
        cout << "소켓 생성 에러" << endl;
        return 0;
    }

    // 3. 연결할 목적지 주소(서버)
    SOCKADDR_IN remoteAddr;
    ::memset(&remoteAddr, 0, sizeof(remoteAddr));
    remoteAddr.sin_family = AF_INET;
                                    // 주소 변환 함수
    // remoteAddr.sin_addr.s_addr = inet_addr("127.0.0.1");    // 4바이트 주소체계
    // 현재 적인 주소체계 입력 함수
    ::inet_pton(AF_INET, "127.0.0.1", &remoteAddr.sin_addr);
    remoteAddr.sin_port = ::htons(7777);    // 상대쪽 포트번호 (서버에서 연 포트)
    /* cf) 엔디안 issue */
    // Little Endian vs Big Endian
    // 네트워크 표준: Big Endian
    // 호스트 표준(케바케): Little Endian(Intel)
    // => htons (host to network short)
    // => htonl (host to network long)

    // 4. 연결
    if (::connect(sock, (sockaddr*)&remoteAddr, sizeof(remoteAddr))) {
        int32 errCode = ::WSAGetLastError();
        cout << "Socket Error Code: " << errCode << endl;
        cout << "소켓 연결 에러" << endl;
        return 0;
    }
    //------------------------------------------
    // 연결 성공
    cout << "Connected To Server!" << endl;




    while (true) {
        ;
    }








    // 소켓 리소스 반환
    ::closesocket(sock);
    // 윈속 라이브러리 정리
    ::WSACleanup();
}

