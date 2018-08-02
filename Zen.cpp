#include "Function.h"

int main()
{
	TrieNode *hroot = getNode();
	string a;
	int query;
	// Construct trie
	News b[100];
	createNews(b);
	cout << "Pls enter the word you want to search: " << endl;
	getline(cin, a);
	updatehistoryTrie(hroot, a);
	cout << "Suggestion:" << endl;
	int comp = printAutoSuggestions(hroot, a);
	if (comp == -1)
		cout << "No other strings found with this prefix\n";
	else if (comp == 0)
		cout << "No string found with this prefix\n";
	//searchInfile(b, a);
	//AND(a, b);
	//OR(a, b);
	//placeholder(a, b);
	// Search for different keys
	system("pause");
	return 0;
}