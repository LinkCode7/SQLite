#include "../pch.h"
#include "group_by.h"
#include "../common/const_define.h"
#include <format>

using namespace Sindy;

void make_group_table();
void _test_group_by();
void make_figure_table();
void test_figure();

void test_group_by()
{
	make_group_table();
	_test_group_by();

	make_figure_table();
	test_figure();
}

void _test_group_by()
{
	auto strPath = TEST_CUR_DB_PATH;
	SQLite database(strPath);
	database.beginTransaction();

	std::string strResultTable = _T("group_by1_result");
	database.dropTable(strResultTable);

	//AddItem(Sindy::group_by::id, Sindy::kIntegerField);
	//AddItem(Sindy::group_by::province, Sindy::kTextField);
	//AddItem(Sindy::group_by::city, Sindy::kTextField);
	//AddItem(Sindy::group_by::county, Sindy::kTextField);
	//AddItem(Sindy::group_by::town, Sindy::kTextField);
	//AddItem(Sindy::group_by::village, Sindy::kTextField);

	std::string strSql = std::format(_T("create table {} as select * from {} group by {},{},{},{}"), 
		strResultTable, 
		Sindy::group_by::table_name, 
		Sindy::group_by::province, 
		Sindy::group_by::city, 
		Sindy::group_by::county, 
		Sindy::group_by::town);

	database.execute(strSql);
	database.commit();
}

void make_group_table()
{
	auto strPath = TEST_CUR_DB_PATH;
	SQLite sqlite(strPath);
	sqlite.beginTransaction();

	sqlite.dropTable(Sindy::group_by::table_name);

	GroupByTable table;
	std::string strSql = table.GetCreateSql();

	if (sqlite.execute(strSql) != SQLITE_DONE)
		return;

	strSql = table.GetInsertSql(Sindy::group_by::table_name);
	sqlite.prepare(strSql);

	int id = 0;
	table.fill(sqlite, id++, _T("浙江"), _T("杭州市"), _T("桐庐县"), _T("小镇2"), _T("村1"));
	table.fill(sqlite, id++, _T("浙江"), _T("湖州市"), _T("安吉县"), _T("小镇1"), _T("村1"));
	table.fill(sqlite, id++, _T("浙江"), _T("宁波市"), _T("象山县"), _T("小镇1"), _T("村1"));
	table.fill(sqlite, id++, _T("浙江"), _T("宁波市"), _T("宁海县"), _T("小镇2"), _T("村1"));
	table.fill(sqlite, id++, _T("浙江"), _T("温州市"), _T("永嘉县"), _T("小镇1"), _T("村1"));
	table.fill(sqlite, id++, _T("浙江"), _T("丽水市"), _T("松阳县"), _T("小镇1"), _T("村1"));
	table.fill(sqlite, id++, _T("浙江"), _T("丽水市"), _T("松阳县"), _T("小镇2"), _T("村1"));
	table.fill(sqlite, id++, _T("河北"), _T("雄安"), _T("县1"), _T("小镇1"), _T("村1"));
	table.fill(sqlite, id++, _T("河北"), _T("雄安"), _T("县1"), _T("小镇1"), _T("村2"));
	table.fill(sqlite, id++, _T("上海"), _T("徐汇"), _T("3-a"), _T("4-a"), _T("5-a"));
	table.fill(sqlite, id++, _T("上海"), _T("黄浦"), _T("3-a"), _T("4-a"), _T("5-a"));
	table.fill(sqlite, id++, _T("上海"), _T("黄浦"), _T("3-b"), _T("4-a"), _T("5-b"));
	table.fill(sqlite, id++, _T("北京"), _T("东城区"), _T("3-b"), _T("4-a"), _T("5-b"));
	table.fill(sqlite, id++, _T("北京"), _T("西城区"), _T("3-b"), _T("4-a"), _T("5-b"));

	sqlite.commit();
}

void GroupByTable::fill(SQLite& db, int id, const std::string& strProvince, const std::string& strCity, const std::string& strCounty, const std::string& strTown, const std::string& strVillage)
{
	this->SetValue(Sindy::group_by::id, id);
	this->SetValue(Sindy::group_by::province, strProvince);
	this->SetValue(Sindy::group_by::city, strCity);
	this->SetValue(Sindy::group_by::county, strCounty);
	this->SetValue(Sindy::group_by::town, strTown);
	this->SetValue(Sindy::group_by::village, strVillage);
	this->InsertRecord(db);
}

