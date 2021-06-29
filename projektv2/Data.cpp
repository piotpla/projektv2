#include "Data.h"

InData::InData() {}; // pusty konstruktor
InData::InData(std::vector< std::vector<double> > data) : data(data) {} // konstruktor argumentowy
InData::InData(const InData& other) { data = other.data; }; // konstruktor kopiujacy

OutData::OutData() {}; // pusty konstruktor
OutData::OutData(std::vector<double>& min, std::vector<double>& max, std::vector<double>& med, std::vector<double>& avg) :
	min(min), max(max), med(med), avg(avg) {}; // konstruktor argumentowy

ErrorLog::ErrorLog() {}; // pusty konstruktor
