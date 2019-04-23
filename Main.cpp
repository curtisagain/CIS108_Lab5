#include <string>
#include <iostream>
#include "MusicDB.h"
#include <vector>
#include "conio.h"

using namespace std;

int main()
{
	string entry;
	musicdb::load(); // loads from txt file
	musicdb::help(); // prints help menu
	do
	{
		cout << ">";
		cin >> entry;
		cin.ignore(); //prevents xutility error, otherwise assigns null to song title

		if (entry == "add")
		{
			musicdb::add();
		}

		else if (entry == "list")
		{
			musicdb::list();
		}

		else if (entry == "save")
		{
			musicdb::save();
		}

		else if (entry == "sort")
		{
			cout << "title : Sort by title.\n";
			cout << "artist : Sort by artist.\n";
			cout << "year : Sort by year released.\n";
			cout << ">";
			cin >> entry;
			if (entry == "title")
				musicdb::titleSort();
			if (entry == "artist")
				musicdb::artistSort();
			if (entry == "year")
				musicdb::yearSort();
		}
		
		else if (entry == "clear")
		{
			musicdb::clear();
		}

		else if (entry == "help")
		{
			musicdb::help();
		}
		
	} while (entry != "exit"); //same do while as calc
	return 0;
}