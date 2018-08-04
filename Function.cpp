#include "Function.h"

//DATABASE
int findex(int level)
{
	int index = 0;
	if (level > 96 && level < 123)
	{
		index = level - 'a'; //index of alphabet: a->z = 0->25
	}
	else if (level == 35)
		index = 26;           //index of hastag #
	else if (level == 36)
		index = 27;			  //index of dollar sign $
	else if (level > 47 && level < 58)
		index = level - '0' + 28;  //index of number 0->9
	return index;
}
void createNews(News a[], int numfile) {
	clock_t begin = clock();
	string newsName = "Group22News", s;
	for (int i = 0; i < numfile ;i++)
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
	clock_t end = clock();
	cout << "Time run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;
}
void insert(struct TrieNode *root, string key, int loc, string filename) {
	struct TrieNode *pCrawl = root;
	int index =0;
	for (int i = 0; i < key.length(); i++)
	{
		index = findex(key[i]);
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
void search(TrieNode *&root, string &key, bool &checkintree, TrieNode *&pcur) //search TrieNode
{
	struct TrieNode *pCrawl = root;
	int index = -1;
	for (int i = 0; i < key.length(); i++)
	{	
		index = findex(key[i]);
	
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
		if ((s[i] < 35 && s[i] > 32) || s[i] > 36 && s[i] <42 || 42<s[i] && s[i]<48 || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || s[i] > 122 || s[i] < 0)
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
void input(TrieNode *root, string *para, string filename) //Nhap tat ca words trong 1 News vao 1 Trie
{
	ifstream fin;
	fin.open(filename);
	string s, stuff;
	TrieNode *sroot = getNode();
	*sroot = stopwords(sroot);
	TrieNode *synroot = getNode();
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
			{
				insert(root, stuff, loc, filename); // checkstop and insert
			}
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


bool isLeafNode(struct TrieNode* root)
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
void output(TrieNode *hroot)
{
ofstream fout;
fout.open("historyTrie.txt");
string t;
char word[20];
int level = 0;
hroot->isEndOfWord = false;
display(fout, hroot, word, level);
fout.close();
}
void outputsyn(TrieNode *sroot) {
	ofstream fout;
	fout.open("synTrie.txt");
	string t;
	char word[20];
	int level = 0;
	sroot->isEndOfWord = false;
	display(fout, sroot, word, level);
	fout.close();
}


//HISTORY



bool isLastNode(struct TrieNode* root)
{
	for (int i = 0; i < 38; i++)
		if (root->children[i])
			return 0;
	return 1;
}
// Recursive function to print auto-suggestions for given
// node.
void suggestionsRec(struct TrieNode* root, string currPrefix)
{
	// found a string in Trie with the given prefix
	if (root->isEndOfWord)
	{
		cout << currPrefix;
		cout << endl;
	}

	// All children struct node pointers are NULL
	if (isLastNode(root))
		return;

	for (int i = 0; i < 38; i++)
	{
		if (root->children[i])
		{
			// append current character to currPrefix string
			currPrefix.push_back(97 + i);

			// recur over the rest
			suggestionsRec(root->children[i], currPrefix);
			currPrefix.pop_back();
		}
	}
}
// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* root, const string query)
{
	struct TrieNode* pCrawl = root;

	// Check if prefix is present and find the
	// the node (of last level) with last character
	// of given string.
	int level;
	int n = query.length();
	for (level = 0; level < n; level++)
	{
		int index = findex(query[level]);

		// no string in the Trie has this prefix
		if (!pCrawl->children[index])
			return 0;

		pCrawl = pCrawl->children[index];
	}

	// If prefix is present as a word.
	bool isWord = (pCrawl->isEndOfWord == true);

	// If prefix is last node of tree (has no
	// children)
	bool isLast = isLastNode(pCrawl);

	// If prefix is present as a word, but
	// there is no subtree below the last
	// matching node.
	if (isWord && isLast)
	{
		cout << query << endl;
		return -1;
	}

	// If there are are nodes below last
	// matching character.
	if (!isLast)
	{
		string prefix = query;
		suggestionsRec(pCrawl, prefix);
		return 1;
	}
}
void updatehistoryTrie(TrieNode *hroot, string a)
{
	ofstream fout;
	inputhistoryTrie(hroot);
	filterword(a);
	insert(hroot, a, 0, "historyTrie.txt");
	output(hroot);
}
void inputhistoryTrie(TrieNode *hroot)
{
	ifstream fin;
	fin.open("historyTrie.txt");
	string s, stuff;
	while (fin.good())
	{
		getline(fin, s, ',');
		getline(fin, stuff, '\n');
		insert(hroot, s,0,"historyTrie.txt");
	}
	fin.close();
}



//SEARCHING & FEATURE


void splitblock(string s, string *&block, int &numblock)
{
	bool checkintree = false;
	if (isSub(s, " ")) {
		int  n = count(s, ' ') + 1;
		int k = 0, i = 0;
		block = new string[n];
		TrieNode *pcur[50];
		while (k != -1)
		{
			k = s.find(' ');
			block[i] = s.substr(0, k);
			filterword(block[i]);
			if (k != -1)
				s.erase(s.begin(), s.begin() + k + 1);
			i++;
		}
		numblock = i;
	}
}
void searchblock(News a[], int numfile, string block[], int numblock)
{
	clock_t begin = clock();
	RankSys rank[100];
	int fuck = 0;
	bool checkintree = false;
	TrieNode *pcur = getNode();
	int o = 0;
	for (int i = 0; i < numfile; i++)
	{
		for (int j = 0; j < numblock; j++)
		{
			search(a[i].root, block[j], checkintree, pcur);
			if (checkintree == true && pcur->isEndOfWord)
			{
				rank[o].times = pcur->count;
				rank[o].filename = i;
				rank[o].ofpcur = j;
				rank[o].loc = pcur->loc[0];
				o++;
			}
			else {
				rank[o].times = 0;
				fuck++;
			}
		}
	}
	if (fuck == 100) {
		cout << "FUCK!";
		return;
	}
	int i, j;
	bool swapped;
	for (i = 0; i < 99; i++)
	{
		swapped = false;
		for (j = 0; j < 99 - i; j++)
		{
			if (rank[j].times < rank[j + 1].times)
			{
				swap(rank[j], rank[j + 1]);
				swapped = true;
			}
		}

		// IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
	int k = 0;
	while (rank[k].times != 0 && k<5)
	{
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 4);
		cout << a[rank[k].filename].filename << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		cout << "Times: " << rank[k].times << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		cout << "In para: " << endl;
		printpara(a[rank[k].filename].para[rank[k].loc], block[rank[k].ofpcur]);
		cout << endl;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 2);
		cout << "/////////////////////////////////////////////////////////" << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		k++;
	}
	clock_t end = clock();
	cout << "Time run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;
}
void printblock(string para, string block[], int numblock)
{
	string stuff, fil;
	int k = 0;
	while (k != -1)
	{
		k = para.find(' ');
		// find the location of ' '
		stuff = para.substr(0, k); //copy the substring from start to location of ' '
		fil = stuff;
		filterword(fil);
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 7);
		for (int i = 0; i < numblock; i++)
		{
			if (fil == block[i])
			{
				HANDLE hConsoleColor;
				hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsoleColor, 4);
				cout << stuff;
			}
			else
				cout << stuff;
			if (k != -1)
			{
				para.erase(para.begin(), para.begin() + k + 1); // delete the string from start to location of ' '+1
			}
			cout << " ";
			fil.clear();
		}
		
	}

}
void AND(string searchword,int numfile, News a[])
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
	filterword(s1);
	filterword(s2);
	rankingtwo(a,numfile, s1, s2);
}
void OR(string searchword, int numfile, News a[])
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
		s2 = searchword.substr(searchword.find('OR') +2);
	}
	filterword(s1);
	filterword(s2);
	rankingor(a,numfile, s1, s2);
}
void WHOLE(string searchword, int numfile, News a[])
{
	TrieNode *pcur = getNode();
	string s;
	int i = searchword.find('\"');
	if (i == -1)
	{
		return;
	}
	else
	{
		s = searchword.substr(searchword.find('\"') +1);
		s.pop_back();
	}
	if (s.find(" ") == -1) rankingone(a, numfile,s);
	else
	rankingwhole(a,numfile, s);
}
void placeholder(string searchword, int numfile, News a[])
{
	RankSys *rank = new RankSys[numfile];
	TrieNode *pcur1 = getNode(), *pcur2 = getNode();
	bool a1 = false, a2 = false;
	string s1, s2, ori, mid, sup;
	ifstream fin;
	string temp, s;
	int k = 0, m = 0;
	if (searchword.find('*') == -1)
	{
		return;
	}
	else
	{
		s1 = searchword.substr(0, searchword.find('*') - 1);
		s2 = searchword.substr(searchword.find('*') + 2);


	}
	for (int i = 0; i < numfile; i++)
	{
		search(a[i].root, s1, a1, pcur1);
		if (a1 == true && pcur1->isEndOfWord)
		{
			for (int j = 0; j < pcur1->count; j++)
			{
				temp = a[i].para[pcur1->loc[j]];
				while (k != 999)
				{
					k = temp.find(s1);
					if (k == -1) break;
					if (k == 0) {
						temp.erase(temp.begin(), temp.begin() + s1.length() + 1);
						}
					else 
						temp.erase(temp.begin(), temp.begin() + k + s1.length()+1);
						k = temp.find(" ");
						mid = temp.substr(0, k);
						temp.erase(temp.begin(), temp.begin() + k + 1);
						k = temp.find(" ");
						s = temp.substr(0, k);
						filterword(s);
						if (s.compare(s2) == 0)
						{
							ori += s1;
							ori += " ";
							ori += mid;
							ori += " ";
							ori += s2;
							rank[m].filename = i;
							rank[m].times++;
							rank[m].loc = pcur1->loc[j];
							m++;
							sup = ori;
							ori.clear();
							temp.clear();
							s.clear();
							break;
						}
				}

			}


		}

	}
	if (m == 0) {
		cout << "FUCK!";
		return;
	}

	int i, j;
	bool swapped;
	for (i = 0; i < m; i++)
	{
		swapped = false;
		for (j = 0; j < m - i; j++)
		{
			if (rank[j].times < rank[j + 1].times)
			{
				swap(rank[j], rank[j + 1]);
				swapped = true;
			}
		}

		// IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
	int t = 0;
	while (rank[t].times != 0 && t<5)
	{
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 4);
		cout << a[rank[t].filename].filename << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		cout << "Times: " << rank[t].times << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		cout << "In para: " << endl;
		printparawhole(a[rank[t].filename].para[rank[t].loc], sup);
		cout << endl;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 2);
		cout << "/////////////////////////////////////////////////////////" << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		t++;
	}
}
void printplaceholder(string para, string s1, string s2, string s)
{
	string stuff, fil;
	int k = 0;
	while (k != -1)
	{
		k = para.find(' ');
		// find the location of ' '
		stuff = para.substr(0, k); //copy the substring from start to location of ' '
		fil = stuff;
		filterword(fil);
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 7);
		if (fil == s1 || fil == s2 || fil == s)
		{
			HANDLE hConsoleColor;
			hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsoleColor, 4);
			cout << stuff;
		}
		else
			cout << stuff;
		if (k != -1)
		{
			para.erase(para.begin(), para.begin() + k + 1); // delete the string from start to location of ' '+1
		}
		cout << " ";
		fil.clear();
	}
}
//----------------------------------------------ULTIMATE----------------------------------------
void swap(RankSys *&xp, RankSys *&yp)
{
	RankSys *temp = xp;
	xp = yp;
	yp = temp;
}
int count(string s, char sub)
{
	int count = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == sub)
		{
			++count;
		}
	}
	return count;
}
//Search one word
void rankingone(News a[], int numfile, string key)
{
	clock_t begin = clock();
	RankSys *rank = new RankSys[numfile];
	int count=0;
	int fuck = 0;
	/*bool checkintree = false;
	if (isSub(a, " ")) {
		int  n = count(a, ' ') + 1;
		int k = 0, i = 0;
		string *block = new string[n];
		TrieNode *pcur[50];
			while (k != -1)
			{
				k = a.find(' ');
				block[i] = a.substr(0, k); 
				if (k != -1)
					a.erase(a.begin(), a.begin() + k + 1);
				i++;
			}
		for (int j = 0; j < n; j++)
		{
			search(root, block[j], checkintree, pcur[j]);
			if (checkintree == false) {
				for (int l = j; l < n-1; l++)
					block[j] = block[j + 1];
					pcur[j] = pcur[j + 1];
			}//if not in trie
			n--;
		}*/
	bool checkintree = false;
	TrieNode *pcur = getNode();
	for (int i = 0; i < numfile; i++)
	{
		search(a[i].root, key, checkintree, pcur);
		if (checkintree == true && pcur->isEndOfWord)
		{
			rank[i].times = pcur->count;
			rank[i].filename = i;
			rank[i].loc = pcur->loc[0];
			count++;
		}
		else {
			rank[i].times = 0;
			fuck++;
			}
	}
	if (fuck == numfile) {
		cout << "FUCK!";
		return;
	}
	int i, j;
	bool swapped;
	for (i = 0; i < count; i++)
	{
		swapped = false;
		for (j = 0; j < count - i; j++)
		{
			if (rank[j].times < rank[j + 1].times)
			{
				swap(rank[j], rank[j + 1]);
				swapped = true;
			}
		}

		// IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
	int k = 0;
	while (rank[k].times !=0 && k<5)
	{
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 4);
		cout << a[rank[k].filename].filename << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		cout << "Times: " << rank[k].times << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		cout << "In para: " << endl;
		printpara(a[rank[k].filename].para[rank[k].loc], key);
		cout << endl;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 2);
		cout << "/////////////////////////////////////////////////////////" << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		k++;
	}
	clock_t end = clock();
	cout << "Time run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;
} //Search one word
//Ranking AND
void rankingtwo(News a[], int numfile, string s1, string s2) {

	RankSys *rank = new RankSys[numfile];
	int fuck = 0, count = 0;
	bool a1 = false, a2 = false;
	bool check = false;
	TrieNode *pcur1 = getNode();
	TrieNode *pcur2 = getNode();
	for (int i = 0; i < numfile; i++)
	{
		int m = 0, n = 0;
		search(a[i].root, s1, a1, pcur1);
		search(a[i].root, s2, a2, pcur2);
		while (m < pcur1->count && n < pcur2->count)
		{
			if (pcur1->loc[m] < pcur2->loc[n])
				m++;
			else if (pcur2->loc[n] < pcur1->loc[m])
				n++;
			else if  ( pcur1->loc[m] == pcur2->loc[n])
			{
				check = true;
				break;
			}
			check = false;
		}
		if (a1 == true && pcur1->isEndOfWord && a2 == true && pcur2->isEndOfWord && check == true)
		{
			rank[i].times = pcur1->count + pcur2->count;
			rank[i].filename = i;
			rank[i].loc = pcur1->loc[m];
			count++;
		
		}
		else {
			rank[i].times = 0;
			fuck++;
		}
}
	if (fuck == numfile) {
		cout << "FUCK!";
		return;
	}
	int i, j;
	bool swapped;
	for (i = 0; i < count; i++)
	{
		swapped = false;
		for (j = 0; j < count - i; j++)
		{
			if (rank[j].times < rank[j + 1].times)
			{
				swap(rank[j], rank[j + 1]);
				swapped = true;
			}
		}

		// IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
	int k = 0;
	while (rank[k].times != 0 && k<5)
	{
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 4);
		cout << a[rank[k].filename].filename << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		cout << "Times: " << rank[k].times << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		cout << "In para: " << endl;
		printparatwo(a[rank[k].filename].para[rank[k].loc], s1,s2);
		cout << endl;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 2);
		cout << "/////////////////////////////////////////////////////////" << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		k++;
	}
}
//Ranking OR
void rankingor(News a[], int numfile, string s1, string s2)
{
	RankSys *rank = new RankSys[numfile];
	int fuck = 0, count = 0;
	bool a1 = false, a2 = false;
	bool check = false;
	TrieNode *pcur1 = getNode();
	TrieNode *pcur2 = getNode();
	for (int i = 0; i < numfile; i++)
	{
		search(a[i].root, s1, a1, pcur1);
		search(a[i].root, s2, a2, pcur2);

		if (a1 == true && pcur1->isEndOfWord && pcur1->count > pcur2->count)
		{

			rank[i].times = pcur1->count;
			rank[i].filename = i;
			rank[i].loc = pcur1->loc[0];
			rank[i].ofpcur = 1;
			count++;
		}
		else if (a2 == true && pcur2->isEndOfWord && pcur2->count >= pcur1->count)
		{
			rank[i].times = pcur2->count;
			rank[i].filename = i;
			rank[i].loc = pcur2->loc[0];
			rank[i].ofpcur = 2;
			count++;
		}
		else {
			rank[i].times = 0;
			fuck++;
		}
	}
	if (fuck == numfile) {
		cout << "FUCK!";
		return;
	}
	int i, j;
	bool swapped;
	for (i = 0; i < count; i++)
	{
		swapped = false;
		for (j = 0; j < count - i; j++)
		{
			if (rank[j].times < rank[j + 1].times)
			{
				swap(rank[j], rank[j + 1]);
				swapped = true;
			}
		}

		// IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
	int k = 0;
	while (rank[k].times != 0 && k<5)
	{
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 4);
		cout << a[rank[k].filename].filename << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		cout << "Times: " << rank[k].times << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		cout << "In para: " << endl;
		if (rank[k].ofpcur == 1)
		printpara(a[rank[k].filename].para[rank[k].loc], s1);
		else if (rank[k].ofpcur == 2)
		printpara(a[rank[k].filename].para[rank[k].loc], s2);
		cout << endl;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 2);
		cout << "/////////////////////////////////////////////////////////" << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		k++;
	}
}
//Ranking Whole
void rankingwhole(News a[], int numfile, string s) {
	RankSys *rank = new RankSys[numfile];
	int m = 0;
	int l = 1;
	for (int i = 0; i < numfile; i++)
	{
		while (!a[i].para[l].empty())
		{
			if (a[i].para[l].find(s) != -1) {
				rank[m].filename = i;
				rank[m].times++;
				rank[m].loc = l;
				m++;
			}
			l++;
		}
		l = 1;
	}
	if (m == 0) {
		cout << "FUCK!";
		return;
	}

	int i, j;
	bool swapped;
	for (i = 0; i < m; i++)
	{
		swapped = false;
		for (j = 0; j < m - i; j++)
		{
			if (rank[j].times < rank[j + 1].times)
			{
				swap(rank[j], rank[j + 1]);
				swapped = true;
			}
		}

		// IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
	int k = 0;
	while (rank[k].times != 0 && k<5)
	{
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 4);
		cout << a[rank[k].filename].filename << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		cout << "Times: " << rank[k].times << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		cout << "In para: " << endl;
		printparawhole(a[rank[k].filename].para[rank[k].loc], s);
		cout << endl;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 2);
		cout << "/////////////////////////////////////////////////////////" << endl;
		SetConsoleTextAttribute(hConsoleColor, 7);
		k++;
	}
}
void printpara(string para, string s) {
	string stuff, fil;
	int k = 0;
	while (k != -1)
	{	
		k = para.find(' ');
		// find the location of ' '
		stuff = para.substr(0, k); //copy the substring from start to location of ' '
		fil = stuff;
		filterword(fil);
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 7);
		if (fil == s)
		{
			HANDLE hConsoleColor;
			hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsoleColor, 4);
				cout << stuff;
		}
		else 
		cout << stuff;
		if (k != -1)
		{
			para.erase(para.begin(), para.begin() + k + 1); // delete the string from start to location of ' '+1
		}
		cout << " ";
		fil.clear();
	}
}
void printparatwo(string para, string s1, string s2) {
	string stuff, fil;
	int k = 0;
	while (k != -1)
	{
		k = para.find(' ');
		// find the location of ' '
		stuff = para.substr(0, k); //copy the substring from start to location of ' '
		fil = stuff;
		filterword(fil);
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 7);
		if (fil == s1 || fil == s2)
		{
			HANDLE hConsoleColor;
			hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsoleColor, 4);
			cout << stuff;
		}
		else
			cout << stuff;
		if (k != -1)
		{
			para.erase(para.begin(), para.begin() + k + 1); // delete the string from start to location of ' '+1
		}
		cout << " ";
		fil.clear();
	}
}
void printparawhole(string para, string s) {
	string stuff, fil;
	int k = 0;
		k = para.find(s);
		// find the location of ' '
		if (k == 0)
		{
			HANDLE hConsoleColor;
			hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsoleColor, 4);
			cout << s;
			para.erase(para.begin(),para.begin() + s.length());
			hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsoleColor, 7);
			cout << para;
			return;
		}
		stuff = para.substr(0, k); //copy the substring from start to location of ' '
		cout << stuff;
		cout << " ";
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 4);
		cout << s;
		cout << " ";
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 7);
		fil = para.substr(k + 1 + s.length());
		cout << fil;
		fil.clear();
		stuff.clear();
}
//Synonym
void SYN(string searchword, int numfile, News a[])
{
	TrieNode *pcur = getNode();
	string s;
	
	if (searchword[0] == '~')
	{
		s = searchword.substr(searchword.find('~') + 1);
	}
	rankingsyn(a, numfile, s);
}
void inputsyntrie(TrieNode *&sroot)
{
	sroot = getNode();
	ifstream fin;
	string gr;
	fin.open("synonym.txt");
	while (fin.good())
	{
		getline(fin, gr, '\n');
		int k = gr.find('-');
		string group = gr.substr(0, k);
		filterword(group);
		gr.erase(gr.begin(), gr.begin() + k + 1);
		string *syno = new string[100];
		int i = 1;
		syno[0] = group;
		while (!gr.empty())
		{
			k = gr.find(',');
			string syn = gr.substr(0, k);
			syno[i] = syn;
			i++;
			if (k == -1) break;
			gr.erase(gr.begin(), gr.begin() + k + 1);
		}
		for (int j = 0; j < i; j++)
		{
			insertsyntrie(sroot, syno[j], syno);
		}
	}
}
void insertsyntrie(TrieNode *&sroot, string key, string *syn)
{
	struct TrieNode *pCrawl = sroot;
	int index = 0;
	for (int i = 0; i < key.length(); i++)
	{
		index = findex(key[i]);
		// The TrieNode looks like: a b c d e f g h j k l m n o p q r s t u v w x y z # $ 0 1 2 3 4 5 6 7 8 9 
		if (!pCrawl->children[index])

			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}
	// mark last node as leaf
	//pCrawl->syn->group = group;
	pCrawl->syn = syn;
	pCrawl->isEndOfWord = true;
}
void checkinsyntree(TrieNode *&root, string key,bool&check, string *&syn)
{
	struct TrieNode *pCrawl = root;
	int index = 0;
	for (int i = 0; i < key.length(); i++)
	{
		index = findex(key[i]);

		if (!pCrawl->children[index])
			check = false;
		pCrawl = pCrawl->children[index];
	}
	if (pCrawl->isEndOfWord)
	{
		check = true;
		syn = pCrawl->syn;
	}
}
void rankingsyn(News a[], int numfile, string s)
{
	TrieNode *sroot = getNode();
	TrieNode *pcur = getNode();
	RankSys *rank = new RankSys[1000];
	int count = 0, fuck = 0, l = 1, m = 0;
	inputsyntrie(sroot);
	bool check = false;
	string *syn = 0;
	checkinsyntree(sroot, s,check,syn);
	if (check == false)
	{
		cout << "No Synonym found!" << endl;
		return;
	}
	else
	{
		for (int i = 0; i < numfile; i++)
		{
			while (!syn[l].empty())
			{
				search(a[i].root, syn[l], check, pcur);
				if (check == true && pcur->isEndOfWord)
				{
					rank[count].times = pcur->count;
					rank[count].filename = i;
					rank[count].loc = pcur->loc[0];
					rank[count].s = syn[l];
					count++;
				}
				else {
					rank[count].times = 0;
					fuck++;
				}
				l++;
			}
			l = 1;
		}
		if (fuck == numfile) {
			cout << "FUCK!";
			return;
		}
		int i, j;
		bool swapped;
		for (i = 0; i < count; i++)
		{
			swapped = false;
			for (j = 0; j < count - i; j++)
			{
				if (rank[j].times < rank[j + 1].times)
				{
					swap(rank[j], rank[j + 1]);
					swapped = true;
				}
			}

			// IF no two elements were swapped by inner loop, then break
			if (swapped == false)
				break;
		}
		int k = 0;
		while (rank[k].times != 0 && k<5)
		{
			HANDLE hConsoleColor;
			hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsoleColor, 4);
			cout << a[rank[k].filename].filename << endl;
			SetConsoleTextAttribute(hConsoleColor, 7);
			cout << "Times: " << rank[k].times << endl;
			SetConsoleTextAttribute(hConsoleColor, 7);
			cout << "In para: " << endl;
			printpara(a[rank[k].filename].para[rank[k].loc], rank[k].s);
			cout << endl;
			hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsoleColor, 2);
			cout << "/////////////////////////////////////////////////////////" << endl;
			SetConsoleTextAttribute(hConsoleColor, 7);
			k++;
		}
	}

}