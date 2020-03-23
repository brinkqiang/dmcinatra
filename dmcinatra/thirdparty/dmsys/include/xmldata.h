#ifndef __XMLDATA_H_INCLUDE__
#define __XMLDATA_H_INCLUDE__

#include "pugixml.hpp"

using namespace pugi;

#ifndef DM_INDENT
#define DM_INDENT "\t"
#endif

#ifndef DM_FLAG
#define DM_FLAG (format_raw | format_no_declaration)
#endif

#ifndef DM_ENCODING
#define DM_ENCODING encoding_auto
#endif

//#ifndef DM_INDENT
//#define DM_INDENT "\t"
//#endif
//
//#ifndef DM_FLAG
//#define DM_FLAG   (parse_default | format_no_declaration)
//#endif
//#ifndef DM_ENCODING
//#define DM_ENCODING encoding_auto
//#endif

template<typename T>
inline void memsetex(T& t)
{
    //memset(&t, 0, sizeof(t));
}

class CXmlData
{
public:
    CXmlData();
    virtual ~CXmlData();

    void Prepare(char* pNetDataEx, int iSize);
    void Reset();

    char* GetData();
    int GetDataLen();

    int GetChar(char& data, const std::string& strName, xml_node& oXml);
    int GetByte(unsigned char& data, const std::string& strName, xml_node& oXml);

    int GetShort(short& data, const std::string& strName, xml_node& oXml);
    int GetWord(unsigned short& data, const std::string& strName, xml_node& oXml);

    int GetInt(int& data, const std::string& strName, xml_node& oXml);
    int GetDword(unsigned int& data, const std::string& strName, xml_node& oXml);

    int GetInt64(long long& data, const std::string& strName, xml_node& oXml);
    int GetUint64(unsigned long long& data, const std::string& strName, xml_node& oXml);

    int GetFloat(float& data, const std::string& strName, xml_node& oXml);

    int GetString(char* data, int nSize, const std::string& strName, xml_node& oXml);
    int GetString(std::string& data, int nSize, const std::string& strName, xml_node& oXml);

    int Strnlen(const char* pszString, int nSize);

    const char* GetVersion();

protected:
    char* m_pBuf;
    int m_iSize;
    int m_iPos;
};

#endif // __XMLDATA_H_INCLUDE__

