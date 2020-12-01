#include <iostream>
#include <string>
#include <unordered_map>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include "Pipe.h"
#include "CompressorStation.h"
#include "Graph.h"
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
int FindObjById(const unordered_map<int, T>& objGroup)
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
		else if (objGroup.find(id) != objGroup.end())
		{
			return id;
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
vector<int> FindObjByFilter(const unordered_map<int, TObj>& group, Filter<TFilter, TObj> f, TFilter param)
{
	vector <int> res;
	for (const pair<int, TObj>& obj : group)
		if (f(obj.second, param))
			res.push_back(obj.first);
	return res;
}

int main()
{
	// ������������� ������������� ���� � ����� (www.cyberforum.ru/cpp-beginners/thread2574044.html)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unordered_map<int, Pipe> pGroup = unordered_map<int, Pipe>{};
	unordered_map<int, CompressorStation> csGroup = unordered_map<int, CompressorStation>{};
	int edgeCount = 0;

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
			<< "12 - ������� ����� � ��\n"
			<< "13 - ������� ���������������� ����\n"
			<< "14 - ��������� �������������� ����������\n"
			<< "0 � ��. - �����\n";

		int inputMenu;
		TryInput(inputMenu, "��� �� ������ �������: ");

		switch (inputMenu)
		{
		case 1:
		{
			PrintTitle("�������� �����");
			Pipe p;
			cin >> p;
			pGroup.insert(make_pair(++Pipe::pMaxId, p));
			break;
		}
		case 2:
		{
			PrintTitle("�������� ��");
			CompressorStation cs;
			cin >> cs;
			csGroup.insert(make_pair(++CompressorStation::csMaxId, cs));
			break;
		}
		case 3:
		{
			PrintTitle("�������� ���� ��������");
			cout << "���������� ���� - " << pGroup.size() << "\n";
			for (const pair<int, Pipe>& p : pGroup)
			{
				cout << "����� " << p.first << ".\n";
				cout << p.second;
			}
			cout << "���������� �� - " << csGroup.size() << "\n";
			for (const pair<int, CompressorStation>& cs : csGroup)
			{
				cout << "������������� ������� " << cs.first << ".\n";
				cout << cs.second;
			}
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
				int id = FindObjById(pGroup);
				if (id != -1)
				{
					pGroup.erase(id);
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
				int id = FindObjById(csGroup);
				if (id != -1)
				{
					csGroup.erase(id);
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
					{
						cout << "����� " << i << ".\n";
						cout << pGroup[i];
					}
					break;
				}
				case 2:
				{
					for (int i : FindObjByFilter(pGroup, CheckPipeByRepairing, false))
					{
						cout << "����� " << i << ".\n";
						cout << pGroup[i];
					}
					break;
				}
				default:
					cout << "����� �� ������ ������ ����\n";
					break;
				}
				cout << "\n�� ������ ��������������� ��� �����?\n"
					<< "1 - �������� ���\n"
					<< "0 � ��. - �����\n";
				TryInput(input, "�������: ");
				if (input == 1)
				{
					for (pair<int, Pipe> p : pGroup)
						p.second.Repair();
					cout << "��� ��������� ����� ������� ��������!\n";
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
					{
						cout << "������������� ������� " << i << ".\n";
						cout << csGroup[i];
					}
					break;
				}
				case 2:
				{
					float percent;
					TryInput(percent, "������� ������� ��� ���������� (��������� �� � ��������� ������ ����������): ");
					for (int i : FindObjByFilter(csGroup, CheckCsByUnusedShops, percent))
					{
						cout << "������������� ������� " << i << ".\n";
						cout << csGroup[i];
					}
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
				int pCount;
				fout << pGroup.size() << '\n'
					<< csGroup.size() << '\n'
					<< Pipe::pMaxId << '\n'
					<< CompressorStation::csMaxId << '\n'
					<< edgeCount << '\n';
				for (pair<int, Pipe> p : pGroup)
				{
					fout << p.first << '\n';
					p.second.SaveToFile(fout);
				}
				for (pair<int, CompressorStation> cs : csGroup)
				{
					fout << cs.first << '\n';
					cs.second.SaveToFile(fout);
				}
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
				pGroup.clear();
				csGroup.clear();
				int pSize;
				int csSize;
				fin >> pSize;
				fin >> csSize;
				fin >> Pipe::pMaxId;
				fin >> CompressorStation::csMaxId;
				fin >> edgeCount;
				while (pSize--)
				{
					int id;
					fin >> id;
					pGroup.insert(make_pair(id, Pipe(fin)));
				}
				while (csSize--)
				{
					int id;
					fin >> id;
					csGroup.insert(make_pair(id, CompressorStation(fin)));
				}
				fin.close();
				cout << "���� ������� ��������!\n";
			}
			else
			{
				cout << "������ ���������� �����!\n";
			}
			break;
		}
		case 12:
		{
			PrintTitle("������� ����� � ��");
			if (pGroup.size() != 0 && csGroup.size() > 1)
			{
				int id = FindObjById(pGroup);
				if (id != -1)
				{
					cout << "��, �� ������� ������� �����:\n";
					int outCsId = FindObjById(csGroup);
					cout << "��, � ������� ������ �����:\n";
					int inCsId = FindObjById(csGroup);
					while (inCsId == outCsId)
					{
						cout << "����� �� ����� ������� � �� �� ����� ��! ������� ������ Id:\n";
						int inCsId = FindObjById(csGroup);
					}
					pGroup[id].outCsId = outCsId;
					pGroup[id].inCsId = inCsId;
					edgeCount++;
				}
				else
				{
					cout << "����� �� ������ ����� ����� � ��...\n";
				}
			}
			else
			{
				cout << "� ��� ��� ���� � �� ��� �����.\n";
			}
			break;
		}
		case 13:
		{
			PrintTitle("���������������� ����");
			Graph g(edgeCount);
			for (const pair<int, Pipe>& p : pGroup)
				if (p.second.inCsId > 0 && p.second.outCsId > 0 && !p.second.GetRepairing())
				{
					g.addEdge(p.second.outCsId - 1, p.second.inCsId - 1);
					cout << "�� " << p.second.outCsId << " -- ����� " << p.first << " -> �� " << p.second.inCsId << '\n';
				}
			
			break;
		}
		case 14:
		{
			PrintTitle("�������������� ����������");
			Graph g(edgeCount);
			for (const pair<int, Pipe>& p : pGroup)
				if (p.second.inCsId > 0 && p.second.outCsId > 0 && !p.second.GetRepairing())
					g.addEdge(p.second.outCsId - 1, p.second.inCsId - 1);
			g.topologicalSort();
			break;
		}
		default:
		{
			return 0;
		}
		}
	}
}