#include "Loader.h"
#include <vector>
#include <string>

CSV::CSV() {}; // konstruktor
// metoda od odczytu pliku CSV
void CSV::run(const std::string& file_name, InData & result)
{
	ErrorLog error;
	
	std::fstream in;
	in.open(file_name, std::ios::in); // otwarcie pliku
	

	if (in.is_open())
	{
		std::string line;

		while (getline(in, line)) // petla przeszukujaca plik i zapisujaca to klasy InData
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
		in.close(); // zamknienie pliku
	}
	else
	{
		std::cerr << "plik nie zostal otworzony!"; // error
		error.newError.push_back("Err 0: Nie mozna otworzyc pliku");
	}
}
