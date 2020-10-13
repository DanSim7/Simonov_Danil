#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <iterator>
using namespace std;

/// <summary>
/// Ввод данных с проверкой типа int
/// </summary>
/// <param name="input">Переменная ввода int</param>
/// <param name="inputText">Текст, запрашивающий ввод переменной</param>
/// <returns></returns>
void TryInput(int& input, string inputText)
{
	cout << inputText;
	cin >> input;
	while (input < 0 || cin.fail()) {
		cout << inputText;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> input;
	}
}

/// <summary>
/// Ввод данных с проверкой типа float
/// </summary>
/// <param name="input">Переменная ввода float</param>
/// <param name="inputText">Текст, запрашивающий ввод переменной</param>
/// <returns></returns>
void TryInput(float& input, string inputText)
{
	cout << inputText;
	cin >> input;
	while (input < 0 || cin.fail()) {
		cout << inputText;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> input;
	}
}

/// <summary>
/// Ввод данных с проверкой типа bool
/// </summary>
/// <param name="input">Переменная ввода bool</param>
/// <param name="inputText">Текст, запрашивающий ввод переменной</param>
/// <returns></returns>
void TryInput(bool& input, string inputText)
{
	cout << inputText;
	cin >> input;
	while (cin.fail()) {
		cout << inputText;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> input;
	}
}

/// <summary>
/// Компрессорная станция
/// </summary>
struct CompressorStation
{
	int id;
	string name;
	int shopsCount;
	int operationShopsCount;
	double efficiency;

	void RecountEfficiency()
	{
		efficiency = operationShopsCount * (1. / shopsCount);
	}
};

/// <summary>
/// Труба
/// </summary>
struct Pipe
{
	int id;
	float length;
	float diameter;
	bool isRepairing;
};

// Объявляем векторы текущего списка труб и компрессорных станций
vector<Pipe> pipeList;
vector<CompressorStation> compStationList;

void AddPipe()
{
	cout << "\n---Добавить трубу---\n";
	Pipe pipe = Pipe();
	vector<int> currentIds = vector<int>(pipeList.size());
	for (int i = 0; i < pipeList.size(); i++)
	{
		currentIds[i] = pipeList[i].id;
	}
	while (true)
	{
		int id;
		TryInput(id, "Введите идентификатор трубы: ");
		bool HasId = false;
		for (int i = 0; i < currentIds.size(); i++)
		{
			if (id == currentIds[i])
			{
				HasId = true;
				break;
			}
		}
		if (HasId)
		{
			cout << "Такой ID трубы уже есть. Пожалуйста, введите другой ID\n";
			continue;
		}
		else
		{
			pipe.id = id;
			break;
		}
	}
	TryInput(pipe.length, "Введите длину трубы: ");
	TryInput(pipe.diameter, "Введите диаметр трубы: ");
	pipe.isRepairing = false;
	cout << endl;
	pipeList.push_back(pipe);
}

void AddCompressorStation()
{
	cout << "\n---Добавить компрессорную станцию---\n";
	CompressorStation cs = CompressorStation();
	vector<int> currentIds = vector<int>(compStationList.size());
	for (int i = 0; i < compStationList.size(); i++)
	{
		currentIds[i] = compStationList[i].id;
	}
	while (true)
	{
		int id;
		TryInput(id, "Введите идентификатор компрессорной станции: ");
		bool HasId = false;
		for (int i = 0; i < currentIds.size(); i++)
		{
			if (id == currentIds[i])
			{
				HasId = true;
				break;
			}
		}
		if (HasId)
		{
			cout << "Такой ID КС уже есть. Пожалуйста, введите другой ID\n";
			continue;
		}
		else
		{
			cs.id = id;
			break;
		}
	}
	cout << "Введите имя КС: ";
	cin >> cs.name;
	TryInput(cs.shopsCount, "Введите общее количество цехов: ");
	TryInput(cs.operationShopsCount, "Введите количество работающих цехов: ");
	while (cs.operationShopsCount > cs.shopsCount) {
		cout << "Ошибка! Количество работающих цехов не может быть больше общего количества цехов\n";
		TryInput(cs.operationShopsCount, "Пожалуйста, введите корректное количество работающих цехов: ");
	}
	cs.RecountEfficiency();
	cout << endl;
	compStationList.push_back(cs);
}

void ShowAll()
{
	cout << "\n---Просмотр всех объектов---\n";
	cout << "Список труб:\n";
	for (int i = 0; i < pipeList.size(); i++)
	{
		cout << "Труба " << pipeList[i].id << ".\n"
			<< "    Длина: " << pipeList[i].length << "\n"
			<< "    Диаметр:" << pipeList[i].diameter << "\n";
		if (pipeList[i].isRepairing)
			cout << "    Находится в ремонте" << "\n";
		else
			cout << "    Не нуждается в ремонте" << "\n";
	}
	cout << "\nСписок КС:\n";
	for (int i = 0; i < compStationList.size(); i++)
	{
		cout << "Компрессорная станция " << compStationList[i].id << ".\n"
			<< "    Имя: " << compStationList[i].name << "\n"
			<< "    Работает " << compStationList[i].operationShopsCount << "/" << compStationList[i].shopsCount << " цехов" "\n"
			<< "    Эффективность: " << compStationList[i].efficiency << "\n";
	}
	cout << "\nНажмите любую клавишу, чтобы продолжить\n";
	_getch();
}

