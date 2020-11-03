#include "CompressorStation.h"

int CompressorStation::csMaxId = 0;
int csId;
std::string Name;
int ShopsCount;
int WorkingShopsCount;
float Efficiency;

CompressorStation::CompressorStation()
{
	csId = ++csMaxId;
	std::cout << "������� ��� ������������� �������: ";
	std::cin.ignore();
	std::getline(std::cin, Name);
	TryInput(ShopsCount, "������� ����� ���-�� �����: ");
	TryInput(WorkingShopsCount, "������� ���-�� ���������� �����: ");
	while (WorkingShopsCount > ShopsCount) {
		std::cout << "������! ���-�� ���������� ����� �� ����� ���� ������ ������ ���-�� �����\n";
		TryInput(WorkingShopsCount, "����������, ������� ���������� ���-�� ���������� �����: ");
	}
	TryInput(Efficiency, "������� ������������ ������������� �������: ");
}

CompressorStation::CompressorStation(std::ifstream& fin)
{
	fin >> csId;
	fin.ignore();
	std::getline(fin, Name);
	fin >> ShopsCount
		>> WorkingShopsCount
		>> Efficiency;
}

int CompressorStation::GetId() const
{
	return csId;
}

std::string CompressorStation::GetName() const
{
	return Name;
}

float CompressorStation::GetPercentUnusedShops() const
{
	return (1 - (WorkingShopsCount * 1.0f / ShopsCount)) * 100;
}

void CompressorStation::RecountShopsCount()
{
	std::cout << "������ � �� ���� " << ShopsCount << " �����.\n";
	std::cout << "1 - ��������� ���������� �����\n"
			  << "2 - ��������� ���������� �����\n"
			  << "0 � ��. - ������\n";
	int input;
	TryInput(input, "�������: ");
	switch (input)
	{
	case 1:
		ShopsCount++;
		std::cout << "���������� ����� ������� ��������� �� " << ShopsCount << "\n";
		break;
	case 2:
		ShopsCount--;
		if (WorkingShopsCount > ShopsCount)
			WorkingShopsCount = ShopsCount;
		std::cout << "���������� ����� ������� ��������� �� " << ShopsCount << "\n";
	default:
		std::cout << "�� ����� �� ������ ��������������.";
		break;
	}
}

void CompressorStation::RecountWorkingShopsCount()
{
	std::cout << "������ � �� �������� " << WorkingShopsCount << "/" << ShopsCount << " �����\n";
	int workingShopsCount;
	TryInput(workingShopsCount, "������� ����� ���������� ���������� �����: ");
	while (workingShopsCount > ShopsCount)
	{
		std::cout << "������! ���������� ���������� ����� �� ����� ���� ������ ������ ���������� �����\n";
		TryInput(workingShopsCount, "������� ����� ���������� ���������� �����: ");
	}
	WorkingShopsCount = workingShopsCount;
}

void CompressorStation::SaveToFile(std::ofstream& fout)
{
	fout << csId << '\n'
		<< Name << '\n'
		<< ShopsCount << '\n'
		<< WorkingShopsCount << '\n'
		<< Efficiency << '\n';
}

std::ostream& operator << (std::ostream& out, const CompressorStation& cs)
{
	std::cout << "������������� ������� " << cs.csId << ".\n"
		<< "    ���: " << cs.Name << "\n"
		<< "    �������� " << cs.WorkingShopsCount << "/" << cs.ShopsCount << " �����" "\n"
		<< "    �������������: " << cs.Efficiency << "\n";
	std::cout << cs.GetPercentUnusedShops() << '\n';
	return out;
}