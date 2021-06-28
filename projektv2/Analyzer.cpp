#include "Analyzer.h"

Minimum::Minimum() {};
void Minimum::run(InData& data_in, OutData& data_out)
{	
		for (unsigned int i = 0; i < data_in.data.size(); ++i) {
			double min = data_in.data[i][0];
			for (unsigned int j = 0; j < data_in.data[i].size(); ++j)
			{
				if (data_in.data[i][j] < min)
					min = data_in.data[i][j];
			}
			data_out.min.push_back(min);
		}
	
};

Maximum::Maximum() {};
void Maximum::run(InData& data_in, OutData& data_out)
{

	for (unsigned int i = 0; i < data_in.data.size(); ++i) 
	{
		double max = data_in.data[i][0];
		for (unsigned int j = 0; j < data_in.data[i].size(); ++j)
		{
			if (data_in.data[i][j] > max)
				max = data_in.data[i][j];
		}
		data_out.max.push_back(max);
	}
};
	
Median::Median() {};
void Median::run(InData& data_in, OutData& data_out)
{

	InData data_tmp(data_in);

	double avg = 0;
	for (unsigned int i = 0; i < data_tmp.data.size(); ++i) 
	{
		std::sort(data_tmp.data[i].begin(), data_tmp.data[i].end());
		int rozm = data_tmp.data[i].size();
		if (rozm % 2 != 0)
			avg = data_tmp.data[i][(rozm / 2) + 0.5];
		else
			avg = (data_tmp.data[i][(rozm / 2) - 1] + data_tmp.data[i][(rozm / 2)]) / 2;
		data_out.med.push_back(avg);
	}
};
	

Average::Average() {};
void Average::run(InData& data_in, OutData& data_out)
{
		for (unsigned int i = 0; i < data_in.data.size(); ++i) 
		{
			double avg = 0;
			int count = 0;
			for (unsigned int j = 0; j < data_in.data[i].size(); ++j)
			{
				avg += data_in.data[i][j];
				count += 1;
			}
			avg = avg / count;
			data_out.avg.push_back(avg);
		}
};


