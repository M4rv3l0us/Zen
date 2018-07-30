#ifndef _FUNCTION_H_
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct TrieNode
{
	TrieNode *children[38];

	// isEndOfWord is true if the node represents
	// end of a word
	bool isEndOfWord;
	int count = 1;
	int loc[2];
	// loc[1,2] is para 1, word 2.
};
struct News
{
	string filename;
	string para[100];
	TrieNode *root;
};
TrieNode *getNode(void);
void createNews(News a[100]);
//TRIENODE
void insert(struct TrieNode *root, string key, int loc[]);
void search(TrieNode *&root, string &key, bool &checkintree, TrieNode *&pcur);
bool isStop(TrieNode *sroot, string s);
TrieNode stopwords(TrieNode *sroot);
void filterword(string &s);
bool isSub(string s1, string s2);
void input(TrieNode *root, string para[], string filename);
//OUTPUT,OPTIMIZE
bool isLeafNode(struct TrieNode* root);
void display(struct TrieNode* root, string str, int level);
void output(News a[]);
//SEARCHING
void searchPara(News a[], string key);
void searchInfile(News a[], string key);
#endif // !_FUNCTION_H_
