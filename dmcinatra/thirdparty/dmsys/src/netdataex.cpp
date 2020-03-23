
#include "netdataex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include   <sys/socket.h>
#include   <netinet/in.h>
#include   <arpa/inet.h>
#endif

inline unsigned long long __htonll(unsigned long long number) {
    return ( htonl( (unsigned long)((number >> 32) & 0xFFFFFFFF)) |
             ((unsigned long long) (htonl((unsigned long)(number & 0xFFFFFFFF)))  << 32));
}

inline unsigned long long __ntohll(unsigned long long number) {
    return ( ntohl( (unsigned long)((number >> 32) & 0xFFFFFFFF) ) |
             ((unsigned long long) (ntohl((unsigned long)(number & 0xFFFFFFFF)))  << 32));
}

CNetDataEx::CNetDataEx() {
    m_pBuf      = NULL;
    m_iSize     = 0;
    m_iPos      = 0;
}

CNetDataEx::~CNetDataEx() {
}

void CNetDataEx::Prepare(char* pNetDataEx, int iSize) {
    m_pBuf      = pNetDataEx;
    m_iSize     = iSize;
    m_iPos      = 0;
}

void CNetDataEx::Reset() {
    m_iPos      = 0;
}

int CNetDataEx::AddByte(unsigned char byByte, const char* pKey) {
    if(m_iPos + (int)sizeof(byByte) > m_iSize) {
        return -1;
    }

    *(unsigned char*)(m_pBuf + m_iPos) = byByte;
    m_iPos += sizeof(byByte);

    return m_iPos;
}

int CNetDataEx::DelByte(unsigned char& byByte, const char* pKey) {
    if(m_iPos + (int)sizeof(byByte) > m_iSize) {
        return -1;
    }

    byByte = *(unsigned char*)(m_pBuf + m_iPos);
    m_iPos += sizeof(byByte);

    return m_iPos;
    return -1;
}

int CNetDataEx::AddChar(char chChar, const char* pKey) {
    if(m_iPos + (int)sizeof(chChar) > m_iSize) {
        return -1;
    }

    *(char*)(m_pBuf + m_iPos) = chChar;
    m_iPos += sizeof(chChar);

    return m_iPos;
}

int CNetDataEx::DelChar(char& chChar, const char* pKey) {
    if(m_iPos + (int)sizeof(chChar) > m_iSize) {
        return -1;
    }

    chChar = *(char*)(m_pBuf + m_iPos);
    m_iPos += sizeof(chChar);

    return m_iPos;
}

int CNetDataEx::AddWord(unsigned short wWord, const char* pKey) {
    if(m_iPos + (int)sizeof(wWord) > m_iSize) {
        return -1;
    }

    *(unsigned short*)(m_pBuf + m_iPos) = htons(wWord);
    m_iPos += sizeof(wWord);

    return m_iPos;
}

int CNetDataEx::DelWord(unsigned short& wWord, const char* pKey) {
    if(m_iPos + (int)sizeof(wWord) > m_iSize) {
        return -1;
    }

    wWord = ntohs(*(unsigned short*)(m_pBuf + m_iPos));
    m_iPos += sizeof(wWord);

    return m_iPos;
}

int CNetDataEx::AddShort(short shShort, const char* pKey) {
    if(m_iPos + (int)sizeof(shShort) > m_iSize) {
        return -1;
    }

    *(short*)(m_pBuf + m_iPos) = htons(shShort);
    m_iPos += sizeof(shShort);

    return m_iPos;
}

int CNetDataEx::DelShort(short& shShort, const char* pKey) {
    if(m_iPos + (int)sizeof(shShort) > m_iSize) {
        return -1;
    }

    shShort = ntohs(*(short*)(m_pBuf + m_iPos));
    m_iPos += sizeof(shShort);

    return m_iPos;
}

int CNetDataEx::AddDword(unsigned int dwDword, const char* pKey) {
    if(m_iPos + (int)sizeof(dwDword) > m_iSize) {
        return -1;
    }

    *(unsigned int*)(m_pBuf + m_iPos) = htonl(dwDword);
    m_iPos += sizeof(dwDword);

    return m_iPos;
}

int CNetDataEx::DelDword(unsigned int& dwDword, const char* pKey) {
    if(m_iPos + (int)sizeof(dwDword) > m_iSize) {
        return -1;
    }

    dwDword = ntohl(*(unsigned int*)(m_pBuf + m_iPos));
    m_iPos += sizeof(dwDword);

    return m_iPos;
}

