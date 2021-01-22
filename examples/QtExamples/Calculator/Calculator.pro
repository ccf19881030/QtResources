FORMS += \
    calculator.ui \
    history.ui \
    about.ui \
    linearAlgebra.ui \
    hugeCalc.ui \
    nonLinearAlgebra.ui \
    constant.ui \
    variable.ui
QT +=widgets
RESOURCES += \
    resource.qrc \

HEADERS += \
    Calculator.h \
    ChildWindow.h \
    BigInt.h \
    HugeCalc.h \
    Calc.h \
    linearAlgebra.h \
    nonLinearAlgebra.h \
    polynomial.h \
    GeneticAlgorithm.h \
    Complex.h

SOURCES += \
    main.cpp \
    Calculator.cpp \
    ChildWindow.cpp \
    HugeCalc.cpp \
    BigInt.cpp \
    Calc.cpp \
    linearAlgebra.cpp \
    nonLinearAlgebra.cpp \
    polynomial.cpp \
    GeneticAlgorithm.cpp \
    Complex.cpp
TRANSLATIONS¡¡+=Chinese.ts\

