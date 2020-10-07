#include <iostream>
#include <string>
#include <list>
using namespace std;

/// <summary>
/// ���� ������ � ��������� ���� int
/// </summary>
/// <param name="input">���������� ����� int</param>
/// <param name="inputText">�����, ������������� ���� ����������</param>
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
/// ���� ������ � ��������� ���� float
/// </summary>
/// <param name="input">���������� ����� float</param>
/// <param name="inputText">�����, ������������� ���� ����������</param>
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
/// ���� ������ � ��������� ���� bool
/// </summary>
/// <param name="input">���������� ����� bool</param>
/// <param name="inputText">�����, ������������� ���� ����������</param>
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
	TryInput(pipe.id, "\n������� ������������� �����: ");
	TryInput(pipe.length, "\n������� ����� �����: ");
	TryInput(pipe.diameter, "\n������� ������� �����: ");
	TryInput(pipe.isRepairing, "\n����� �� �������? (true ��� false): ");
	pipeList.push_front(pipe);
}

void AddCompressorStation() {

}

void ShowAll() {
	cout << "������ ����:";
	for (Pipe pipe : pipeList)
	{
		cout << "����� " << pipe.id << ".\n"
			<< "    �����: " << pipe.length << "\n"
			<< "    �������:"  << pipe.length << "\n"
			<< "    � �������: " << pipe.length << "\n";
	}
	cout << "������ ��:";
	for (CompressorStation compStation : compStationList)
	{
		cout << "������������� ������� " << compStation.id << ".\n"
			<< "    ���: " << compStation.name << "\n"
			<< "    �������� " << compStation.shopsCount << "/" << compStation.operationShopsCount << " �����" "\n"
			<< "    �������������: " << compStation.efficiency << "\n";
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

		cout << "���� ������ ��������\n";
		cout << "1 - �������� �����\n";
		cout << "2 - �������� ��\n";
		cout << "3 - �������� ���� ��������\n";
		cout << "4 - ������������� �����\n";
		cout << "5 - ������������� ��\n";
		cout << "6 - ���������\n";
		cout << "7 - ���������\n";
		cout << "0 - �����\n";

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
		default:
			return 0;
		break;
		}
		
	}
}

