#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include "Pipe.h"
#include "CompressorStation.h"
#include "utilities.h"
using namespace std;

void PrintTitle(string title)
{
	// Меняем цвет фона и шрифта, а потом возвращаем на место (mvblog.ru/archives/144/)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((7 << 4) | 0));
	cout << '\n' << ' ' << title << ' ';
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	cout << endl;
}

template <typename T>
int FindObjById(const vector<T>& objGroup)
{
	while (true)
	{
		int id;
		TryInput(id, "Введите ID (0 - выйти): ");
		if (id == 0)
		{
			cout << "Вы вышли из режима поиска по ID.\n";
			return -1;
		}
		else
		{
			for (int i = 0; i < objGroup.size(); i++)
				if (id == objGroup[i].GetId())
					return i;
		}
		cout << "Такого ID не существует. Пожалуйста, введите существующий ID.\n";
	}
}

template <typename TParam, typename TObj>
using Filter = bool(*)(const TObj& obj, TParam param);

bool CheckPipeByRepairing(const Pipe& p, bool param)
{
	return p.GetRepairing() == param;
}

bool CheckCsByName(const CompressorStation& cs, string param)
{
	return cs.GetName() == param;
}

bool CheckCsByUnusedShops(const CompressorStation& cs, float param)
{
	return cs.GetPercentUnusedShops() <= param;
}

template <typename TFilter, typename TObj>
vector<int> FindObjByFilter(const vector<TObj>& group, Filter<TFilter, TObj> f, TFilter param)
{
	vector <int> res;
	int i = 0;
	for (auto& obj : group)
	{
		if (f(obj, param))
			res.push_back(i);
		i++;
	}
	return res;
}

