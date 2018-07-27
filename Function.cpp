#include "Function.h"

void createNews(News a[100]) {
	string newsName = "Group22News", s;
	for (int i = 0; i <= 99; i++)
	{
		std::string s = std::to_string(i + 1);
		if (i < 10) s = "0" + s;
		s += ".txt";
		newsName += s;
		a[i].filename = newsName;
		a[i].root = getNode();
		input(a[i].root, a[i].para, newsName);
	}
}
void insert(struct TrieNode *root, string key) //insert word into Trie
{
	struct TrieNode *pCrawl = root;
	int index;
	for (int i = 0; i < key.length(); i++)
	{
		if (key[i] > 60 && key[i] < 123)
		{
			index = key[i] - 'a';
		}
		else if (key[i] > 47 && key[i] < 58)
			index = key[i] - '0';

		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	if (pCrawl->isEndOfWord == true) pCrawl->count++;
	pCrawl->isEndOfWord = true;
}
bool search(struct TrieNode *root, string key)
{
	struct TrieNode *pCrawl = root;
	int index;
	for (int i = 0; i < key.length(); i++)
	{
		if (key[i] > 60 && key[i] < 123)
		{
			index = key[i] - 'a';
		}
		else if (key[i] > 47 && key[i] < 58)
			index = key[i] - '0';

		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl != NULL && pCrawl->isEndOfWord);
}
TrieNode stopwords(TrieNode *sroot)
{
	ifstream fin;
	fin.open("stopwords.txt");
	sroot = getNode();
	string a;
	while (fin.good())
	{
		getline(fin, a, '\n');
		filterword(a);
		insert(sroot, a);
	}
	fin.close();
	return *sroot;
}
bool isStop(TrieNode *sroot, string s)
{
	if (search(sroot, s)) return true;
	return false;
}
void filterword(string &s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if ((s[i] < 48 && s[i] > 32 )|| (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || s[i] >122 || s[i] == -106)
		{
			s.erase(s.begin() + i);
			i--;
		}

	}
	int i = 0;
	while (s[i])
	{
		s[i] = tolower(s[i]);
		i++;
	}
}
bool isSub(string s1, string s2)
{
	if (s1.find(s2) != std::string::npos) {
		return true;
	}
	else return false;
} //check string 
bool checkEnd(string s)
{
	if (isSub(s, "\n\n")) return true;
	return false;
}// check end of paragrap.h //check end of paragraph
void input(TrieNode *root, string para[], string filename) //Nhap tat ca words trong 1 News vao 1 Trie
{
	ifstream fin;
	fin.open(filename);
	string s, stuff;
	TrieNode *sroot = getNode();
	*sroot = stopwords(sroot);
	int i = 0, j = 0;
	int k = 0;
	while (fin.good()) {
		k = 0;
		getline(fin, s, '\n');
		para[j] = s;
		j++;
		filterword(s);
		while(k!=-1)
		{
			k = s.find(' ');
			stuff = s.substr(i, k);
			i = 0;
			if (k != -1)
			{
				s.erase(s.begin(), s.begin() + k + 1);
			}
			if (!isStop(sroot, stuff)) insert(root, stuff);
			stuff.clear();
		}
	}
	fin.close();
}
TrieNode *getNode(void)
{
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < 38; i++)
		pNode->children[i] = NULL;

	return pNode;
}