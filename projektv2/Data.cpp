#include "Data.h"

InData::InData() {};
InData::InData(std::vector< std::vector<double> > data) : data(data) {}
InData::InData(const InData& other) { data = other.data; };

OutData::OutData() {};
OutData::OutData(std::vector<double>& min, std::vector<double>& max, std::vector<double>& med, std::vector<double>& avg) :
	min(min), max(max), med(med), avg(avg) {};

ErrorLog::ErrorLog() {};