int main()
{
	// Устанавливаем русскоязычный ввод и вывод (www.cyberforum.ru/cpp-beginners/thread2574044.html)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<Pipe> pGroup = vector<Pipe>{};
	vector<CompressorStation> csGroup = vector<CompressorStation>{};

	while (true)
	{
		PrintTitle("МЕНЮ");
		cout << "1 - Добавить трубу\n"
			<< "2 - Добавить КС\n"
			<< "3 - Просмотр всех объектов\n"
			<< "4 - Редактировать трубу\n"
			<< "5 - Редактировать КС\n"
			<< "6 - Удалить трубу\n"
			<< "7 - Удалить КС\n"
			<< "8 - Поиск труб\n"
			<< "9 - Поиск КС\n"
			<< "10 - Сохранить\n"
			<< "11 - Загрузить\n"
			<< "0 и пр. - Выход\n";

		int inputMenu;
		TryInput(inputMenu, "Что Вы хотите сделать: ");

		switch (inputMenu)
		{
		case 1:
		{
			PrintTitle("ДОБАВИТЬ ТРУБУ");
			pGroup.push_back(Pipe());

			break;
		}
		case 2:
		{
			PrintTitle("ДОБАВИТЬ КС");
			csGroup.push_back(CompressorStation());
			break;
		}
		case 3:
		{
			PrintTitle("ПРОСМОТР ВСЕХ ОБЪЕКТОВ");
			cout << "Количество труб - " << pGroup.size() << "\n";
			for (auto& p : pGroup)
				cout << p;
			cout << "Количество КС - " << csGroup.size() << "\n";
			for (auto& cs : csGroup)
				cout << cs;
			break;
		}
		case 4:
		{
			PrintTitle("РЕДАКТИРОВАТЬ ТРУБУ");
			if (pGroup.size() != 0)
			{
				int index = FindObjById(pGroup);
				if (index != -1)
					pGroup[index].Edit();
			}
			else
			{
				cout << "У Вас нет труб для редактирования.\n";
			}
			break;
		}
		case 5:
		{
			PrintTitle("РЕДАКТИРОВАТЬ КС");
			if (csGroup.size() != 0)
			{
				int index = FindObjById(csGroup);
				if (index != -1)
				{
					cout << "\nЧто Вы хотите сделать с КС?\n"
						<< "1 - Увеличить/уменьшить общее количество цехов\n"
						<< "2 - Изменить количество работающих цехов\n"
						<< "0 и пр. - Отмена\n";
					int input;
					TryInput(input, "Введите: ");
					switch (input)
					{
					case 1:
						csGroup[index].RecountShopsCount();
						break;
					case 2:
						csGroup[index].RecountWorkingShopsCount();
						break;
					default:
						cout << "Вы вышли из режима редактирования.";
						break;
					}
				}
			}
			else
			{
				cout << "У Вас нет КС для редактирования.\n";
			}
			break;
		}
		case 6:
		{
			PrintTitle("УДАЛИТЬ ТРУБУ");
			if (pGroup.size() != 0)
			{
				int index = FindObjById(pGroup);
				if (index != -1)
				{
					// www.cplusplus.com/reference/vector/vector/erase/
					pGroup.erase(pGroup.cbegin() + index);
					cout << "Труба успешно удалена!\n";
				}
			}
			else
			{
				cout << "У Вас нет трубы для удаления.\n";
			}
			break;
		}
		case 7:
		{
			PrintTitle("УДАЛИТЬ КС");
			if (csGroup.size() != 0)
			{
				int index = FindObjById(csGroup);
				if (index != -1)
				{
					// www.cplusplus.com/reference/vector/vector/erase/
					csGroup.erase(csGroup.cbegin() + index);
					cout << "КС успешно удалена!\n";
				}
			}
			else
			{
				cout << "У Вас нет КС для удаления.\n";
			}
			break;
		}
		case 8:
		{
			PrintTitle("ПОИСК ТРУБ");
			if (pGroup.size() != 0)
			{
				int input;
				TryInput(input, "Ищем трубу в ремонте? (1 - да, 2 - нет, пр. - выйти)\n");
				switch (input)
				{
				case 1:
				{
					for (int i : FindObjByFilter(pGroup, CheckPipeByRepairing, true))
						cout << pGroup[i];
					break;
				}
				case 2:
				{
					for (int i : FindObjByFilter(pGroup, CheckPipeByRepairing, false))
						cout << pGroup[i];
					break;
				}
				default:
					cout << "Выход из режима поиска труб\n";
					break;
				}
			}
			else
			{
				cout << "У Вас нет трубы для поиска.\n";
			}
			break;
		}
		case 9:
		{
			PrintTitle("ПОИСК КС");
			if (csGroup.size() != 0)
			{
				int input;
				cout << "По какому фильтру ищем КС?\n";
				TryInput(input, "(1 - по названию, 2 - по проценту незадействованных цехов, пр. - выйти): ");
				switch (input)
				{
				case 1:
				{
					string name;
					cout << "Введите имя КС для фильтрации: ";
					cin.ignore();
					getline(cin, name);
					for (int i : FindObjByFilter(csGroup, CheckCsByName, name))
						cout << csGroup[i];
					break;
				}
				case 2:
				{
					float percent;
					TryInput(percent, "Введите процент для фильтрации (покажутся КС с процентом меньше указанного): ");
					for (int i : FindObjByFilter(csGroup, CheckCsByUnusedShops, percent))
						cout << csGroup[i];
					break;
				}
				default:
					cout << "Выход из режима поиска труб\n";
					break;
				}
			}
			else
			{
				cout << "У Вас нет КС для поиска.\n";
			}
			break;
		}
		case 10:
		{
			PrintTitle("СОХРАНИТЬ");
			if (pGroup.size() == 0 && csGroup.size() == 0)
			{
				cout << "Внимание! У Вас ни одной трубы и КС. Вы действительно хотите сохранить данные?\n";
				int input;
				TryInput(input, "(1 - да, 0 и пр. - нет): ");
				if (input != 1)
				{
					cout << "Отмена сохранения...\n";
					break;
				}
			}
			string filename;
			cout << "Введите имя файла сохранения (.txt): ";
			cin >> filename;
			ofstream fout;
			fout.open(filename + ".txt", ios::out);
			if (fout.is_open())
			{
				fout << pGroup.size() << '\n'
					<< csGroup.size() << '\n'
					<< Pipe::pMaxId << '\n'
					<< CompressorStation::csMaxId << '\n';
				for (auto& p : pGroup)
					p.SaveToFile(fout);
				for (auto& cs : csGroup)
					cs.SaveToFile(fout);
				fout.close();
				cout << "Файл успешно сохранён!\n";
			}
			else
			{
				cout << "Ошибка сохранения файла!\n";
			}
			break;
		}
		case 11:
		{
			PrintTitle("ЗАГРУЗИТЬ");
			string filename;
			cout << "Введите имя файла загрузки (.txt): ";
			cin >> filename;
			ifstream fin;
			fin.open(filename + ".txt", ios::in);
			if (fin.is_open())
			{
				pGroup.resize(0);
				csGroup.resize(0);
				int pSize;
				int csSize;
				fin >> pSize;
				fin >> csSize;
				fin >> Pipe::pMaxId;
				fin >> CompressorStation::csMaxId;
				while (pSize--)
					pGroup.push_back(Pipe(fin));
				while (csSize--)
					csGroup.push_back(CompressorStation(fin));
				fin.close();
				cout << "Файл успешно загружен!\n";
			}
			else
			{
				cout << "Ошибка сохранения файла!\n";
			}
			break;
		}
		default:
		{
			return 0;
		}
		}
	}
}