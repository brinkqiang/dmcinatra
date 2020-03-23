#ifndef __DMERRORDATA_H_INCLUDE__
#define __DMERRORDATA_H_INCLUDE__

#include <string>
#include <sstream>
#include <iostream>

class IDMErrorData
{
public:
    virtual ~IDMErrorData(){}

public:
    inline std::stringstream& LastErrorData()
    {
        return m_sError;
    }

    inline std::string GetLastErrorData()
    {
        return LastErrorData().str();
    }

    inline void ResetLastErrorData()
    {
        m_sError.str("");
        m_sError.clear();
    }

	void operator=(IDMErrorData& oError)
	{
		m_sError << oError.m_sError.str();
	}

    virtual void OnError(const std::string& strError)
    {
        std::cout << strError << std::endl;
    }

    virtual std::string GetPath()
    {
        return std::string();
    }
    virtual std::string GetTplPath()
    {
        return std::string();
    }

private:
    std::stringstream m_sError;
};

#endif // __DMERRORDATA_H_INCLUDE__
