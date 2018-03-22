
#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
using namespace std;
struct prefixTree{
	char c;
	prefixTree *Child[26];
	bool end;
};
typedef prefixTree *Tree;

void CreateTree( Tree &t ){										//khoi tao gia tri cho cay					
	t->c = ' ' ;
	for( int i = 0 ; i < 26 ; i++ ) t->Child[i] = NULL ;
	t->end = false ;
}
void InstallTree(Tree &cp, string s) {							// truyen tu vao cay
	prefixTree *t = cp;
	for (int i = 0; i < s.size(); i++) {							
		if (t->Child[s[i] - 97] == NULL) {						
			Tree tNew=new prefixTree; 
			CreateTree(tNew);
			tNew->c = s[i];
			t->Child[s[i] - 97] = tNew;
		}
		
		if(i==s.size()-1)t->Child[s[i] - 97]->end=true;
		t=t->Child[s[i] - 97];
	}	
}

void PrintTree(Tree t,string s) {								//in ra xau s+ chuoi ky tu trong cay truyen vao
	if (t->end == true)
		cout << s<<endl;	
	string cps =s;
	Tree cpt=t;
	
	for (int i = 0; i < 26; i++){
		if (t->Child[i] != NULL) {
			t=t->Child[i];
			s+= t->c;		
			PrintTree(t,s);
		}
	t=cpt;
	s=cps;
	}	
}			
void PrintSuggest(Tree t, string s) {							// in ra tu goi y
	Tree cpt=t;	
	for (int i = 0; i < s.size(); i++){							// xac dinh xau s trong cay tu dien,tim cay con cua s
		if(t->Child[s[i] - 97]==NULL){
			cout << "Can't suggest"<<endl;
			return;
		}	
		t= t->Child[s[i] - 97];
	 }	 
	PrintTree(t, s);
}

int main() {
	string s,CLOSE="no";
	Tree t=new prefixTree;
	CreateTree(t);
	ifstream ifs;
	ifs.open("dictionary.txt");
	if (ifs.fail()) {
		cout << "File khong ton tai\n";
		return 0;
	}
	while (ifs.eof() == false) {
		string ss;
		ifs >> ss;
		InstallTree(t, ss);
	};
	ifs.close();

		while (CLOSE!="yes") {
		cout << "\n\n\n Typing: ";
		fflush(stdin); cin >> s;
		cout << endl<<"Suggestion:"<<endl;
		PrintSuggest(t, s);
		cout << "\n\n\nDo you want to close? : " << endl;
		cin >> CLOSE;
	}
	return 0;
}

