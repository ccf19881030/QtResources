#include "cgetintegral.h"
#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/QNetworkRequest>
#include <QEventLoop>
#include <QRegExp>
#include <QDebug>
#include "chelp.h"
#include <QPixmap>
#include <Qtime>
#include <QFile>

CGetIntegral::CGetIntegral(QObject *parent) :
    QObject(parent)
{
    m_pValidateDialog = new CValidateDialog();
}

CGetIntegral::~CGetIntegral()
{
    delete m_pValidateDialog;
}

void CGetIntegral::setCookie(const QString &cookie)
{
    m_Cookie = cookie;
    m_Cookie = "FullCookie=1; bdshare_firstime=1438318619461; download_first=1; " + m_Cookie;
}

/*
 *   函数名: simulationDownResource
 *   说明:  验证码部分做的不是很好。没有去深入他的切换机制。
 *
 *   原因: 官网的验证码机制不完善，会出现验证码无效问题。待改善
 *
 */

void CGetIntegral::simulationDownResource(const QString &postUrl, const QString &postRef)
{
    // 模拟下载资源
    QNetworkRequest networkRequest;

    networkRequest.setUrl(QUrl(postUrl));
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkRequest.setRawHeader(QByteArray("Referer"),postRef.toLatin1());
    networkRequest.setRawHeader(QByteArray("Cookie"), m_Cookie.toLatin1());

    QByteArray postData = "ds=dx&validate_code=" +m_ValidateCode.toLatin1() +"&basic%5Breal_name%5D=&basic%5Bmobile%5D=&basic%5Bemail%5D=&basic%5Bjob%5D=&basic%5Bcompany%5D=&basic%5Bprovince%5D=&basic%5Bcity%5D=&basic%5Bindustry%5D=";

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(networkRequest, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QString str = reply->readAll();
    reply->deleteLater();

    if (str.contains("show_validate_pop")) {

        CHelp::setLog(QString("好吧，出现验证码了，您手动输入吧!!"));

        m_pValidateDialog->setPixmap(m_PrePixmap);

        if (1 != m_pValidateDialog->exec()) // 以模式对话框方式打开
              return;
        m_ValidateCode = m_pValidateDialog->getValidateCode();

        // 重新发出请求
        simulationDownResource(postUrl, postRef);
    } else {

        // resetCode
        m_PrePixmap = getValidateCodePix(postRef);
    }
}

QPixmap CGetIntegral::getValidateCodePix(QString ref, int style)
{
    // 获取验证码  "src","/index.php/rest/tools/validcode/source_ip_validate/1"+Math.random());

    // 产生随机数
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QString rand = "http://download.csdn.net/index.php/rest/tools/validcode/source_ip_validate/10.";
    for (int i =0; i< 16; ++i)
        rand.append(QString::number(qrand()%9));

    if (style == 1) {

        rand = "http://download.csdn.net/index.php/rest/tools/validcode/source_ip_validate";
    }

    QNetworkAccessManager manager;
    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(rand));
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkRequest.setRawHeader(QByteArray("Referer"),ref.toLatin1());
    networkRequest.setRawHeader(QByteArray("Cookie"), m_Cookie.toLatin1());

    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(rand)));

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray str = reply->readAll();
    reply->deleteLater();

    if (style == 1) {

        QString tmp = reply->rawHeader("Set-Cookie");
        m_Cookie = tmp.remove(" path=/") + m_Cookie;
    }

    QPixmap pixmap ;
    pixmap.loadFromData(str);
    return pixmap;
}

