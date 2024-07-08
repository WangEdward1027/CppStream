#include <iostream> 
#include <fstream>
#include <string>
#include <string.h>
#include <limits>
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::string;

//方法一:兼容C的写法，使用较少
void test1(){
    ifstream ifs("test.txt");
    if(!ifs.good()){
        cerr << "文件打开失败" << endl;
    }

    char buff[100] = {0};
    while(ifs.getline(buff, sizeof(buff))){  //默认以\n作为分隔符
        cout << buff << endl;
        memset(buff, 0, sizeof(buff)); //完成最后一次读取后清空缓冲区buff
    }
}

//方法二:更方便，工作中更常用
void test2(){
    ifstream ifs("test.txt");
    if(!ifs.good()){
        cerr << "文件打开失败" << endl;
    }

    string line;
    while(getline(ifs,line)){ //默认以\n作为分隔符
        cout << line << endl;
    }
}

//只读一行,读取ifs和cin
void test3(){
    ifstream ifs("test.txt");
    char buff[100]= {0};
    ifs.getline(buff, sizeof(buff),' '); //以空格作为分隔符
    cout << buff << endl;
    cin.getline(buff, sizeof(buff), ' '); //以空格作为分隔符
    cout << buff << endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//清空cin输入缓冲区
}

//只读一行,读取ifs和cin
void test4(){
    ifstream ifs("test.txt");
    string line;
    getline(ifs, line, ' '); //以空格作为分隔符
    cout << line << endl;;
    getline(cin, line, ' '); //以空格作为分隔符
    cout << line << endl;;
}

int main()
{
    test1();
    test2();
    cout << endl;
    
    test3();
    cout << endl;
    
    test4();
    return 0;
}
