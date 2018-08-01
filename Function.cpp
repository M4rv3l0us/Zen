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
/*void newcreateNews(News a[100]) {
string s, orifilename = "Group22News";
ifstream fin;
fin.open("newtrie.txt");
string stuff;
string time, filename;
while (fin.good()) {
for (int i = 0; i <= 99; i++)
{
std::string s = std::to_string(i + 1); //convert number into string
if (i <= 8) s = "0" + s;
s += ".txt";
orifilename += s; // create News' name, e.g Group22News01.txt
a[i].filename = orifilename;
a[i].root = getNode(); // create new node
inputpara(a[i].root, a[i].para, orifilename);
while (fin.good())
{
int loc[50] = { 0 };
getline(fin, s, ',');
if (s == "isendoftrie") break;
getline(fin, filename, ',');
getline(fin, time, ',');
int t_dec = stoi(time, 0, 10);
int j = 0;
for (; j<t_dec - 1; j++)
{
getline(fin, stuff, ',');
int i_dec = stoi(stuff, 0, 10);
loc[j] = i_dec;
}
getline(fin, stuff, '\n');
int i_dec = stoi(stuff, 0, 10);
loc[j] = i_dec;
newinsert(a[i].root, s, orifilename, loc);
}
orifilename = "Group22News";
}
}
}*/
void insert(struct TrieNode *root, string key, int loc, string filename) {
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
			index = key[i] - '0' + 28;  //index of number 0->9
										// The TrieNode looks like: a b c d e f g h j k l m n o p q r s t u v w x y z # $ 0 1 2 3 4 5 6 7 8 9 
		if (!pCrawl->children[index])

			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	if (pCrawl->isEndOfWord == true) pCrawl->count++; // count the end of words (not yet completed)
	pCrawl->isEndOfWord = true;
	pCrawl->filename = filename;
	if (pCrawl->loc[0] == 0) {
		pCrawl->loc[0] = loc;
	}
	else
	{
		int k = 0;
		while (pCrawl->loc[k] != 0) k++;
		pCrawl->loc[k] = loc;
	}
}
/*void newinsert(struct TrieNode *root, string key, string filename, int loc[]) {
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
index = key[i] - '0' + 28;  //index of number 0->9
// The TrieNode looks like: a b c d e f g h j k l m n o p q r s t u v w x y z # $ 0 1 2 3 4 5 6 7 8 9
if (!pCrawl->children[index])

pCrawl->children[index] = getNode();

pCrawl = pCrawl->children[index];
}

// mark last node as leaf
if (pCrawl->isEndOfWord == true) pCrawl->count++; // count the end of words (not yet completed)
pCrawl->isEndOfWord = true;
pCrawl->filename = filename;
for (int i = 0; i < pCrawl->count; i++)
pCrawl->loc[i] = loc[i];
}*/
void search(TrieNode *&root, string &key, bool &checkintree, TrieNode *&pcur) //search TrieNode
{
	struct TrieNode *pCrawl = root;
	int index = 0;
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
			index = key[i] - '0' + 28;  //index of number 0->9

		if (!pCrawl->children[index])
		{
			checkintree = false;
			return;
		}

		pCrawl = pCrawl->children[index];
	}
	if (pCrawl->isEndOfWord)
	{
		checkintree = true;
		pcur = pCrawl;
		return;
	}
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
		insert(sroot, a, 0, "trie.txt");
	}
	fin.close();
	return *sroot;
}
bool isStop(TrieNode *sroot, string s) //check stopwords
{
	bool checkintree = false;
	TrieNode *pcur = getNode();
	search(sroot, s, checkintree, pcur);
	if (checkintree) return true;
	return false;
}
void filterword(string &s) //filter bullshit characters such as " +-*/ and tolower word
{
	for (int i = 0; i < s.length(); i++)
	{
		if ((s[i] < 35 && s[i] > 32) || s[i] > 36 && s[i] <42 ||42<s[i] && s[i]<48 || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || s[i] > 122 || s[i] < 0)
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
	int j = 1, k = 0;
	int loc;
	while (fin.good()) {
		k = 0;
		getline(fin, s, '\n');
		while (s.empty())
			getline(fin, s, '\n');
		para[j] = s;//store the paragraph
		loc = j;
		j++;
		filterword(s); //filter words
		while (k != -1)
		{	//After losing homeless
			k = s.find(' ');
			// find the location of ' '
			stuff = s.substr(0, k); //copy the substring from start to location of ' '
			if (k != -1)
			{
				s.erase(s.begin(), s.begin() + k + 1); // delete the string from start to location of ' '+1
			}
			if (stuff != " ")
				insert(root, stuff, loc, filename); // checkstop and insert
			stuff.clear(); // clear stuff
		}
	}
	fin.close();
}
/*void inputpara(TrieNode*root, string para[], string filename) {
ifstream fin;
fin.open(filename);
int i = 0;
string s;
while (fin.good()) {
getline(fin, s, '\n');
while (s.empty())
getline(fin, s, '\n');
para[i] = s;//store the paragraph
i++;
}
fin.close();
}*/
TrieNode *getNode(void)
{
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < 38; i++)
		pNode->children[i] = NULL;
	for (int j = 0; j < 49; j++)
		pNode->loc[j] = 0;

	return pNode;
}
//OUTPUT,OPTIMIZE
/*bool isLeafNode(struct TrieNode* root)
{
return root->isEndOfWord != false;
}
// function to display the content of Trie
void display(ofstream &fout, struct TrieNode* root, char word[], int level)
{
if (isLeafNode(root))
{
word[level] = '\0';
fout << word << "," << root->filename << "," << root->count;
for (int j = 0; j < root->count; j++)
{
if (root->loc[j] != 0)
fout << "," << root->loc[j];
}
fout << endl;
}
int i;
for (i = 0; i < 38; i++)
{
// if NON NULL child is found
// add parent key to str and
// call the display function recursively
// for child node
if (root->children[i])
{
if (i < 26)
{
word[level] = i + 'a'; //index of alphabet: a->z = 0->25
}
else if (i == 26)
word[level] = '#';//index of hastag #
else if (i == 27)
word[level] = '$';		  //index of dollar sign $
else if (i > 27 && i < 38)
word[level] = i - 28 + '0';  //index of number 0->9
display(fout, root->children[i], word, level + 1);
}
}
}
void output(News a[])
{
ofstream fout;
fout.open("trie.txt");
string t;
char word[20];
int level = 0;
for (int i = 0; i <= 99; i++)
{
a[i].root->isEndOfWord = false;
display(fout, a[i].root, word, level);
}
fout.close();
}*/
//SEARCHING
void searchInfile(News a[], string key)
{
	bool checkintree = false;
	TrieNode *pcur = getNode();
	for (int i = 0; i < 99; i++)
	{
		search(a[i].root, key, checkintree, pcur);
		if (checkintree == true && pcur->isEndOfWord)
		{
			cout << a[i].filename << endl;
			cout << "Times: " << pcur->count << endl;
			cout << "Loc: ";
			for (int j = 0; j < pcur->count; j++)
				if (pcur->loc[j] != 0)
					cout << pcur->loc[j] << ",";
			cout << endl;
			cout << a[i].para[pcur->loc[0]] << endl;
		}

	}
}
void searchPara(News a[], string key)
{
	bool checkintree = false;
	TrieNode *pcur = getNode();
	for (int i = 0; i < 99; i++)
	{
		search(a[i].root, key, checkintree, pcur);
		if (checkintree == true && pcur->isEndOfWord)
		{
			cout << a[i].filename << endl;
			cout << "Times: " << pcur->count << endl;
			cout << a[i].para[pcur->loc[0]];
		}
	}
}

