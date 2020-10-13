#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <iterator>
using namespace std;

/// <summary>
/// ���� ������ � ��������� ���� int
/// </summary>
/// <param name="input">���������� ����� int</param>
/// <param name="inputText">�����, ������������� ���� ����������</param>
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
/// ���� ������ � ��������� ���� float
/// </summary>
/// <param name="input">���������� ����� float</param>
/// <param name="inputText">�����, ������������� ���� ����������</param>
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
/// ���� ������ � ��������� ���� bool
/// </summary>
/// <param name="input">���������� ����� bool</param>
/// <param name="inputText">�����, ������������� ���� ����������</param>
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
/// ������������� �������
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
/// �����
/// </summary>
struct Pipe
{
	int id;
	float length;
	float diameter;
	bool isRepairing;
};

// ��������� ������� �������� ������ ���� � ������������� �������
vector<Pipe> pipeList;
vector<CompressorStation> compStationList;

void AddPipe()
{
	cout << "\n---�������� �����---\n";
	Pipe pipe = Pipe();
	vector<int> currentIds = vector<int>(pipeList.size());
	for (int i = 0; i < pipeList.size(); i++)
	{
		currentIds[i] = pipeList[i].id;
	}
	while (true)
	{
		int id;
		TryInput(id, "������� ������������� �����: ");
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
			cout << "����� ID ����� ��� ����. ����������, ������� ������ ID\n";
			continue;
		}
		else
		{
			pipe.id = id;
			break;
		}
	}
	TryInput(pipe.length, "������� ����� �����: ");
	TryInput(pipe.diameter, "������� ������� �����: ");
	pipe.isRepairing = false;
	cout << endl;
	pipeList.push_back(pipe);
}

void AddCompressorStation()
{
	cout << "\n---�������� ������������� �������---\n";
	CompressorStation cs = CompressorStation();
	vector<int> currentIds = vector<int>(compStationList.size());
	for (int i = 0; i < compStationList.size(); i++)
	{
		currentIds[i] = compStationList[i].id;
	}
	while (true)
	{
		int id;
		TryInput(id, "������� ������������� ������������� �������: ");
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
			cout << "����� ID �� ��� ����. ����������, ������� ������ ID\n";
			continue;
		}
		else
		{
			cs.id = id;
			break;
		}
	}
	cout << "������� ��� ��: ";
	cin >> cs.name;
	TryInput(cs.shopsCount, "������� ����� ���������� �����: ");
	TryInput(cs.operationShopsCount, "������� ���������� ���������� �����: ");
	while (cs.operationShopsCount > cs.shopsCount) {
		cout << "������! ���������� ���������� ����� �� ����� ���� ������ ������ ���������� �����\n";
		TryInput(cs.operationShopsCount, "����������, ������� ���������� ���������� ���������� �����: ");
	}
	cs.RecountEfficiency();
	cout << endl;
	compStationList.push_back(cs);
}

void ShowAll()
{
	cout << "\n---�������� ���� ��������---\n";
	cout << "������ ����:\n";
	for (int i = 0; i < pipeList.size(); i++)
	{
		cout << "����� " << pipeList[i].id << ".\n"
			<< "    �����: " << pipeList[i].length << "\n"
			<< "    �������:" << pipeList[i].diameter << "\n";
		if (pipeList[i].isRepairing)
			cout << "    ��������� � �������" << "\n";
		else
			cout << "    �� ��������� � �������" << "\n";
	}
	cout << "\n������ ��:\n";
	for (int i = 0; i < compStationList.size(); i++)
	{
		cout << "������������� ������� " << compStationList[i].id << ".\n"
			<< "    ���: " << compStationList[i].name << "\n"
			<< "    �������� " << compStationList[i].operationShopsCount << "/" << compStationList[i].shopsCount << " �����" "\n"
			<< "    �������������: " << compStationList[i].efficiency << "\n";
	}
	cout << "\n������� ����� �������, ����� ����������\n";
	_getch();
}

