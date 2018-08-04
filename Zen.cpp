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
	clock_t begin = clock();
	SYN(a, n, b);
	SINGLE(a, n, b);
	INTITLE(a, n, b);
	MINUS(a, n, b);
	PLACEHOLDER(a,n, b);
	WHOLE(a,n, b);
	AND(a,n, b);
	OR(a,n, b);
	cout << "Suggestion:" << endl;
	int comp = printAutoSuggestions(hroot, a);
	if (comp == -1)
	{
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 4);
		cout << "No other strings found with this prefix\n";
	}
	else if (comp == 0)
	{
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 4);
		cout << "No string found with this prefix\n";
	}

	clock_t end = clock();
	cout << "Time run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;
	system("pause");
	return 0;
}