void AND(string searchword, News a[])
{
	TrieNode *pcur1 = getNode(), *pcur2 = getNode();
	bool a1 = false, a2 = false;
	string s1, s2;
	if (searchword.find('AND') == -1)
	{
		return;
	}
	else
	{
		s1 = searchword.substr(0, searchword.find('AND') - 3);
		s2 = searchword.substr(searchword.find('AND') + 2);
	}
	for (int i = 0; i < 99; i++)
	{
		search(a[i].root, s1, a1, pcur1);
		search(a[i].root, s2, a2, pcur2);
		if (a1 == true && pcur1->isEndOfWord && a2 == true && pcur2->isEndOfWord)
		{
			cout << a[i].filename;

		}
	}
}
void OR(string searchword, News a[])
{
	TrieNode *pcur1 = getNode(), *pcur2 = getNode();
	bool a1 = false, a2 = false;
	string s1, s2;
	if (searchword.find('OR') == -1)
	{
		return;
	}
	else
	{
		s1 = searchword.substr(0, searchword.find('OR') - 2);
		s2 = searchword.substr(searchword.find('OR') + 1);
	}
	for (int i = 0; i < 99; i++)
	{
		search(a[i].root, s1, a1, pcur1);
		search(a[i].root, s2, a2, pcur2);
		if ((a1 == true && pcur1->isEndOfWord) || (a2 == true && pcur2->isEndOfWord))
		{
			cout << a[i].filename;

		}
	}
}
void placeholder(string searchword, News a[])
{
	TrieNode *pcur1 = getNode(), *pcur2 = getNode();
	bool a1 = false, a2 = false;
	string s1, s2;
	ifstream fin;
	string temp;
	if (searchword.find('*') == -1)
	{
		return;
	}
	else
	{
		s1 = searchword.substr(0, searchword.find('*') - 1);
		s2 = searchword.substr(searchword.find('*') + 1);
	}
	for (int i = 0; i < 99; i++)
	{
		search(a[i].root, s1, a1, pcur1);
		if (a1 == true && pcur1->isEndOfWord)
		{
			fin.open(a[i].filename);
			getline(fin, temp, ' ');
			while (temp.compare(s1) != 0)
			{
				getline(fin, temp, ' ');
				if (temp.compare(s1) == 0)
				{
					getline(fin, temp, ' ');
					getline(fin, temp, ' ');
					if (temp.compare(s2) == 0)
					{
						cout << a[i].filename;
					}
				}
			}
		}
	}
}