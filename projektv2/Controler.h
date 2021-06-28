#ifndef CONTROLER_H
#define CONTROLER_H
#include "Analyzer.h"
#include "Loader.h"
#include "Saver.h"
#include "Data.h"
#include <vector>
#include <string>

class Controler {
public:
	Controler();
	InData read_file(std::string file_name);
	OutData analyze(InData data_in);
	void advanced();
	void save_file(OutData data_out);
	void show_error(std::vector<std::string> &newError);
};

#endif
