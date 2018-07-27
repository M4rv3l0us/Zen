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
	int count = 0;
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
void insert(struct TrieNode *root, string key);
bool search(struct TrieNode *root, string key);
bool isStop(TrieNode *sroot,string s);
TrieNode stopwords(TrieNode *sroot);
void filterword(string &s);
bool isSub(string s1, string s2);
void input(TrieNode *root, string para[], string filename);
#endif // !_FUNCTION_H_
