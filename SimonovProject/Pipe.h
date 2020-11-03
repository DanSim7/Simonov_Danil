#pragma once
#include <iostream>
#include "utilities.h"
#include <fstream>

class Pipe
{
	int pId;
	float Length;
	float Diameter;
	bool IsRepairing;
public:
	static int pMaxId;
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	Pipe();
	Pipe(std::ifstream& fin);
	int GetId() const;
	bool GetRepairing() const;
	void Edit();
	void SaveToFile(std::ofstream& fout);
};