#include "Function.h"

//DATABASE
void createNews(News a[100]) {
	string newsName = "Group22News", s; 
	for (int i = 0; i <= 99; i++)
	{
		std::string s = std::to_string(i + 1); //convert number into string
		if (i <= 8) s = "0" + s;
		s += ".txt";
		newsName += s; // create News' name, e.g Group22News01.txt
		a[i].filename = newsName;
		a[i].root = getNode(); // create new node
		input(a[i].root, a[i].para, newsName); //input root, para and name of a News into database
		newsName = "Group22News";
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
			index = key[i] - 'a'; //index of alphabet: a->z = 0->25
		}
		else if (key[i] == 35)
			index = 26;           //index of hastag #
		else if (key[i] == 36)
			index = 27;			  //index of dollar sign $
		else if (key[i] > 47 && key[i] < 58)
			index = key[i] - '0' + 27;  //index of number 0->9
		// The TrieNode looks like: a b c d e f g h j k l m n o p q r s t u v w x y z # $ 0 1 2 3 4 5 6 7 8 9 
		if (!pCrawl->children[index])

			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	if (pCrawl->isEndOfWord == true) pCrawl->count++; // count the end of words (not yet completed)
	pCrawl->isEndOfWord = true;
}
bool search(struct TrieNode *root, string key) //search TrieNode
{
	struct TrieNode *pCrawl = root;
	int index=0;
	for (int i = 0; i < key.length(); i++)
	{
		if (key[i] > 60 && key[i] < 123)
		{
			index = key[i] - 'a'; //index of alphabet: a->z = 0->25
		}
		else if (key[i] == 35)
			index = 26;           //index of hastag #
		else if (key[i] == 36)
			index = 27;			  //index of dollar sign $
		else if (key[i] > 47 && key[i] < 58)
			index = key[i] - '0' + 27;  //index of number 0->9

		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl != NULL && pCrawl->isEndOfWord);
}
TrieNode stopwords(TrieNode *sroot) //stopwords filter
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
bool isStop(TrieNode *sroot, string s) //check stopwords
{
	if (search(sroot, s)) return true;
	return false;
}
void filterword(string &s) //filter bullshit characters such as " +-*/ and tolower word
{
	for (int i = 0; i < s.length(); i++)
	{
		if ((s[i] < 35 && s[i] > 32) || s[i] > 36 && s[i] <48 || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || s[i] > 122 || s[i] < 0)
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
		while (s.empty())
			getline(fin, s, '\n');
		para[j] = s; //store the paragraph
		j++;
		filterword(s); //filter words
		while(k!=-1)
		{	//After losing homeless
			k = s.find(' '); // find the location of ' '
			stuff = s.substr(i, k); //copy the substring from start to location of ' '
			i = 0; //reset i
			if (k != -1)
			{
				s.erase(s.begin(), s.begin() + k + 1); // delete the string from start to location of ' '+1
			}
			if (!isStop(sroot, stuff) && stuff != " ")
				insert(root, stuff); // checkstop and insert
			stuff.clear(); // clear stuff
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
//SEARCHING
bool isinTrie(TrieNode *root, string key)
{
	if (search(root, key)) return true;
	return false;
}
void searchInfile(News a[], string key)
{
	for (int i = 0; i < 99; i++)
	{
		if (isinTrie(a[i].root, key))
			cout << a[i].filename << endl;
	}
}
void searchPara(News a[], string key)
{
	int b[100];
	for (int j = 0; j < 99; j++)
	{
		b[j] = 0;
	}
	int i = 0, j = 0;

}
