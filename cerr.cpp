#include <unistd.h>
#include <iostream> 
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

void test(){
    cerr << 1; //立即输出到屏幕
    cout << 3; //没有立即刷新缓冲区,等sleep后程序结束才输出到屏幕上
    sleep(5);
}

int main()
{
    test();   
    return 0;
}