void EditPipe()
{
	cout << "\n---Редактировать трубу---\n";

	if (pipeList.size() == 0)
	{
		cout << "\nУ Вас нет труб для редактирования\n";
	}
	else
	{
		int pipeIndex;
		bool HasId = false;
		while (!HasId)
		{
			int id;
			TryInput(id, "Введите идентификатор трубы: ");
			for (int i = 0; i < pipeList.size(); i++)
			{
				if (id == pipeList[i].id)
				{
					HasId = true;
					pipeIndex = i;
					break;
				}
			}
			if (!HasId)
			{
				cout << "Такой ID трубы не существует. Пожалуйста, введите существующий ID\n";
				continue;
			}
		}
		bool isEditing = true;
		while (isEditing)
		{
			cout << "\nЧто Вы хотите сделать с трубой?\n"
				<< "1 - Удалить\n"
				<< "2 - Починить/Сломать\n"
				<< "3 - Отмена\n";
			int input;
			TryInput(input, "Введите: ");
			switch (input)
			{
			case 1:
			{
				auto iteration = pipeList.cbegin();
				pipeList.erase(iteration + pipeIndex);
				cout << "Труба успешно удалена\n";
				isEditing = false;
			}
			break;
			case 2:
				pipeList[pipeIndex].isRepairing = !(pipeList[pipeIndex].isRepairing);
				if (pipeList[pipeIndex].isRepairing)
					cout << "Труба успешно сломана и находится в ремонте!\n";
				else
					cout << "Ремонт трубы успешно завершён!\n";
				break;
			case 3:
				isEditing = false;
				break;
			}
		}
	}
	cout << "\nНажмите любую клавишу, чтобы продолжить\n";
	_getch();
}

void EditCompressorStation()
{
	cout << "\n---Редактировать компрессорную станцию---\n";

	if (compStationList.size() == 0)
	{
		cout << "\nУ Вас нет КС для редактирования\n";
	}
	else
	{
		int csIndex;
		bool HasId = false;
		while (!HasId)
		{
			int id;
			TryInput(id, "Введите идентификатор КС: ");
			for (int i = 0; i < compStationList.size(); i++)
			{
				if (id == compStationList[i].id)
				{
					HasId = true;
					csIndex = i;
					break;
				}
			}
			if (!HasId)
			{
				cout << "Такой ID КС не существует. Пожалуйста, введите существующий ID\n";
				continue;
			}
		}
		bool isEditing = true;
		while (isEditing)
		{
			cout << "\nЧто Вы хотите сделать с КС?\n"
				<< "1 - Удалить\n"
				<< "2 - Увеличить/уменьшить общее количество цехов\n"
				<< "3 - Изменить количество работающих цехов\n"
				<< "4 - Отмена\n";
			int input;
			TryInput(input, "Введите: ");
			switch (input)
			{
			case 1:
			{
				auto iteration = pipeList.cbegin();
				pipeList.erase(iteration + csIndex);
				cout << "КС успешно удалена\n";
				isEditing = false;
			}
			break;
			case 2:
				cout << "Сейчас в КС есть " << compStationList[csIndex].shopsCount << " цехов.\n";
				cout << "1 - Увеличить количество цехов\n"
					<< "2 - Уменьшить количество цехов\n";
				TryInput(input, "");
				switch (input)
				{
				case 1:
					compStationList[csIndex].shopsCount++;
					cout << "Количество цехов успешно увеличено до " << compStationList[csIndex].shopsCount + "\n";
				break;
				case 2:
					compStationList[csIndex].shopsCount--;
					if (compStationList[csIndex].operationShopsCount > compStationList[csIndex].shopsCount)
						compStationList[csIndex].operationShopsCount = compStationList[csIndex].shopsCount;
					cout << "Количество цехов успешно уменьшено до " << compStationList[csIndex].shopsCount + "\n";
				default:
					cout << "Введён неверный символ. Закрытие редактирования КС.";
				break;
				compStationList[csIndex].RecountEfficiency();
				}
			break;
			case 3:
				cout << "Сейчас в КС работают " << compStationList[csIndex].operationShopsCount << "/" << compStationList[csIndex].shopsCount << " цехов\n";
				int operationShopsCount;
				TryInput(operationShopsCount, "Введите новое количество работающих цехов: ");
				while (operationShopsCount > compStationList[csIndex].shopsCount)
				{
					cout << "Ошибка! Количество работающих цехов не может быть больше общего количества цехов\n";
					TryInput(operationShopsCount, "Введите новое количество работающих цехов: ");
				}
				compStationList[csIndex].operationShopsCount = operationShopsCount;
				compStationList[csIndex].RecountEfficiency();
			break;
			case 4:
				isEditing = false;
			break;
			}
		}
	}
	cout << "\nНажмите любую клавишу, чтобы продолжить\n";
	_getch();
}

void Save()
{
	cout << "\n---Сохранить---\n";
}

void Load()
{
	cout << "\n---Загрузить---\n";
}

void Menu()
{
	bool isRunning = true;

	while (isRunning)
	{
		cout << "\n---МЕНЮ---\n"
			 << "1 - Добавить трубу\n"
			 << "2 - Добавить КС\n"
			 << "3 - Просмотр всех объектов\n"
			 << "4 - Редактировать трубу\n"
			 << "5 - Редактировать КС\n"
			 << "6 - Сохранить\n"
			 << "7 - Загрузить\n"
			 << "0 - Выход\n";

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
		}
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	Menu();
}