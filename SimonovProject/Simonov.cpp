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
	// ������ ���� ���� � ������, � ����� ���������� �� ����� (mvblog.ru/archives/144/)
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
		TryInput(id, "������� ID (0 - �����): ");
		if (id == 0)
		{
			cout << "�� ����� �� ������ ������ �� ID.\n";
			return -1;
		}
		else
		{
			for (int i = 0; i < objGroup.size(); i++)
				if (id == objGroup[i].GetId())
					return i;
		}
		cout << "������ ID �� ����������. ����������, ������� ������������ ID.\n";
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
	// ������������� ������������� ���� � ����� (www.cyberforum.ru/cpp-beginners/thread2574044.html)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<Pipe> pGroup = vector<Pipe>{};
	vector<CompressorStation> csGroup = vector<CompressorStation>{};

	while (true)
	{
		PrintTitle("����");
		cout << "1 - �������� �����\n"
			<< "2 - �������� ��\n"
			<< "3 - �������� ���� ��������\n"
			<< "4 - ������������� �����\n"
			<< "5 - ������������� ��\n"
			<< "6 - ������� �����\n"
			<< "7 - ������� ��\n"
			<< "8 - ����� ����\n"
			<< "9 - ����� ��\n"
			<< "10 - ���������\n"
			<< "11 - ���������\n"
			<< "0 � ��. - �����\n";

		int inputMenu;
		TryInput(inputMenu, "��� �� ������ �������: ");

		switch (inputMenu)
		{
		case 1:
		{
			PrintTitle("�������� �����");
			pGroup.push_back(Pipe());

			break;
		}
		case 2:
		{
			PrintTitle("�������� ��");
			csGroup.push_back(CompressorStation());
			break;
		}
		case 3:
		{
			PrintTitle("�������� ���� ��������");
			cout << "���������� ���� - " << pGroup.size() << "\n";
			for (auto& p : pGroup)
				cout << p;
			cout << "���������� �� - " << csGroup.size() << "\n";
			for (auto& cs : csGroup)
				cout << cs;
			break;
		}
		case 4:
		{
			PrintTitle("������������� �����");
			if (pGroup.size() != 0)
			{
				int index = FindObjById(pGroup);
				if (index != -1)
					pGroup[index].Edit();
			}
			else
			{
				cout << "� ��� ��� ���� ��� ��������������.\n";
			}
			break;
		}
		case 5:
		{
			PrintTitle("������������� ��");
			if (csGroup.size() != 0)
			{
				int index = FindObjById(csGroup);
				if (index != -1)
				{
					cout << "\n��� �� ������ ������� � ��?\n"
						<< "1 - ���������/��������� ����� ���������� �����\n"
						<< "2 - �������� ���������� ���������� �����\n"
						<< "0 � ��. - ������\n";
					int input;
					TryInput(input, "�������: ");
					switch (input)
					{
					case 1:
						csGroup[index].RecountShopsCount();
						break;
					case 2:
						csGroup[index].RecountWorkingShopsCount();
						break;
					default:
						cout << "�� ����� �� ������ ��������������.";
						break;
					}
				}
			}
			else
			{
				cout << "� ��� ��� �� ��� ��������������.\n";
			}
			break;
		}
		case 6:
		{
			PrintTitle("������� �����");
			if (pGroup.size() != 0)
			{
				int index = FindObjById(pGroup);
				if (index != -1)
				{
					// www.cplusplus.com/reference/vector/vector/erase/
					pGroup.erase(pGroup.cbegin() + index);
					cout << "����� ������� �������!\n";
				}
			}
			else
			{
				cout << "� ��� ��� ����� ��� ��������.\n";
			}
			break;
		}
		case 7:
		{
			PrintTitle("������� ��");
			if (csGroup.size() != 0)
			{
				int index = FindObjById(csGroup);
				if (index != -1)
				{
					// www.cplusplus.com/reference/vector/vector/erase/
					csGroup.erase(csGroup.cbegin() + index);
					cout << "�� ������� �������!\n";
				}
			}
			else
			{
				cout << "� ��� ��� �� ��� ��������.\n";
			}
			break;
		}
		case 8:
		{
			PrintTitle("����� ����");
			if (pGroup.size() != 0)
			{
				int input;
				TryInput(input, "���� ����� � �������? (1 - ��, 2 - ���, ��. - �����)\n");
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
					cout << "����� �� ������ ������ ����\n";
					break;
				}
			}
			else
			{
				cout << "� ��� ��� ����� ��� ������.\n";
			}
			break;
		}
		case 9:
		{
			PrintTitle("����� ��");
			if (csGroup.size() != 0)
			{
				int input;
				cout << "�� ������ ������� ���� ��?\n";
				TryInput(input, "(1 - �� ��������, 2 - �� �������� ����������������� �����, ��. - �����): ");
				switch (input)
				{
				case 1:
				{
					string name;
					cout << "������� ��� �� ��� ����������: ";
					cin.ignore();
					getline(cin, name);
					for (int i : FindObjByFilter(csGroup, CheckCsByName, name))
						cout << csGroup[i];
					break;
				}
				case 2:
				{
					float percent;
					TryInput(percent, "������� ������� ��� ���������� (��������� �� � ��������� ������ ����������): ");
					for (int i : FindObjByFilter(csGroup, CheckCsByUnusedShops, percent))
						cout << csGroup[i];
					break;
				}
				default:
					cout << "����� �� ������ ������ ����\n";
					break;
				}
			}
			else
			{
				cout << "� ��� ��� �� ��� ������.\n";
			}
			break;
		}
		case 10:
		{
			PrintTitle("���������");
			if (pGroup.size() == 0 && csGroup.size() == 0)
			{
				cout << "��������! � ��� �� ����� ����� � ��. �� ������������� ������ ��������� ������?\n";
				int input;
				TryInput(input, "(1 - ��, 0 � ��. - ���): ");
				if (input != 1)
				{
					cout << "������ ����������...\n";
					break;
				}
			}
			string filename;
			cout << "������� ��� ����� ���������� (.txt): ";
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
				cout << "���� ������� �������!\n";
			}
			else
			{
				cout << "������ ���������� �����!\n";
			}
			break;
		}
		case 11:
		{
			PrintTitle("���������");
			string filename;
			cout << "������� ��� ����� �������� (.txt): ";
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
				cout << "���� ������� ��������!\n";
			}
			else
			{
				cout << "������ ���������� �����!\n";
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