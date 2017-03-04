#include "EchoServer.h"
using namespace std;

int main(int argc, const char *argv[])
{
    EchoServer server(InetAddress(8989), "./data/test.txt", "./data/cache.txt");
    server.start();
    return 0;
}