int CNetDataEx::AddInt(int nInt, const char* pKey) {
    if(m_iPos + (int)sizeof(nInt) > m_iSize) {
        return -1;
    }

    *(int*)(m_pBuf + m_iPos) = htonl(nInt);
    m_iPos += sizeof(nInt);

    return m_iPos;
}

int CNetDataEx::DelInt(int& nInt, const char* pKey) {
    if(m_iPos + (int)sizeof(nInt) > m_iSize) {
        return -1;
    }

    nInt = ntohl(*(int*)(m_pBuf + m_iPos));
    m_iPos += sizeof(nInt);

    return m_iPos;
}

int CNetDataEx::AddUint64(unsigned long long qwUint64, const char* pKey) {
    if(m_iPos + (int)sizeof(qwUint64) > m_iSize) {
        return -1;
    }

    *(unsigned long long*)(m_pBuf + m_iPos) = __htonll(qwUint64);
    m_iPos += sizeof(qwUint64);

    return m_iPos;
}

int CNetDataEx::DelUint64(unsigned long long& qwUint64, const char* pKey) {
    if(m_iPos + (int)sizeof(qwUint64) > m_iSize) {
        return -1;
    }

    qwUint64 = __ntohll(*(unsigned long long*)(m_pBuf + m_iPos));
    m_iPos += sizeof(qwUint64);

    return m_iPos;
}

int CNetDataEx::AddInt64(long long llInt64, const char* pKey) {
    if(m_iPos + (int)sizeof(llInt64) > m_iSize) {
        return -1;
    }

    *(long long*)(m_pBuf + m_iPos) = __htonll(llInt64);
    m_iPos += sizeof(llInt64);

    return m_iPos;
}

int CNetDataEx::DelInt64(long long& llInt64, const char* pKey) {
    if(m_iPos + (int)sizeof(llInt64) > m_iSize) {
        return -1;
    }

    llInt64 = __ntohll(*(long long*)(m_pBuf + m_iPos));
    m_iPos += sizeof(llInt64);

    return m_iPos;
}

int CNetDataEx::AddFloat(float fFloat, const char* pKey) {
    if(m_iPos + (int)sizeof(fFloat) > m_iSize) {
        return -1;
    }

    *(float*)(m_pBuf + m_iPos) = fFloat;
    m_iPos += sizeof(fFloat);

    return m_iPos;
}

int CNetDataEx::DelFloat(float& fFloat, const char* pKey) {
    if(m_iPos + (int)sizeof(fFloat) > m_iSize) {
        return -1;
    }

    fFloat = (*(float*)(m_pBuf + m_iPos));
    m_iPos += sizeof(fFloat);

    return m_iPos;
}

int CNetDataEx::AddBlob( const void* pBlob, int iSize, const char* pKey) {
    if(iSize <= 0 || NULL == pBlob) {
        return 0;
    }

    if (m_iPos + iSize > m_iSize) {
        return -1;
    }

    memcpy(m_pBuf + m_iPos, pBlob, iSize);
    m_iPos += sizeof(iSize);

    return m_iPos;
}

int CNetDataEx::DelBlob( void* pOut, int iSize, const char* pKey) {
    if(iSize <= 0 || NULL == pOut) {
        return 0;
    }

    if (m_iPos + iSize > m_iSize) {
        return -1;
    }

    memcpy(pOut, m_pBuf + m_iPos, iSize);
    m_iPos += sizeof(iSize);
    return m_iPos;
}

int CNetDataEx::AddString(const char* pszString, int iSize, const char* pKey) {
    int iLen = Strnlen(pszString, iSize-1);

    if(m_iPos + (int)sizeof(unsigned short) + iLen > m_iSize) {
        return -1;
    }

    if(-1 == AddWord(iLen)) {
        return -1;
    }

    memcpy(m_pBuf + m_iPos, pszString, iLen);
    m_iPos += iLen;

    return m_iPos;
}

int CNetDataEx::DelString(char* pszOut, int iSize, const char* pKey) {
    unsigned short wLen = 0;

    if(-1 == DelWord(wLen)) {
        return -1;
    }

    if(m_iPos + (int)wLen > m_iSize) {
        return -1;
    }

    if( int(wLen + 1) > iSize ) {
        return -1;
    }

    memcpy(pszOut, m_pBuf+m_iPos, wLen);
    pszOut[wLen] = '\0';
    m_iPos += wLen;

    return m_iPos;
}

int CNetDataEx::Strnlen(const char* pszString, int iSize, const char* pKey) {
    int i;
    const char* ptr = pszString;

    for(i = 0; i < iSize; i++) {
        if('\0' == *ptr) {
            return i;
        }

        ptr++;
    }

    return iSize;
}
