#include <stdio.h>
#include <string.h>
#include "dmnetbuffer.h"


CDMNetBuffer::CDMNetBuffer(void) {
    m_pBuffer = NULL;
    m_pHead = NULL;
    m_pTail = NULL;
    m_nSize = 0;
}

CDMNetBuffer::~CDMNetBuffer(void) {
    if (m_pBuffer != NULL) {
        delete m_pBuffer;
    }
}

bool CDMNetBuffer::Init(int32_t nSize) {
    m_pBuffer = new char[nSize];

    if (NULL == m_pBuffer) {
        return false;
    }

    m_pHead = m_pBuffer;
    m_pTail = m_pBuffer;
    m_nSize = nSize;

    return true;
}

bool CDMNetBuffer::PushBack(const char* pData, int32_t nLen, int32_t pack) {
    int32_t nDist = (int32_t)(m_pTail + (uint32_t)m_nSize - m_pHead);
    int32_t nUsed = nDist >= m_nSize ? (nDist - m_nSize) : nDist;

    if (nLen + nUsed + 1 > m_nSize) {
        return false;
    }

    if (m_pTail + nLen >= m_pBuffer + m_nSize) {
        int32_t nSeg1 = (int32_t)(m_pBuffer + m_nSize - m_pTail);
        int32_t nSeg2 = nLen - nSeg1;
        memmove(m_pTail, pData, nSeg1);
        memmove(m_pBuffer, pData + nSeg1, nSeg2);
        m_pTail = m_pBuffer + nSeg2;
    }
    else {
        memmove(m_pTail, pData, nLen);
        m_pTail += nLen;
    }

    return true;
}

bool CDMNetBuffer::PopFront(char* pBuf, int32_t nLen) {
    int32_t nDist = (int32_t)(m_pTail + (uint32_t)m_nSize - m_pHead);
    int32_t nUsed = nDist >= m_nSize ? (nDist - m_nSize) : nDist;

    if (nLen > nUsed) {
        return false;
    }

    if (m_pHead + nLen >= m_pBuffer + m_nSize) {
        int32_t nSeg1 = (int32_t)(m_pBuffer + m_nSize - m_pHead);
        int32_t nSeg2 = nLen - nSeg1;
        memmove(pBuf, m_pHead, nSeg1);
        memmove(pBuf + nSeg1, m_pBuffer, nSeg2);
        m_pHead = m_pBuffer + nSeg2;
    }
    else {
        memmove(pBuf, m_pHead, nLen);
        m_pHead += nLen;
    }

    return true;
}

bool CDMNetBuffer::PopFront(std::string * data, int32_t nLen)
{
    int32_t nDist = (int32_t)(m_pTail + (uint32_t)m_nSize - m_pHead);
    int32_t nUsed = nDist >= m_nSize ? (nDist - m_nSize) : nDist;

    if (nLen > nUsed) {
        return false;
    }

    if (m_pHead + nLen >= m_pBuffer + m_nSize) {
        int32_t nSeg1 = (int32_t)(m_pBuffer + m_nSize - m_pHead);
        int32_t nSeg2 = nLen - nSeg1;
        data->append(m_pHead, nSeg1);
        //memcpy(pBuf, m_pHead, nSeg1);
        data->append(m_pBuffer, nSeg2);
        //memcpy(pBuf + nSeg1, m_pBuffer, nSeg2);
        m_pHead = m_pBuffer + nSeg2;
    }
    else {
        data->append(m_pHead, nLen);
        //memcpy(pBuf, m_pHead, nLen);
        m_pHead += nLen;
    }

    return true;
}

void CDMNetBuffer::DiscardFront(int32_t nLen) {
    int32_t nDist = (int32_t)(m_pTail + (uint32_t)m_nSize - m_pHead);
    int32_t nUsed = nDist >= m_nSize ? (nDist - m_nSize) : nDist;

    if (nLen > nUsed) {
        return;
    }

    if (m_pHead + nLen >= m_pBuffer + m_nSize) {
        int32_t nSeg1 = (int32_t)(m_pBuffer + m_nSize - m_pHead);
        int32_t nSeg2 = nLen - nSeg1;
        m_pHead = m_pBuffer + nSeg2;
    }
    else {
        m_pHead += nLen;
    }
}

bool CDMNetBuffer::Peek(char* pBuf, int32_t nLen)
{
    int32_t nDist = (int32_t)(m_pTail + (uint32_t)m_nSize - m_pHead);
    int32_t nUsed = nDist >= m_nSize ? (nDist - m_nSize) : nDist;

    if (nLen > nUsed) {
        return false;
    }

    if (m_pHead + nLen >= m_pBuffer + m_nSize) {
        int32_t nSeg1 = (int32_t)(m_pBuffer + m_nSize - m_pHead);
        int32_t nSeg2 = nLen - nSeg1;
        memmove(pBuf, m_pHead, nSeg1);
        memmove(pBuf + nSeg1, m_pBuffer, nSeg2);
    }
    else {
        memmove(pBuf, m_pHead, nLen);
    }

    return true;
}

int32_t CDMNetBuffer::GetSize() {
    int32_t nDist = (int32_t)(m_pTail + (uint32_t)m_nSize - m_pHead);
    int32_t nUsed = nDist >= m_nSize ? (nDist - m_nSize) : nDist;

    return nUsed;
}
