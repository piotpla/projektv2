#include "Loader.h"
#include <vector>
#include <string>

CSV::CSV() {};
void CSV::run(const std::string& file_name, InData & result)
{
	ErrorLog error;
	
	std::fstream in;
	in.open(file_name, std::ios::in);
	

	if (in.is_open())
	{
		std::string line;

		while (getline(in, line))
		{
			std::string field;
			std::vector<double> v;
			std::stringstream ss(line);


			while (getline(ss, field, ','))  // if czy puste
			{
				if (!field.empty())
				{
					v.push_back(std::stod(field));
				}
				else std::cerr << "pusta linia .\n";
			}

			result.data.push_back(v);
		}
		in.close();
	}
	else
	{
		std::cerr << "plik nie zostal otworzony!";
		error.newError.push_back("Err 0: Nie mozna otworzyc pliku");
	}
}
