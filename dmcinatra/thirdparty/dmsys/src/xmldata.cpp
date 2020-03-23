#include <sstream>
#include <memory.h>
#include "xmldata.h"

#ifdef WIN32
#include <stdlib.h>
inline long long int strtoll(const char* nptr, char** endptr, int base) {
    return _strtoi64(nptr, endptr, base);
}
inline unsigned long long int strtoull(const char* nptr, char** endptr,
                                       int base) {
    return _strtoui64(nptr, endptr, base);
}
inline long long int strtoq(const char* nptr, char** endptr, int base) {
    return _strtoi64(nptr, endptr, base);
}
inline unsigned long long int strtouq(const char* nptr, char** endptr,
                                      int base) {
    return _strtoui64(nptr, endptr, base);
}
inline long long atoll(const char* nptr) {
    return _atoi64(nptr);
}
#else
#include <stdlib.h>
#endif


CXmlData::CXmlData() {
    m_pBuf    = NULL;
    m_iSize = 0;
    m_iPos    = 0;
}

CXmlData::~CXmlData() {
}

void CXmlData::Prepare(char* pNetDataEx, int iSize) {
    m_pBuf    = pNetDataEx;
    m_iSize    = iSize;
    m_iPos    = 0;
}

void CXmlData::Reset() {
    m_iPos = 0;
}

char* CXmlData::GetData() {
    return m_pBuf;
}

int CXmlData::GetDataLen() {
    return m_iPos;
}

int CXmlData::GetChar(char& data, const std::string& strName, xml_node& oXml) {
    memsetex(data);

    if(m_iPos + (int)sizeof(data) > m_iSize) {
        return -1;
    }

    if (!oXml.empty()) {
        data = oXml.text().as_int();
    }

    m_iPos += sizeof(data);
    return m_iPos;
}

int CXmlData::GetByte(unsigned char& data, const std::string& strName,
                      xml_node& oXml) {
    memsetex(data);

    if(m_iPos + (int)sizeof(data) > m_iSize) {
        return -1;
    }

    if (!oXml.empty()) {
        data = oXml.text().as_int();
    }

    m_iPos += sizeof(data);
    return m_iPos;
}

int CXmlData::GetShort(short& data, const std::string& strName,
                       xml_node& oXml) {
    memsetex(data);

    if(m_iPos + (int)sizeof(data) > m_iSize) {
        return -1;
    }

    if (!oXml.empty()) {
        data = oXml.text().as_int();
    }

    m_iPos += sizeof(data);
    return m_iPos;
}

int CXmlData::GetWord(unsigned short& data, const std::string& strName,
                      xml_node& oXml) {
    memsetex(data);

    if(m_iPos + (int)sizeof(data) > m_iSize) {
        return -1;
    }

    if (!oXml.empty()) {
        data = oXml.text().as_int();
    }

    m_iPos += sizeof(data);
    return m_iPos;
}

int CXmlData::GetInt(int& data, const std::string& strName, xml_node& oXml) {
    memsetex(data);

    if(m_iPos + (int)sizeof(data) > m_iSize) {
        return -1;
    }

    if (!oXml.empty()) {
        data = oXml.text().as_int();
    }

    m_iPos += sizeof(data);
    return m_iPos;
}

int CXmlData::GetDword(unsigned int& data, const std::string& strName,
                       xml_node& oXml) {
    memsetex(data);

    if(m_iPos + (int)sizeof(data) > m_iSize) {
        return -1;
    }

    if (!oXml.empty()) {
        data = oXml.text().as_uint();
    }

    m_iPos += sizeof(data);
    return m_iPos;
}

int CXmlData::GetInt64(long long& data, const std::string& strName,
                       xml_node& oXml) {
    memsetex(data);

    if(m_iPos + (int)sizeof(data) > m_iSize) {
        return -1;
    }

    if (!oXml.empty()) {
        data = oXml.text().as_llong();
    }

    m_iPos += sizeof(data);
    return m_iPos;
}

int CXmlData::GetUint64(unsigned long long& data, const std::string& strName,
                        xml_node& oXml) {
    memsetex(data);

    if(m_iPos + (int)sizeof(data) > m_iSize) {
        return -1;
    }

    if (!oXml.empty()) {
        data = oXml.text().as_ullong();
    }

    m_iPos += sizeof(data);
    return m_iPos;
}

int CXmlData::GetFloat(float& data, const std::string& strName,
                       xml_node& oXml) {
    memsetex(data);

    if(m_iPos + (int)sizeof(data) > m_iSize) {
        return -1;
    }

    if (!oXml.empty()) {
        data = oXml.text().as_float();
    }

    m_iPos += sizeof(data);
    return m_iPos;
}

int CXmlData::GetString(char* data, int nSize, const std::string& strName,
                        xml_node& oXml) {
    memsetex(data);

    if(m_iPos + nSize > m_iSize) {
        return -1;
    }

    int nLen = strlen(oXml.text().as_string());

    if (nLen >= nSize) {
        return -1;
    }

    strcpy(data, oXml.text().as_string());
    m_iPos += nLen;
    return m_iPos;
}

int CXmlData::GetString(std::string& data, int nSize,
                        const std::string& strName, xml_node& oXml) {
    memsetex(data);

    if(m_iPos + nSize > m_iSize) {
        return -1;
    }

    if (!oXml.empty()) {
        data = oXml.text().as_string();
    }

    m_iPos += (int)data.size();
    return m_iPos;
}

int CXmlData::Strnlen(const char* pszString, int nSize) {
    int i;
    const char* ptr = pszString;

    for(i = 0; i < nSize; i++) {
        if('\0' == *ptr) {
            return i;
        }

        ptr++;
    }

    return nSize;
}

const char* CXmlData::GetVersion() {
    return "v1.0.1";
}
