#ifndef ANALYZER_H
#define ANALYZER_H
#include "Data.h"
#include <vector>
#include <iostream>
#include <algorithm>

// klasa bazowa
class Analyzer 
{
public:
	virtual ~Analyzer() {};
	virtual void run(InData & data_in, OutData & data_out) = 0;
};

// klasa dziedziczace do konketnych obliczen
class Minimum : public Analyzer 
{
public:
	Minimum();
	void run(InData & data_in, OutData & data_out) override;
};

class Maximum : public Analyzer
{
public:
	Maximum();
	void run(InData& data_in, OutData& data_out) override;
};

class Median : public Analyzer
{
public:
	Median();
	void run(InData& data_in, OutData& data_out) override;
};

class Average : public Analyzer
{
public:
	Average();
	void run(InData& data_in, OutData& data_out) override;
};

#endif
