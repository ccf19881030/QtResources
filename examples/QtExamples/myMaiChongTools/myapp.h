#ifndef MYAPP_H
#define MYAPP_H

#include <QString>

class myApp
{
public:
    static QString PortName;    
    static int CountChuChang;
    static int CountWeiXiu;
    static bool UsePwd;
    static QString PassWord;

    static void ReadConfig();
    static void WriteConfig();
};

#endif // MYAPP_H
