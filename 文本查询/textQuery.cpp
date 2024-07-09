#include <iostream> 
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <utility>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::set;
using std::ifstream;
using std::istringstream;
using std::pair;

class TextQuery
{
public:
    void readFile(const string & filename); //解析文件
    void query(const string & word); //单词查询
private:
    vector<string> _lines;  //O(1) //存储每一行的内容
    map<string,set<int>> _wordNumbers;  //单词,对应的所有行号
    map<string,int> _dict;  //单词出现的次数
};

void TextQuery::readFile(const string & filename){
    ifstream ifs(filename);
    if(!ifs.good()){
        cerr << filename << " open failed." << endl;
        return;
    }
    
    string line;
    int lineNumber = 0;
    while(getline(ifs, line)){   //先读入一行
        ++lineNumber;
        //1.将每行内容存储到vector
        _lines.push_back(line);
        
        //2.处理行:去除标点符号和数字,非字母被替换为空格
        for(auto & ch : line){
            if(!isalpha(ch)){
                ch = ' ';
            }
        }    

        istringstream iss(line);
        string word;
        while(iss >> word){  
            //3.插入map:不存在的word会直接插入{word,0}
            ++_dict[word];
            
            //4.记录单词行号:将行号插入对应单词的set中
            _wordNumbers[word].insert(lineNumber);
        }
    }
    ifs.close();   
}

void TextQuery::query(const string & word){
    cout << "-----------------------------" << endl;
    //1.输出词频
    cout << "element " << word << " occurs "  <<_dict[word]  << " times." << endl;
    //2.输出单词所在行号
    for(auto & lines : _wordNumbers[word]){ //_wordNumbers[word]是set<int>
        cout << "(line "<< lines << ") ";
        //3.输出该行号的内容
        cout << _lines[lines-1] << endl;       
    }
    cout << "-----------------------------" << endl;
}

int main(int argc, char * argv[])
{
    if(argc != 3){
        cout << "Usage: ./程序名 文件名 查询单词" << endl;
        cout << "请重试" << endl;
        return 1;
    }
    string queryWord(argv[2]);
    TextQuery tq;
    tq.readFile(argv[1]);
    tq.query(queryWord);
    return 0;
}
