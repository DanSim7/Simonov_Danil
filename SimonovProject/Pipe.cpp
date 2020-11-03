#include "Pipe.h"

int Pipe::pMaxId = 0;
int pId;
float Length;
float Diameter;
bool IsRepairing;

Pipe::Pipe()
{
	pId = ++pMaxId;
	TryInput(Length, "Введите длину трубы (в метрах): ");
	TryInput(Diameter, "Введите диаметр трубы (в миллиметрах): ");
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
		std::cout << "\nО, нет! Труба сломана!\n";
	else
		std::cout << "\nТруба не нуждается в ремонте.\n";
	std::cout << "Что Вы хотите сделать с трубой?\n"
		<< "1 - Починить/Сломать\n"
		<< "0 и пр. - Отмена\n";
	int input;
	TryInput(input, "Введите: ");
	switch (input)
	{
	case 1:
	{
		IsRepairing = !IsRepairing;
		if (IsRepairing)
			std::cout << "Труба успешно сломана и находится в ремонте!\n";
		else
			std::cout << "Ремонт трубы успешно завершён!\n";
		break;
	}
	default:
	{
		std::cout << "Вы вышли из режима редактирования.\n";
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
	out << "Труба " << p.pId << ".\n"
		<< "    Длина: " << p.Length << '\n'
		<< "    Диаметр: " << p.Diameter << '\n';
	if (p.IsRepairing)
		out << "    Находится в ремонте" << '\n';
	else
		out << "    Не нуждается в ремонте" << '\n';
	return out;
}