void EditPipe()
{
	cout << "\n---������������� �����---\n";

	if (pipeList.size() == 0)
	{
		cout << "\n� ��� ��� ���� ��� ��������������\n";
	}
	else
	{
		int pipeIndex;
		bool HasId = false;
		while (!HasId)
		{
			int id;
			TryInput(id, "������� ������������� �����: ");
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
				cout << "����� ID ����� �� ����������. ����������, ������� ������������ ID\n";
				continue;
			}
		}
		bool isEditing = true;
		while (isEditing)
		{
			cout << "\n��� �� ������ ������� � ������?\n"
				<< "1 - �������\n"
				<< "2 - ��������/�������\n"
				<< "3 - ������\n";
			int input;
			TryInput(input, "�������: ");
			switch (input)
			{
			case 1:
			{
				auto iteration = pipeList.cbegin();
				pipeList.erase(iteration + pipeIndex);
				cout << "����� ������� �������\n";
				isEditing = false;
			}
			break;
			case 2:
				pipeList[pipeIndex].isRepairing = !(pipeList[pipeIndex].isRepairing);
				if (pipeList[pipeIndex].isRepairing)
					cout << "����� ������� ������� � ��������� � �������!\n";
				else
					cout << "������ ����� ������� ��������!\n";
				break;
			case 3:
				isEditing = false;
				break;
			}
		}
	}
	cout << "\n������� ����� �������, ����� ����������\n";
	_getch();
}

void EditCompressorStation()
{
	cout << "\n---������������� ������������� �������---\n";

	if (compStationList.size() == 0)
	{
		cout << "\n� ��� ��� �� ��� ��������������\n";
	}
	else
	{
		int csIndex;
		bool HasId = false;
		while (!HasId)
		{
			int id;
			TryInput(id, "������� ������������� ��: ");
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
				cout << "����� ID �� �� ����������. ����������, ������� ������������ ID\n";
				continue;
			}
		}
		bool isEditing = true;
		while (isEditing)
		{
			cout << "\n��� �� ������ ������� � ��?\n"
				<< "1 - �������\n"
				<< "2 - ���������/��������� ����� ���������� �����\n"
				<< "3 - �������� ���������� ���������� �����\n"
				<< "4 - ������\n";
			int input;
			TryInput(input, "�������: ");
			switch (input)
			{
			case 1:
			{
				auto iteration = pipeList.cbegin();
				pipeList.erase(iteration + csIndex);
				cout << "�� ������� �������\n";
				isEditing = false;
			}
			break;
			case 2:
				cout << "������ � �� ���� " << compStationList[csIndex].shopsCount << " �����.\n";
				cout << "1 - ��������� ���������� �����\n"
					<< "2 - ��������� ���������� �����\n";
				TryInput(input, "");
				switch (input)
				{
				case 1:
					compStationList[csIndex].shopsCount++;
					cout << "���������� ����� ������� ��������� �� " << compStationList[csIndex].shopsCount + "\n";
				break;
				case 2:
					compStationList[csIndex].shopsCount--;
					if (compStationList[csIndex].operationShopsCount > compStationList[csIndex].shopsCount)
						compStationList[csIndex].operationShopsCount = compStationList[csIndex].shopsCount;
					cout << "���������� ����� ������� ��������� �� " << compStationList[csIndex].shopsCount + "\n";
				default:
					cout << "����� �������� ������. �������� �������������� ��.";
				break;
				compStationList[csIndex].RecountEfficiency();
				}
			break;
			case 3:
				cout << "������ � �� �������� " << compStationList[csIndex].operationShopsCount << "/" << compStationList[csIndex].shopsCount << " �����\n";
				int operationShopsCount;
				TryInput(operationShopsCount, "������� ����� ���������� ���������� �����: ");
				while (operationShopsCount > compStationList[csIndex].shopsCount)
				{
					cout << "������! ���������� ���������� ����� �� ����� ���� ������ ������ ���������� �����\n";
					TryInput(operationShopsCount, "������� ����� ���������� ���������� �����: ");
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
	cout << "\n������� ����� �������, ����� ����������\n";
	_getch();
}

void Save()
{
	cout << "\n---���������---\n";
}

void Load()
{
	cout << "\n---���������---\n";
}

void Menu()
{
	bool isRunning = true;

	while (isRunning)
	{
		cout << "\n---����---\n"
			 << "1 - �������� �����\n"
			 << "2 - �������� ��\n"
			 << "3 - �������� ���� ��������\n"
			 << "4 - ������������� �����\n"
			 << "5 - ������������� ��\n"
			 << "6 - ���������\n"
			 << "7 - ���������\n"
			 << "0 - �����\n";

		int inputMenu;
		TryInput(inputMenu, "��� �� ������ �������: ");

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