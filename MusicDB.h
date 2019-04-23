#pragma once
using namespace std;
#include "Song.h"


namespace musicdb
{
	void add();
	string enum_tostring(struc::aSong::genre genre_index);
	struc::aSong::genre str_toenum(string entry);
	void list();
	void save();
	void clear();
	void help();
	void load();
	bool titleBool(struc::aSong, struc::aSong);
	void titleSort();
	bool artistBool(struc::aSong, struc::aSong);
	void artistSort();
	bool yearBool(struc::aSong, struc::aSong);
	void yearSort();
}

