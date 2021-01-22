#ifndef CALCULATOR_H
#define CALCULATOR_H
#include"ui_calculator.h"
#include"ChildWindow.h"
class QTableWidget;
class QTableWidgetItem;
class Calculator : public QMainWindow, public Ui::Calculator
{
    Q_OBJECT
public:
    Constant *constantDialog;
    History *historyDialog;    
public:
    Calculator( QWidget* parent=0);
protected:
    void closeEvent(QCloseEvent *event);
private:
    void readSettings();
    void writeSettings();
private slots:
    //选择不同进制
    void decSystem();
    void binSystem();
    void octSystem();
    void hexSystem();
    //选择数域
    void realSystem();
    void complexSystem();
    //双曲函数
    void hyperbolicSystem();
    void changeLanguage(bool isChange);
    void changePrecision();
    void inputNumOne();
    void inputNumTwo();
    void inputNumThree();
    void inputNumFour();
    void inputNumFive();
    void inputNumSix();
    void inputNumSeven();
    void inputNumEight();
    void inputNumNine();
    void inputNumZero();
    void inputNumA();
    void inputNumB();
    void inputNumC();
    void inputNumD();
    void inputNumE();
    void inputNumF();
    //输入虚数单位
    void inputNumI();
    void inputNumEi();

    void inputPoint();
    void inputOperAdd();
    void inputOperSubtract();
    void inputOperMultiply();
    void inputOperDivide();
    void inputOperMod();
    void inputOperDiv();
    void inputOperPercent();

    void inputOperFact();
    void inputOperComb();
    void inputOperPower();
    void inputOperSqr();
    void inputOperCub();
    void inputOperExpE();
    void inputOperExp10();
    void inputOperSqrt();
    void inputOperCur();
    void inputOperXYsqrt();

    void inputFunSin();
    void inputFunCos();
    void inputFunTan();
    void inputFunCot();
    void inputFunArcSin();
    void inputFunArcCos();
    void inputFunArcTan();
    void inputFunArcCot();
    void inputFunLg();
    void inputFunLn();
    void inputFunLog();
    void inputFunAbs();
    void inputFunPow();
    void inputFunGcd();
    void inputFunLcm();

    void inputLeftBack();
    void inputRightBack();

    void inputConst_e();
    void inputConst_g();
    void inputConst_pi();
    void inputConstant();
    void clearExpress();
    void backspace();
    void redo();
    void undo();
    void fold();

    void insertNewResult();
    void insertMemorySystem();
    void insertMemoryResult();
    void getResult();

    void showHistory();
    void showVariable();
    void showConstant();
    void setTopHint();
    void windowColorChange(QColor color);
    void textviewColorChange(QColor color);
    void expressionFontChange(QFont font);
    void defaultSettings();
    void showFontDialog();
    void showWindowColorDialog();
    void showTextViewColorDialog();
    void setData();
    void setHistoryIndex();
    void getHugeCalcWidget();
    void getLinearAlgebraWidget();
    void getnonLinearAlgebraWidget();
    void help();
    void about();
    void giveSuggestions();
    void ElseTools();
private:
    int historyIndex;
    int oldSystem,newSystem;
    bool isChangeSystem;
    bool isCorrect;
    bool isChangeColor;
    bool isChangeFont;
};

#endif // CALCULATOR_H
