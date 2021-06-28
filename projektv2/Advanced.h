#ifndef ADVANCED_H
#define ADVANDED_H
#include "Analyzer.h"

class WKP : public Analyzer {
	WKP();
	void run(InData & data_in, OutData & data_out) override;
};

#endif
