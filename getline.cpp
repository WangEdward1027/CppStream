//getline的两种使用

#include <iostream> 
#include <fstream>
#include <string.h>
#include <string>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ifstream;
using std::string;

void test(){
    ifstream ifs;
    //文件输入流是要将数据从文件中读取到内存
    //流对象绑定的这个文件必须要存在
    //否则流对象进入failbit状态,无法正常工作
    ifs.open("explicit.cpp");

    if(!ifs){
        cerr << "ifstream open file failed" << endl;
        return;
    }

    //1.兼容C的方式
    char buff[100] = {0};
    while(ifs.getline(buff, sizeof(buff))){
        cout << buff << endl;
        memset(buff, 0 , sizeof(buff));  //完成一次读取后清空
    }
    ifs.clear();    //将流状态从eofbit恢复为goodbit
    ifs.seekg(0);   //将文件游标移动到文件开头

    //2.工作中更常用, 采用string提供的getline
    string line;
    //string提供的getiline的返回值是ifs对象
    while(getline(ifs, line)){
        cout << line << endl;
    }

    ifs.close();
}

int main()
{
    test();
    return 0;
}
