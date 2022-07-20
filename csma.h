#ifndef CSMA_H
#define CSMA_H
#include <QLCDNumber>
#include <QWidget>

//DELETEME maybe not needed to run ???
/*
QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
class Button;
*/

//! [0]
class CSMASim : public QWidget
{
    Q_OBJECT

public:
    CSMASim(QWidget *parent = nullptr);

private slots:
    void startClicked();



//! [1]
private:
//! [1] //! [2]
    int cableLength; //parameter A
    int packetLength; //k value parameter B
    float pval; //parameter C
    int tickSensingT;// parameter D
    int maxRun; //parameter E




    QLCDNumber *cableLCD = new QLCDNumber(3); //A
    QLCDNumber *msgLCD = new QLCDNumber(3); //B
    QLCDNumber *delayLCD = new QLCDNumber(3); //D
    QLCDNumber *tickLCD = new QLCDNumber(4); //E
    QLCDNumber *prob_LCD = new QLCDNumber(2); //C

};
//! [10]


#endif // CSMA_H
