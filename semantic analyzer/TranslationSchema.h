// C语言词法分析器
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#define endl "\n"<<flush
using namespace std;

struct word {
    string name;
    int type;
    double value;
};

unordered_map<string,int> identifier2idx;
vector<string> words;
vector<word> identifiers;
bool wrong=false;

void split(string &prog){
	string tmp=prog;
	int pre=0,cur=tmp.find("\n");
	while(cur!=tmp.npos){
		if(cur>pre){
			words.push_back(tmp.substr(pre,cur-pre));
		}
		pre=cur+1;
		cur=tmp.find("\n",pre);
	}
	if(pre!=tmp.size()){
		words.push_back(tmp.substr(pre));
	}
}

void init(string &prog){
	split(prog);
}

void error(int line,const string &str){
    wrong=true;
    cout<<"error message:line "<<line<<","<<str<<endl;
}

void readParameters(){
    stringstream ss(words[0]);
    string now;
    int cnt=0;
    vector<string> line;
    while(ss>>now){
        line.push_back(now);
    }
    for(int i=0;i<line.size();i+=5){
        vector<string> v(line.begin()+i,line.begin()+i+5);
        word tmp;
        tmp.name=v[1];
        identifier2idx[v[1]]=cnt++;
        if(v[0]=="int"){
            tmp.type=0;
            if(v[3].find('.')!=v[3].npos){//int
                error(1,"realnum can not be translated into int type");
                return ;
            }
            else{
                tmp.value=stoi(v[3]);
            }
        }
        else if(v[0]=="real"){
            tmp.type=1;
            tmp.value=stod(v[3]);
        }
        else{
            error(1,"unaccepted tokens");
            return ;
        }
        identifiers.emplace_back(tmp);
    }
}

int findStr(vector<string> & vec,const string &str,int start=0){
    for(int i=start;i<vec.size();++i){
        if(vec[i]==str){
            return i;
        }
    }
    return -1;
}

int toThen(vector<string> & vec,int start=0){
    return findStr(vec,"then",start);
}

int toElse(vector<string> & vec,int start=0){
    return findStr(vec,"else",start);
}

void doOperation(int line,vector<string> &operations){
    int idx1=identifier2idx[operations[0]],idx2=identifier2idx[operations[2]];
    double tmp=0;

    if(identifier2idx.find(operations[4])!=identifier2idx.end()){// x=y+z
        int idx3=identifier2idx[operations[4]];
        if(operations[3]=="+"){
            tmp=identifiers[idx2].value+identifiers[idx3].value;
        }
        else if(operations[3]=="-"){
            tmp=identifiers[idx2].value-identifiers[idx3].value;
        }
        else if(operations[3]=="*"){
            tmp=identifiers[idx2].value*identifiers[idx3].value;
        }
        else if(operations[3]=="/"){
            tmp=(double)identifiers[idx2].value/identifiers[idx3].value;
        }
    }
    else { //x=y+0
        if(operations[3]=="+"){
            tmp=identifiers[idx2].value+stod(operations[4]);
        }
        else if(operations[3]=="-"){
            tmp=identifiers[idx2].value-stod(operations[4]);
        }
        else if(operations[3]=="*"){
            tmp=identifiers[idx2].value*stod(operations[4]);
        }
        else if(operations[3]=="/"){
            if(operations[4]=="0"){
                error(line,"division by zero");
                return ;
            }
            tmp=(double)identifiers[idx2].value/stod(operations[4]);
        }
    }
    
    for(int i=5;i<operations.size();i+=2){
        if(operations[i]==";"){
            break;
        }
        if(identifier2idx.find(operations[i+1])!=identifier2idx.end()){// x=y+z
            int idx3=identifier2idx[operations[i+1]];
            if(operations[i]=="+"){
                tmp=tmp+identifiers[idx3].value;
            }
            else if(operations[i]=="-"){
                tmp=tmp-identifiers[idx3].value;
            }
            else if(operations[i]=="*"){
                tmp=tmp*identifiers[idx3].value;
            }
            else if(operations[i]=="/"){
                tmp=(double)tmp/identifiers[idx3].value;
            }
        }
        else { //x=y+0
            if(operations[i]=="+"){
                tmp=tmp+stod(operations[i+1]);
            }
            else if(operations[i]=="-"){
                tmp=tmp-stod(operations[i+1]);
            }
            else if(operations[i]=="*"){
                tmp=tmp*stod(operations[i+1]);
            }
            else if(operations[i]=="/"){
                if(operations[i+1]=="0"){
                    error(line,"division by zero");
                    return ;
                }
                tmp=(double)tmp/stod(operations[i+1]);
            }
        }
    }

    identifiers[idx1].value=tmp;
}

