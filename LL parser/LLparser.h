// C语言词法分析�?
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
/* 不要修改这个标准输入函数 */
unordered_map<string,int> TERMINALS,NONTERMINALS;
vector<vector<vector<string>>> table;
stack<pair<string,int>> stk; // content line
vector<string> words,ans;

void insert_table(){//insert strings in reverse
	table[0][0]={"compoundstmt"};
	table[1][0]={"compoundstmt"};
	table[1][2]={"whilestmt"};
	table[1][3]={"ifstmt"};
	table[1][4]={"assgstmt"};
	table[1][21]={"E"};
	table[2][0]={"}","stmts","{"};
	table[3][1]={"E"};
	table[3][2]={"stmts","stmt"};
	table[3][3]={"stmts","stmt"};
	table[3][4]={"stmts","stmt"};
	table[3][5]={"stmts","stmt"};
	table[4][3]={"stmt","else","stmt","then",")","boolexpr","(","if"};
	table[5][2]={"stmt",")","boolexpr","(","while"};
	table[6][4]={";","arithexpr","=","ID"};
	table[7][4]={"arithexpr","boolop","arithexpr"};
	table[8][13]={">"};
	table[8][14]={"<"};
	table[8][15]={"=="};
	table[8][16]={"<="};
	table[8][17]={">="};
	table[9][4]={"arithexprprime","multexpr"};
	table[9][5]={"arithexprprime","multexpr"};
	table[10][6]={"E"};
	table[10][7]={"E"};
	table[10][8]={"E"};
	table[10][9]={"arithexprprime","multexpr","+"};
	table[10][10]={"arithexprprime","multexpr","-"};
	table[10][12]={"E"};
	table[10][15]={"E"};
	table[11][4]={"multexprprime","simpleexpr"};
	table[11][5]={"multexprprime","simpleexpr"};
	table[12][6]={"E"};
	table[12][7]={"multexprprime","simpleexpr","*"};
	table[12][8]={"multexprprime","simpleexpr","/"};
	table[12][9]={"E"};
	table[12][10]={"E"};
	table[12][12]={"E"};
	table[12][15]={"E"};
	table[13][4]={"ID"};
	table[13][5]={"NUM"};
	table[13][11]={")","arithexpr","("};

	table[10][1]={"E"};
	table[12][1]={"E"};
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
	table.resize(14,vector<vector<string>>(22,vector<string>(0)));
	insert_table();
	stk.push({"program",0});
}

void println(const string &str,int layer){
	string tmp="";
	for(int i=0;i<layer;++i){
		tmp+="\t";
	}
	tmp+=str;
	ans.push_back(tmp);
	stk.pop(); //the word has been dealt
}

void error(string &lost,int line){
	cout<<"�﷨����,��"+to_string(line)+"��,ȱ��\""+lost+"\""<<endl;
}

void LLparse(string &prog){
	for(int i=0;i<words.size();++i){
		stringstream ss(words[i]);
		string now;
		while(ss>>now){
			while(!stk.empty()){

				string str=stk.top().first;
				int layer=stk.top().second;
				if(str=="E"){
					println(str,layer);
					continue ;
				}
				if(TERMINALS.find(str)!=TERMINALS.end()){//str is a terminal
					if(str!=now){
						error(str,i); //index starts from 0 but the loss is before.
						println(str,layer);
						continue;
					}
					else{
						println(str,layer);
						break;
					}
				}
				
				println(str,layer);
				int row=NONTERMINALS[str],col=TERMINALS[now];
				for(const string &s:table[row][col]){
					stk.push({s,layer+1});
				}
			}
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
/* 你可以添加其他函�? */

void Analysis()
{
	string prog;
	read_prog(prog);
	
	/* 骚年�? 请开始你们的表演 */
    /********* Begin *********/
    init(prog);
    LLparse(prog);
	for(const string &s:ans){
		cout<<s<<endl;
	}
	
    /********* End *********/
	
}