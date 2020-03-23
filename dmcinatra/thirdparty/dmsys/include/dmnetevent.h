
#ifndef __DMNETEVENT_H_INCLUDE__
#define __DMNETEVENT_H_INCLUDE__

enum ENetEvtType
{
    NETEVT_INVALID = 0,
    NETEVT_ESTABLISH,
    NETEVT_ASSOCIATE,
    NETEVT_CONN_ERR,
    NETEVT_ERROR,
    NETEVT_TERMINATE,
    NETEVT_RECV,
};

class CDMBaseSession;

struct SEstablishEvt
{
    CDMBaseSession* poSession;
    bool           bAccepted;
    uint64_t   qwParentID;  
};

struct SAssociateEvt
{
    CDMBaseSession* poSession;
    uint64_t   qwConnectionID;
};

struct SConnErrEvt
{
    int32_t   nSysErrCode;
    uint64_t   qwConnectorID;
};

struct SErrorEvt
{
    CDMBaseSession* poSession;
    uint64_t   qwConnectionID;
    int32_t   nUserErrCode;
    int32_t   nSysErrCode;
};

struct STerminateEvt
{
    CDMBaseSession* poSession;
    uint64_t   qwConnectionID;
    bool   bAccepted;
    uint64_t   qwParentID;
};

struct SRecvEvt
{
    CDMBaseSession* poSession;
    uint64_t   qwConnectionID;
    char*     pData;
    int32_t   nLen;
};

struct SNetEvent
{
    ENetEvtType  nType;
    union
    {
        SEstablishEvt  stEstablish;
        SAssociateEvt  stAssociate;
        SConnErrEvt    stConnErr;
        SErrorEvt      stError;
        STerminateEvt  stTerminate;
        SRecvEvt       stRecv;
    }stUn;
};

#endif // __DMNETEVENT_H_INCLUDE__
