#include "Function.h"

int main()
{
	struct TrieNode *root = getNode();
	string a;
	string sentence = "After losing fight to levy";
	// Construct trie
	News b[100];
	createNews(b);

	cout << "Pls enter the word you want to search: " << endl;
	cin >> a;
	filterword(a);
	if (search(b[0].root, a) == true) cout << "YES" << "times:" << b[0].root->count << b[0].filename;
	else cout << "No";
	// Search for different keys
	system("pause");
	return 0;
}