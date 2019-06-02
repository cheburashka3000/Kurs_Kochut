#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;
class Stego
{
private:
	char* PathToContainer;
	int ipow(int a,int b);
	inline string checkKont(const int& what);
	inline string checkMessage(char* mespyt, string& kont);
	inline int checkZifr(string& text);
public:
	Stego()=delete;
	Stego(char* contpyt);
	string hide(char* mespyt);
	string extract();
};

class stego_error: public invalid_argument
{
public:
	explicit stego_error (const string& what_arg):invalid_argument(what_arg) {};
	explicit stego_error (const char* what_arg):invalid_argument(what_arg) {};
};
