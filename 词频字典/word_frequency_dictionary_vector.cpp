//vector实现词频字典，只统计单词字母，去除数字和其他符号

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

struct Record{
    string _word;
    int _frequency;
};

class Dictionary
{
public:
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
        cout << "文件" << filename << "打开失败"  << endl;
        return;
    }

    string word;
    cout << "开始读取圣经内容..." << endl;
    while(ifs.good()){
        ifs >> word;
        //只统计大小写字母,去掉数字和其他符号
        int len = word.length();
        bool alphabet = true;
        for(int i = 0; i < len; i++){
            if(!( (word[i]>='A'&& word[i]<='Z')  || (word[i]>='a' && word[i]<='z'))){
                alphabet = false;
                break;
            }
        }
        if(alphabet == false)   continue; //不是字母,不计入词频字典
        
        auto it = find_word(word);
        if(it != _dict.end()){
            it->_frequency++;
        }else{
            _dict.push_back({word,1});
        }
    }
    
    cout << "读取完毕。" << endl;
    ifs.close();
}

void Dictionary::store(const string & filename){
    ofstream ofs(filename);
    if(!ofs.good()){
        cout << "文件" << filename << "打开失败" << endl;
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
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");
    dict.store("dictionary.txt");
    return 0;
}
