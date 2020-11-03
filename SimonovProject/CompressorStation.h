#pragma once
#include <string>
#include <iostream>
#include "utilities.h"
#include <fstream>

class CompressorStation
{
	int csId;
	std::string Name;
	int ShopsCount;
	int WorkingShopsCount;
	float Efficiency;
public:
	static int csMaxId;
	friend std::ostream& operator << (std::ostream& out, const CompressorStation& cs);
	CompressorStation();
	CompressorStation(std::ifstream& fin);
	int GetId() const;
	std::string GetName() const;
	float GetPercentUnusedShops() const;
	void RecountShopsCount();
	void RecountWorkingShopsCount();
	void SaveToFile(std::ofstream& fout);
};