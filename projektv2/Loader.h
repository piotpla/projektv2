#ifndef LOADER_H
#define LOADER_H
#include "Data.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

// klasa bazowa
class Loader
{
public:
	virtual ~Loader() {};
	virtual void run(const std::string& file_name, InData & result) = 0;
};

// klasa dziedziczace do konketnych obliczen
class CSV : public Loader
{
public:
	CSV();
	void run(const std::string& file_name, InData & result) override;
};

#endif
