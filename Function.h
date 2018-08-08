#pragma once
#ifndef _FUNCTION_H_
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <windows.h>
using namespace std;
struct number {
	string data;
	number *next;
};
struct TrieNode
{
	TrieNode *children[38];

	// isEndOfWord is true if the node represents
	// end of a word
	bool isEndOfWord;
	string filename;
	int count = 1;
	int loc[50];
	string *syn;
	// loc={1,2,3} para 1, para 2, para 3
};
struct News
{
	string filename;
	string para[100];
	TrieNode *root;
};
struct RankSys {
	int filename;
	int times = 0;
	int loc;
	int ofpcur;
	string s;
};
TrieNode *getNode(void);
void createNews(News a[], int numfile, number *&nroot);
//void newcreateNews(News a[100]);
//TRIENODE
void insert(struct TrieNode *root, string key, int loc, string filename);
void search(TrieNode *&root, string &key, bool &checkintree, TrieNode *&pcur);
bool isStop(TrieNode *sroot, string s);
TrieNode stopwords(TrieNode *sroot);
void filterword(string &s);
bool isSub(string s1, string s2);
void input(TrieNode *root, string *para, string filename, number *&nroot, number *&cur);
//void inputpara(TrieNode*root, string para[], string filename);
//OUTPUT,OPTIMIZE
bool isLeafNode(struct TrieNode* root);
void display(ofstream &fout, struct TrieNode* root, char word[], int level);
void output(TrieNode *hroot);
//-------------------------------HISTORY---------------------------------
int findex(int level);
bool isLastNode(struct TrieNode* root);
void suggestionsRec(struct TrieNode* root, string currPrefix);
int printAutoSuggestions(TrieNode* root, const string query);
void updatehistoryTrie(TrieNode *hroot, string a);
void inputhistoryTrie(TrieNode *hroot);
//SEARCHING
void xoa(int a[], int&n);
void searchInfile(News a[], string key);
void SINGLE(string a, int n, News b[]);
void AND(string searchword,int numfile, News a[]);
void OR(string searchword,int numfile, News a[]);
void WHOLE(string searchword,int numfile, News a[]);
void MINUS(string searchword, int numfile, News a[]);
void PLACEHOLDER(string searchword,int numfile, News a[]);
void INTITLE(string searchword, int numfile, News a[]);
void TXT(string searchword, int numfile, News a[]);
void SUPERAND(string searchword, int numfile, News a[]);
//-----------------------------------------------ULTIMATE--------------------------------------------
void splitblock(string s, string *&block, int &numblock);
void searchblock(News a[], int numfile, string block[], int numblock);
void printblock(string para, string block[], int numblock);
int count(string s, char sub);
void swap(RankSys *&xp, RankSys *&yp);
void rankingone(News a[], int numfile, string key);
void rankingtwo(News a[],int numfile, string s1, string s2);
void rankingthree(News a[], int numfile, string s1, string s2);
void rankingor(News a[],int numfile, string s1, string s2);
void rankingwhole(News a[],int numfile, string s); 
void rankingminus(News a[], int numfile, string s1, string s2);
void rankingtitle(News a[], int numfile, string key);
void printpara(string para, string s);
void printparatwo(string para, string s1, string s2);
void printparawhole(string para, string s);
//Synonym
void SYN(string searchword, int numfile, News a[]);
void rankingsyn(News a[], int numfile, string s);
void inputsyntrie(TrieNode *&sroot);
void insertsyntrie(TrieNode *&sroot, string key, string *syn);
void checkinsyntree(TrieNode *&root, string key, bool&check, string *&syn);
void outputsyn(TrieNode *sroot);
//NUMBERLAND
void insertnumber(number * &nroot, string key, number *&cur);
void rankingnum(News a[], int numfile, string s1, string s2, number *&nroot);
void NUM(string searchword, News a[], int numfile, number *&nroot);
#endif // !_FUNCTION_H_
