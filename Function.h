#pragma once
#ifndef _FUNCTION_H_
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
struct TrieNode
{
	TrieNode *children[38];

	// isEndOfWord is true if the node represents
	// end of a word
	bool isEndOfWord;
	string filename;
	int count = 1;
	int loc[50];
	// loc={1,2,3} para 1, para 2, para 3
};
struct News
{
	string filename;
	string para[100];
	TrieNode *root;
};
TrieNode *getNode(void);
void createNews(News a[100]);
//void newcreateNews(News a[100]);
//TRIENODE
void insert(struct TrieNode *root, string key, int loc, string filename);
//void newinsert(struct TrieNode *root, string key, string filename, int loc[]);
void search(TrieNode *&root, string &key, bool &checkintree, TrieNode *&pcur);
bool isStop(TrieNode *sroot, string s);
TrieNode stopwords(TrieNode *sroot);
void filterword(string &s);
bool isSub(string s1, string s2);
void input(TrieNode *root, string para[], string filename);
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
void AND(string searchword, News a[]);
void OR(string searchword, News a[]);
void placeholder(string searchword, News a[]);
void intitle(string searchword, News a[]);
void exactmatch(string searchword, News a[]);


#endif // !_FUNCTION_H_