void semanticAnalyze(){
    for(int i=2;i<words.size()-1;++i){
        stringstream ss(words[i]);
        string now;
        vector<string> line(0);
        while(ss>>now){
            line.push_back(now);
        }
        if(line[0]=="if"){
            if(line[3]==">="){
                if(line[2]>=line[4]){ //execute then
                    int Then=toThen(line,4);
                    vector<string> operations(line.begin()+Then+1,line.begin()+Then+7);
                    doOperation(i+1,operations);
                }
                else{//execute when
                    int Else=toElse(line,4);
                    vector<string> operations(line.begin()+Else+1,line.begin()+Else+7);
                    doOperation(i+1,operations);
                }
            }
            else if(line[3]=="<="){
                if(line[2]<=line[4]){ //execute then
                    int Then=toThen(line,4);
                    vector<string> operations(line.begin()+Then+1,line.begin()+Then+7);
                    doOperation(i+1,operations);
                }
                else{//execute when
                    int Else=toElse(line,4);
                    vector<string> operations(line.begin()+Else+1,line.begin()+Else+7);
                    doOperation(i+1,operations);
                }
            }
            else if(line[3]=="=="){
                if(line[2]==line[4]){ //execute then
                    int Then=toThen(line,4);
                    vector<string> operations(line.begin()+Then+1,line.begin()+Then+7);
                    doOperation(i+1,operations);
                }
                else{//execute when
                    int Else=toElse(line,4);
                    vector<string> operations(line.begin()+Else+1,line.begin()+Else+7);
                    doOperation(i+1,operations);
                }
            }
            else if(line[3]==">"){
                if(line[2]>line[4]){ //execute then
                    int Then=toThen(line,4);
                    vector<string> operations(line.begin()+Then+1,line.begin()+Then+7);
                    doOperation(i+1,operations);
                }
                else{//execute when
                    int Else=toElse(line,4);
                    vector<string> operations(line.begin()+Else+1,line.begin()+Else+7);
                    doOperation(i+1,operations);
                }
            }
            else if(line[3]=="<"){
                if(line[2]<line[4]){ //execute then
                    int Then=toThen(line,4);
                    vector<string> operations(line.begin()+Then+1,line.begin()+Then+7);
                    doOperation(i+1,operations);
                }
                else{//execute when
                    int Else=toElse(line,4);
                    vector<string> operations(line.begin()+Else+1,line.begin()+Else+7);
                    doOperation(i+1,operations);
                }
            }
        }
        else if(identifier2idx.find(line[0])!=identifier2idx.end()){ //identifier
            doOperation(i+1,line);
        }

    }
}

void output(){
    if(!wrong){
        for(int i=0;i<identifiers.size();++i){
            cout<<identifiers[i].name<<": "<<identifiers[i].value<<endl;
        }
    }
}

void read_prog(string& prog)
{
    char c;
    while(scanf("%c",&c)!=EOF){
        prog += c;
    }
}
/* 你可以添加其他函数 */

void Analysis()
{
    string prog;
    read_prog(prog);
    /* 骚年们 请开始你们的表演 */
    /********* Begin *********/
    init(prog);
    readParameters();
    semanticAnalyze();
    output();
    /********* End *********/
    
}