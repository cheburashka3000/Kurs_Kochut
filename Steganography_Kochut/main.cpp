#include "stego.h"
using namespace std;
int main()
{
	setlocale (LC_ALL, "Russian");
	cout << "Здравствуйте!\nА Вы знаете, что такое стеганография?\nВы хотите спрятать или извлечь?\n(Пожалуйста, напишите (hide) или (extract)\nв зависимости от того, что Вы хотите сделать)\n\n";
	string rezim;
	while (true) {
		cin >> rezim;
		cout << endl;
		if ((rezim == "hide") || (rezim == "extract"))
			if (rezim == "hide") {
				cout << "Введите путь для контейнера: ";
				char* contpyt;
				contpyt = new char[6000];
				cin >> contpyt;
				cout << endl;
				cout << "Введите путь для сообщения: ";
				char* mespyt;
				mespyt = new char[6000];
				cin >> mespyt;
				Stego rab(contpyt);
				rab.hide(mespyt);
				cout << "\nСообщение успешно спрятано!\n\nНадеюсь, Вам понравилась моя работа.\nДо свидания!\n\n";
				delete [] contpyt;
				delete [] mespyt;
				return 0;
			} else {
				cout << "Введите путь для контейнера: ";
				char* contpyt;
				contpyt = new char[6000];
				cin >> contpyt;
				string Message;
				Stego rab(contpyt);
				Message = rab.extract();
				cout << "\nСообщение из контейнера: " << Message << "\nКонтейнер был удалён ради вашей безопасности!\n\nНадеюсь, Вам понравилась моя работа.\nДо свидания!\n\n";
				delete [] contpyt;
				return 0;
			}
		else
			cout << "Пожалуйста, следуйте инструкциям на экране!\n\n";
	}
}
