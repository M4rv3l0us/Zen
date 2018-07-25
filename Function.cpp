#include "Function.h"

void createNews(News a[100]) {
	string newsName = "Group22News", s;
	for (int i = 0; i <= 99; i++)
	{
		std::string s = std::to_string(i + 1);
		if (i < 10) s = "0" + s;
		s += ".txt";
		newsName += s;
		a[i].filename == newsName;
		a[i].root = NULL;
	}
}
void insert(struct TrieNode *root, string key)
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

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
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
		if (s[i] < 48 || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || s[i] >122 || s[i] == ' ' || s[i] == '\n')
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
}
bool checkEnd(string s)
{
	if (isSub(s, ".\n\n")) return true;
	 return false;
}
void input(TrieNode *root)
{
	ifstream fin;
	fin.open("Group22News01.txt");
	string s, stuff;
	TrieNode *sroot = getNode();
	*sroot = stopwords(sroot);
	int i = 0;
	while (fin.good()) {
		getline(fin, s, ' ');
		if (!checkEnd(s))
		{
			filterword(s);
			while (isStop(sroot, s))
			{
				getline(fin, s, ' ');
				filterword(s);
			}
		}
		if (checkEnd(s))
		{ //homeless./n/nCorrections
			while (s[i] != '.')
				i++;
			int n = s.length();
			for (int k = 0; k<i; k++)
			{
				stuff += s[k];
			}
			s.erase(s.begin(), s.begin() + i+3);
			filterword(stuff);
			if (!isStop(sroot,stuff))
			{
				insert(root, stuff);
			}
			i = 0;
			stuff.clear();
			filterword(s);
			while (isStop(sroot, s))
			{
				getline(fin, s, ' ');
				filterword(s);
			}
		}
		insert(root, s);
	}
	fin.close();
}
TrieNode *getNode(void)
{
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < 26; i++)
		pNode->children[i] = NULL;

	return pNode;
}