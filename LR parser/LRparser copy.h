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
vector<vector<pair<int,string>>> actionTable; //shift : the state reduce: pop,add
vector<vector<int>> gotoTable;
stack<pair<string,int>> stk;
vector<string> words,ans,oldString,newString;


void create_action_table(){
    actionTable[0][0]={3,""};
    actionTable[1][21]={1,"acc"};
	actionTable[2][21]={1,"program"};

	actionTable[3][0]={3,""};
	actionTable[3][1]={0,"stmts"};
	actionTable[3][2]={11,""};
	actionTable[3][3]={10,""};
	actionTable[3][4]={12,""};
	

	actionTable[4][1]={13,""};
	actionTable[5][0]={3,""};

	actionTable[5][1]={0,"stmts"};
	actionTable[5][2]={11,""};
	actionTable[5][3]={10,""};
	actionTable[5][4]={12,""};

	actionTable[6][1]={1,"stmt"};
	actionTable[6][20]={1,"stmt"};
	actionTable[7][1]={1,"stmt"};
	actionTable[7][20]={1,"stmt"};
	actionTable[8][1]={1,"stmt"};
	actionTable[8][20]={1,"stmt"};
	actionTable[9][1]={1,"stmt"};
	actionTable[9][20]={1,"stmt"};

	actionTable[10][11]={15,""};
	actionTable[11][11]={16,""};

	actionTable[12][18]={17,""};

	actionTable[13][1]={3,"compoundstmt"};
	actionTable[13][20]={3,"compoundstmt"};
	actionTable[13][21]={3,"compoundstmt"};

	actionTable[14][1]={2,"stmts"};

	actionTable[15][4]={22,""};
	actionTable[15][5]={23,""};
	actionTable[15][11]={24,""};
	actionTable[16][4]={22,""};
	actionTable[16][5]={23,""};
	actionTable[16][11]={24,""};
	actionTable[17][4]={22,""};
	actionTable[17][5]={23,""};
	actionTable[17][11]={24,""};

	actionTable[18][1]={27,""};

	actionTable[19][13]={30,""};
	actionTable[19][14]={29,""};
	actionTable[19][15]={33,""};
	actionTable[19][16]={31,""};
	actionTable[19][17]={32,""};


	actionTable[20][1]={0,"arithexprprime"};
	actionTable[20][6]={0,"arithexprprime"};
	actionTable[20][9]={35,""};
	actionTable[20][10]={36,""};
	actionTable[20][12]={0,"arithexprprime"};
	actionTable[20][13]={0,"arithexprprime"};
	actionTable[20][14]={0,"arithexprprime"};
	actionTable[20][15]={0,"arithexprprime"};
	actionTable[20][16]={0,"arithexprprime"};
	actionTable[20][17]={0,"arithexprprime"};
	actionTable[20][20]={0,"arithexprprime"};

	actionTable[21][1]={0,"multexprprime"};
	actionTable[21][6]={0,"multexprprime"};
	actionTable[21][7]={38,""};
	actionTable[21][8]={39,""};
	actionTable[21][9]={0,"multexprprime"};
	actionTable[21][10]={0,"multexprprime"};
	actionTable[21][12]={0,"multexprprime"};
	actionTable[21][13]={0,"multexprprime"};
	actionTable[21][14]={0,"multexprprime"};
	actionTable[21][15]={0,"multexprprime"};
	actionTable[21][16]={0,"multexprprime"};
	actionTable[21][17]={0,"multexprprime"};
	actionTable[21][20]={0,"multexprprime"};

	actionTable[22][1]={1,"simpleexpr"};
	actionTable[22][6]={1,"simpleexpr"};
	actionTable[22][7]={1,"simpleexpr"};
	actionTable[22][8]={1,"simpleexpr"};
	actionTable[22][9]={1,"simpleexpr"};
	actionTable[22][10]={1,"simpleexpr"};
	actionTable[22][12]={3,"simpleexpr"};
	actionTable[22][13]={1,"simpleexpr"};
	actionTable[22][14]={1,"simpleexpr"};
	actionTable[22][15]={1,"simpleexpr"};
	actionTable[22][16]={1,"simpleexpr"};
	actionTable[22][17]={1,"simpleexpr"};
	actionTable[22][20]={1,"simpleexpr"};

	actionTable[23][1]={1,"simpleexpr"};
	actionTable[23][6]={1,"simpleexpr"};
	actionTable[23][7]={1,"simpleexpr"};
	actionTable[23][8]={1,"simpleexpr"};
	actionTable[23][9]={1,"simpleexpr"};
	actionTable[23][10]={1,"simpleexpr"};
	actionTable[23][12]={1,"simpleexpr"};
	actionTable[23][13]={1,"simpleexpr"};
	actionTable[23][14]={1,"simpleexpr"};
	actionTable[23][15]={1,"simpleexpr"};
	actionTable[23][16]={1,"simpleexpr"};
	actionTable[23][17]={1,"simpleexpr"};
	actionTable[23][20]={1,"simpleexpr"};

	actionTable[24][11]={24,""};
	actionTable[25][12]={40,""};
	actionTable[26][6]={57,""};
	actionTable[27][19]={42,""};
	actionTable[28][4]={22,""};
	actionTable[28][5]={23,""};
	actionTable[28][11]={24,""};

	actionTable[29][4]={1,"boolop"};
	actionTable[29][5]={1,"boolop"};
	actionTable[29][11]={1,"boolop"};

	actionTable[30][4]={1,"boolop"};
	actionTable[30][5]={1,"boolop"};
	actionTable[30][11]={1,"boolop"};

	actionTable[31][4]={1,"boolop"};
	actionTable[31][5]={1,"boolop"};
	actionTable[31][11]={1,"boolop"};

	actionTable[32][4]={1,"boolop"};
	actionTable[32][5]={1,"boolop"};
	actionTable[32][11]={1,"boolop"};

	actionTable[33][4]={1,"boolop"};
	actionTable[33][5]={1,"boolop"};
	actionTable[33][11]={1,"boolop"};

	actionTable[34][1]={2,"arithexpr"};
	actionTable[34][6]={2,"arithexpr"};
	actionTable[34][12]={2,"arithexpr"};
	actionTable[34][13]={2,"arithexpr"};
	actionTable[34][14]={2,"arithexpr"};
	actionTable[34][15]={2,"arithexpr"};
	actionTable[34][16]={2,"arithexpr"};
	actionTable[34][17]={2,"arithexpr"};
	actionTable[34][20]={2,"arithexpr"};


	actionTable[35][4]={22,""};
	actionTable[35][5]={23,""};
	actionTable[35][11]={24,""};
	actionTable[36][4]={22,""};
	actionTable[36][5]={23,""};
	actionTable[36][11]={24,""};

	actionTable[37][1]={2,"multexpr"};
	actionTable[37][6]={2,"multexpr"};
	actionTable[37][9]={2,"multexpr"};
	actionTable[37][10]={2,"multexpr"};
	actionTable[37][12]={2,"multexpr"};
	actionTable[37][13]={2,"multexpr"};
	actionTable[37][14]={2,"multexpr"};
	actionTable[37][15]={2,"multexpr"};
	actionTable[37][16]={2,"multexpr"};
	actionTable[37][17]={2,"multexpr"};
	actionTable[37][20]={2,"multexpr"};

	actionTable[38][4]={22,""};
	actionTable[38][5]={23,""};
	actionTable[38][11]={24,""};
	actionTable[39][4]={22,""};
	actionTable[39][5]={23,""};
	actionTable[39][11]={24,""};

	actionTable[40][0]={3,""};
	actionTable[40][2]={11,""};
	actionTable[40][3]={10,""};
	actionTable[40][4]={12,""};

	actionTable[41][12]={49,""};

	actionTable[42][0]={3,""};
	actionTable[42][2]={11,""};
	actionTable[42][3]={10,""};
	actionTable[42][4]={12,""};	
	
	actionTable[43][12]={3,"boolexpr"};

	actionTable[44][1]={0,"arithexprprime"};
	actionTable[44][6]={0,"arithexprprime"};
	actionTable[44][9]={35,""};
	actionTable[44][10]={36,""};
	actionTable[44][12]={0,"arithexprprime"};
	actionTable[44][13]={0,"arithexprprime"};
	actionTable[44][14]={0,"arithexprprime"};
	actionTable[44][15]={0,"arithexprprime"};
	actionTable[44][16]={0,"arithexprprime"};
	actionTable[44][17]={0,"arithexprprime"};
	actionTable[44][20]={0,"arithexprprime"};


	actionTable[45][1]={0,"arithexprprime"};
	actionTable[45][6]={0,"arithexprprime"};
	actionTable[45][9]={35,""};
	actionTable[45][10]={36,""};
	actionTable[45][12]={0,"arithexprprime"};
	actionTable[45][13]={0,"arithexprprime"};
	actionTable[45][14]={0,"arithexprprime"};
	actionTable[45][15]={0,"arithexprprime"};
	actionTable[45][16]={0,"arithexprprime"};
	actionTable[45][17]={0,"arithexprprime"};
	actionTable[45][20]={0,"arithexprprime"};
	

	actionTable[46][7]={38,""};
	actionTable[46][8]={39,""};
	actionTable[47][7]={38,""};
	actionTable[47][8]={39,""};

	actionTable[48][1]={5,"whilestmt"};
	actionTable[48][20]={5,"whilestmt"};

	actionTable[49][20]={55,""};

	actionTable[50][1]={1,"simpleexpr"};
	actionTable[50][6]={1,"simpleexpr"};
	actionTable[50][7]={1,"simpleexpr"};
	actionTable[50][8]={1,"simpleexpr"};
	actionTable[50][9]={1,"simpleexpr"};
	actionTable[50][10]={1,"simpleexpr"};
	actionTable[50][12]={3,"simpleexpr"};
	actionTable[50][13]={1,"simpleexpr"};
	actionTable[50][14]={1,"simpleexpr"};
	actionTable[50][15]={1,"simpleexpr"};
	actionTable[50][16]={1,"simpleexpr"};
	actionTable[50][17]={1,"simpleexpr"};
	actionTable[50][20]={1,"simpleexpr"};

	actionTable[51][1]={0,"arithexprprime"};
	actionTable[51][6]={0,"arithexprprime"};
	actionTable[51][12]={0,"arithexprprime"};
	actionTable[51][13]={0,"arithexprprime"};
	actionTable[51][14]={0,"arithexprprime"};
	actionTable[51][15]={0,"arithexprprime"};
	actionTable[51][16]={0,"arithexprprime"};
	actionTable[51][17]={0,"arithexprprime"};
	actionTable[51][20]={0,"arithexprprime"};

	actionTable[52][1]={0,"arithexprprime"};
	actionTable[52][6]={0,"arithexprprime"};
	actionTable[52][12]={0,"arithexprprime"};
	actionTable[52][13]={0,"arithexprprime"};
	actionTable[52][14]={0,"arithexprprime"};
	actionTable[52][15]={0,"arithexprprime"};
	actionTable[52][16]={0,"arithexprprime"};
	actionTable[52][17]={0,"arithexprprime"};
	actionTable[52][20]={0,"arithexprprime"};

	actionTable[53][1]={0,"multexprprime"};
	actionTable[53][6]={0,"multexprprime"};
	actionTable[53][9]={0,"multexprprime"};
	actionTable[53][10]={0,"multexprprime"};
	actionTable[53][12]={0,"multexprprime"};
	actionTable[53][13]={0,"multexprprime"};
	actionTable[53][14]={0,"multexprprime"};
	actionTable[53][15]={0,"multexprprime"};
	actionTable[53][16]={0,"multexprprime"};
	actionTable[53][17]={0,"multexprprime"};
	actionTable[53][20]={0,"multexprprime"};

	actionTable[54][1]={0,"multexprprime"};
	actionTable[54][6]={0,"multexprprime"};
	actionTable[54][9]={0,"multexprprime"};
	actionTable[54][10]={0,"multexprprime"};
	actionTable[54][12]={0,"multexprprime"};
	actionTable[54][13]={0,"multexprprime"};
	actionTable[54][14]={0,"multexprprime"};
	actionTable[54][15]={0,"multexprprime"};
	actionTable[54][16]={0,"multexprprime"};
	actionTable[54][17]={0,"multexprprime"};
	actionTable[54][20]={0,"multexprprime"};


	actionTable[55][0]={3,""};
	actionTable[55][2]={11,""};
	actionTable[55][3]={10,""};
	actionTable[55][4]={12,""};

	actionTable[56][1]={8,"ifstmt"};
	actionTable[56][20]={8,"ifstmt"};

	actionTable[57][1]={4,"assgstmt"};
}


