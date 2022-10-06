#include "../pch.h"
#include "HighPerformance.h"

#include "..\common\SindySQLite.h"
#include "../common/SindyRunTime.h"
#include <format>

#define PERFORMANCE_TABLE_NAME _T("PerformanceSQL")

#define TEST_HIGH_PERFORMANCE
#define PERFORMANCE_ROW_COUNT 10*10000

namespace TestSQLitePerformance
{
	void entry()
	{
		std::string strDbPath = TEST_CUR_DB_PATH;
		//testPragma(strDbPath);

		testInsert(strDbPath);

		testUpdate(strDbPath);
		testSelect(strDbPath);

		// testExistsData(strDbPath);
		// bindInsertSQLWithNumeric(strDbPath);

		selectCount(strDbPath);
	}

	void testInsert(const std::string& strDbPath)
	{
		{
			Sindy::SQLite db(strDbPath);
			db.dropTable(PERFORMANCE_TABLE_NAME, strDbPath);
		}

		Sindy::RunTime time;

		std::string strLog;

#ifdef TEST_HIGH_PERFORMANCE
		Sindy::SQLite database(strDbPath);

		database.beginTransaction();

		std::string strCreateSql = std::format("CREATE TABLE {}(\
								   com_id INT PRIMARY KEY NOT NULL,\
								   com_type INT NOT NULL,\
								   floor_id INT OT NULL,\
								   name TEXT NOT NULL,\
								   show_id INT NOT NULL,\
								   mode INT,\
								   note TEXT)", PERFORMANCE_TABLE_NAME);

		database.execute(strCreateSql);

		std::string strInsertSql = std::format("insert into {}(com_id, com_type, floor_id, name, show_id, mode, note) \
									values(:com_id, :com_type, :floor_id, :name, :show_id, :mode, :note)", PERFORMANCE_TABLE_NAME);

		database.prepare(strInsertSql);

		for (int i = 1; i <= PERFORMANCE_ROW_COUNT; ++i)
		{
			database.bindInt(_T(":com_id"), i);
			database.bindInt(_T(":com_type"), i * 100);
			database.bindInt(_T(":floor_id"), 1);

			database.bindText(_T(":name"), _T("Link"));

			database.bindInt(_T(":show_id"), 0);
			database.bindInt(_T(":mode"), 0);

			database.bindText(_T(":note"), _T("test note"));


			database.step();
			database.resetSyntax();
		}

		database.commit();
		strLog = std::format("预编译(prepared statement)：插入{}条记录", PERFORMANCE_ROW_COUNT);
#else
		Sindy::SQLite database(strDbPath);

		database.beginTransaction();

		std::string strCreateSql = std::format("CREATE TABLE {}(\
								   com_id INT PRIMARY KEY NOT NULL,\
								   com_type INT NOT NULL,\
								   floor_id INT OT NULL,\
								   name TEXT NOT NULL,\
								   show_id INT NOT NULL,\
								   mode INT,\
								   note TEXT)", PERFORMANCE_TABLE_NAME);
		database.execute(strCreateSql);

		for (int i = 1; i <= PERFORMANCE_ROW_COUNT; ++i)
		{
			std::string strInsertSql = std::format("insert into {}(com_id, com_type, floor_id, name, show_id, mode, note) \
									   values({}, {}, {}, '{}', {}, {}, '{}')", PERFORMANCE_TABLE_NAME,
				i, i * 100, 1, _T("Link"), 0, 0, _T("test note"));
			database.execute(strInsertSql);
		}

		database.commit();
		strLog = std::format("insert：插入{}条记录", PERFORMANCE_ROW_COUNT);
#endif // TEST_HIGH_PERFORMANCE

		time.write(TEST_LOG_PATH, strLog);
	}

