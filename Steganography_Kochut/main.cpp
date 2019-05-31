#include "stego.h"
using namespace std;
int main()
{
    setlocale (LC_ALL, "Russian");
    cout << "Здравствуйте!\nА Вы знаете, что такое стеганография?\nВы хотите спрятать или извлечь?\n(Пожалуйста, напишите (hide) или (extract)\nв зависимости от того, что Вы хотите сделать)\n\n";
    string rezim;
    Stego rab;
    while (true)
    {
        cin >> rezim;
        cout << endl;
        if ((rezim == "hide") || (rezim == "extract"))
            if (rezim == "hide")
            {
                rab.hide();
                return 0;
            }
            else
            {
                rab.extract();
                return 0;
            }
        else
            cout << "Пожалуйста, следуйте инструкциям на экране!\n\n";
    }
}