void create_goto_table(){
    gotoTable[0][0]=1;
    gotoTable[0][2]=2;

    gotoTable[3][1]=5;
	gotoTable[3][2]=9;
	gotoTable[3][3]=4;
	gotoTable[3][4]=6;
	gotoTable[3][5]=7;
	gotoTable[3][6]=8;

	gotoTable[5][1]=5;
	gotoTable[5][2]=9;
	gotoTable[5][3]=14;
	gotoTable[5][4]=6;
	gotoTable[5][5]=7;
	gotoTable[5][6]=8;

	gotoTable[15][7]=18;
	gotoTable[15][9]=19;
	gotoTable[15][11]=20;
	gotoTable[15][13]=21;
	
	gotoTable[16][7]=25;
	gotoTable[16][9]=19;
	gotoTable[16][11]=20;
	gotoTable[16][13]=21;
	gotoTable[17][9]=26;
	gotoTable[17][11]=20;
	gotoTable[17][13]=21;
	gotoTable[19][8]=28;
	gotoTable[20][10]=34;

	gotoTable[21][12]=37;

	gotoTable[24][9]=40;
	gotoTable[24][11]=20;
	gotoTable[24][13]=21;

	gotoTable[28][9]=43;
	gotoTable[28][11]=20;
	gotoTable[28][13]=21;
	gotoTable[35][11]=44;
	gotoTable[35][13]=21;
	gotoTable[36][11]=45;

	gotoTable[40][1]=48;
	gotoTable[40][2]=9;
	gotoTable[40][4]=6;
	gotoTable[40][5]=7;
	gotoTable[40][6]=8;

	gotoTable[42][1]=49;
	gotoTable[42][2]=9;
	gotoTable[42][4]=6;
	gotoTable[42][5]=7;
	gotoTable[42][6]=8;

	gotoTable[44][10]=50;
	gotoTable[45][10]=51;
	gotoTable[46][12]=52;
	gotoTable[47][13]=53;
	
	gotoTable[55][1]=56;
	gotoTable[55][2]=9;
	gotoTable[55][4]=6;
	gotoTable[55][5]=7;
	gotoTable[55][6]=8;
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
	actionTable.resize(100,vector<pair<int,string>>(22));
    gotoTable.resize(100,vector<int>(14));
	create_table();
	stk.push({"start",0});
}

