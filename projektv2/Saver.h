#ifndef SAVER_H
#define SAVER_H
#include <vector>
#include <fstream>
#include "Data.h"

// klasa bazowa
class Saver
{
public:
	virtual ~Saver() {};
	virtual void run(OutData & Outdata, std::string file_name) = 0;
};

// klasa dziedziczace do konketnych obliczen
class CSVsaver : public Saver
{
public:
	CSVsaver();
	void run(OutData & Outdata, std::string file_name) override;
};

#endif
