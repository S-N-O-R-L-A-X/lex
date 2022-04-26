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
#include <regex>
#include <unordered_set>
using namespace std;
/* 不要修改这个标准输入函数 */
unordered_map<string,int> string2num;
unordered_set<char> sign;
vector<string> ans;
void init(){
	string2num={{"auto",1},{"break",2},{"case",3},{"char",4},{"const",5},{"continue",6},{"default",7},{"do",8},{"double",9},{"else",10},{"enum",11},{"extern",12},{"float",13},{"for",14},{"goto",15},{"if",16},{"int",17},{"long",18},{"register",19},{"return",20},{"short",21},{"signed",22},{"sizeof",23},{"static",24},{"struct",25},{"switch",26},{"typedef",27},{"union",28},{"unsigned",29},{"void",30},{"volatile",31},{"while",32},{"-",33},{"--",34},{"-=",35},{"->",36},{"!",37},{"!=",38},{"%",39},{"%=",40},{"&",41},{"&&",42},{"&=",43},{"(",44},{")",45},{"*",46},{"*=",47},{",",48},{".",49},{"/",50},{"/=",51},{":",52},{";",53},{"?",54},{"[",55},{"]",56},{"^",57},{"^=",58},{"{",59},{"|",60},{"||",61},{"|=",62},{"}",63},{"~",64},{"+",65},{"++",66},{"+=",67},{"<",68},{"<<",69},{"<<=",70},{"<=",71},{"=",72},{"==",73},{">",74},{">=",75},{">>",76},{">>=",77},{"\"",78},{"/*注释*/",79},{"常数",80},{"标识符",81}};
	sign={'<', '>', '=', '+', '-', '*', '/', ':', ';', '(', ')', '[', ']', '|', '"', ',', '&'};
}

void read_prog(string& prog)
{
	char c;
	while(scanf("%c",&c)!=EOF){
		prog += c;
	}
}
/* 你可以添加其他函数 */
void easy_deal(const string &str,int cnt){
	if(string2num.find(str)!=string2num.end()){
		ans.push_back(to_string(cnt)+":<"+str+","+to_string(string2num[str])+">");
	}
	else{
		ans.push_back(to_string(cnt)+":<"+str+",81"+">");
	}
}

void deal(string &str){
	stringstream ss(str);
	string now;
	int cnt=1;
	while(ss>>now){
		if(string2num.find(now)!=string2num.end()){
			ans.push_back(to_string(cnt)+":<"+now+","+to_string(string2num[now])+">");
		}
		else{
			int start=0;
			for(int i=0;i<now.size();){
				if(sign.find(now[i])!=sign.end()){//sign
					string former=now.substr(start,i-start);
					easy_deal(now.substr(start,i-start),cnt);
					start=i;
					while(i<now.size()&&sign.find(now[i])!=sign.end()){//always sign
						i++;
					}
					string signs=now.substr(start,i-start);
					
					easy_deal(signs,cnt);
				}
				else{
					++i;
				}
			}
			easy_deal(now.substr(start,now.size()),cnt);
		}
	}
}

void Analysis()
{
	string prog;
	read_prog(prog);
	/* 骚年们 请开始你们的表演 */
    /********* Begin *********/
    init();
    deal(prog);
	for(const string & line:ans){
		cout<<line<<endl;
	}
    /********* End *********/
	cout<<"end!";
}