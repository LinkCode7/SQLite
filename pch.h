#ifndef MY_PCH_H
#define MY_PCH_H


#define UNKNOWN_INT 0
#define UNKNOWN_DOUBLE 999999999

#ifndef _T
#define _T
#endif

#define COMPONENT_TABLE_NAME "component"

#define TEST_CUR_DB_PATH "..//..//..//test.db3"
#define TEST_LOG_PATH "..//..//..//run_time.log"

#include <vector>
#include <iostream>

namespace Sindy
{
	// 比较两个浮点数：0表示相同 1表示前面大 -1表示后面大
	int compareDouble(double src1, double src2, double tol = 0.000001);
}

#endif // !MY_PCH_H
