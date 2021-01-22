## Qt5.9 C++开发指南 源代码
最近在看《Qt5.9 C++开发指南》这本书，这本书可以从[异步社区](https://www.epubit.com/bookDetails?id=N25171)上下载源代码，不过需要注册有点麻烦：
![Qt 5.9 C++开发指南](https://img-blog.csdnimg.cn/20210117185623789.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
这本书以Qt 5.9 LTS版本为开发平台，详细介绍了包括Qt应用程序的基本架构、信号与槽工作机制、图形显示的Graphics/View架构、数据编辑和显示的Model/View架构、对话框和多窗口的设计与调用方法等技术；也介绍了常用界面组件、文件读写、绘图、图表、数据可视化、数据库、多线程、网络、多媒体等模块的使用。每个编程主题都精心设计了完整的实例程序，适用于Qt支持的任何平台。目前Qt已经到了6.0.1版本，这本书算是国内比较新的一本书了，很久之前看过中文版的《Qt GUI C++ 4》这本书，不过是基于Qt 4.0版本的。

这本书的源代码有人已经托管到Github上面了，可以从[wlnetman/Qt59_cpp_dev_guide](https://github.com/wlnetman/Qt59_cpp_dev_guide)或者[LewisGu/Qt5.9C-DevelopmentTutorialCode](https://github.com/LewisGu/Qt5.9C-DevelopmentTutorialCode)这两个仓库下载。
![Qt59_cpp_dev_guide](https://img-blog.csdnimg.cn/20210117185342230.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)

![Qt5.9C-DevelopmentTutorialCode](https://img-blog.csdnimg.cn/20210117185309243.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
## 使用QPalette设置QPlainTextEdit颜色时，不生效
练习2.2 可视化UI设计的示例程序[sample2_2](https://github.com/wlnetman/Qt59_cpp_dev_guide/tree/master/samp2_2)时，第32页的编写一个设置QPlainTextEdit的文本编辑框txtEdit的字体颜色时，使用QPalette调色板设置QPlainTextEdit的文本编辑框的字体颜色没有生效，具体槽函数代码如下：
```cpp
void QWDialog::setTextFontColor()
{
    // 通过调用色板来选择字体颜色
    QPalette plet = ui->txtEdit->palette();
    if (ui->rBtnBlue->isChecked()) {
        plet.setColor(QPalette::Text, Qt::blue);
    } else if (ui->rBtnRed->isChecked()) {
        plet.setColor(QPalette::Text, Qt::red);
    } else if (ui->rBtnBlack->isChecked()) {
        plet.setColor(QPalette::Text, Qt::black);
    } else {
        plet.setColor(QPalette::Text, Qt::black);
    }

    ui->txtEdit->setPalette(plet);
}
```

## 解决方法
对照了一下书中的代码和我自己写的代码，发现问题出现在我设置了QPlainTextEdit的文本编辑框txtEdit的样式表的字体颜色：
![设置了样式表颜色属性](https://img-blog.csdnimg.cn/20210117183636861.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
解决方法就是把这个样式表的颜色设置给去掉。
当选择Red单选按钮时，发现下面的文本编辑中的`Hello,world 
It is my demo.`文本变成了红色。如下图所示：
![选择Red单选按钮](https://img-blog.csdnimg.cn/20210117183747214.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
最后查阅了Qt的官方文档：
![Qt关于setPalette的官方文档](https://img-blog.csdnimg.cn/20210117184132935.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
也就是说，Qt官方文档中规定不能将`void	setPalette(const QPalette &)`函数和样式表一起使用。在实际使用时，如果使用了样式表设置了QPlainTextEdit文本编辑框的颜色，那么再使用QPalette设置QPlainTextEdit颜色时，不生效，以样式表的为准。


## 参考资料
- [https://doc.qt.io/qt-5/qwidget.html#palette-prop](https://doc.qt.io/qt-5/qwidget.html#palette-prop)
- [【Qt】使用QPalette设置按钮颜色时，不生效](https://blog.csdn.net/u010168781/article/details/88250451)
