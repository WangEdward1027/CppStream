//进行优化：
//1.避免频繁动态扩容,vector提前reserver()空间
//2.ifs直接读word，变为getline(一个单词一个单词读，变为一行一行读取文章)。然后对每行数据进行处理
//3.使用sort，对vector进行排序

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <algorithm>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;

struct Record{
    Record(const string & word, int frequency)
    :_word(word)
    ,_frequency(frequency)
    {}

    string _word;
    int _frequency;
};

bool operator<(const Record & lhs, const Record & rhs){
    return lhs._word < rhs._word;
}

class Dictionary
{
public:
    Dictionary(int capacity){
        _dict.reserve(capacity); //预先申请vector空间,减少动态扩容的次数
    }

    void read(const string & filename);
    void store(const string & filename);
private:
    vector<Record> _dict;
    //查找单词是否已经存在于词典中
    vector<Record>::iterator find_word(const string & word);
};

//查找单词在词典中的位置(迭代器)
vector<Record>::iterator Dictionary::find_word(const string & word){
    for(auto it =_dict.begin(); it != _dict.end(); ++it){
        if(it->_word == word){
            return it;
        }
    }
    return _dict.end();
}

void Dictionary::read(const string & filename){
    ifstream ifs(filename);
    if(!ifs.good()){
        cerr << "文件" << filename << "打开失败"  << endl;
        return;
    }

    string line;
    cout << "开始读取圣经内容..." << endl;
    while(getline(ifs, line)){
        istringstream iss(line);
        string word;
        while(iss >> word){
            //1.处理单词:只统计大小写字母,去掉数字和其他符号
            int len = word.length();
            bool alphabet = true;
            for(int i = 0; i < len; i++){
                if(!( (word[i]>='A'&& word[i]<='Z')  || (word[i]>='a' && word[i]<='z'))){
                    alphabet = false;
                    break;
                }
            }
            if(alphabet == false)   continue; //不是字母,不计入词频字典
            
            //2.插入到vector
            auto it = find_word(word);
            if(it != _dict.end()){
                it->_frequency++;
            }else{
                /* _dict.push_back({word,1}); */
                _dict.push_back(Record(word,1));
            }
        }
    }
    
    sort(_dict.begin(), _dict.end()); //将元素进行排序
    cout << "读取完毕。" << endl;
    ifs.close();
}

void Dictionary::store(const string & filename){
    ofstream ofs(filename);
    if(!ofs.good()){
        cerr << "文件" << filename << "打开失败" << endl;
        return;
    }
    
    cout << "开始输出词频字典..." << endl;

    //1.下标方式遍历vector
    for(size_t i = 0; i < _dict.size(); ++i){
        ofs << _dict[i]._word << " " << _dict[i]._frequency << endl;
    }

    /* //2.增强for循环方式遍历 */
    /* for(auto & record : _dict){ */
    /*     ofs << record._word << " " << record._frequency << endl; */
    /* } */

    /* //3.迭代器方式遍历 */
    /* for(auto it = _dict.begin(); it != _dict.end(); ++it){ */
    /*     cout << it->_word << " " << it->_frequency << endl; */
    /* } */

    cout << "输出词频字典: dictionary.txt 完毕。" << endl;
    ofs.close();
}

int main()
{
    Dictionary dict(10000);
    dict.read("The_Holy_Bible.txt");
    dict.store("dictionary.txt");
    return 0;
}
