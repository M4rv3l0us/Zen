#include "Function.h"

int main()
{
	struct TrieNode *root = getNode();
	string a;
	string sentence = "After losing fight to levy";
	// Construct trie
	input(root);
	cout << "Pls enter the word you want to search: " << endl;
	cin >> a;
	if (search(root, a) == true && isSub(sentence, a) == true) cout << sentence;
	else cout << "No";
	// Search for different keys
	system("pause");
	return 0;
}