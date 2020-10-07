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
void TryInput(int& input, string inputText) {
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
void TryInput(float& input, string inputText) {
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

		cout << "���� ������ ��������\n";
		cout << "1 - �������� �����\n";
		cout << "2 - �������� ��\n";
		cout << "3 - �������� ���� ��������\n";
		cout << "4 - ������������� �����\n";
		cout << "5 - ������������� ��\n";
		cout << "6 - ���������\n";
		cout << "7 - ���������\n";
		cout << "0 - �����\n";

		int inputMenu = 0;
		TryInput(inputMenu, "��� �� ������ �������: ");
		
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