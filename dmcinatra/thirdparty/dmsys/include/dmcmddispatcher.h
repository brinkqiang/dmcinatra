
#ifndef __DMCMDDISPATCHER_H_INCLUDE__
#define __DMCMDDISPATCHER_H_INCLUDE__

#include <assert.h>
#include <map>
#include <string>
#include <vector>

typedef std::vector<std::string> DISPATCHER_CMDS;

template<typename T>
class TCmdDispatcher {
  public:
    typedef typename int (T::*CMD_FUNC)(DISPATCHER_CMDS& cmds, void* pData);
    typedef std::map<std::string, CMD_FUNC> MapCmdFunc;
    typedef typename MapCmdFunc::iterator MapCmdFuncIt;

  public:
    TCmdDispatcher() {
    }
    virtual ~TCmdDispatcher() {
    }

    bool Register(const std::string& strCmd, CMD_FUNC fnIn) {
        MapCmdFuncIt It = m_mapCmdFunc.find(strCmd);

        if (It != m_mapCmdFunc.end()) {
            assert(0);
            return false;
        }

        m_mapCmdFunc[strCmd] = fnIn;
        return true;
    }

    CMD_FUNC Find(const std::string& strCmd) {
        MapCmdFuncIt It = m_mapCmdFunc.find(strCmd);

        if (It == m_mapCmdFunc.end()) {
            return NULL;
        }

        return It->second;
    }

    int Call(DISPATCHER_CMDS& cmds, void* pData = NULL) {
        if (cmds.empty()) {
            return -1;
        }

        CMD_FUNC pFunc = Find(cmds[0]);

        if (NULL == pFunc) {
            return -2;
        }

        return (static_cast<T*>(this)->*pFunc)(cmds, pData);
    }

  private:
    MapCmdFunc m_mapCmdFunc;
};

#endif // __DMCMDDISPATCHER_H_INCLUDE__

