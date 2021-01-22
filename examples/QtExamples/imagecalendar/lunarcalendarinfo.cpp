#pragma execution_character_set("utf-8")

#include "lunarcalendarinfo.h"
#include "qdebug.h"

LunarCalendarInfo *LunarCalendarInfo::self = 0;
LunarCalendarInfo::LunarCalendarInfo(QObject *parent) : QObject(parent)
{
	//每年春节对应的公历日期
	springFestival << 130 << 217 << 206;                                                    // 1968 1969 1970
	springFestival << 127 << 215 << 203 << 123 << 211 << 131 << 218 << 207 << 128 << 216;   // 1971--1980
	springFestival << 205 << 125 << 213 << 202 << 220 << 209 << 219 << 217 << 206 << 127;   // 1981---1990
	springFestival << 215 << 204 << 123 << 210 << 131 << 219 << 207 << 128 << 216 << 205;   // 1991--2000
	springFestival << 124 << 212 << 201 << 122 << 209 << 129 << 218 << 207 << 126 << 214;   // 2001--2010
	springFestival << 203 << 123 << 210 << 131 << 219 << 208 << 128 << 216 << 205 << 125;   // 2011--2020
	springFestival << 212 << 201 << 122 << 210 << 129 << 217 << 206 << 126 << 213 << 203;   // 2021--2030
	springFestival << 123 << 211 << 131 << 219 << 208 << 128 << 215 << 204 << 124 << 212;   // 2031--2040

	//16--18位表示闰几月 0--12位表示农历每月的数据 高位表示1月 低位表示12月(农历闰月就会多一个月)
	nLunarData << 461653 << 1386 << 2413;                                                               // 1968 1969 1970
	nLunarData << 330077 << 1197 << 2637 << 268877 << 3365 << 531109 << 2900 << 2922 << 398042 << 2395; // 1971--1980
	nLunarData << 1179 << 267415 << 2635 << 661067 << 1701 << 1748 << 398772 << 2742 << 2391 << 330031; // 1981---1990
	nLunarData << 1175 << 1611 << 200010 << 3749 << 527717 << 1452 << 2742 << 332397 << 2350 << 3222;   // 1991--2000
	nLunarData << 268949 << 3402 << 3493 << 133973 << 1386 << 464219 << 605 << 2349 << 334123 << 2709;  // 2001--2010
	nLunarData << 2890 << 267946 << 2773 << 592565 << 1210 << 2651 << 395863 << 1323 << 2707 << 265877; // 2011--2020
	nLunarData << 1706 << 2773 << 133557 << 1206 << 398510 << 2638 << 3366 << 335142 << 3411 << 1450;   // 2021 -- 2030
	nLunarData << 200042 << 2413 << 723293 << 1197 << 2637 << 399947 << 3365 << 3410 << 334676 << 2906; // 2031 -- 2040

	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x69 << 0x78 << 0x87; // 1970
	chineseTwentyFourData << 0x96 << 0xB4 << 0x96 << 0xA6 << 0x97 << 0x97 << 0x78 << 0x79 << 0x79 << 0x69 << 0x78 << 0x77; // 1971
	chineseTwentyFourData << 0x96 << 0xA4 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 1972
	chineseTwentyFourData << 0xA5 << 0xB5 << 0x96 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x78 << 0x78 << 0x78 << 0x87 << 0x87; // 1973
	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x69 << 0x78 << 0x87; // 1974
	chineseTwentyFourData << 0x96 << 0xB4 << 0x96 << 0xA6 << 0x97 << 0x97 << 0x78 << 0x79 << 0x78 << 0x69 << 0x78 << 0x77; // 1975
	chineseTwentyFourData << 0x96 << 0xA4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x88 << 0x89 << 0x88 << 0x78 << 0x87 << 0x87; // 1976
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 1977
	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x79 << 0x78 << 0x87; // 1978
	chineseTwentyFourData << 0x96 << 0xB4 << 0x96 << 0xA6 << 0x96 << 0x97 << 0x78 << 0x79 << 0x78 << 0x69 << 0x78 << 0x77; // 1979
	chineseTwentyFourData << 0x96 << 0xA4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 1980
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x77 << 0x87; // 1981
	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x79 << 0x77 << 0x87; // 1982
	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x78 << 0x79 << 0x78 << 0x69 << 0x78 << 0x77; // 1983
	chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 1984
	chineseTwentyFourData << 0xA5 << 0xB4 << 0xA6 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 1985
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x79 << 0x77 << 0x87; // 1986
	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x79 << 0x78 << 0x69 << 0x78 << 0x87; // 1987
	chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 1988
	chineseTwentyFourData << 0xA5 << 0xB4 << 0xA5 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 1989
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x79 << 0x77 << 0x87; // 1990
	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x86 << 0x97 << 0x88 << 0x78 << 0x78 << 0x69 << 0x78 << 0x87; // 1991
	chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 1992
	chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 1993
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x78 << 0x87 << 0x87; // 1994
	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x76 << 0x78 << 0x69 << 0x78 << 0x87; // 1995
	chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 1996
	chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 1997
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x78 << 0x87 << 0x87; // 1998
	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x69 << 0x78 << 0x87; // 1999
	chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2000
	chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2001
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x78 << 0x87 << 0x87; // 2002
	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x69 << 0x78 << 0x87; // 2003
	chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2004
	chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2005
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 2006
	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x69 << 0x78 << 0x87; // 2007
	chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x87 << 0x78 << 0x87 << 0x86; // 2008
	chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2009
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 2010
	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x79 << 0x78 << 0x87; // 2011
	chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA5 << 0xA6 << 0x87 << 0x88 << 0x87 << 0x78 << 0x87 << 0x86; // 2012
	chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2013
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 2014
	chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x79 << 0x77 << 0x87; // 2015
	chineseTwentyFourData << 0x95 << 0xB4 << 0xA5 << 0xB4 << 0xA5 << 0xA6 << 0x87 << 0x88 << 0x87 << 0x78 << 0x87 << 0x86; // 2016
	chineseTwentyFourData << 0xA5 << 0xC3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2017
	chineseTwentyFourData << 0xA5 << 0xB4 << 0xA6 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 2018
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x79 << 0x77 << 0x87; // 2019
	chineseTwentyFourData << 0x95 << 0xB4 << 0xA5 << 0xB4 << 0xA5 << 0xA6 << 0x97 << 0x87 << 0x87 << 0x78 << 0x87 << 0x86; // 2020
	chineseTwentyFourData << 0xA5 << 0xC3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2021
	chineseTwentyFourData << 0xA5 << 0xB4 << 0xA5 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2022
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x79 << 0x77 << 0x87; // 2023
	chineseTwentyFourData << 0x95 << 0xB4 << 0xA5 << 0xB4 << 0xA5 << 0xA6 << 0x97 << 0x87 << 0x87 << 0x78 << 0x87 << 0x96; // 2024
	chineseTwentyFourData << 0xA5 << 0xC3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2025
	chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2026
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x78 << 0x87 << 0x87; // 2027
	chineseTwentyFourData << 0x95 << 0xB4 << 0xA5 << 0xB4 << 0xA5 << 0xA6 << 0x97 << 0x87 << 0x87 << 0x78 << 0x87 << 0x96; // 2028
	chineseTwentyFourData << 0xA5 << 0xC3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2029
	chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2030
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x78 << 0x87 << 0x87; // 2031
	chineseTwentyFourData << 0x95 << 0xB4 << 0xA5 << 0xB4 << 0xA5 << 0xA6 << 0x97 << 0x87 << 0x87 << 0x78 << 0x87 << 0x96; // 2032
	chineseTwentyFourData << 0xA5 << 0xC3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2033
	chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x78 << 0x88 << 0x78 << 0x87 << 0x87; // 2034
	chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 2035
	chineseTwentyFourData << 0x95 << 0xB4 << 0xA5 << 0xB4 << 0xA5 << 0xA6 << 0x97 << 0x87 << 0x87 << 0x78 << 0x87 << 0x96; // 2036
	chineseTwentyFourData << 0xA5 << 0xC3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2037
	chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2038

	//农历日期名称
	dayName << "*" << "初一" << "初二" << "初三" << "初四" << "初五" << "初六" << "初七" << "初八" << "初九" << "初十"
	        << "十一" << "十二" << "十三" << "十四" << "十五" << "十六" << "十七" << "十八" << "十九" << "二十"
	        << "廿一" << "廿二" << "廿三" << "廿四" << "廿五" << "廿六" << "廿七" << "廿八" << "廿九" << "三十";

	//农历月份名称
	monName << "*" << "正月" << "二月" << "三月" << "四月" << "五月" << "六月" << "七月" << "八月" << "九月" << "十月" << "冬月" << "腊月";

	//二十四节气
	solarTerm << "小寒" << "大寒" << "立春" << "雨水" << "惊蛰" << "春分" << "清明" << "谷雨"
	          << "立夏" << "小满" << "芒种" << "夏至" << "小暑" << "大暑" << "立秋" << "处暑"
	          << "白露" << "秋分" << "寒露" << "霜降" << "立冬" << "小雪" << "大雪" << "冬至";

	//天干
	strTiangan << "甲" << "乙" << "丙" << "丁" << "戊" << "己" << "庚" << "辛" << "壬" << "癸";

	//地支
	strDizhi << "子" << "丑" << "寅" << "卯" << "辰" << "巳" << "午" << "未" << "申" << "酉" << "戌" << "亥";

	//属相
	strAnimal << "鼠" << "牛" << "虎" << "兔" << "龙" << "蛇" << "马" << "羊" << "猴" << "鸡" << "狗" << "猪";

	//公历每月前面的天数
	monthAdd << 0 << 31 << 59 << 90 << 120 << 151 << 181 << 212 << 243 << 273 << 304 << 334;
}

