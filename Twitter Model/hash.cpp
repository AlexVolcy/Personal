#include "hash.h"
#include <iostream>
using namespace std;

unsigned long long calculateHash(string mystring)
{
	unsigned long long result = 0;
	unsigned int square = 0;
	unsigned int castLetter;
	unsigned int secretNums[4];
	unsigned long long testExp = 1;

	for (int i = mystring.size()-1; i >= 0; i--)
	{
		castLetter = (unsigned int)mystring[i]; //p(n something)
		result += castLetter*testExp; //128^ * p(n something)
		testExp *= 128;
		square++;
	}

	unsigned int w1 = 0; //most significant
	unsigned int w2 = 0;
	unsigned int w3 = 0;
	unsigned int w4 = 0; //least significant

	w4 = result%65521;

	result = result/65521;
	w3 = result%65521;

	result = result/65521;
	w2 = result%65521;

	result = result/65521;
	w1 = result%65521;

	secretNums[0] = w1;
	secretNums[1] = w2;
	secretNums[2] = w3;
	secretNums[3] = w4;


	result = (45912 * secretNums[0] + 35511 * secretNums[1] + 65169 * secretNums[2] + 4625 * secretNums[3]);
	result = result%65521;

	return result;
}