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
void TryInput(int& input, string inputText)
{
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
void TryInput(float& input, string inputText)
{
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
void TryInput(bool& input, string inputText)
{
	do {
		cout << inputText;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> input;
	} while (cin.fail());
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

list<Pipe> pipeList;
list<CompressorStation> compStationList;

void AddPipe()
{
	Pipe pipe = Pipe();
	TryInput(pipe.id, "\nВведите идентификатор трубы: ");
	TryInput(pipe.length, "\nВведите длину трубы: ");
	TryInput(pipe.diameter, "\nВведите диаметр трубы: ");
	TryInput(pipe.isRepairing, "\nТруба на ремонте? (true или false): ");
	pipeList.push_front(pipe);
}

void AddCompressorStation() {

}

void ShowAll() {
	cout << "Список труб:";
	for (Pipe pipe : pipeList)
	{
		cout << "Труба " << pipe.id << ".\n"
			<< "    Длина: " << pipe.length << "\n"
			<< "    Диаметр:"  << pipe.length << "\n"
			<< "    В ремонте: " << pipe.length << "\n";
	}
	cout << "Список КС:";
	for (CompressorStation compStation : compStationList)
	{
		cout << "Компрессорная станция " << compStation.id << ".\n"
			<< "    Имя: " << compStation.name << "\n"
			<< "    Работает " << compStation.shopsCount << "/" << compStation.operationShopsCount << " цехов" "\n"
			<< "    Эффективность: " << compStation.efficiency << "\n";
	}
}

void EditPipe() {

}

void EditCompressorStation() {

}

void Save() {

}

void Load() {

}


int main()
{
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

		int inputMenu;
		TryInput(inputMenu, "Что Вы хотите сделать: ");
		
		switch (inputMenu)
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
		case 4:
			EditPipe();
			break;
		case 5:
			EditCompressorStation();
			break;
		case 6:
			Save();
			break;
		case 7:
			Load();
			break;
		case 0:
			isRunning = false;
			break;
		default:
			return 0;
		break;
		}
		
	}
}

