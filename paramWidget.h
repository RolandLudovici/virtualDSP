#ifndef PARAMWIDGET_H
#define PARAMWIDGET_H

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class paramWidget : public QWidget {
    Q_OBJECT

public:
    paramWidget(QWidget *parent = nullptr, double value=0.0, double stepSize=1.0, double lowerLim=-0xFFFF,
                double upperLim = 0xFFFF, QString label=QString("Label"), QString unit=QString("NV"));
    ~paramWidget();

    inline double getValue() {
        return value;
    }

    inline void setValue(double value) {
        if (value<lowerLim) {
            this->value = lowerLim;
        } else if (value>upperLim) {
            this->value = upperLim;
        } else {
            this->value = std::roundf(value*10e5)/10e5;
        }
        actText = QString::number(this->value) + QString(" ") + QString(unit);
        valueField.setText(actText);
    }

    inline int setStepSize(double stepSize) {
        if (stepSize>=0.0001 && stepSize<10000) {
            this->stepSize=stepSize;
            return 0;
        } else {
            return -1;
        }
    }

    inline void setLabel(QString str) {
        fieldLabel.setText(str);
    }

    inline void setUnit(QString str) {
        unit = str;
    }

    inline void setLimits(double lowerLim, double upperLim) {
        this->lowerLim = lowerLim;
        this->upperLim = upperLim;
    }

    inline void setReadOnly(bool flag) {
        valueField.setReadOnly(flag);
    }

signals:
    void valueChanged(double);

    void valueChanged(unsigned int);

private slots:
    void increaseValue();

    void decreaseValue();

    void lineEditHandle();

    //void setLimiThres(double val);

private:
    void valueChangeHandle();

    QPushButton plusButton, minusButton;

    QIcon plusIcon, minusIcon;

    QLabel fieldLabel;

    QLineEdit valueField;

    QString unit, actText;

    double value, stepSize, lowerLim, upperLim;
};

#endif // MAINWINDOW_H