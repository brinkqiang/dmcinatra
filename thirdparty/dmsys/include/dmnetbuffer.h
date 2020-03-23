
#ifndef __DMNETBUFFER_H_INCLUDE__
#define __DMNETBUFFER_H_INCLUDE__

#include "dmtypes.h"
#include <string>

class CDMNetBuffer {
  public:
    CDMNetBuffer(void);
    ~CDMNetBuffer(void);

    bool Init(int32_t nSize);

    bool PushBack(const char* pData, int32_t nLen, int32_t pack = 0);

    bool PopFront(char* pBuf, int32_t nLen);
    bool PopFront(std::string* data, int32_t nLen);
    void DiscardFront(int32_t nLen);

    bool Peek(char* pBuf, int32_t nLen);

    const char* GetHead() {
        return m_pHead;
    }
    const char* GetTail() {
        return m_pTail;
    }
    int32_t GetSize();
  protected:
    char* m_pBuffer;
    char* m_pHead;
    char* m_pTail;
    int32_t m_nSize;
};

#endif // __DMNETBUFFER_H_INCLUDE__
