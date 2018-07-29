#include "Function.h"

int main()
{
	struct TrieNode *root = getNode();
	string a;
	// Construct trie
	News b[100];
	createNews(b);

	cout << "Pls enter the word you want to search: " << endl;
	cin >> a;
	filterword(a);
	searchInfile(b, a);
	// Search for different keys
	system("pause");
	return 0;
}