#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;
class Stego
{
private:
    int ipow(int a,int b);
    inline string checkKont(char* contpyt);
    inline string checkMessage(char* mespyt, string& kont);
    inline int checkZifr(string& text);
public:
    int hide();
    int extract();
};

class stego_error: public invalid_argument
{
public:
explicit stego_error (const string& what_arg):invalid_argument(what_arg) {};
explicit stego_error (const char* what_arg):invalid_argument(what_arg) {};
};
