#include "Saver.h"
#include "Data.h"
#include <fstream>
#include <iostream>

CSVsaver::CSVsaver() {};
void CSVsaver::run( OutData & data, std::string file_name)
{
	std::fstream out;
		out.open(file_name, std::ios::out);
		if (out.is_open())
		{
			out << "WYNIKI: \n";
			out << "Minimal: \n";
			for (short i = 0; i < data.min.size(); i++) //tmp
			{
				out << data.min[i];
				if (data.min.size()!=i-1)
				{
					out << "|";
				}
			}
			out << "\n";
			out << "Maximal: \n";
			for (short i = 0; i < data.max.size(); i++) //tmp
			{
				out << data.max[i];
				if (data.max.size() != i - 1)
				{
					out << "|";
				}
			}
			out << "\n";
			out << "Median: \n";
			for (short i = 0; i < data.med.size(); i++) //tmp
			{
				out << data.med[i];
				if (data.med.size() != i - 1)
				{
					out << "|";
				}
			}
			out << "\n";
			out << "Average: \n";
			for (short i = 0; i < data.avg.size(); i++) //tmp
			{
				out << data.avg[i];
				if (data.avg.size() != i - 1)
				{
					out << "|";
				}
			}
		out.close();
		}
		
		else std::cerr << "blad";
		
}