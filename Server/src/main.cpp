#include <TCPKernel.h>

int main(int argc,char *argv[])
{
    int port = _DEF_PORT;
    if( argc >= 2 )
    {
        port = atoi(argv[1]);
    }
    TcpKernel * pKernel =  TcpKernel::GetInstance();

    //开启服务 给定端口, 可以使用输入的port
    pKernel->Open(port);
    std::cout << "Server is running at port:" << port << std::endl;
    // 事件循环 : 循环监听事件
    pKernel->EventLoop();

    pKernel->Close();

    return 0;
}
