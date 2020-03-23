
#ifndef __DMLOCK_H_INCLUDE__
#define __DMLOCK_H_INCLUDE__

#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

class CDMLockNull {
  public:
    CDMLockNull() {}
    ~CDMLockNull() {}
    inline void Lock(void) {}
    inline void UnLock(void) {}
};

class CDMLock {
  private:
    volatile bool m_bIsSafe;
    inline void SetIsSafe() {
        m_bIsSafe = true;
    }
#ifdef WIN32
    CRITICAL_SECTION  m_lock;
#else
    pthread_mutex_t m_lock;
#endif
  public:
    CDMLock(void) {
#ifdef WIN32
        InitializeCriticalSection(&m_lock);
#else
        pthread_mutex_init(&m_lock,NULL);
#endif
        SetIsSafe();
    }

    ~CDMLock() {
        if (m_bIsSafe) {
#ifdef WIN32
            DeleteCriticalSection(&m_lock);
#else
            pthread_mutex_destroy(&m_lock);
#endif
        }
    }

    inline void Lock(void) {
        if (m_bIsSafe) {
#ifdef WIN32
            EnterCriticalSection(&m_lock);
#else
            pthread_mutex_lock(&m_lock);
#endif
        }
    }

    inline void UnLock(void) {
        if (m_bIsSafe) {
#ifdef WIN32
            LeaveCriticalSection(&m_lock);
#else
            pthread_mutex_unlock(&m_lock);
#endif
        }
    }

    CDMLock(CDMLock*);
    CDMLock(const CDMLock&);
    void operator=(const CDMLock&);
};

template<typename Mutex>
class CDMLockGuard {
  private:
    Mutex& m_lock;
  public:
    explicit CDMLockGuard(Mutex& lock)
        : m_lock(lock) {
        m_lock.Lock();
    }
    ~CDMLockGuard() {
        m_lock.UnLock();
    }
};

#endif // __DMLOCK_H_INCLUDE__