void CGetIntegral::evaluateResource()
{
    if (m_EvaluateUrlList.count() == 0) {

        emit stopEvaluate();
        return;
    }

    static int order =0;

    if (m_EvaluateUrlList.count() == order) {

        emit stopEvaluate();
        return;
    }

    CHelp::setLog(QString("正在评价资源:%1").arg(m_EvaluateUrlList.at(order)));
    // 评价内容
    QStringList evaluate;
    evaluate<<QString("%E8%B0%A2%E8%B0%A2%E6%A5%BC%E4%B8%BB~~%E5%A5%BD%E6%A3%92")<<
            QString("%e8%b0%a2%e8%b0%a2%e5%92%af%7e%7e%e8%b0%a2%e8%b0%a2v")<<
            QString("%e5%af%b9%e6%88%91%e5%b8%ae%e5%8a%a9%e5%be%88%e5%a4%a7%7e")<<
            QString("%e7%bb%88%e4%ba%8e%e6%89%be%e5%88%b0%e4%ba%86%7e")<<
            QString("%e8%b0%a2%e8%b0%a2%7e%e6%84%9f%e8%b0%a2%e5%88%86%e4%ba%ab");
    // 先获取时间戳
    QDateTime time = QDateTime::currentDateTime();
    QString Ts = QString::number(time.msecsTo(QDateTime(QDate(1970, 1, 1), QTime(0,0,0,0))));
    Ts.remove('-');

    // 产生随机数
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    // 选择其中一个评价内容

    QString id = m_EvaluateUrlList.at(order) ;
    id = id.mid(id.lastIndexOf('/')+1);
    QString url = "http://download.csdn.net/index.php/comment/post_comment?jsonpcallback=jsonp" + Ts+"&sourceid=" +id +
            "&content="+ evaluate[qrand()%4] +"&rating=4&t=" +Ts;

    QNetworkAccessManager manager;
    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(url));
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkRequest.setRawHeader(QByteArray("Referer")," http://download.csdn.net"+m_EvaluateUrlList.at(order).toLatin1());
    networkRequest.setRawHeader(QByteArray("Cookie"), m_Cookie.toLatin1());

    QNetworkReply *reply = manager.get(networkRequest);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray str = reply->readAll();
    reply->deleteLater();

    if (order == m_EvaluateUrlList.count()-1) {
        emit stopEvaluate();
        order = 0;
        return;
    }

    ++order;

    CHelp::setLog(QString("该资源评价成功:%1").arg(m_EvaluateUrlList.at(order)));

    CHelp::setLog(QString("正在准备评价资源:%1").arg(m_EvaluateUrlList.at(order)));

}

void CGetIntegral::getDownUrlList(const QString &url/* 资源分区地址: 比如c和android资源地址*/,
                             const int &getPageNum)
{

    m_DownUrlList.clear(); // 先清空数据  防止重复使用

    // 获取下载列表资源
    int order = getPageNum, j =0;
    int nPage = 0; // 页面
    while (order < getPageNum + 3&& j<= 100 /*最多访问一百次就要退出了*/) {

        /*
         *<dt><a href="/detail/ORIETech/3364291">
         *7个Android应用程序源代码</a>
         *<span class="marks">0</span></dt>
         */

        // 用Get方式请求
        QNetworkRequest networkRequest;
        ++nPage;
        networkRequest.setUrl(QUrl(url + QString("/")+QString::number(nPage)));
        networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        networkRequest.setRawHeader(QByteArray("Referer"),url.toLatin1());
        networkRequest.setRawHeader(QByteArray("Cookie"), m_Cookie.toLatin1());

        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(networkRequest);

        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        QString str = reply->readAll();
        reply->deleteLater();

        // 正则匹配获取
        QRegExp rx("<dt><a href=.{1,300}</span></dt>");
        rx.setMinimal(true);

        QRegExp re("/detail/[^\"]{1,30}\"");

        int pos = 0;
        while ((pos = rx.indexIn(str, pos)) != -1)
        {
            re.indexIn(rx.cap(0));
            if (rx.cap(0).contains("marks\">0")) {

                re.indexIn(rx.cap(0));
                QString tmp = re.cap(0);
                m_DownUrlList.append(tmp.remove("\"").remove("/detail/"));
                CHelp::setLog(QString("成功获取资源地址:") + tmp);
            }
            pos += rx.matchedLength();
        }
        ++j, ++order;
    }
}