bool LunarCalendarInfo::isLoopYear(int year)
{
	return (((0 == (year % 4)) && (0 != (year % 100))) || (0 == (year % 400)));
}

int LunarCalendarInfo::getTotalMonthDays(int year, int month)
{
	int nDays = 0;
	int nLoopDay = isLoopYear(year) ? 1 : 0;

	switch (month) {
		case  1:
			nDays =   0;
			break;

		case  2:
			nDays =  31;
			break;

		case  3:
			nDays =  59 + nLoopDay;
			break;

		case  4:
			nDays =  90 + nLoopDay;
			break;

		case  5:
			nDays = 120 + nLoopDay;
			break;

		case  6:
			nDays = 151 + nLoopDay;
			break;

		case  7:
			nDays = 181 + nLoopDay;
			break;

		case  8:
			nDays = 212 + nLoopDay;
			break;

		case  9:
			nDays = 243 + nLoopDay;
			break;

		case 10:
			nDays = 273 + nLoopDay;
			break;

		case 11:
			nDays = 304 + nLoopDay;
			break;

		case 12:
			nDays = 334 + nLoopDay;
			break;

		default:
			nDays = 0;
			break;
	}

	return nDays;
}

int LunarCalendarInfo::getFirstDayOfWeek(int year, int month)
{
	int week = 0;
	week = (year + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
	week += getTotalMonthDays(year, month);
	return week % 7;
}

QString LunarCalendarInfo::getHoliday(int month, int day)
{
	int temp = (month << 8) | day;
	QString strHoliday;

	switch (temp) {
		case 0x0101:
			strHoliday = "元旦";
			break;

		case 0x020E:
			strHoliday = "情人节";
			break;

		case 0x0308:
			strHoliday = "妇女节";
			break;

		case 0x0401:
			strHoliday = "愚人节";
			break;

		case 0x0501:
			strHoliday = "劳动节";
			break;

		case 0x0504:
			strHoliday = "青年节";
			break;

		case 0x0601:
			strHoliday = "儿童节";
			break;

		case 0x0701:
			strHoliday = "建党节";
			break;

		case 0x0801:
			strHoliday = "建军节";
			break;

		case 0x090A:
			strHoliday = "教师节";
			break;

		case 0x0A01:
			strHoliday = "国庆节";
			break;

		case 0x0C18:
			strHoliday = "圣诞节";
			break;

		default:
			break;
	}

	return strHoliday;
}

QString LunarCalendarInfo::getSolarTerms(int year, int month, int day)
{
	QString strSolarTerms;
	int dayTemp = 0;
	int index = (year - 1970) * 12 + month - 1;

	if (day < 15) {
		dayTemp = 15 - day;

		if ((chineseTwentyFourData.at(index) >> 4) == dayTemp) {
			strSolarTerms = solarTerm.at(2 * (month - 1));
		}
	} else if (day > 15) {
		dayTemp = day - 15;

		if ((chineseTwentyFourData.at(index) & 0x0f) == dayTemp) {
			strSolarTerms = solarTerm.at(2 * (month - 1) + 1);
		}
	}

	return strSolarTerms;
}

QString LunarCalendarInfo::getLunarFestival(int month, int day)
{
	int temp = (month << 8) | day;
	QString strFestival;

	switch (temp) {
		case 0x0101:
			strFestival = "春节";
			break;

		case 0x010F:
			strFestival = "元宵节";
			break;

		case 0x0202:
			strFestival = "龙抬头";
			break;

		case 0x0505:
			strFestival = "端午节";
			break;

		case 0x0707:
			strFestival = "七夕节";
			break;

		case 0x080F:
			strFestival = "中秋节";
			break;

		case 0x0909:
			strFestival = "重阳节";
			break;

		case 0x0C08:
			strFestival = "腊八节";
			break;

		default:
			break;
	}

	return strFestival;
}

QString LunarCalendarInfo::getLunarYear(int year)
{
	int ntemp = 0;
	QString strTime = "";

	if (year > 1924) {
		ntemp = year - 1924;
		strTime.append(strTiangan.at(ntemp % 10));
		strTime.append(strDizhi.at(ntemp % 12));
		strTime.append(strAnimal.at(ntemp % 12));
	}

	return strTime;
}

void LunarCalendarInfo::getLunarCalendarInfo(int year, int month, int day, QString &strHoliday, QString &strSolarTerms, QString &strLunarFestival, QString &strLunarYear, QString &strLunarMonth, QString &strLunarDay)
{
	int nTheLunarCalendarInfo, nIsEnd, nMonTemp, k, n, nBit;

	strHoliday = getHoliday(month, day);
	strSolarTerms = getSolarTerms(year, month, day);

	//现在计算农历:获得当年春节的公历日期(比如：2015年春节日期为(2月19日))
	//以此为分界点,2.19前面的农历是2014年农历(用2014年农历数据来计算)
	//2.19以及之后的日期，农历为2015年农历(用2015年农历数据来计算)
	nMonTemp = year - 1968;
	int springFestivalMonth = springFestival.at(nMonTemp) / 100;
	int springFestivalDaty = springFestival.at(nMonTemp) % 100;

	if (month < springFestivalMonth) {
		nMonTemp--;
		nTheLunarCalendarInfo = 365 * 1 + day + monthAdd.at(month - 1) - 31 * ((springFestival.at(nMonTemp) / 100) - 1) - springFestival.at(nMonTemp) % 100 + 1;

		if ((!(year % 4)) && (month > 2)) {
			nTheLunarCalendarInfo = nTheLunarCalendarInfo + 1;
		}

		if ((!((year - 1) % 4))) {
			nTheLunarCalendarInfo = nTheLunarCalendarInfo + 1;
		}
	} else if (month == springFestivalMonth) {
		if (day < springFestivalDaty) {
			nMonTemp--;
			nTheLunarCalendarInfo = 365 * 1 + day + monthAdd.at(month - 1) - 31 * ((springFestival.at(nMonTemp) / 100) - 1) - springFestival.at(nMonTemp) % 100 + 1;

			if ((!(year % 4)) && (month > 2)) {
				nTheLunarCalendarInfo = nTheLunarCalendarInfo + 1;
			}

			if ((!((year - 1) % 4))) {
				nTheLunarCalendarInfo = nTheLunarCalendarInfo + 1;
			}
		} else {
			nTheLunarCalendarInfo = day + monthAdd.at(month - 1) - 31 * ((springFestival.at(nMonTemp) / 100) - 1) - springFestival.at(nMonTemp) % 100 + 1;

			if ((!(year % 4)) && (month > 2)) {
				nTheLunarCalendarInfo = nTheLunarCalendarInfo + 1;
			}
		}
	} else {
		nTheLunarCalendarInfo = day + monthAdd.at(month - 1) - 31 * ((springFestival.at(nMonTemp) / 100) - 1) - springFestival.at(nMonTemp) % 100 + 1;

		if ((!(year % 4)) && (month > 2)) {
			nTheLunarCalendarInfo = nTheLunarCalendarInfo + 1;
		}
	}

	//计算农历天干地支月日
	nIsEnd = 0;

	while (nIsEnd != 1)  {
		if (nLunarData.at(nMonTemp) < 4095) {
			k = 11;
		} else {
			k = 12;
		}

		n = k;

		while (n >= 0)   {
			nBit = nLunarData.at(nMonTemp);
			nBit = nBit >> n;
			nBit = nBit % 2;

			if (nTheLunarCalendarInfo <= (29 + nBit))    {
				nIsEnd = 1;
				break;
			}

			nTheLunarCalendarInfo = nTheLunarCalendarInfo - 29 - nBit;
			n = n - 1;
		}

		if (nIsEnd) {
			break;
		}

		nMonTemp = nMonTemp + 1;
	}

	//农历的年月日
	year = 1969 + nMonTemp - 1;
	month = k - n + 1;
	day = nTheLunarCalendarInfo;

	if (k == 12)  {
		if (month == (nLunarData.at(nMonTemp) / 65536) + 1) {
			month = 1 - month;
		} else if (month > (nLunarData.at(nMonTemp) / 65536) + 1) {
			month = month - 1;
		}
	}

    strLunarYear = getLunarYear(year);
    strLunarMonth = monName.at(qAbs(month));
    strLunarDay = dayName.at(qAbs(day));
    strLunarFestival = getLunarFestival(qAbs(month), qAbs(day));
}

QString LunarCalendarInfo::getLunarYearMonthDay(int year, int month, int day)
{
	QString strHoliday;
	QString strSolarTerms;
	QString strLunarFestival;
	QString strLunarYear;
	QString strLunarMonth;
	QString strLunarDay;

	LunarCalendarInfo::Instance()->getLunarCalendarInfo(year, month, day,
	        strHoliday, strSolarTerms, strLunarFestival,
	        strLunarYear, strLunarMonth, strLunarDay);

	return QString("%1年 %2%3").arg(strLunarYear).arg(strLunarMonth).arg(strLunarDay);
}

QString LunarCalendarInfo::getLunarMonthDay(int year, int month, int day)
{
	QString strHoliday;
	QString strSolarTerms;
	QString strLunarFestival;
	QString strLunarYear;
	QString strLunarMonth;
	QString strLunarDay;

	LunarCalendarInfo::Instance()->getLunarCalendarInfo(year, month, day,
	        strHoliday, strSolarTerms, strLunarFestival,
	        strLunarYear, strLunarMonth, strLunarDay);

	return QString("%1%2").arg(strLunarMonth).arg(strLunarDay);
}
