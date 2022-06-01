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

unordered_map<string,int> TERMINALS,NONTERMINALS;
vector<vector<vector<string>>> actionTable,gotoTable;
stack<pair<string,int>> stk;
vector<string> words,ans;

void insert_table(){
    // actionTable[0][0]=;
}


void init(string &prog){
    NONTERMINALS={{"program",0},{"stmt",1},{"compoundstmt",2},{"stmts",3},{"ifstmt",4},{"whilestmt",5},{"assgstmt",6},{"boolexpr",7},{"boolop",8},{"arithexpr",9},{"arithexprprime",10},{"multexpr",11},{"multexprprime",12},{"simpleexpr",13}};
	TERMINALS={{"{",0},{"}",1},{"while",2},{"if",3},{"ID",4},{"NUM",5},{";",6},{"*",7},{"/",8},{"+",9},{"-",10},{"(",11},{")",12},{">",13},{"<",14},{"==",15},{"<=",16},{">=",17},{"=",18},{"then",19},{"else",20},{"$",21}};
	// split(prog);
	actionTable.resize(14,vector<vector<string>>(22,vector<string>(0)));
	// insert_table();
	stk.push({"program",0});
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
    
    
    /********* End *********/
    
}