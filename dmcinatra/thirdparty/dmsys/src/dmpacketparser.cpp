
#include "dmpacketparser.h"
#include <memory.h>

int32_t DMAPI HPacketParser::ParsePacket( const char* pBuf, int32_t nLen ) {
    if (nLen < sizeof(SPacketHeader)) {
        return 0;
    }

    SPacketHeader* pHeader = (SPacketHeader*)pBuf;

    int32_t nPacketLen = CheckPacketHeader(pHeader);

    if (nPacketLen < 0) {
        return -1;
    }

    if (nPacketLen <= nLen) {
        return nPacketLen;
    }

    return 0;
}

int32_t DMAPI HPacketParser::GetPacketHeaderSize()
{
    return sizeof(SPacketHeader);
}

int32_t HPacketParser::BuildPacketHeader( SPacketHeader* pHeader,
        uint16_t wDataLen, uint8_t byFlags /*= 0*/, uint8_t byOptLen /*= 0*/,
        const uint8_t* pOptData) {

    pHeader->wCheckSum = ((wDataLen ^ PACKET_CHECKSUM1) & PACKET_CHECKSUM2);
    pHeader->wMark = PACKET_MARK;
    pHeader->wDataLen = wDataLen;
    pHeader->byFlags = byFlags;
    pHeader->byOptLen = byOptLen;

    if (byOptLen != 0) {
        memcpy(pHeader + sizeof(byOptLen), pOptData, byOptLen);
    }

    pHeader->wMark = htons(pHeader->wMark);
    pHeader->wDataLen = htons(pHeader->wDataLen);
    pHeader->wCheckSum = htons(pHeader->wCheckSum);

    return sizeof(*pHeader) + byOptLen;
}

int32_t HPacketParser::CheckPacketHeader( SPacketHeader* pHeader ) {

    pHeader->wMark = ntohs(pHeader->wMark);
    pHeader->wDataLen = ntohs(pHeader->wDataLen);
    pHeader->wCheckSum = ntohs(pHeader->wCheckSum);

    if (PACKET_MARK != pHeader->wMark) {
        return -1;
    }

    uint16_t wCheckSum = ((pHeader->wDataLen ^ PACKET_CHECKSUM1) &
                          PACKET_CHECKSUM2);

    if (wCheckSum != pHeader->wCheckSum) {
        return -1;
    }

    return sizeof(*pHeader) + pHeader->wDataLen + pHeader->byOptLen;
}

int32_t DMAPI HDMPacketParser::ParsePacket(const char* pBuf, int32_t nLen) {
    if (nLen < GetPacketHeaderSize()) {
        return 0;
    }

    SDMPacketHeader* pHeader = (SDMPacketHeader*)pBuf;

    int32_t nPacketLen = CheckPacketHeader(pHeader);

    if (nPacketLen < 0) {
        return nPacketLen;
    }

    if (nPacketLen <= nLen) {
        return nPacketLen;
    }

    return 0;
}

int32_t DMAPI HDMPacketParser::GetPacketHeaderSize()
{
    return sizeof(SDMPacketHeader);
}

int32_t HDMPacketParser::BuildPacketHeader(SDMPacketHeader* pHeader,
        int32_t nDataLen) {
    pHeader->wMark = PACKET_MARK;
    pHeader->nDataLen = nDataLen;
    pHeader->wCheckSum = ((nDataLen ^ PACKET_CHECKSUM1) & PACKET_CHECKSUM2);

    pHeader->wMark = htons(pHeader->wMark);
    pHeader->nDataLen = htonl(pHeader->nDataLen);
    pHeader->wCheckSum = htons(pHeader->wCheckSum);

    return sizeof(*pHeader);
}

int32_t HDMPacketParser::CheckPacketHeader(SDMPacketHeader* pHeader) {

    pHeader->wMark = ntohs(pHeader->wMark);
    pHeader->nDataLen = ntohl(pHeader->nDataLen);
    pHeader->wCheckSum = htons(pHeader->wCheckSum);

    if (PACKET_MARK != pHeader->wMark) {
        return -1000;
    }

    uint16_t wCheckSum = ((pHeader->nDataLen ^ PACKET_CHECKSUM1) &
                           PACKET_CHECKSUM2);

    if (wCheckSum != pHeader->wCheckSum) {
        return -1001;
    }

    return sizeof(*pHeader) + pHeader->nDataLen;
}

int32_t DMAPI HNotParser::GetPacketHeaderSize()
{
    return 0;
}
