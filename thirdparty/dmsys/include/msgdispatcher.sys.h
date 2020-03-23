
#ifndef __MSGDISPATCHER_SYS_H_INCLUDE__
#define __MSGDISPATCHER_SYS_H_INCLUDE__

#include <assert.h>
#include <stddef.h>

#include <google/protobuf/message.h>
#include "dmos.h"
#include "dmtypes.h"
#include "msgperformance.cf.h"

template<class T>
int GetMSGID()
{
	static T msg;
	return msg.id();
}

template<class T>
int GetMSGID(T& msg)
{
	return msg.id();
}

template<typename T>
class TMsgDispatcherPB
{
public:
    typedef int (T::*MSG_FUNC)(::google::protobuf::Message& msg, int nLen, const void* pObject);
    enum{ FUN_SIZE_MAX = 20480 };

    static inline uint32_t GetTickCount32()
    {
#ifdef WIN32
        return ::GetTickCount();
#else
        struct timespec ts = {0};
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#endif
    }

    class MsgGuard
    {
    public:
        MsgGuard(CDMCF_msgperformance& oConfig, uint16_t wMsgID, ::google::protobuf::Message& msg, int nLen)
        : m_oConfig(oConfig), m_wMsgID(wMsgID), m_msg(msg), m_nLen(nLen), m_dwStart(0), m_msgpf(NULL)
        {
            auto it = m_oConfig.GetMeta().mutable_map_xmsg()->find(wMsgID);
            if (it != m_oConfig.GetMeta().mutable_map_xmsg()->end())
            {
                m_msgpf = &it->second;
                m_dwStart = GetTickCount32();
            }
        }
        ~MsgGuard()
        {
            if (NULL != m_msgpf)
            {
                uint32_t dwEnd = GetTickCount32();
                uint32_t dwUse = dwEnd - m_dwStart;

                m_msgpf->set_msgcount(m_msgpf->msgcount()+1);
                m_msgpf->set_totalmsgsize(m_msgpf->totalmsgsize() + m_nLen);
                m_msgpf->set_totalconsumetime(m_msgpf->totalconsumetime() + dwUse);

                if (dwUse > m_msgpf->maxconsumetime())
                {
                    m_msgpf->set_maxconsumetime(dwUse);
                }

                m_msgpf->set_avgconsumetime(m_msgpf->totalconsumetime() / m_msgpf->msgcount());

                m_oConfig.GetMeta().mutable_xtotal()->set_totalsize(m_oConfig.GetMeta().xtotal().totalsize() + m_nLen);
            }
        }
    private:
        CDMCF_msgperformance& m_oConfig;
        uint16_t m_wMsgID;
        int m_nLen;
        uint32_t m_dwStart;
        ::msgperformance::dmnode_xmsg* m_msgpf;
		::google::protobuf::Message& m_msg;
    };

public:
    TMsgDispatcherPB()
    {
        m_nMsgCount = 0;
        memset(m_arFunctions, 0, sizeof(m_arFunctions));
        memset(m_arMsgSizes, 0, sizeof(m_arMsgSizes));
    }

    virtual ~TMsgDispatcherPB()
    {

    }

    void Register(uint16_t wMsgID, MSG_FUNC fnIn, int nLen)
    {
        MSG_FUNC pFunc = Find(wMsgID);
        if(NULL != pFunc)
        {
            assert(0 && "MsgID Repeat");
            return;
        }

        if (wMsgID >= FUN_SIZE_MAX)
        {
            assert(0 && "MsgID >= FUN_SIZE_MAX");
            return;
        }

        assert(nLen >= 0);
        assert(0 == m_arFunctions[wMsgID]);
        m_arFunctions[wMsgID] = fnIn;
        m_arMsgSizes[wMsgID] = nLen;
        ++m_nMsgCount;

    
        ::msgperformance::dmnode_xmsg xmsg;
        xmsg.set_msgid(wMsgID);
        m_msgperformance.GetMeta().mutable_map_xmsg()->insert({ xmsg.msgid(), xmsg});
    }

    static inline int GetErrorDefault(){ return -1;}
    static inline int GetErrorNG(){ return -1;}

    MSG_FUNC Find(uint16_t wMsgID)
    {
        if(wMsgID >= FUN_SIZE_MAX) return NULL;
        return m_arFunctions[wMsgID];
    }

    int Call(uint16_t wMsgID, ::google::protobuf::Message& msg, int nLen, const void* pObject = NULL)
    {
        MSG_FUNC pFunc = Find(wMsgID);
        if(NULL == pFunc)
        {
            return GetErrorNG();
        }
        return (static_cast<T*>(this)->*pFunc)(msg, nLen, pObject);
    }

    int MGCall(uint16_t wMsgID, ::google::protobuf::Message& msg, int nLen, const void* pObject = NULL)
    {
        MsgGuard oGuard(m_msgperformance, wMsgID, msg, nLen);
        return Call(wMsgID, msg, nLen, pObject);
    }

    int GetMsgSize(uint16_t wMsgID)
    {
        if(wMsgID >= FUN_SIZE_MAX) return -1;
        return m_arMsgSizes[wMsgID];
    }

    int GetMsgCount(){ return m_nMsgCount;}

    CDMCF_msgperformance& GetMsgPerformance(){ return m_msgperformance;};

private:
    MSG_FUNC m_arFunctions[FUN_SIZE_MAX];
    int  m_arMsgSizes[FUN_SIZE_MAX];
    int  m_nMsgCount;

    CDMCF_msgperformance m_msgperformance;
    
};

#endif // __MSGDISPATCHER_SYS_H_INCLUDE__
