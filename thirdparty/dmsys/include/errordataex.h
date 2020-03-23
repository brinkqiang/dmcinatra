#ifndef __ERRORDATAEX_H_INCLUDE__
#define __ERRORDATAEX_H_INCLUDE__

#include <string>
#include <sstream>

class IErrorDataEx
{
public:
    virtual ~IErrorDataEx(){}

public:
    inline std::stringstream& LastErrorDataEx()
    {
        return m_sError;
    }

    inline std::string GetLastErrorDataEx()
    {
        return LastErrorDataEx().str();
    }

    inline void ResetLastErrorDataEx()
    {
        m_sError.str("");
        m_sError.clear();
    }

	void operator=(IErrorDataEx& oError)
	{
		m_sError << oError.m_sError.str();
	}

private:
    std::stringstream m_sError;
};

#endif // __ERRORDATAEX_H_INCLUDE__
