#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Question{
    std::string sentence;
    std::string ans;
};
std::vector<struct Question> tofs;
std::vector<struct Question> choices;

void LoadTOF(){
    std::ifstream  tof_file("./TrueOrFalse.txt");
    std::string line;
    struct Question tmp;

    bool flag=false;//flag: 0-read questions, 1-read answers
    while(std::getline(tof_file,line)){
        if(line.length()==0)continue;
        // printf("%s\n",line.c_str()); 
        //use question no as the start of a tof
        if(line[0]>='0'&&line[0]<='9')flag=false;
        if(!flag){
            tmp.sentence=line;
            flag=!flag;
        }
        else{
            tmp.ans+=line;
            tofs.push_back(tmp);
            tmp.ans.clear();
        }
    }

    // for(auto iter = tofs.begin();iter!=tofs.end();iter++){
    //     printf("%s",iter->sentence.c_str());
    //     printf("Ans:%s\n",iter->ans.c_str());
    // }
}

void LoadChoice(const char* file){
    std::ifstream  tof_file(file);
    std::string line;
    struct Question tmp;

    bool flag=false;//flag: 0-read questions, 1-read answers
    while(std::getline(tof_file,line)){
        if(line.length()==0)continue;
        // printf("%s\n",line.c_str()); 
        // printf("%s %d\n",line.substr(0,6).c_str(),line.substr(0,6)==std::string("答案")); 
        //use question no as the start of a tof
        if(line.substr(0,6)==std::string("答案"))flag=true;
        if(!flag){
            tmp.sentence+=line+"\n";
        }
        else{
            tmp.ans=line;
            choices.push_back(tmp);
            tmp.sentence.clear();
            flag=false;
        }
    }

    // for(auto iter = choices.begin();iter!=choices.end();iter++){
    //     printf("%s",iter->sentence.c_str());
    //     printf("Ans:%s\n",iter->ans.c_str());
    // }
}

void TestTOF(){
    printf("print 1 or 0 to choose true-or-false\n");
    int res;
    for(auto iter = tofs.begin();iter!=tofs.end();iter++){
        printf("%s\n",iter->sentence.c_str());
        std::cin>>res;
        printf("Ans:%s\n",iter->ans.c_str());
    }
}

void TestChoice(){
    std::string res;
    for(auto iter = choices.begin();iter!=choices.end();iter++){
        printf("%s",iter->sentence.c_str());
        std::cin>>res;
        printf("Ans:%s\n\n",iter->ans.c_str());
    }
}

int main(){
    LoadTOF();
    TestTOF();
    
    LoadChoice("./SingleChoice.txt");
    printf("print A-D to choose single-choice for rignt answer\n");
    TestChoice();
    choices.clear();

    LoadChoice("./MultipleChoice.txt");
    printf("print A-D to choose multiple-choice for rignt answer\n");
    TestChoice();
}