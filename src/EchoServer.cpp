#include "EchoServer.h"
#include <iostream>
#include <string>

using namespace std;
using namespace placeholders;

EchoServer::EchoServer(const InetAddress &addr, const string& text_name, const string& cache_name)
    :server_(addr),
     pool_(1000, 4),
     words_(text_name),
     cache_(cache_name)
{
    server_.setConnection(bind(&EchoServer::onConnection, this, _1));
    server_.setMessage(bind(&EchoServer::onMessage, this, _1));
    server_.setClose(bind(&EchoServer::onClose, this, _1));
    
    timer_thread_.setTimer(3, 3);
    timer_thread_.setTimerCallback(bind(&Cache::write_to_file, &cache_));
}

void EchoServer::start()
{
    pool_.start();
    timer_thread_.startTimerThread();
    server_.start();
}

EchoServer::~EchoServer()
{
    timer_thread_.cancelTimerThread();
}

void EchoServer::onConnection(const TcpConnectionPtr &conn)
{
    cout << conn->getPeerAddr().toIp() << " port: "
        << conn->getPeerAddr().toPort() << " online" <<endl;
    conn->send("Hello, welcome to Echo Server!!!\r\n");
}


void EchoServer::onMessage(const TcpConnectionPtr &conn)
{
    string s(conn->receive());
    //不要把recv任务放到线程池
    //conn->send(s);
    pool_.addTask(bind(&EchoServer::compute, this, s, conn));
}

//把计算任务和tcp回发做成一个函数，交给线程池
void EchoServer::compute(const std::string &word, const TcpConnectionPtr &conn)
{
    string s;
    s.assign(word, 0, word.size() - 2);

    set<string> value;
    bool judge = false;
    cout << "---------" << endl;
    cout << "find : " << s << endl;

    cache_.get(s, value, judge);
    if(judge == false)
    {   
        words_.priority_queue_init(s);
        words_.priority_queue_fetch(value);
        cache_.put(s, value);
    }   
    
    conn->send(s);
    conn->send(" : ");
    if(value.empty())
    {
        conn->send("there are not candidates of ");
        conn->send(s);
        conn->send("\r\n");
    }
    else
    {
        for(set<string>::iterator it = value.begin(); it != value.end(); it++)
        {
            conn->send("  ");
            conn->send(*it);
        }
        conn->send("\r\n");
    }

    cout << "size : " << cache_.list_size() << endl;
    cout << "list : " << endl;
    cache_.list_show();
//    cache_.write_to_file();
    cout << "-----------" << endl;
}

void EchoServer::onClose(const TcpConnectionPtr &conn)
{
    cout << conn->getPeerAddr().toIp() << " port: "
        << conn->getPeerAddr().toPort() << " offline" << endl;
    conn->shutdown();
}



