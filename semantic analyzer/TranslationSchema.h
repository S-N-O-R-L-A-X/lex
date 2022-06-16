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

unordered_map<string,int> TERMINALS,NONTERMINALS,identifier2idx;
vector<vector<pair<int,string>>> actionTable; //shift : the state reduce: pop,add
vector<vector<int>> gotoTable;
stack<pair<string,int>> stk;
vector<string> words,ans,oldString,newString;

struct word {
    int type;
    double value;
};

vector<word> identifiers;

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
    NONTERMINALS={{"program",0},{"stmt",1},{"compoundstmt",2},{"stmts",3},{"ifstmt",4},{"whilestmt",5},{"assgstmt",6},{"boolexpr",7},{"boolop",8},{"arithexpr",9},{"arithexprprime",10},{"multexpr",11},{"multexprprime",12},{"simpleexpr",13}};
	TERMINALS={{"{",0},{"}",1},{"while",2},{"if",3},{"ID",4},{"NUM",5},{";",6},{"*",7},{"/",8},{"+",9},{"-",10},{"(",11},{")",12},{">",13},{"<",14},{"==",15},{"<=",16},{">=",17},{"=",18},{"then",19},{"else",20},{"$",21}};
	split(prog);
	actionTable.resize(100,vector<pair<int,string>>(22));
    gotoTable.resize(100,vector<int>(14));
	// create_table();
	stk.push({"start",0});
}

void error(){

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
        identifier2idx[v[1]]=cnt++;
        if(v[0]=="int"){
            tmp.type=0;
            if(v[3].find('.')!=v[3].npos){//int
                error();
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
            error();
            return ;
        }
    }
	
}

void semanticAnalyze(){
    for(int i=2;i<words.size();++i){
        stringstream ss(words[i]);
        string now;
        vector<string> line;
        while(ss>>now){
            line.push_back(now);
        }

        for(int i=0;i<line.size();++i){

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
    
    
    /********* End *********/
    
}