#include "Function.h"

int main()
{
	TrieNode *hroot = getNode();
	string a;
	int query;
	// Construct trie
	News b[100];
	int n = 100;
	createNews(b,n);
	cout << "Pls enter the word you want to search: " << endl;
	getline(cin, a);
	string *block = new string;
	/*if (isSub(a, " ")) {
		int n = 0;
		splitblock(a, block,n);
		searchblock(b, block, n);
	}*/
	updatehistoryTrie(hroot, a);
	SYN(a, n, b);
	SINGLE(a, n, b);
	INTITLE(a, n, b);
	MINUS(a, n, b);
	placeholder(a,n, b);
	WHOLE(a,n, b);
	AND(a,n, b);
	OR(a,n, b);
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