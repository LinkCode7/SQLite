#include <iostream>
#include "pch.h"

#include "./sql/case_when.h"
#include "./sql/group_by.h"
#include "./sql/petal.h"
#include "./effective/CFunctions.h"
#include "./effective/HighPerformance.h"

#include "./sample/ExpresstionTest.h"

#include <string>
#include <format>
#include "./common/const_define.h"
int main()
{
	std::string strSql;
	{
		std::string strResultTable = "statistics_sum_result"; // 长度限制?：statistics1_sum_result/statistics_sum_result,statistics1_case_when_result

		std::string view = "create table {} as select sum({}) result, CASE {} WHEN '中国' THEN '亚洲' WHEN '印度' THEN '亚洲' WHEN '日本' THEN '亚洲' WHEN '美国' THEN '北美洲' WHEN '加拿大' THEN '北美洲' WHEN '墨西哥' THEN '北美洲' WHEN '英国' THEN '欧洲' WHEN '法国' THEN '欧洲' WHEN '德国' THEN '欧洲' ELSE '其它' END as state from {} GROUP BY {}";

		strSql = std::format(view, strResultTable, Sindy::statistics::population, Sindy::statistics::country, Sindy::statistics::table_name, Sindy::statistics::country);
	}

	test_case_when();
	test_group_by();
	test_petal();

	SQLiteCFunction::entry();
	TestSQLitePerformance::entry();

	TestMathExpresstion::entry();
	return 0;
}

int Sindy::compareDouble(double src1, double src2, double tol)
{
	double dblSub = src1 - src2;
	if (std::abs(dblSub) <= tol)
		return 0;
	else if (dblSub > tol)
		return 1;
	else
		return -1;
}