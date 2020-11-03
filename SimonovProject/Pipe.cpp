#include "Pipe.h"

int Pipe::pMaxId = 0;
int pId;
float Length;
float Diameter;
bool IsRepairing;

Pipe::Pipe()
{
	pId = ++pMaxId;
	TryInput(Length, "������� ����� ����� (� ������): ");
	TryInput(Diameter, "������� ������� ����� (� �����������): ");
	IsRepairing = true;
}

Pipe::Pipe(std::ifstream& fin)
{
	fin >> pId
		>> Length
		>> Diameter
		>> IsRepairing;
}

int Pipe::GetId() const
{
	return pId;
}

bool Pipe::GetRepairing() const
{
	return IsRepairing;
}

void Pipe::Edit()
{
	if (IsRepairing)
		std::cout << "\n�, ���! ����� �������!\n";
	else
		std::cout << "\n����� �� ��������� � �������.\n";
	std::cout << "��� �� ������ ������� � ������?\n"
		<< "1 - ��������/�������\n"
		<< "0 � ��. - ������\n";
	int input;
	TryInput(input, "�������: ");
	switch (input)
	{
	case 1:
	{
		IsRepairing = !IsRepairing;
		if (IsRepairing)
			std::cout << "����� ������� ������� � ��������� � �������!\n";
		else
			std::cout << "������ ����� ������� ��������!\n";
		break;
	}
	default:
	{
		std::cout << "�� ����� �� ������ ��������������.\n";
		break;
	}
	}
}

void Pipe::SaveToFile(std::ofstream& fout)
{
	fout << pId << '\n'
		<< Length << '\n'
		<< Diameter << '\n'
		<< IsRepairing << '\n';
}

std::ostream& operator << (std::ostream& out, const Pipe& p)
{
	out << "����� " << p.pId << ".\n"
		<< "    �����: " << p.Length << '\n'
		<< "    �������: " << p.Diameter << '\n';
	if (p.IsRepairing)
		out << "    ��������� � �������" << '\n';
	else
		out << "    �� ��������� � �������" << '\n';
	return out;
}