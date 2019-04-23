
#include <string>

#pragma once
namespace struc
{
	struct aSong {
		int songNumber;
		char title[64];
		char artist[32];
		char album[64];
		int trackNumber;
		int year;
		enum genre
		{
			Fail = 0,
			Blues,
			Country,
			Electronic,
			Folk,
			HipHop,
			Jazz,
			Latin,
			Pop,
			Rock
		} Genre;

	};
};