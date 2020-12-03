#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

typedef map <string, int>::const_iterator it_type;

const int NO_ITEMS = 3;
const int ITEM_W = 16;

bool isAlNum(const char& ch)
{
	return isalnum(ch);
}

bool isNotAlNum(const char& ch)
{
	return !isalnum(ch);
}

void toLow(char& ch)
{
	ch = tolower(ch);
	return;
}

void print_words(const map <string, int> &map)
{
	int count = 0;
	int num = 0;

	for (it_type it = map.begin(); it != map.end(); it++)
	{
		if (count == NO_ITEMS)
		{
			count = 0;
			cout << endl;
		}
		num += (*it).second;
		cout << setw(ITEM_W) << left << (*it).first << ":" << setw(3) << (*it).second << " ";
		count++;
	}
	cout << endl << endl;
	cout << "Number of words from file: " << num << endl;
	cout << "Number of words written: " << (int)map.size();
}

void clean_entry(const string& dirty, string& clean)
{

	string::const_iterator start = dirty.begin();
	string::const_iterator end = dirty.begin();
	start = find_if(dirty.begin(), dirty.end(), [] (char ch)->bool {return (isalnum(ch) > 0);});
	end = find_if(dirty.begin(), dirty.end(), [] (char ch)->bool {return (0 < !isalnum(ch));});
	clean = dirty.substr(start-dirty.begin(), end - start);
	for_each(clean.begin(), clean.end(), toLow);
	

//	int index = 0;
//	int indexEnd = 0;

//	bool punct = false;
//	bool start = false;
//	bool finish = false;

//	for (int i = 0; i < (int)dirty.length(); i++)
//	{
//		if(isNotAlNum(dirty[i]))
//		{
//			punct = true;
//		}

//		if (isAlNum(dirty[i]) && start == false)
//		{
//			start = true;
//			index = i;
//		}	

//		if (start == true)
//		{
//			if (isNotAlNum(dirty[i]))
//			{
//				finish = true;
//				indexEnd = i;
//			}
//		}
//
//		if (finish == true)
//		{
//			break;
//		}
//	}

//	clean = dirty.substr(index, indexEnd - index);

//	for_each(clean.begin(), clean.end(), toLow);

//	if (punct == false)
//	{
//		clean = dirty;
//		for_each(clean.begin(), clean.end(), toLow);
//	}



}

void get_words(map <string, int>& map)
{
	string dirtyWord;
	string cleanWord;
	while (cin)
	{
		cin >> dirtyWord;
		clean_entry(dirtyWord, cleanWord);
		if (cleanWord.size() > 0)
		{
			map[cleanWord]++;
		}
	}
}

int main()
{
	map<string, int> map;
	get_words(map);
	print_words(map);
	return 0;
}
