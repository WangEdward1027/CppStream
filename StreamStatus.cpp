//判断流的状态

#include <iostream> 
#include <limits>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::string;

void printStreamStatus(istream & is){
    cout << "is' goodbit:"  << is.good() << endl;
    cout << "is' badbit:"  <<  is.bad()  << endl;
    cout << "is' failbit:"  << is.fail() << endl;
    cout << "is' eofbit:"  <<  is.eof()  << endl;
    cout << endl;
}

void test0(){
    printStreamStatus(cin);

    int num = 10;
    cin >> num;
    cout << "num:" << num << endl;
    printStreamStatus(cin);
    
    //如果第一次输错,不是int类型,会跳过第二次的输入,num自动为0
    cin >> num;
    cout << "num:" << num << endl;
    printStreamStatus(cin);

    //如果经过了第一次的输入,使得标准输入流进入failbit/eofbit状态
    //希望能够恢复流的状态
    if(!cin.good()){
        cin.clear();    //恢复流的状态
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "恢复流的状态" << endl;
    }
    printStreamStatus(cin);
    
    string line;
    cin >> line;
    cout << "line:" << line << endl;
    printStreamStatus(cin);
}

int main()
{
    test0();   
    return 0;
}
