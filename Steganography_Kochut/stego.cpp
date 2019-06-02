#include "stego.h"

using namespace std;

Stego::Stego(char* contpyt)
{
	PathToContainer = contpyt;
};

string Stego::hide(char* mespyt)
{
	string kont = checkKont(1);
	while (kont.find("  ") != string::npos)
		kont.replace (kont.find("  "),2," ");
	string stroka = checkMessage(mespyt, kont);
	int cimvol = stroka.length();
	int cek[cimvol*8];
	int i,c,power, a = 0;
	for( i=0 ; i < cimvol ; i++ ) {
		c = stroka[i];
		for( power=7 ; power+1 ; power--, a++ )
			if( c >= (1<<power) ) {
				c -= (1<<power);
				cek[a] = 1;
			} else
				cek[a] = 0;
	}
	int razmer = 0;
	for(i = 0; i < a; i++) {
		if (cek[i] == 1)
			razmer++;
	}
	razmer += kont.length();
	string fin[razmer];
	i = 0;
	int s = 0;
	for (unsigned int j = 0; j < kont.length(); i++, j++) {
		if (kont[j] == ' ')
			if (cek[s] == 1) {
				fin[i] = kont[j];
				fin[i+1] = " ";
				i++;
				s++;
			} else {
				fin[i] = kont[j];
				s++;
			}
		else
			fin[i] = kont[j];
	}
	ofstream megasecret(PathToContainer);
	string HiddenMessage;
	for(i=0; i < razmer; i++) {
		megasecret << fin[i];
		HiddenMessage += fin[i];
	}
	megasecret.close();
	return HiddenMessage;
}

string Stego::extract()
{
	string text = checkKont(2);
	int zifr = checkZifr(text);
	int message[zifr];
	int j = 0;
	for (unsigned int i = 0; i < text.length(); i++) {
		if ((text[i] == ' ') && (text[i-1] != ' ')) {
			message[j] = 0;
			j++;
		}
		if ((text[i] == ' ') && (text[i+1] == ' ')) {
			message[j-1] = 1;
		}
	}
	string Message;
	char topsekret;
	int i=0;
	while(true) {
		topsekret = 0;
		for(j = 7; j >= 0; j--) {
			topsekret += ipow(2,(j)) * message[i];
			i++;
		}
		Message += topsekret;
		if(i >= zifr)
			break;
	}
	//remove(PathToContainer);
	return Message;
}

int Stego::ipow(int a,int b)
{
	if (b>0)
		return a*ipow(a, b-1);
	else
		return 1;
}

inline string Stego::checkKont(const int& what)
{
	ifstream file(PathToContainer);
	if (!(file.is_open()))
		throw stego_error("Контейнер не найден!!!\nПожалуйста, проверьте правильно ли Вы указали путь для контейнера!!!\n");
	long file_size;
	file.seekg(0, ios::end);
	file_size = file.tellg();
	file.seekg(0, ios::beg);
	if (file_size == 0)
		throw stego_error("Контейнер пустой!!!\n");
	string text;
	string kont;
	int Investigator = 0;
	while(getline(file,text)) {
		if (Investigator > 0 && what == 1)
			kont += " ";
		if (Investigator > 0 && what == 2)
			kont += "_";
		kont += text;
		Investigator++;
	}
	file.close();
	return kont;
}

inline string Stego::checkMessage(char* mespyt, string& kont)
{
	int probel = 0;
	for (unsigned int i = 0; i < kont.length(); i++)
		if (kont[i] == ' ')
			probel++;
	ifstream mes(mespyt);
	if (!(mes.is_open()))
		throw stego_error("Сообщение не найдено!!!\nПожалуйста, проверьте правильно ли Вы указали путь для сообщения!!!\n");
	string stroka, strok;
	int Investigator = 0;
	while(getline(mes,strok)) {
		if (Investigator > 0)
			kont += " ";
		stroka += strok;
		Investigator++;
	}
	mes.close();
	int cimvol = stroka.length();
	if (cimvol == 0)
		throw stego_error("В файле с сообщением нет текста!!!\n");
	if (cimvol*8 > probel)
		throw stego_error("Контейнер слишком мал для данного сообщения!!!\n");
	return stroka;
}

inline int Stego::checkZifr(string& text)
{
	int zifr = 0;
	for (unsigned int i = 0; i < text.length(); i++) {
		if (text[i] == ' ')
			zifr++;
		if ((text[i] == ' ') && (text[i+1] == ' '))
			zifr--;
	}
	zifr -= zifr%8;
	if (zifr < 8)
		throw stego_error("В этом контейнере нет сообщения!!!\n");
	return zifr;
}
