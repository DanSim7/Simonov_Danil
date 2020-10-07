#include <iostream>
#include <string>
#include <list>
using namespace std;

/// <summary>
/// Ввод данных с проверкой типа int
/// </summary>
/// <param name="input">Переменная ввода int</param>
/// <param name="inputText">Текст, запрашивающий ввод переменной</param>
/// <returns></returns>
void TryInput(int& input, string inputText) {
	do {
		cout << inputText;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> input;
	} while (cin.fail());
}

/// <summary>
/// Ввод данных с проверкой типа float
/// </summary>
/// <param name="input">Переменная ввода float</param>
/// <param name="inputText">Текст, запрашивающий ввод переменной</param>
/// <returns></returns>
void TryInput(float& input, string inputText) {
	do {
		cout << inputText;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> input;
	} while (cin.fail());
}

/// <summary>
/// Ввод данных с проверкой типа bool
/// </summary>
/// <param name="input">Переменная ввода bool</param>
/// <param name="inputText">Текст, запрашивающий ввод переменной</param>
/// <returns></returns>
void TryInput(bool& input, string inputText) {
	do {
		cout << inputText;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> input;
	} while (cin.fail());
}

int main() {
	setlocale(LC_ALL, "ru");
	bool isRunning = true;
	
	while (isRunning) {

		cout << "Меню выбора действий\n";
		cout << "1 - Добавить трубу\n";
		cout << "2 - Добавить КС\n";
		cout << "3 - Просмотр всех объектов\n";
		cout << "4 - Редактировать трубу\n";
		cout << "5 - Редактировать КС\n";
		cout << "6 - Сохранить\n";
		cout << "7 - Загрузить\n";
		cout << "0 - Выход\n";

		int inputMenu = 0;
		TryInput(inputMenu, "Что Вы хотите сделать: ");
		
		switch (input)
		{
		case 1:
			AddPipe();
		break;
		case 2:
			AddCompressorStation();
		break;
		case 3:
			ShowAll();
		break;
		default:
			return 0;
		break;
		}
		isRunning = false;
		
	}
}

void AddPipe() {

}

void AddCompressorStation() {

}

void ShowAll() {

}

struct CompressorStation {
	int id;
	string name;
	int shopsCount;
	int operationShopsCount;
	float efficiency;
	list<bool> shop;
};

struct Pipe {
	int id;
	float length;
	float diameter;
	bool isRepairing;
};