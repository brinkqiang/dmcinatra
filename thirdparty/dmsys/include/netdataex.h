#ifndef __NETDATAEX_H_INCLUDE__
#define __NETDATAEX_H_INCLUDE__

#include <bitset>

template<size_t _Bits>
struct Bits
{
    enum { bits = _Bits};
};

template<size_t _Bits>
class CNetDataOpt
{
    typedef Bits<_Bits> BITS;
public:
    bool Has(size_t pos){ return m_bitset.test(pos); }
    void Set(size_t pos){ m_bitset.set(pos); }
    void UnSet(size_t pos){ m_bitset.reset(pos); }
    void Set(){ m_bitset.set(); }
    void UnSet(){ m_bitset.reset(); }
    void* GetOpt(){ return &m_bitset; }
    size_t GetOptSize(){ return sizeof(m_bitset); }
private:
    std::bitset<BITS::bits> m_bitset;
};

template<>
class CNetDataOpt<0>
{
public:
    bool Has(size_t pos){ return true; }
    void Set(size_t pos){}
    void UnSet(size_t pos){}
    void Set(){}
    void UnSet(){}
    void* GetOpt(){ return NULL; }
    size_t GetOptSize(){ return 0; }
};

class INetDataEx
{
public:
    virtual ~INetDataEx() = 0;

    virtual void Prepare(char* pNetDataEx, int iSize) = 0;
    virtual void Reset() = 0;

    virtual char* GetData() = 0;
    virtual int GetDataLen() = 0;

    virtual int AddByte(unsigned char byByte, const char* pKey) = 0;
    virtual int DelByte(unsigned char& byByte, const char* pKey) = 0;

    virtual int AddChar(char chChar, const char* pKey) = 0;
    virtual int DelChar(char& chChar, const char* pKey) = 0;

    virtual int AddWord(unsigned short wWord, const char* pKey) = 0;
    virtual int DelWord(unsigned short& wWord, const char* pKey) = 0;

    virtual int AddShort(short shShort, const char* pKey) = 0;
    virtual int DelShort(short& shShort, const char* pKey) = 0;

    virtual int AddDword(unsigned int dwDword, const char* pKey) = 0;
    virtual int DelDword(unsigned int& dwDword, const char* pKey) = 0;

    virtual int AddInt(int nInt, const char* pKey) = 0;
    virtual int DelInt(int& nInt, const char* pKey) = 0;

    virtual int AddUint64(unsigned long long qwUint64, const char* pKey) = 0;
    virtual int DelUint64(unsigned long long& qwUint64, const char* pKey) = 0;

    virtual int AddInt64(long long llInt64, const char* pKey) = 0;
    virtual int DelInt64(long long& llInt64, const char* pKey) = 0;

    virtual int AddFloat(float fFloat, const char* pKey) = 0;
    virtual int DelFloat(float& fFloat, const char* pKey) = 0;

    virtual int AddBlob(const void* pBlob, int iSize, const char* pKey) = 0;
    virtual int DelBlob(void* pOut, int iSize, const char* pKey) = 0;

    virtual int AddString(const char* pszString, int iSize, const char* pKey) = 0;
    virtual int DelString(char* pszOut, int iSize, const char* pKey) = 0;

    virtual int Strnlen(const char* pszString, int iSize, const char* pKey) = 0;
};

inline INetDataEx::~INetDataEx()
{

}

class CNetDataEx : public INetDataEx
{
public:
    CNetDataEx();
    virtual ~CNetDataEx();

    void Prepare(char* pNetDataEx, int iSize);
    void Reset();

    char* GetData(){ return m_pBuf; }
    int GetDataLen(){ return m_iPos; }

    int AddByte(unsigned char byByte, const char* pKey = "");
    int DelByte(unsigned char& byByte, const char* pKey = "");

    int AddChar(char chChar, const char* pKey = "");
    int DelChar(char& chChar, const char* pKey = "");

    int AddWord(unsigned short wWord, const char* pKey = "");
    int DelWord(unsigned short& wWord, const char* pKey = "");

    int AddShort(short shShort, const char* pKey = "");
    int DelShort(short& shShort, const char* pKey = "");

    int AddDword(unsigned int dwDword, const char* pKey = "");
    int DelDword(unsigned int& dwDword, const char* pKey = "");

    int AddInt(int nInt, const char* pKey = "");
    int DelInt(int& nInt, const char* pKey = "");

    int AddUint64(unsigned long long qwUint64, const char* pKey = "");
    int DelUint64(unsigned long long& qwUint64, const char* pKey = "");

    int AddInt64(long long llInt64, const char* pKey = "");
    int DelInt64(long long& llInt64, const char* pKey = "");

    int AddFloat(float fFloat, const char* pKey = "");
    int DelFloat(float& fFloat, const char* pKey = "");

    int AddBlob(const void* pBlob, int iSize, const char* pKey = "");
    int DelBlob(void* pOut, int iSize, const char* pKey = "");

    int AddString(const char* pszString, int iSize, const char* pKey = "");
    int DelString(char* pszOut, int iSize, const char* pKey = "");

    int Strnlen(const char* pszString, int iSize, const char* pKey = "");

protected:
    char* m_pBuf;
    int m_iSize;
    int m_iPos;
};

#endif // __NETDATAEX_H_INCLUDE__


