#include "lyrics.h"
#include <QFile>
#include <QTextCodec>
#include <QDebug>

Lyrics::Lyrics(QObject *parent) : QObject(parent)
{

}

Lyrics::~Lyrics()
{

}

QList<QString> Lyrics::getLyric(QString url)
{
    url.remove("file:///");
    url.remove(".mp3");
    url.append(".lrc");
    time.clear();
    list.clear();
    QString temp = "";
    QFile file(url);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextCodec *codec = QTextCodec::codecForLocale();
        temp = codec->toUnicode(file.readAll());
        QList<QString> tempList;
        tempList = temp.split("\n");

        for(int i=0;i<tempList.size();i++)
        {
            QString temps = tempList.at(i);
            if(temps.at(1).digitValue() >= 0 && !temps.at(10).isNull())
            {
                long count6 = temps.at(1).digitValue() * 10 * 60 * 100;
                long count5 = temps.at(2).digitValue() * 60 * 100;
                long count4 = temps.at(4).digitValue() * 10 * 100;
                long count3 = temps.at(5).digitValue() * 100;
                long count2 = temps.at(7).digitValue() * 10;
                long count1 = temps.at(8).digitValue();

                long sum = count1 + count2 + count3 + count4 + count5 + count6;
                temps.remove(0,10);
                if(temps.count()>0)
                {
                    list.append(temps);
                    time.append(sum);
                }
            }
        }
    }else{
        temp = "歌词未找到";
        list<<""<<""<<temp<<""<<"";
    }
    list.insert(0,"");
    list.append("");
    list.append("");
    return list;
}

QList<double> Lyrics::getTime()
{
    return time;
}
