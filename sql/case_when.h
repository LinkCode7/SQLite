#pragma once
#include "../common/table_data.h"



void test_case_when();




class StatisticsTable : public Sindy::TableData
{
public:
	StatisticsTable();
	std::string GetCreateSql();

	void fill(Sindy::SQLite& sqlite, const std::string& strCountry, int population);
};