#ifndef ECHO_TCP_SERVER_H
#define ECHO_TCP_SERVER_H 

#include "echo/TcpServer.h"
#include "echo/ThreadPool.h"
#include "echo/NonCopyable.h"
#include "Words.h"
#include "Cache.h"
#include "TimerThread.h"

class EchoServer : NonCopyable
{
    public:
        ~EchoServer();
        EchoServer(const InetAddress &addr, const std::string& text_name, const std::string& cache_name);
        void start();
        
    private:
        TcpServer server_;
        ThreadPool pool_;
        Words words_;
        Cache cache_;
        TimerThread timer_thread_;

    private:
        void onConnection(const TcpConnectionPtr &conn);
        void onMessage(const TcpConnectionPtr &conn);
        void onClose(const TcpConnectionPtr &conn);

        void compute(const std::string &s, const TcpConnectionPtr &conn);
};



#endif  /*ECHO_TCP_SERVER_H*/
