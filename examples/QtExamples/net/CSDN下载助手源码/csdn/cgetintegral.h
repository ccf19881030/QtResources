/*
 *   文件名: CGetIntegral.h
 *
 *   功能: 此类专门用来伪装下载文件 然后评价获取积分
 *      流程: 先判断是否有待评价资源  有就先下载
 *          无   选择下载区域  爬虫获取下载列表   然后进行一一下载
 *                  下载前需要判断是否出现验证码  有  人工打码
 *                      下载10个后停止下载  5分钟后进入评价
 */

#ifndef CGETINTEGRAL_H
#define CGETINTEGRAL_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "cvalidatedialog.h"
#include <QPixmap>
#include <QTimer>

class CGetIntegral : public QObject
{
    Q_OBJECT
public:
    explicit CGetIntegral(QObject *parent = 0);
    ~CGetIntegral();
    
    void setCookie(const QString &cookie);

signals:
    void stopEvaluate();

    void sendSimulationDownOver();

public:
    // 模拟下载
    void simulationDownResource(const QString &postUrl, const QString &postRef);

    // 获取下载资源列表
    void getDownUrlList(const QString &url/* 资源分区地址: 比如c和android资源地址*/, const int &getPageNum);

    // 准备模拟下载资源  此函数进行组装下载信息和控制进度
    void startSimulationDown();

    // 获取评价资源
    void getEvaluateResourceList();

    QPixmap getValidateCodePix(QString ref, int style =0);
    
    int getIntegralNum();

public slots:
    // 评价资源
    void evaluateResource();

private:

    QString m_Cookie;

    QStringList m_DownUrlList; // 资源下载列表

    QStringList m_EvaluateUrlList;

    CValidateDialog *m_pValidateDialog;

    QString m_ValidateCode;

    QPixmap m_PrePixmap;
};

#endif // CGETINTEGRAL_H
