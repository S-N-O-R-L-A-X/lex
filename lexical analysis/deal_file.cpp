#include <iostream>
#include <fstream>
using namespace std;
int main(){
    ifstream fin("./c_keys copy.txt");
    ofstream fout("./out.txt");
    while(!fin.eof()){
        string s;
        fin>>s;
        s="{\""+s+"},";
        fout<<s;
        cout<<s<<endl;
    }   
}