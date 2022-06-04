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
using namespace std;

// class Word {
// public:
// 	int flag;//1 is shift,0 is reduce
// 	int state;
// 	vector<string> left;
// 	Word(int _flag=1,int _state=-1,vector<string> &_left={}){
// 		flag = _flag;
// 		state=_state;
// 		left=_left;
// 	}
// };


unordered_map<string,int> TERMINALS,NONTERMINALS;
vector<vector<pair<int,vector<string>>>> actionTable; //shift : the state reduce: pop,add
vector<vector<int>> gotoTable;
stack<pair<string,int>> stk;
vector<string> words,ans;



void create_action_table(){
    actionTable[0][0]={1,{}};
    // actionTable[0][2]={{10,""}};
    // actionTable[0][3]={{9,""}};
    // actionTable[0][4]={{11,""}};
    // actionTable[0][5]={{24,""}};
    // actionTable[0][7]={{22,""}};
    // actionTable[0][8]={{23,""}};
    // actionTable[0][9]={{19,""}};
    // actionTable[0][10]={{20,""}};
    // actionTable[0][11]={{25,""}};
    // actionTable[0][13]={{14,""}};
    // actionTable[0][14]={{13,""}};
    // actionTable[0][15]={{17,""}};
    // actionTable[0][16]={{15,""}};
    // actionTable[0][17]={{16,""}};

    // actionTable[1][21]={{-1,"$"}};


}


void create_goto_table(){
    gotoTable[0][0]=1;
    gotoTable[0][2]=2;
    gotoTable[0][4]=3;
    gotoTable[0][5]=4;
    gotoTable[0][6]=5;

    gotoTable[6][3]=26;

    gotoTable[7][1]=8;
}

void create_table(){
    create_action_table();
    create_goto_table();
}

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
	actionTable.resize(100,vector<pair<int,vector<string>>>(22));
    gotoTable.resize(100,vector<int>(14));
	create_table();
	stk.push({"program",0});
}

void println(const string &str){
	string tmp="";
	tmp+=str;
	ans.push_back(tmp);
	// stk.pop(); //the word has been dealt
}

void error(string &lost,int line){
	cout<<"�﷨����,��"+to_string(line)+"��,ȱ��\""+lost+"\""<<endl;
}

void LRparse(string &prog){
	for(int i=0;i<words.size();++i){
		stringstream ss(words[i]);
		string now;
		while(ss>>now){
			while(!stk.empty()){

				string str=stk.top().first;
				int state=stk.top().second;
				// if(str=="E"){
				// 	println(str);
				// 	continue ;
				// }
				if(TERMINALS.find(now)!=TERMINALS.end()){//now can be identified
					int idx=TERMINALS[now];
					int num=actionTable[state][idx].first;
					vector<string> left=actionTable[state][idx].second;
					if(left.size()==0){ //shift
						stk.push({now,num});
					}
					else{ //reduce
						while(num--){
							stk.pop();
						}

						int col=TERMINALS[left[0]],go=gotoTable[state][col];
						stk.push({left[0],go});
					}
				}
				else{
					error(now,i);
				}
				
				// for(const auto pr:gotoTable[row][col]){
                //     cout<<"hi";
				// 	stk.push({s,layer+1});
				// }
			}
		}
	}
}


/* 不要修改这个标准输入函数 */
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
    LRparse(prog);
	for(const string &s:ans){
		cout<<s<<endl;
	}
    
    /********* End *********/
    
}