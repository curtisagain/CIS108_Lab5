#include "MusicDB.h"
#include "Song.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;
struc::aSong song;
vector<struc::aSong> allSongs;
int totalSongs = 0;
const int maxSongs = 8; 
string fileName = "MusicFile.db";

void musicdb::add()
{
	if (totalSongs == maxSongs)
	{
		cout << "Song database is full. Please clear.";
	}

	else
	{
		string inputstr;
		cout << "Enter song title: ";
		getline(cin >> ws, inputstr); //**second parameter must be a string, s.title is a character array** **use string copy function**
		if (inputstr.length() > sizeof(song.title))
			throw runtime_error("Song title is too large!"); //used runtime_error rather than exception because string args to exception are a VS extension
		else
			strcpy_s(song.title, inputstr.c_str());
		cout << "Enter artist: ";
		getline(cin, inputstr);
		if (inputstr.length() > sizeof(song.artist))
			throw runtime_error("Artist name is too large!");
		else
			strcpy_s(song.artist, inputstr.c_str());
		cout << "Enter album name: ";
		getline(cin, inputstr);
		if (inputstr.length() > sizeof(song.artist))
			throw runtime_error("Album name is too large!");
		else
			strcpy_s(song.album, inputstr.c_str());
		cout << "Enter genre: ";
		getline(cin, inputstr);
		song.Genre = str_toenum(inputstr);
		cout << "Enter track #: ";
		getline(cin, inputstr);
		try
		{
			song.trackNumber = stoi(inputstr);
		}
		catch (invalid_argument)
		{
			throw runtime_error("Numeric input required for track field");
		}
		catch (out_of_range)
		{
			throw runtime_error("Input is too large!");
		}
		cout << "Enter year: ";
		getline(cin, inputstr);
		try
		{
			int iyear = stoi(inputstr);
			if (iyear <= 2019)
				song.year = iyear;
			else
				throw runtime_error("You can't add songs from the future!");
		}
		catch (invalid_argument)
		{
			throw runtime_error("Numeric input required for year field");
		}
		catch (out_of_range)
		{
			throw runtime_error("Input is too large!");
		}
		totalSongs++;
		allSongs.push_back(song);
	}


}
string musicdb::enum_tostring(struc::aSong::genre genre_index) {
	if (genre_index == 1) {
		return "Blues";
	}
	else if (genre_index == 2) {
		return "Country";
	}
	else if (genre_index == 3) {
		return "Electronic";
	}
	else if (genre_index == 4) {
		return "Folk";
	}
	else if (genre_index == 5) {
		return "Hip-Hop";
	}
	else if (genre_index == 6) {
		return "Jazz";
	}
	else if (genre_index == 7) {
		return "Latin";
	}
	else if (genre_index == 8) {
		return "Pop";
	}
	else if (genre_index == 9) {
		return "Rock";
	}
	else {
		return "Other";
	}
}
struc::aSong::genre musicdb::str_toenum(string entry) { //Wesley's solution for going from enum to string
	if (entry == "blues" || entry == "Blues") {
		return struc::aSong::genre::Blues;
	}
	else if (entry == "country" || entry == "Country") {
		return struc::aSong::genre::Country;
	}
	else if (entry == "electronic" || entry == "Electronic" || entry == "edm" || entry == "EDM") {
		return struc::aSong::genre::Electronic;
	}
	else if (entry == "folk" || entry == "Folk") {
		return struc::aSong::genre::Folk;
	}
	else if (entry == "hiphop" || entry == "HipHop" || entry == "Hip Hop" || entry == "hip hop" || entry == "Hip-Hop" || entry == "rap" || entry == "Rap") {
		return struc::aSong::genre::HipHop;
	}
	else if (entry == "jazz" || entry == "Jazz") {
		return struc::aSong::genre::Jazz;
	}
	else if (entry == "latin" || entry == "Latin") {
		return struc::aSong::genre::Latin;
	}
	else if (entry == "pop" || entry == "Pop") {
		return struc::aSong::genre::Pop;
	}
	else if (entry == "rock" || entry == "Rock") {
		return struc::aSong::genre::Rock;
	}
	else {
		return struc::aSong::genre::Fail;
	}
}
void musicdb::list()
{
	int currentSong = 1;
	if (totalSongs == 1)
	{
		cout << "There is 1 song in the database\n";
	}
	else
	{
		cout << "There are " << totalSongs << " songs in the database\n";
	}
	for (int i = 0; i < totalSongs; i++)
	{
		cout << "Song #" << currentSong;
		cout << "\nSong title: " << allSongs[i].title;
		cout << "\nArtist: " << allSongs[i].artist;
		cout << "\nAlbum: " << allSongs[i].album;
		cout << "\nTrack #: " << allSongs[i].trackNumber;
		cout << "\nRelease year: " << allSongs[i].year;
		cout << "\nGenre: " << allSongs[i].Genre << "\n\n";
		currentSong++;
	}
}

void musicdb::save()
{
	ofstream database;
	database.open("MusicFile.db", fstream::app);
	database << song.title << song.artist << song.album << song.trackNumber << song.year << song.Genre << "\n";
	database.close();
}// writes to database


void musicdb::clear()
{
	ofstream database;
	database.open("MusicFile.db", ofstream::trunc); //truncates
	database.close();
	totalSongs = 0;
}

void musicdb::help()
{
	cout << "Commands in this program:\n";
	cout << "1. add - Add a new song to the database.\n";
	cout << "2. list - List the songs in the database.\n";
	cout << "3. save - Save the songs to the database.\n";
	cout << "4. clear - Clear the current songs inside of the database.\n";
	cout << "5. help - Display this menu again.\n";
	cout << "6. exit - Close program.\n";
}

void musicdb::load(){
	struc::aSong s;
	ifstream infile;
	allSongs.clear();

	try
	{
		infile.open(fileName, ios::in | ios::binary);
		infile.exceptions(ifstream::failbit);

		while (infile.is_open() && infile.peek() != EOF)
		{
			infile.exceptions(ifstream::badbit);
			infile.read((char*)& s, sizeof(song));
			allSongs.push_back(song);
		};
		infile.close();
	}
	catch (const ifstream::failure) {
		cout << "Error opening file " << fileName << endl;
	}
}

bool sort_title(struc::aSong& ls, struc::aSong& rs) {
	return ls.title[0] < rs.title[0];
}

bool sort_artist(struc::aSong& ls, struc::aSong& rs) {
	return ls.artist[0] < rs.artist[0];
}


bool musicdb::titleBool(struc::aSong left, struc::aSong right)
{
	char* l = left.title;
	char* r = right.title;
	return strcmp(l, r) < 0;
}

void musicdb::titleSort()
{
	sort(allSongs.begin(), allSongs.end(), titleBool);
}

bool musicdb::artistBool(struc::aSong left, struc::aSong right)
{
	char* l = left.artist;
	char* r = right.artist;
	return strcmp(l, r) < 0;
}

void musicdb::artistSort()
{
	sort(allSongs.begin(), allSongs.end(), artistBool);
}

bool musicdb::yearBool(struc::aSong left, struc::aSong right)
{
	return (left.year < right.year);
}

void musicdb::yearSort()
{
	sort(allSongs.begin(), allSongs.end(), yearBool);
}