	void bindInsertSQLWithNumeric(const std::string& strDbPath)
	{
		Sindy::RunTime time;

		std::string strMsg;
		std::string strLog;

		Sindy::SQLite database(strDbPath);

		database.beginTransaction();

		std::string strInsertSql = std::format("insert into {}(com_id, com_type, floor_id, name, show_id, mode, note) values(?,?,?,?,?,?,?)", PERFORMANCE_TABLE_NAME);

		database.prepare(strInsertSql);
		strMsg = database.errorMessage();

		for (int i = PERFORMANCE_ROW_COUNT + 1; i <= PERFORMANCE_ROW_COUNT + 10; ++i)
		{
			database.bindInt(1, i); // 从1开始
			database.bindInt(2, i * 100);
			database.bindInt(3, 1);

			database.bindText(4, "Link");

			database.bindInt(5, 0);
			database.bindInt(6, 0);

			database.bindText(7, "test note");

			database.step();
			database.resetSyntax();
		}

		database.commit();
		strLog = std::format("预编译(prepared statement)：插入{}条记录", PERFORMANCE_ROW_COUNT);

		time.write(TEST_LOG_PATH, strLog);
	}

	void testUpdate(const std::string& strDbPath)
	{
		Sindy::RunTime time;

		std::string strMsg;
		std::string strLog;

#ifdef TEST_HIGH_PERFORMANCE
		Sindy::SQLite database(strDbPath);

		database.beginTransaction();

		std::string strUpdateSql = std::format("update {} set show_id=:0 where com_id=:1", PERFORMANCE_TABLE_NAME);

		database.prepare(strUpdateSql);
		strMsg = database.errorMessage();

		for (int i = 1; i <= PERFORMANCE_ROW_COUNT; ++i)
		{
			database.bindInt(_T(":0"), 0);
			database.bindInt(_T(":1"), i);

			strMsg = database.errorMessage();
			database.step();
			strMsg = database.errorMessage();
			database.resetSyntax();
		}

		database.commit();
		strLog = std::format("预编译(prepared statement)：更新{}条记录", PERFORMANCE_ROW_COUNT);
#else
		Sindy::SQLite database(strDbPath);

		database.beginTransaction();

		for (int i = 1; i <= PERFORMANCE_ROW_COUNT; ++i)
		{
			std::string strUpdateSql = std::format("update {} set show_id={} where com_id={}", PERFORMANCE_TABLE_NAME, 777, i);

			database.execute(strUpdateSql);
		}

		database.commit();
		strLog = std::format("update：更新{}条记录", PERFORMANCE_ROW_COUNT);
#endif // TEST_HIGH_PERFORMANCE

		time.write(TEST_LOG_PATH, strLog);
	}

	void testSelect(const std::string& strDbPath)
	{
		Sindy::RunTime time;

		std::string strMsg;
		std::string strLog;

#ifdef TEST_HIGH_PERFORMANCE
		Sindy::SQLite database(strDbPath);

		database.beginTransaction();

		std::string strSelectSql = std::format("select * from {} where com_id=:com_id", PERFORMANCE_TABLE_NAME);

		database.prepare(strSelectSql);

		for (int i = 1; i <= PERFORMANCE_ROW_COUNT; ++i)
		{
			database.bindInt(_T(":com_id"), i);

			if (database.step() == SQLITE_ROW)
			{
				int iComType = -1;
				database.getValueInt(_T("com_type"), iComType);
			}

			database.resetSyntax();
		}

		strLog = std::format(_T("预编译(prepared statement)：select{}次"), PERFORMANCE_ROW_COUNT);
#else
		Sindy::SQLite database(strDbPath);

		database.beginTransaction();

		for (int i = 1; i <= PERFORMANCE_ROW_COUNT; ++i)
		{
			std::string strSelectSql = std::format("select * from {} where com_id={}", PERFORMANCE_TABLE_NAME, i);

			database.prepare(strSelectSql);
			if (database.step() == SQLITE_ROW)
			{
				int iComType = -1;
				database.getValueInt(_T("com_type"), iComType);
			}
		}

		strLog = std::format("select：select{}次", PERFORMANCE_ROW_COUNT);
#endif // TEST_HIGH_PERFORMANCE

		time.write(TEST_LOG_PATH, strLog);
	}

