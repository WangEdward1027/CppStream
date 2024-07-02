//输入一个int型数据

#include <iostream>
#include <limits>
using std::cout;
using std::cin;
using std::endl;

void InputInt(int & number){
    cout << "请输入一个int型数据" << endl;
    cin >> number;
    while(!cin.eof()){
        if(cin.bad()){
            cout << "cin has broken!" << endl;
            return;
        }else if(cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "请输入一个int型的数据, 看清楚一点!" << endl;
            cin >> number;
        }else{
            cout << "num:" << number << endl;
            break;
        }
    }
}

//用逗号表达式重写该函数
void InputInteger(int & num){
    cout << "请输入一个int型数据" << endl;
    //逗号表达式整体的值,为最后一个逗号之后的表达式的值
    //逗号表达式前面的内容会执行，但不影响最终判断的条件。
    while(cin >> num , !cin.eof()){
        if(cin.bad()){
            cout << "cin has broken!" << endl;
            return;
        }else if(cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "请输入一个int型数据" << endl;
        }else{
            cout << "num" << num << endl;
            break;
        }
    }
}

void test0(){
    int num = 0;
    InputInt(num);
}

void test1(){
    int num = 0;
    cin >> num;
    if(cin.good()){
        cout << "cin.good()" << endl;
    }else{
        cout << "!cin.good()" << endl;
    }
    
    //不清空状态
    cin >> num;
    if(cin){    //等价于cin.good()
        cout << "cin" << endl;
    }else{
        cout << "!cin" << endl;
    }
}

//连续输入:输入流运算符默认以换行符、空格符、制表符作为分隔符
//cin对象完成一次输入后,返回值就是cin对象本身
void test2(){
    int num = 0, num2 = 0;
    cout << &cin << endl;
    cout << &(cin >> num) << endl;
    //执行过程相当于(cin >> num) >> num2
    cout << &(cin >> num >> num2) << endl;
}

int main()
{
    test0();   
    /* test1(); */   
    /* test2(); */   
    return 0;
}
