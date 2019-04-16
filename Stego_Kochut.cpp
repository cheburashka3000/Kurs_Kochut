//ССЫЛКА НА РЕПОЗИТОРИЙ
//https://github.com/cheburashka3000/Kurs_Kochut

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;
int tajna();
int netajna();
int ipow(int a,int b);
int main()
{
    setlocale (0,"");
    cout << "Здравствуйте!\nА Вы знаете, что такое стеганография?\nВы хотите спрятать или извлечь?\n(Пожалуйста, напишите (hide) или (extract)\nв зависимости от того, что Вы хотите сделать)\n\n";
    string rezim;
    while (true)
    {
        cin >> rezim;
        cout << endl;
        if ((rezim == "hide") || (rezim == "extract"))
            if (rezim == "hide")
            {
                tajna();
                return 0;
            }
            else
            {
                netajna();
                return 0;
            }
        else
            cout << "Пожалуйста, следуйте инструкциям на экране!\n\n";
    }
}

int tajna ()
{
    cout << "Введите путь для контейнера: ";
    char* contpyt;
    contpyt = new char[60];
    cin >> contpyt;
    ifstream file(contpyt);
    cout << endl;
    cout << "Введите путь для сообщения: ";
    char* mespyt;
    mespyt = new char[60];
    cin >> mespyt;
    ifstream mes(mespyt);
    delete [] mespyt;
    cout << endl;
    if (!(file.is_open()))
    {
        cout << "Контейнер не найден!!!\nПожалуйста, проверьте правильно ли Вы указали путь для контейнера!!!\n";
        return -1;
    }
    if (!(mes.is_open()))
    {
        cout << "Сообщение не найдено!!!\nПожалуйста, проверьте правильно ли Вы указали путь для сообщения!!!\n";
        return -1;
    }
    string kont;
    getline(file,kont);
    int probel = 0;
    while (kont.find("  ") != string::npos)
    {
        kont.replace (kont.find("  "),2," ");
    }
    for (unsigned int i = 0; i < kont.length(); i++)
        if (kont[i] == ' ')
            probel++;
    file.close();
    string stroka;
    getline(mes,stroka);
    int cimvol = stroka.length();
    for(int i=0 ; i < cimvol ; i++ )
        if ((stroka[i] == 'ё') || ((stroka[i] >= 'А') && (stroka[i] <= 'я')))
        {
            cout << "Пожалуйста, в сообщение используйте только латинские буквы!!!\n";
            return -3;
        }
    if (cimvol*8 > probel)
    {
        cout << "Контейнер слишком мал для данного сообщения!!!\n";
        return -2;
    }
    int cek[cimvol*8];
    int i,c,power, a = 0;
    for( i=0 ; i < cimvol ; i++ )
    {
        c = stroka[i];
        for( power=7 ; power+1 ; power--, a++ )
            if( c >= (1<<power) )
            {
                c -= (1<<power);
                cek[a] = 1;
            }
            else
                cek[a] = 0;
    }
    int razmer = 0;
    for(i = 0; i < a; i++)
    {
        if (cek[i] == 1)
            razmer++;
    }
    razmer +=kont.length();
    string fin[razmer];
    i = 0;
    int s = 0;
    for (unsigned int j = 0; j < kont.length(); i++, j++)
    {
        if (kont[j] == ' ')
            if (cek[s] == 1)
            {
                fin[i] = kont[j];
                fin[i+1] = " ";
                i++;
                s++;
            }
            else
            {
                fin[i] = kont[j];
                s++;
            }
        else
            fin[i] = kont[j];
    }
    ofstream megasecret(contpyt);
    for(i=0; i < razmer; i++)
        megasecret << fin[i];
    file.close();
    mes.close();
    delete [] contpyt;
    cout << "Сообщение успешно спрятано!\n\nНадеюсь, Вам понравилась моя работа.\nДо свидания!\n\n";
    return 0;
}

int netajna()
{
    cout << "Введите путь для контейнера: ";
    char* contpyt;
    contpyt = new char[60];
    cin >> contpyt;
    ifstream file(contpyt);
    cout << endl;
    if (!(file.is_open()))
    {
        cout << "Контейнер не найден!!!\nПожалуйста, проверьте правильно ли Вы указали путь для контейнера!!!\n";
        return -1;
    }
    string text;
    getline(file,text);
    file.close();
    int zifr = 0;
    for (unsigned int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ')
            zifr++;
        if ((text[i] == ' ') && (text[i+1] == ' '))
            zifr--;
    }
    zifr -= zifr%8;
    if (zifr < 8)
    {
        cout << "В этом контейнере нет сообщения!!!\n";
        return -5;
    }
    int message[zifr];
    int j = 0;
    for (unsigned int i = 0; i < text.length(); i++)
    {
        if ((text[i] == ' ') && (text[i-1] != ' '))
        {
            message[j] = 0;
            j++;
        }
        if ((text[i] == ' ') && (text[i+1] == ' '))
        {
            message[j-1] = 1;
        }
    }
    char topsekret;
    int i=0;
    cout << "Сообщение из контейнера: ";
    while(true)
    {
        topsekret = 0;
        for(j = 7; j >= 0; j--)
        {
            topsekret += ipow(2,(j)) * message[i];
            i++;
        }
        cout << topsekret;
        if(i >= zifr)
            break;
    }
    int minus = 0;
    while (text.find("  ") != string::npos)
    {
        text.replace (text.find("  "),2," ");
    }
    remove(contpyt);
    delete [] contpyt;
    cout << "\n\nКонтейнер был удалён ради вашей безопасности!\n\nНадеюсь, Вам понравилась моя работа.\nДо свидания!\n\n";
    return 0;
}

int ipow(int a,int b)
{
    if (b>0)
        return a*ipow(a, b-1);
    else
        return 1;
}
