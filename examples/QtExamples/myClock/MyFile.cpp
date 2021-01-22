#include "MyFile.h"
#include <QDebug>

MyFile::MyFile(QObject * parent):
    QThread(parent)
{
    m_running = false;
    m_type = 0;
    m_path = "";

    this->start();
}

void MyFile::run()
{
    while(m_running){
        if(m_type == 0){
            //0 read
            read();
        }
        else if(m_type == 1){
            //1 write
            write();
        }
        else{}
    }
}

void MyFile::readFile(QString path)
{
    m_running = false;
    m_path = path;
    m_type = 0;
    m_running = true;
    this->start();
}

void MyFile::writeFile(QString path, QVariantList data)
{
    m_running = false;
    m_path = path;
    m_type = 1;
    m_data = data;
    m_running = true;
    this->start();
}

void MyFile::read()
{
    QVariantList _list;
    QVariantMap _map;
    QSettings * readIni = new QSettings(m_path,QSettings::IniFormat);
    for(int i=0;i<2;i++){
        QString time = readIni->value("clock"+QString::number(i)+"/time").toString();
        QString tips = readIni->value("clock"+QString::number(i)+"/tips").toString();
        _map.insert("time",time);
        _map.insert("tips",tips);
        _list.append(_map);
    }
    delete readIni;
    m_running = false;

    emit getReadFile(_list);
}

void MyFile::write()
{
    QSettings * writeIni = new QSettings(m_path,QSettings::IniFormat);

    for(int i=0;i<m_data.size();i++){
        QVariantMap _map = m_data.at(i).toMap();

        writeIni->setValue("clock"+QString::number(i)+"/time",_map.value("time").toString());
        writeIni->setValue("clock"+QString::number(i)+"/tips",_map.value("tips").toString());

    }
    delete writeIni;
    m_running = false;

    emit getWriteResult(true);
}
