#pragma once
#include "../common/table_data.h"
#include "../common/SindySQLite.h"

void test_petal();

class AddSumRecordTable : public Sindy::TableData
{
public:
	AddSumRecordTable();
	std::string GetCreateSql();

	void fill(Sindy::SQLite& db, int id, const std::string& strName, int type, double width);
};