void CGetIntegral::startSimulationDown()
{
    QString preCookie = m_Cookie;
    // 这里需要解析和组装获取的资源地址列表

    for (int i=0; i< m_DownUrlList.count(); ++i) {

        QString refUrl = QString("http://download.csdn.net/download/") + m_DownUrlList.at(i);

        // 再次访问此页面  获取真正的下载请求地址

        QNetworkRequest networkRequest;
        networkRequest.setUrl(QUrl(refUrl));
        networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        networkRequest.setRawHeader(QByteArray("Referer"),QByteArray("http://download.csdn.net/detail/") + m_DownUrlList.at(i).toLatin1());
        networkRequest.setRawHeader(QByteArray("Cookie"), m_Cookie.toLatin1());

        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(networkRequest);

        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        QString str = reply->readAll();
        reply->deleteLater();

        QRegExp rx("http://download.csdn.net/index.php/source/do_download/[^\"]{1,200}\""); // 获取真正的下载地址

        rx.indexIn(str);

        CHelp::setLog(QString("正在模拟下载资源:") + m_DownUrlList.at(i));

        m_Cookie = preCookie;
        // 开始请求下载
        m_PrePixmap = getValidateCodePix(refUrl, 1);

        simulationDownResource(rx.cap(0).remove("\""), refUrl);

        CHelp::setLog(QString("模拟下载完成:") + m_DownUrlList.at(i));
    }

    CHelp::setLog(QString("模拟下载完成!请在10分钟以后点击评价资源!"));

    emit sendSimulationDownOver();
    m_Cookie = preCookie;
}

int CGetIntegral::getIntegralNum()
{
    // http://download.csdn.net/my
    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl("http://download.csdn.net/my"));
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkRequest.setRawHeader(QByteArray("Cookie"), m_Cookie.toLatin1());

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(networkRequest);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QString str = reply->readAll();
    reply->deleteLater();

    QRegExp rx("<em>积 分：\\d{1,10}");

    rx.indexIn(str);

    int ret = rx.cap(0).remove("<em>积 分：").toInt();

    CHelp::setLog(QString("积分获取成功!当前共有 %1 积分!").arg(ret));

    return ret;
}

void CGetIntegral::getEvaluateResourceList()
{
    m_EvaluateUrlList.clear();

    // 获取等待评价的资源

    // href="/detail/xxb_zrx/8947637#comment" class="btn-comment">立即评价，通过可返分</a>

    // http://download.csdn.net/my/downloads
    int page =1, index = 0;
    while (index < page) {

        QNetworkRequest networkRequest;
        networkRequest.setUrl(QUrl(QString("http://download.csdn.net/my/downloads/%1").arg(index+1)));
        networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        networkRequest.setRawHeader(QByteArray("Referer"),QByteArray("http://download.csdn.net/my"));
        networkRequest.setRawHeader(QByteArray("Cookie"), m_Cookie.toLatin1());

        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(networkRequest);

        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        QString str = reply->readAll();
        reply->deleteLater();

        QRegExp rx("/detail/[^#]{1,100}#comment\" class=\"btn-comment\">立即评价");
        int pos = 0;
        while ((pos = rx.indexIn(str, pos)) != -1)
        {
            QString tmp = rx.cap(0);
            tmp.remove("#comment\" class=\"btn-comment\">立即评价");
            m_EvaluateUrlList.append(tmp);
            CHelp::setLog(QString("成功获取评价资源地址:") + tmp);
            pos += rx.matchedLength();
        }
        rx.setPattern("共\\d页");
        rx.indexIn(str);
        page = rx.cap(0).remove("共").remove("页").toInt();
        index ++;
    }

    if (m_EvaluateUrlList.count() == 0) {

        CHelp::setLog(QString("当前所需评价资源为空!!"));
        emit stopEvaluate();    
    }
}









