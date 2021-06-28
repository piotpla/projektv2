#include "Controler.h"

Controler::Controler() {};
InData Controler::read_file(std::string file_name) 
{
	std::string enl = file_name.substr((file_name.size() - 3), 3);
	InData data;

	if (enl == "csv")
	{
		CSV csv;
		csv.run(file_name, data);
		return data;
	}
};

OutData Controler::analyze(InData data_in) {
	OutData dane_out;

	Minimum min;
	min.run(data_in, dane_out);

	Maximum max;
	max.run(data_in, dane_out);

	Median med;
	med.run(data_in, dane_out);

	Average avg;
	avg.run(data_in, dane_out);

	return dane_out;
};

void Controler::advanced() {

};

void Controler::save_file(OutData data_out, std::string file_name) {
	CSVsaver result;
	result.run(data_out, file_name);
};

void Controler::show_error(std::vector<std::string> &newError) {
	//najpierw wyczysc wszystko (to sie bedzie za kazdym razem dzialo dla ulatwienia zycia naszego)
	if(newError.empty())
	{
		//tu ma wypisaæ ¿e brak b³êdów, chyba, ¿e w GUI siê bêdzie jakoœ inaczej da³o to zrobiæ
	}
	else
	{
		for(short i=0; i< newError.size();i++)
		{
			//wypisuj po linijce errory
		}
	}
};