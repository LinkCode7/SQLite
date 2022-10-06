#ifndef CONST_DEFINE_H
#define CONST_DEFINE_H

#define SINDY_API

#ifndef _TCHAR
#define _TCHAR char
#endif

namespace Sindy
{
	namespace common
	{
		SINDY_API extern const _TCHAR id[];
		SINDY_API extern const _TCHAR dwg[]; // 图纸ID
		SINDY_API extern const _TCHAR zy[]; // 专业
		SINDY_API extern const _TCHAR item[];
		SINDY_API extern const _TCHAR com_id[];
		SINDY_API extern const _TCHAR com_type[];
		SINDY_API extern const _TCHAR unit[];
		SINDY_API extern const _TCHAR handle[];
		SINDY_API extern const _TCHAR row_type[];
		SINDY_API extern const _TCHAR is_private[];

		SINDY_API extern const _TCHAR main[];
		SINDY_API extern const _TCHAR name[]; // 逻辑名称
		SINDY_API extern const _TCHAR alias_name[]; // 别名
		SINDY_API extern const _TCHAR code_name[]; // 代号，编号
		SINDY_API extern const _TCHAR caption[]; // 显示名称
		SINDY_API extern const _TCHAR type[];
		SINDY_API extern const _TCHAR width[];
		SINDY_API extern const _TCHAR align[];
		SINDY_API extern const _TCHAR level[]; // index/序号
		SINDY_API extern const _TCHAR cj[]; // 层级

		SINDY_API extern const _TCHAR layer[];
		SINDY_API extern const _TCHAR color[];

		SINDY_API extern const _TCHAR schema[];
		SINDY_API extern const _TCHAR key[];
		SINDY_API extern const _TCHAR value[];
		SINDY_API extern const _TCHAR note[];
		SINDY_API extern const _TCHAR params[];
		SINDY_API extern const _TCHAR param_id[];
		SINDY_API extern const _TCHAR property[];
		SINDY_API extern const _TCHAR state[];
		SINDY_API extern const _TCHAR section[];
		SINDY_API extern const _TCHAR select[];
		SINDY_API extern const _TCHAR count[];

		SINDY_API extern const _TCHAR show2d[];
		SINDY_API extern const _TCHAR show3d[];

		SINDY_API extern const _TCHAR subtotal[]; // 小计
		SINDY_API extern const _TCHAR total[]; // 合计
		SINDY_API extern const _TCHAR formula[]; // 计算公式
		SINDY_API extern const _TCHAR formula_des[]; //计算公式-描述
		SINDY_API extern const _TCHAR calc_item[]; // 计算部位
		SINDY_API extern const _TCHAR adjust[]; // 调整值

		SINDY_API extern const _TCHAR regex[];
		SINDY_API extern const _TCHAR hide[];
		SINDY_API extern const _TCHAR list_data[];
		SINDY_API extern const _TCHAR mode[];
		SINDY_API extern const _TCHAR input_mode[];
		SINDY_API extern const _TCHAR is_default[];

		SINDY_API extern const _TCHAR data[];
	} // namespace common



	namespace group_by
	{
		SINDY_API extern const _TCHAR table_name[];
		using common::id;
		SINDY_API extern const _TCHAR province[]; // 省
		SINDY_API extern const _TCHAR city[]; // 市
		SINDY_API extern const _TCHAR county[]; // 县
		SINDY_API extern const _TCHAR town[]; // 镇
		SINDY_API extern const _TCHAR village[]; // 村

	} // namespace group_by


	namespace figure
	{
		SINDY_API extern const _TCHAR table_name[];
		SINDY_API extern const _TCHAR letter[];
		SINDY_API extern const _TCHAR field1[];
		SINDY_API extern const _TCHAR field2[];
		SINDY_API extern const _TCHAR field3[];
		SINDY_API extern const _TCHAR field4[];
		SINDY_API extern const _TCHAR field5[];
	} // namespace figure

	namespace add_sum_record
	{
		SINDY_API extern const _TCHAR table_name[];
		using Sindy::common::id;
		using Sindy::common::name;
		using Sindy::common::type;
		using Sindy::common::width;
	} // namespace add_sum_record

	namespace statistics
	{
		SINDY_API extern const _TCHAR table_name[];

		SINDY_API extern const _TCHAR country[]; // 国家
		SINDY_API extern const _TCHAR population[]; // 人口
	} // namespace statistics

} // namespace Sindy

#endif // !CONST_DEFINE_H