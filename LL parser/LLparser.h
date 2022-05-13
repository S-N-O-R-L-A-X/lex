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
/* 不要修改这个标准输入函数 */
unordered_map<string,int> TERMINALS,NONTERMINALS;
vector<vector<vector<string>>> table;
stack<pair<string,int>> stk;


void insert_table(){//insert strings in reverse
	table[0][0]={"compoundstmt"};
	table[1][2]={"whilestmt"};
	table[1][3]={"ifstmt"};
	table[1][4]={"assgstmt"};
	table[2][0]={"}","stmts","{"};
	table[3][1]={"E"};
	table[3][4]={"stmts","stmt"};
	table[6][4]={";","arithexpr","=","ID"};
	table[7][4]={"arithexpr","boolop","arithexpr"};
	table[9][4]={"arithexprprime","multexpr"};
	table[9][5]={"arithexprprime","multexpr"};
	table[10][6]={"E"};
	table[11][4]={"multexprprime","simpleexpr"};
	table[11][5]={"multexprprime","simpleexpr"};
	table[12][6]={"E"};
	table[13][4]={"ID"};
	table[13][5]={"NUM"};
}

void init(){
    NONTERMINALS={{"program",0},{"stmt",1},{"compoundstmt",2},{"stmts",3},{"ifstmt",4},{"whilestmt",5},{"assgstmt",6},{"boolexpr",7},{"boolop",8},{"arithexpr",9},{"arithexprprime",10},{"multexpr",11},{"multexprprime",12},{"simpleexpr",13}};
	TERMINALS={{"{",0},{"}",1},{"while",2},{"if",3},{"ID",4},{"NUM",5},{";",6},{"*",7},{"/",8},{"+",9},{"-",10},{"(",11},{")",12},{">",13},{"<",14},{"==",15},{"<=",16},{">=",17},{"=",18},{"then",19},{"else",20},{"$",21}};
	table.resize(14,vector<vector<string>>(20,vector<string>(0)));
	insert_table();
	stk.push({"program",0});
}

void println(const string &str,int layer){
	for(int i=0;i<layer;++i){
		cout<<"\t";
	}
	cout<<str<<endl;
}

void error(){
	cout<<"error"<<endl;
}

void LLparse(string &prog){
	stringstream ss(prog);
	string now;
	
	while(ss>>now){
		while(!stk.empty()){
			auto [str,layer]=stk.top();
			if(str=="E"){
				println(str,layer);
				stk.pop();
				continue ;
			}
			if(TERMINALS.find(str)!=TERMINALS.end()){//str is a terminal
				if(str!=now){
					error();
					
					break;
				}
				else{
					println(str,layer);
					stk.pop();
					break;
				}
			}
			stk.pop();
			
			println(str,layer);
			int row=NONTERMINALS[str],col=TERMINALS[now];
			for(const string &s:table[row][col]){
				stk.push({s,layer+1});
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
/* 你可以添加其他函数 */

void Analysis()
{
	string prog;
	read_prog(prog);
	
	/* 骚年们 请开始你们的表演 */
    /********* Begin *********/
    init();
	prog+=" $";
    LLparse(prog);
    /********* End *********/
	
}