
#ifndef __DMPACKETPARSER_H_INCLUDE__
#define __DMPACKETPARSER_H_INCLUDE__

#include "dmtypes.h"
#include "dmos.h"
#include "dmsingleton.h"
#include "dmmsgheader.h"

class IDMPacketParser {
  public:
    virtual ~IDMPacketParser(){}
    virtual int32_t DMAPI ParsePacket(const char* pBuf, int32_t nLen) = 0;
    virtual int32_t DMAPI GetPacketHeaderSize() = 0;
};

static inline const char* memnctr(const char* src, size_t len, char flag) {
    for (size_t i=0; i < len; ++i) {
        if (src[i] == flag) {
            return &src[i];
        }
    }

    return NULL;
}

class HPacketParser :
    public IDMPacketParser,
    public TSingleton<HPacketParser> {
    friend class TSingleton<HPacketParser>;
  public:
    virtual int32_t DMAPI ParsePacket(const char* pBuf, int32_t nLen);
    virtual int32_t DMAPI GetPacketHeaderSize();
    int32_t BuildPacketHeader(SPacketHeader* pHeader, uint16_t wDataLen,
                              uint8_t byFlags = 0, uint8_t byOptLen = 0, const uint8_t* pOptData = 0);
    int32_t CheckPacketHeader(SPacketHeader* pHeader);
  private:
    HPacketParser() {}
    virtual ~HPacketParser() {}
};

class HDMPacketParser :
    public IDMPacketParser,
    public TSingleton<HDMPacketParser> {
    friend class TSingleton<HDMPacketParser>;
  public:
    virtual int32_t DMAPI ParsePacket(const char* pBuf, int32_t nLen);
    virtual int32_t DMAPI GetPacketHeaderSize();

    int32_t BuildPacketHeader(SDMPacketHeader* pHeader, int32_t nDataLen);
    int32_t CheckPacketHeader(SDMPacketHeader* pHeader);
  private:
    HDMPacketParser() {}
    virtual ~HDMPacketParser() {}
};

class HNotParser :
    public IDMPacketParser,
    public TSingleton<HNotParser> {
    friend class TSingleton<HNotParser>;
  public:
    virtual int32_t DMAPI ParsePacket(const char* pBuf, int32_t nLen) {
        return nLen;
    }
    virtual int32_t DMAPI GetPacketHeaderSize();
  private:
    HNotParser() {}
    virtual ~HNotParser() {}
};

class HNCParser :
    public IDMPacketParser,
    public TSingleton<HNCParser> {
    friend class TSingleton<HNCParser>;
public:
    virtual int32_t DMAPI ParsePacket(const char* pBuf, int32_t nLen) {
        const char* p = memnctr(pBuf, nLen, '\n');

        if (NULL == p) {
            return 0;
        }

        return (int32_t)(p - pBuf + 1);
    }
    virtual int32_t DMAPI GetPacketHeaderSize() { return 0; }
  private:
    HNCParser() {}
    virtual ~HNCParser() {}
};

typedef std::deque<std::string> DMMESSAGE_QUEUE;

const int  DMSEND_BUF_MAX = 65535;
const int  DMRECV_BUF_MAX = 65535;

#endif // __DMPACKETPARSER_H_INCLUDE__

