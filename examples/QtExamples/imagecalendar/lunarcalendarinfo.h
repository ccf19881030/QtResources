#ifndef LunarCalendarInfoINFO_H
#define LunarCalendarInfoINFO_H

/**
 * 农历信息类 作者:feiyangqingyun(QQ:517216493) 2016-12-10
 * 1:计算是否闰年
 * 2:计算国际节日
 * 3:计算二十四节气
 * 4:计算农历年 天干+地支+生肖
 * 5:计算指定年月日农历信息,包括公历节日和农历节日及二十四节气
 */

#include <QObject>
#include <QMutex>

class LunarCalendarInfo : public QObject
{
	Q_OBJECT
public:
	explicit LunarCalendarInfo(QObject *parent = 0);
	static LunarCalendarInfo *Instance()
	{
		if (!self) {
			static QMutex mutex;
			QMutexLocker locker(&mutex);

			if (!self) {
				self = new LunarCalendarInfo;
			}
		}

		return self;
	}

	//计算是否闰年
	bool isLoopYear(int year);

	//计算指定年月对应到该月共多少天
	int getTotalMonthDays(int year, int month);

	//计算指定年月对应星期
	int getFirstDayOfWeek(int year, int month);

	//计算国际节日
	QString getHoliday(int month, int day);

	//计算二十四节气
	QString getSolarTerms(int year, int month, int day);

	//计算农历节日(必须传入农历年份月份)
	QString getLunarFestival(int month, int day);

	//计算农历年 天干+地支+生肖
	QString getLunarYear(int year);

	//计算指定年月日农历信息,包括公历节日和农历节日及二十四节气
	void getLunarCalendarInfo(int year, int month, int day,
	                          QString &strHoliday,
	                          QString &strSolarTerms,
	                          QString &strLunarFestival,
	                          QString &strLunarYear,
	                          QString &strLunarMonth,
	                          QString &strLunarDay);

	//获取指定年月日农历年份及属相
	QString getLunarYearMonthDay(int year, int month, int day);
	QString getLunarMonthDay(int year, int month, int day);

private:
	static LunarCalendarInfo *self;

	QList<int> springFestival;
	QList<int> nLunarData;
	QList<int> chineseTwentyFourData;

	QList<QString> dayName;
	QList<QString> monName;
	QList<QString> solarTerm;

	QList<QString> strTiangan;
	QList<QString> strDizhi;
	QList<QString> strAnimal;

	QList<int> monthAdd;

};

#endif // LunarCalendarInfoINFO_H