	void testExistsData(const std::string& strDbPath)
	{
		Sindy::RunTime time;

		std::string strMsg;
		std::string strLog;

		std::string strSql;
		Sindy::SQLite database(strDbPath);
		database.beginTransaction();

		int iComType = 50000000 / 2;

		int iKind = 1;
		for (int i = 0; i < 1; ++i)
		{
			switch (iKind)
			{
			case 1:
			{
				strSql = std::format("select com_type from {} where com_type={}", PERFORMANCE_TABLE_NAME, iComType);
				database.prepare(strSql);

				if (database.step() == SQLITE_ROW)
					strLog = std::format("TestExists(true)：select com_type from ... where com_type={}", iComType);
				else
					strLog = std::format("TestExists(false)：select com_type from ... where com_type={}", iComType);

				break;
			}
			case 2:
			{
				strSql = std::format("select com_type from {} where com_type={} limit 1", PERFORMANCE_TABLE_NAME, iComType);
				database.prepare(strSql);

				if (database.step() == SQLITE_ROW)
					strLog = std::format("TestExists(true)：select com_type from ... where com_type={} limit 1", iComType);
				else
					strLog = std::format("TestExists(false)：select com_type from ... where com_type={} limit 1", iComType);

				break;
			}
			case 3:
			{
				strSql = std::format("select exists (select com_type from {} where com_type={}) as result", PERFORMANCE_TABLE_NAME, iComType);
				database.prepare(strSql);

				if (database.step() == SQLITE_ROW)
				{
					int iRet = database.getValueInt(0);
					strLog = std::format("TestExists(true)：select exists (select com_type from ... where com_type={}) as result", iComType);
				}
				else
				{
					std::cout << ">>> TestExists(Error)" << std::endl;
					return;
				}
				break;
			}
			default:
			{
				std::cout << ">>> TestExists(Error)" << std::endl;
				return;
			}
			}
		}

		time.write(TEST_LOG_PATH, strLog);
	}

	// 1. 2.dataset update 3.
	void testPragma(const std::string& strDbPath)
	{
		Sindy::SQLite database(strDbPath);
		// 关闭同步机制
		database.execute("PRAGMA synchronous=OFF");
		database.execute("PRAGMA count_changes=OFF");
		database.execute("PRAGMA journal_mode=MEMORY");
		database.execute("PRAGMA temp_store=MEMORY");
	}

	void testLargeField(const std::string& strDbPath, const std::string& strTableName, bool isLarge)
	{
		Sindy::SQLite database(strDbPath);

		if (database.isTableExist(strTableName, strDbPath))
			return;

		std::string strCreateSql;
		if (isLarge)
		{
			strCreateSql = "CREATE TABLE test_table(handle TEXT,bulge FLOAT,from_x FLOAT,from_y FLOAT,to_x FLOAT,to_y FLOAT,\
							  min_x FLOAT,min_y FLOAT,max_x FLOAT,max_y FLOAT, primary key (handle))";
		}
		else
		{
			strCreateSql = "CREATE TABLE test_table(handle TEXT,bulge FLOAT,from_x FLOAT,from_y FLOAT,to_x FLOAT,to_y FLOAT,\
							  min_x FLOAT,min_y FLOAT,max_x FLOAT,max_y FLOAT, primary key (handle))";
		}

		database.execute(strCreateSql);
	}

	// COUNT：填充1000000个元素 总计：266ms
	// SELECT * ：填充1000000个元素 总计：1453ms
	void selectCount(const std::string& strDbPath)
	{
		Sindy::RunTime time;

		std::string strLog;
		std::vector<int> array;

#ifdef TEST_HIGH_PERFORMANCE
		Sindy::SQLite database(strDbPath);
		database.prepare(std::format("SELECT COUNT(*) AS result FROM {}", COMPONENT_TABLE_NAME));

		auto msg = database.errorMessage();
		int iCount = -1;
		while (database.step() == SQLITE_ROW)
		{
			database.getValueInt(_T("result"), iCount);
		}

		for (int i = 0; i < iCount; ++i)
		{
			array.push_back(0);
		}

		strLog = std::format(_T("COUNT：填充{}个元素"), array.size());
#else
		Sindy::SQLite database(strDbPath);
		database.prepare(std::format("SELECT * FROM {}", COMPONENT_TABLE_NAME));

		while (database.step() == SQLITE_ROW)
		{
			array.push_back(0);
		}

		strLog = std::format("SELECT * ：填充{}个元素", array.size());
#endif // TEST_HIGH_PERFORMANCE


		time.write(TEST_LOG_PATH, strLog);
	}

} // namespace TestSQLitePerformance