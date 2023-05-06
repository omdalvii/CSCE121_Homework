# include "TemperatureData.h"
#include <iostream>
using std::string;

#define DEBUG(X) if(false){std::cout << "[DEBUG] " << X << std::endl;}

TemperatureData::TemperatureData() {}

TemperatureData::TemperatureData(string id, int year, int month, double temperature):
id(id),
year(year),
month(month),
temperature(temperature) {}

TemperatureData::~TemperatureData() {}

bool TemperatureData::operator<(const TemperatureData& b) {
	if (this->id == b.id) {
		DEBUG("ids same")
		if (this->year == b.year) {
			DEBUG("years same")
			if (this->month == b.month) {
				DEBUG("month same")
				DEBUG("sorted based on temp")
				return (this->temperature < b.temperature);
			}
			else {
				DEBUG("sorted based on month")
				return (this->month < b.month);
			}
		}
		else {
			DEBUG("sorted based on year")
			return (this->year < b.year);
		}
	}
	else {
		DEBUG("sorted based on id")
		return (this->id < b.id);
	}
}

