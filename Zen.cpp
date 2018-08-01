#include "Function.h"

int main()
{
	struct TrieNode *root = getNode();
	string a;
	// Construct trie
	News b[100];
	createNews(b);
	cout << "Pls enter the word you want to search: " << endl;
	getline(cin, a);
	filterword(a);
	searchInfile(b, a);
	AND(a, b);
	OR(a, b);
	placeholder(a, b);
	// Search for different keys
	system("pause");
	return 0;
}