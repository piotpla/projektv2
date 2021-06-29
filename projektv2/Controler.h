#ifndef CONTROLER_H
#define CONTROLER_H
#include "Analyzer.h"
#include "Loader.h"
#include "Saver.h"
#include "Data.h"
#include <vector>
#include <string>

//klasa kontrolera
class Controler {
public:
	Controler(); // konstruktor
	InData read_file(std::string file_name); // odczyt pliku
	OutData analyze(InData data_in); // analiza danych
	void advanced(); // zaawansowane
	void save_file(OutData data_out, std::string file_name); // zapis pliku
	void show_error(std::vector<std::string> &newError); // wypis bledow
};

#endif
