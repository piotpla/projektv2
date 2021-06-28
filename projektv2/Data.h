#ifndef DATA_H
#define DATA_H
#include <vector>
#include <string>

class InData
{
public:
	std::vector< std::vector<double> > data;

	InData();
	InData(std::vector< std::vector<double> > data);
	InData(const InData& other);
};

class OutData
{
public:
	std::vector<double> min;
	std::vector<double> max;
	std::vector<double> med;
	std::vector<double> avg;

	OutData();
	OutData(std::vector<double>& min, std::vector<double>& max, std::vector<double>& med, std::vector<double>& avg);
};

class ErrorLog
{
public:
	std::vector<std::string> newError;
	ErrorLog();
};

#endif