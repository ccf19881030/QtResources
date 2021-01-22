#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H
#include"ui_linearAlgebra.h"
class LinearAlgebra:public QWidget, public Ui_linearAlgebra
{
    Q_OBJECT
public:
    LinearAlgebra(QWidget* parent=0);
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void changeRow(int row);
    void changeCol(int col);
    void changeColWidth(int colWidth);

    void on_inputPushButton_clicked();
    void on_outputPushButton_clicked();
    void on_inputComboBox_activated(int Index);
    void on_outputComboBox_activated(int Index);
    void on_Calc_pushButton_clicked();
    void on_clearPushButton_clicked();
protected:
    bool eventFilter(QObject *target, QEvent *event);
protected:
      void dragEnterEvent(QDragEnterEvent *event);
      void dropEvent(QDropEvent *event);
private:
      bool readFile(const QString &fileName);
private:
    double **matrix[4];
    bool isAssiged[4];
    int matrixRow[4],matrixCol[4];

    unsigned ladderSwapCount[4];            //阶梯化过程中交换次数
    int *pivcol[4],*augPivcol;              //记录阶梯化过程中交换的列数
    double **ladderMatrix[4];               //阶梯矩阵
    bool isLadder[4];                       //是否已经阶梯化
    int Rank[4];                            //矩阵的秩
    double Det[4];                          //矩阵的行列式值
    double *eigen_Value_Real[4];            //矩阵的特征值的实部
    double *eigen_Value_Comp[4];            //矩阵的特征值的虚部
protected:
    void assign(int Index1,int Index2);     //赋值
    void assign(int Index,double **a,int row,int col);
    bool add(int Index,int Index1,int Index2);//matrix[Index]=matrix[Index1]+matrix[Index2]
    bool subtract(int Index,int Index1,int Index2);//减法
    bool multiply(int Index,int Index1,int Index2);//乘法
    void multiply(int Index1,double n,int Index2); //数乘
    bool power(int Index1,int Index2,int n);       //乘幂
    bool transpose(int Index);              //求转置
    bool adjoint(int Index);                //求伴随矩阵
    bool ladder(int Index);                 //求阶梯矩阵
    int augLadder();                        //求增广矩阵的阶梯矩阵,返回增广矩阵的秩
    void rank(int Index);                   //求矩阵的秩
    void det(int Index, bool val=0);        //求行列式的值
    bool inver(int Index);                  //求逆矩阵
    bool generInver(int Index);             //求广义逆矩阵
    bool matrixQR(int Index);               //求QR分解
    void homogen(int Index);                //求其次线性方程组通解
    bool inhomogen(int Index);              //求非齐次线性方程组通解
    void eigenValue(int Index, bool val=0); //求特征值
    void maxEigenValue(int Index);          //求绝对值最大的特征值
    void eigenVector(int Index);            //求特征向量
    void eigenPolyomial(int Index);         //求特征多项式
    void isOrthogonal(int Index);           //判断否为正交矩阵
    double trace(int Index);                //求矩阵的迹
    double trace(double **a,int n);         //求给定矩阵的迹
};
void sss(double fg[],double cs[]);           //求广义逆矩阵的需要用到
#endif // LINEARALGEBRA_H
