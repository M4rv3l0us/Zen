#include "Function.h"

int main()
{
	TrieNode *hroot = getNode();
	number *nroot;
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	string a;
	int query;
	// Construct trie
	News b[100];
	int n = 100;
	createNews(b,n,nroot);
	cout << "How many queries? ";
	cin >> query;
	cin.ignore();
	for (int i = 0; i < query; i++)
	{
		cout << "Pls enter the word you want to search: " << endl;
		getline(cin, a);
		updatehistoryTrie(hroot, a);
		clock_t begin = clock();
		SYN(a, n, b);
		SINGLE(a, n, b);
		INTITLE(a, n, b);
		MINUS(a, n, b);
		PLACEHOLDER(a, n, b);
		WHOLE(a, n, b);
		AND(a, n, b);
		OR(a, n, b);
		TXT(a, n, b);
		NUM(a, b, n, nroot);
		cout << "Suggestion:" << endl;
		int comp = printAutoSuggestions(hroot, a);
		if (comp == -1)
		{
			SetConsoleTextAttribute(hConsoleColor, 4);
			cout << "No other strings found with this prefix\n";
		}
		else if (comp == 0)
		{
			
			SetConsoleTextAttribute(hConsoleColor, 4);
			cout << "No string found with this prefix\n";
		}
		SetConsoleTextAttribute(hConsoleColor, 7);
		clock_t end = clock();
		cout << "Time run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;
		system("pause");
		system("cls");
		cin.ignore();
	}
	system("pause");
	return 0;
}