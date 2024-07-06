//map实现词频字典，只统计单词字母，去除数字和其他符号
//由于map的自动排序功能, 效率比起vector大幅提升。 (插入时查找遍历map的红黑树速度远大于遍历线性的vector)

#include <iostream> 
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::map;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::pair;

class Dictionary
{
public:
    void read(const string & filename);
    void store(const string & filename);
private:
    map<string,int> _dict;
};

void Dictionary::read(const string & filename){
    ifstream ifs(filename);   
    if(!ifs.good()){
        cerr << "文件" << filename <<  "打开失败" << endl;
        return;
    }
    
    cout << "开始读取圣经内容..." << endl;
    string line;
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
    
            //2.插入到map
            if(_dict.count(word) == 0){
                _dict.insert(pair<string,int>(word,1));
            }else{
                ++_dict[word];
            }
        }
    }
    cout << "读取完毕。" << endl;
    ifs.close();
}

void Dictionary::store(const string & filename){
    ofstream ofs(filename);
    if(!ofs.good()){
        cerr << "ofstream open" << filename << "failed" << endl;
    }
    
    cout << "开始输出词频字典..." << endl;
    for(auto & ele : _dict){
        ofs << ele.first << " " << ele.second << endl;
    }

    cout << "输出完毕" << endl;
    ofs.close();
}

int main()
{
    Dictionary dict;   
    dict.read("The_Holy_Bible.txt");
    dict.store("mapDict.txt");
    return 0;
}
