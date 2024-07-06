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
    }
    
    string line;
    int lineNumber = 0;
    while(getline(ifs, line)){
        ++lineNumber;
        //1.将每行内容存储到vector
        _lines.push_back(line);
        
        istringstream iss(line);
        string word;
        while(iss >> word){ //先读入一行,再对一行中的每个单词进行处理
            //2.处理单词:标点符号去掉
            string cleanword;
            for(size_t i = 0; i < word.size(); ++i){
                if(isalpha(word[i])){ //仅统计字母
                    cleanword += word[i];
                }
            }          

            //3.插入map
            if(_dict.count(cleanword) == 0){
                _dict.insert(pair<string,int>(cleanword,1));
            }else{
                ++_dict[cleanword];
            }
            
            //4.记录单词行号:将行号插入对应单词的set中
            _wordNumbers[cleanword].insert(lineNumber);
        }
    }
    ifs.close();   
}

void TextQuery::query(const string & word){
    cout << "-----------------------------" << endl;
    //1.输出词频
    cout << "element " << word << " occurs "  <<_dict[word]  << " times." << endl;
    //2.输出单词所在行号
    for(auto & ele : _wordNumbers[word]){
        cout << "(line "<< ele << ") ";
        //3.输出该行号的内容
        cout << _lines[ele-1] << endl;       
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