GroupByTable::GroupByTable()
{
	AddItem(Sindy::group_by::id, Sindy::kIntegerField);
	AddItem(Sindy::group_by::province, Sindy::kTextField);
	AddItem(Sindy::group_by::city, Sindy::kTextField);
	AddItem(Sindy::group_by::county, Sindy::kTextField);
	AddItem(Sindy::group_by::town, Sindy::kTextField);
	AddItem(Sindy::group_by::village, Sindy::kTextField);
}
std::string GroupByTable::GetCreateSql()
{
	return _CreateSql(Sindy::group_by::table_name, false, false);
}

void test_figure()
{
	auto strPath = TEST_CUR_DB_PATH;
	SQLite database(strPath);
	database.beginTransaction();

	std::string strResultTable = _T("figure_result");
	database.dropTable(strResultTable);

	std::string strSql = std::format(_T("create table {} as select * from {} group by {},{},{},{}"),
		strResultTable,
		Sindy::figure::table_name,
		Sindy::figure::field1,
		Sindy::figure::field2,
		Sindy::figure::field3,
		Sindy::figure::field4);

	strSql = std::format(_T("create table {} as select {},sum(field1) field1,sum(field2) field2,sum(field3) field3,sum(field4) field4,sum(field5) field5 from {} group by {},{},{},{}"),
		strResultTable,
		Sindy::figure::letter,
		Sindy::figure::table_name,
		Sindy::figure::field1,
		Sindy::figure::field2,
		Sindy::figure::field3,
		Sindy::figure::field4);

	database.execute(strSql);
	auto strMsg = database.errorMessage();
	database.commit();
}

void make_figure_table()
{
	auto strPath = TEST_CUR_DB_PATH;
	SQLite sqlite(strPath);
	sqlite.beginTransaction();

	sqlite.dropTable(Sindy::figure::table_name);

	FigureTable table;
	std::string strSql = table.GetCreateSql();

	if (sqlite.execute(strSql) != SQLITE_DONE)
		return;

	strSql = table.GetInsertSql(Sindy::figure::table_name);
	sqlite.prepare(strSql);

	table.fill(sqlite, "a", 1, 2, 3, 4, 5);
	table.fill(sqlite, "b", 11, 2, 3, 4, 5);
	table.fill(sqlite, "c", 11, 22, 3, 4, 5);
	table.fill(sqlite, "d", 11, 22, 333, 4, 5);
	table.fill(sqlite, "e", 1, 22, 33, 4, 5);
	table.fill(sqlite, "f", 1, 22, 33, 444, 5);
	table.fill(sqlite, "g", 1, 22, 33, 444, 55);
	table.fill(sqlite, "h", 11, 22, 33, 44, 55);
	table.fill(sqlite, "i", 11, 22, 33, 44, 5);

	sqlite.commit();
}

void FigureTable::fill(SQLite& db, const std::string& letter, int val1, int val2, int val3, int val4, int val5)
{
	this->SetValue(Sindy::figure::letter, letter);
	this->SetValue(Sindy::figure::field1, val1);
	this->SetValue(Sindy::figure::field2, val2);
	this->SetValue(Sindy::figure::field3, val3);
	this->SetValue(Sindy::figure::field4, val4);
	this->SetValue(Sindy::figure::field5, val5);
	this->InsertRecord(db);
}

FigureTable::FigureTable()
{
//#define _FIELD_TYPE_ Sindy::kIntegerField
#define _FIELD_TYPE_ Sindy::kTextField
	// 文本字段类型也能执行sum操作（group by时）
	AddItem(Sindy::figure::letter, Sindy::kTextField);
	AddItem(Sindy::figure::field1, _FIELD_TYPE_);
	AddItem(Sindy::figure::field2, _FIELD_TYPE_);
	AddItem(Sindy::figure::field3, _FIELD_TYPE_);
	AddItem(Sindy::figure::field4, _FIELD_TYPE_);
	AddItem(Sindy::figure::field5, _FIELD_TYPE_);
#undef _FIELD_TYPE_
}
std::string FigureTable::GetCreateSql()
{
	return _CreateSql(Sindy::figure::table_name, false, false);
}