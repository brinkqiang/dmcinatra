
#ifndef __DMLOAD_H_INCLUDE__
#define __DMLOAD_H_INCLUDE__

#include "dmutil.h"

template<typename T>
class CDMLoadImpl : public T {
  public:
    CDMLoadImpl() {}
    virtual ~CDMLoadImpl() {}

    bool LoadXMLFile() {
        OnLoadXMLBegin();
        bool bRet = T::LoadXML(DMGetRootPath());

        if (!bRet) {
            OnLoadXMLEnd();
        }

        return bRet;
    }

    bool LoadCSVFile() {
        OnLoadCSVBegin();
        bool bRet = T::LoadCSV(DMGetRootPath());

        if (!bRet) {
            OnLoadCSVEnd();
        }

        return bRet;
    }

    bool SaveCSVFile() {
        return T::SaveCSV(DMGetRootPath());
    }

    bool SaveXMLFile() {
        return T::SaveXML(DMGetRootPath());
    }

    bool LoadFile() {
        return LoadCSVFile() && LoadXMLFile();
    }

    bool LoadFrom(T& config) {
        std::stringstream ss;
        config.GetXMLDoc(ss);

        return T::SetXMLDoc(ss.str());
    }

    virtual void OnLoadXMLBegin() {}
    virtual void OnLoadXMLEnd() {}

    virtual void OnLoadCSVBegin() {}
    virtual void OnLoadCSVEnd() {}

    virtual void OnError( const std::string& strError ) {
        std::cout << strError << std::endl;
    }
};

#endif // __DMLOAD_H_INCLUDE__