void reduce(int pop_num,const string &left){
	vector<string> vec;
	string tmp="";
	while(pop_num--){
		vec.push_back(stk.top().first);
		stk.pop();
	}
	for(int i=vec.size()-1;i>=0;--i){
		tmp+=vec[i]+' ';
	}
	if(!tmp.empty()){
		tmp.pop_back();
	}
	
	oldString.push_back(left);
	newString.push_back(tmp);
}
	
void old2new(){
	int n=newString.size()-1;
	ans.push_back("program =>");
	for(int i=n;i>=1;--i){
		string s=ans[n-i];
		int pos=s.rfind(oldString[i-1]);
		if(newString[i-1].empty()){ //reduce by a->ab
			s.replace(pos,oldString[i-1].size()+1,newString[i-1]);
		}
		else{
			s.replace(pos,oldString[i-1].size(),newString[i-1]);
		}
		if(i==1){
			s=s.substr(0,s.size()-3); //pop back => in the last string
		}
		ans.push_back(s);
	}
	
}

void error(string &lost,int line){
	cout<<"语法错误,第"+to_string(line)+"行,缺少\""+lost+"\""<<endl;
	cout<<"\n";
}

void LRparse(string &prog){
	for(int i=0;i<words.size();++i){
		stringstream ss(words[i]);
		string now;
		while(ss>>now){
			
			while(stk.top().first!="acc"){
				string str=stk.top().first;
				int state=stk.top().second;
				// if(str=="E"){
				// 	println(str);
				// 	continue ;
				// }
				if(TERMINALS.find(now)!=TERMINALS.end()){//now can be identified
					int idx=TERMINALS[now];
					int num=actionTable[state][idx].first;
					string left=actionTable[state][idx].second;
					if(left.size()==0){ // shift
						if(num==0){ 
							string lost=";";
							stk.push({lost,actionTable[state][6].first});
							error(lost,i);
							continue ;
						}
						stk.push({now,num});
						break ;
					}
					else{ // reduce
						reduce(num,left);
						int col=NONTERMINALS[left],go=gotoTable[stk.top().second][col];
						if(go==0){ 
							error(left,i);
						}
						stk.push({left,go});
					}
				}
				else{
					error(now,i);
				}
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
	words.push_back("$");
    LRparse(prog);
	old2new();
	for(const string &s:ans){
		cout<<s<<endl;
	}
    
    /********* End *********/
    
}