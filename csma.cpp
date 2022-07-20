#include "csma.h"

#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QDial>
#include <QListWidget>
#include <QLabel>
#include <QLCDNumber>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QString>
#include <fstream>
#include <iostream>
#include <array>
#include <string>

using namespace std;


CSMASim::CSMASim(QWidget *parent)
    : QWidget(parent), cableLength(7), packetLength(5)
    , pval(0.1), tickSensingT(5), maxRun(4000)
{
    QWidget *window = new QWidget;
    window->setWindowTitle("CSMASim");


//"Cable Length"
QSpinBox *spinBox = new QSpinBox;
spinBox->setRange(7, 99);
spinBox->setValue(7);
spinBox->setMinimumHeight(30);
spinBox->setMinimumWidth(200);

QVBoxLayout *cableLayout = new QVBoxLayout;
cableLayout->setAlignment(Qt::AlignCenter);

QLabel *cableLabel = new QLabel();
cableLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
cableLabel->setAlignment(Qt::AlignCenter);
cableLabel->setText("Cable Length");
cableLabel->setFixedWidth(200);
cableLabel->setFixedHeight(50);

//QLCDNumber *cableLCD = new QLCDNumber(3);
cableLCD->setSegmentStyle(QLCDNumber::Flat);
cableLCD->setFixedSize(200, 30);
cableLCD->display("7");
QObject::connect(spinBox, SIGNAL(valueChanged(int)), cableLCD, SLOT(display(int)));
cableLayout->addWidget(cableLCD);
cableLayout->addWidget(spinBox);
cableLayout->addWidget(cableLabel);



//"Message Length"
QListWidget *list = new QListWidget();
//*list << 1 << 2 << 3;
new QListWidgetItem("Select:", list);
QListWidgetItem *firstRow = list->item(0);
firstRow->setFlags(firstRow->flags() & ~Qt::ItemIsEnabled);
new QListWidgetItem("1", list);
new QListWidgetItem("2", list);
new QListWidgetItem("3", list);
new QListWidgetItem("4", list);
new QListWidgetItem("5", list);

list->setMinimumHeight(300);
list->setMinimumWidth(200);

QVBoxLayout *msgLayout = new QVBoxLayout;
msgLayout->setAlignment(Qt::AlignCenter);

QLabel *msgLabel = new QLabel();
msgLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
msgLabel->setText("Message Length");
msgLabel->setAlignment(Qt::AlignCenter);
msgLabel->setFixedWidth(200);
msgLabel->setFixedHeight(50);

//QLCDNumber *msgLCD = new QLCDNumber(3);
msgLCD->setSegmentStyle(QLCDNumber::Flat);
msgLCD->setFixedSize(200, 30);
msgLCD->display("3");
QObject::connect(list, SIGNAL(currentRowChanged(int)), msgLCD, SLOT(display(int)));


//"Probability % Dial"
QDial *dial = new QDial;
dial->setRange(10, 50);
dial->setMinimumHeight(300);
dial->setMinimumWidth(200);
dial->setNotchesVisible(true);
dial->setPageStep(100);

QVBoxLayout *prob_Layout = new QVBoxLayout;
prob_Layout->setAlignment(Qt::AlignCenter);

QLabel *prob_Label = new QLabel();
prob_Label->setFrameStyle(QFrame::Box | QFrame::Raised);
prob_Label->setText("Probability %");
prob_Label->setAlignment(Qt::AlignCenter);
prob_Label->setFixedWidth(200);
prob_Label->setFixedHeight(50);

//QLCDNumber *prob_LCD = new QLCDNumber(2);
prob_LCD->setSegmentStyle(QLCDNumber::Flat);
prob_LCD->display("10");
prob_LCD->setFixedSize(200, 30);
QObject::connect(dial, SIGNAL(valueChanged(int)), prob_LCD, SLOT(display(int)));
prob_Layout->addWidget(prob_LCD);
prob_Layout->addWidget(dial);
prob_Layout->addWidget(prob_Label);



//carrier delay radioButton
QButtonGroup *radioGroup = new QButtonGroup();
QRadioButton *radio0 = new QRadioButton("0");
QRadioButton *radio1 = new QRadioButton("1");
QRadioButton *radio2 = new QRadioButton("2");
QRadioButton *radio3 = new QRadioButton("3");
QRadioButton *radio4 = new QRadioButton("4");
QRadioButton *radio5 = new QRadioButton("5");

radio0->setChecked(true); //radio 0 checked at boot

radioGroup->addButton(radio0);
radioGroup->addButton(radio1);
radioGroup->addButton(radio2);
radioGroup->addButton(radio3);
radioGroup->addButton(radio4);
radioGroup->addButton(radio5);

radioGroup->setId(radio0, 0);
radioGroup->setId(radio1, 1);
radioGroup->setId(radio2, 2);
radioGroup->setId(radio3, 3);
radioGroup->setId(radio4, 4);
radioGroup->setId(radio5, 5);

QVBoxLayout *vboxDelay = new QVBoxLayout;
vboxDelay->addWidget(radio0);
vboxDelay->addWidget(radio1);
vboxDelay->addWidget(radio2);
vboxDelay->addWidget(radio3);
vboxDelay->addWidget(radio4);
vboxDelay->addWidget(radio5);
vboxDelay->addStretch(1);

QLabel *delayLabel = new QLabel();
delayLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
delayLabel->setText("Carrier Busy Delay");
delayLabel->setAlignment(Qt::AlignCenter);
delayLabel->setFixedWidth(200);
delayLabel->setFixedHeight(50);

//QLCDNumber *delayLCD = new QLCDNumber(3);
delayLCD->setSegmentStyle(QLCDNumber::Flat);
delayLCD->setFixedSize(200, 30);
delayLCD->display("0");
QObject::connect(radioGroup, SIGNAL(idPressed(int)), delayLCD, SLOT(display(int)));



//"Total Ticks"
int max = 5000;
QSlider *slider = new QSlider(Qt::Vertical);
slider->setRange(0, 5000);
slider->setFocusPolicy(Qt::StrongFocus);
slider->setMinimumHeight(300);
slider->setMinimumWidth(200);
slider->setTickPosition(QSlider::TicksRight);
slider->setTickInterval(1000);
slider->setSingleStep(1);
slider->setMouseTracking(true);

QVBoxLayout *tickLayout = new QVBoxLayout;
tickLayout->setAlignment(Qt::AlignCenter);

QLabel *tickLabel = new QLabel();
tickLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
tickLabel->setText("Total Ticks");
tickLabel->setAlignment(Qt::AlignCenter);
tickLabel->setFixedWidth(200);
tickLabel->setFixedHeight(50);

//QLCDNumber *tickLCD = new QLCDNumber(4);
tickLCD->setSegmentStyle(QLCDNumber::Flat);
tickLCD->setFixedSize(200, 30);
tickLCD->display("3000");
QObject::connect(slider, SIGNAL(sliderMoved(int)), tickLCD, SLOT(display(int)));
tickLayout->addWidget(tickLCD);
tickLayout->addWidget(slider);
tickLayout->addWidget(tickLabel);



//start simulation
QPushButton *start = new QPushButton("Start Simulation");
start->setMinimumWidth(200);
start->setMinimumHeight(100);
//QObject::connect(start, SIGNAL(clicked()), start, SLOT(clicked()));
connect(start, SIGNAL(clicked()), this,  SLOT(startClicked()));


//grid layout
QGridLayout *grid = new QGridLayout;
//cable length, column 0
grid->addWidget(cableLCD, 0, 0);
grid->addWidget(spinBox, 1, 0);
grid->addWidget(cableLabel, 2, 0);
//message length, column 1
grid->addWidget(msgLCD, 0, 1);
grid->addWidget(list, 1, 1);
grid->addWidget(msgLabel, 2, 1);
//probability, column 2
grid->addWidget(prob_LCD, 0, 2);
grid->addWidget(dial, 1, 2);
grid->addWidget(prob_Label, 2, 2);
//delay, column 3
grid->addWidget(delayLCD, 0, 3);
//grid->addWidget(radioGroup, 1, 3);
grid->addLayout(vboxDelay, 1, 3);
grid->addWidget(delayLabel, 2, 3);
//ticks, column 4
grid->addWidget(tickLCD, 0, 4);
grid->addWidget(slider, 1, 4);
grid->addWidget(tickLabel, 2, 4);
//start
grid->addWidget(start, 1, 5);


window->setLayout(grid);
window->show();
}




void CSMASim::startClicked()
{

    //put the variables from the widgets into the private variables of CSMASim
    cableLength = cableLCD->intValue(); //parameter A
    packetLength = msgLCD->intValue();; //k value parameter B
    pval = (prob_LCD->value()/100.00); //parameter C
    tickSensingT = delayLCD->intValue();;// parameter D
    maxRun = tickLCD->intValue();;


    /*std::cout << "Cable Length: " << cableLength <<  std::endl;
    std::cout << "Packet Length: " << packetLength <<  std::endl;
    std::cout << "P Val: " << pval <<  std::endl;
    std::cout << "Sensing: " << tickSensingT <<  std::endl;
    std::cout << "Max Ticks: " << maxRun <<  std::endl;*/
    //run the CSMA program


    struct packet {
      string source;
      string destination;
      int length;
      int attempts;
      bool success;
    };

    struct station {
      string stationName;
      int stationNum;
      string currStatus;
      string nextStatus;
      int position;
      packet message;
    };

    int cableLen = cableLength; //cable length variable (A)
    int ticks = 0;
    int maxrun = maxRun; //execute for at least 3000 ticks (E)
    int packLen = packetLength; //k value random (B)
    float pVal = pval; //proability of generating message (C)
    int tickSensing = tickSensingT; //(D)

    /*------------------------*/
    //initiate data structures and input for each station and the carrier
    //structure per station, another structure for carrier(array)
    /*------------------------*/

    packet var [cableLen];
    packet * carrier[100]; // cable length variable (A)
    for (int i = 0; i < cableLen; i++) {
      carrier[i] = &var [i]; // assign the address
    }

    //declare station1-3 structs
    station * s1;
    station * s2;
    station * s3;

    s1 = new station();
    s1 -> position = 0;
    s1 -> stationName = "s1";
    s1 -> stationNum = 1;
    s2 = new station();
    s2 -> position = 3;
    s2 -> stationName = "s2";
    s2 -> stationNum = 2;
    s3 = new station();
    s3 -> position = 6;
    s3 -> stationName = "s3";
    s3 -> stationNum = 3;

    station * stations[3];

    stations[0] = new station;
    stations[0] = s1;
    stations[1] = new station;
    stations[1] = s2;
    stations[2] = new station;
    stations[2] = s3;

    ofstream a3_output;
    a3_output.open("a3_output.csv");


    while (ticks < maxrun) {
      /*------------------------*/
      //Check status of the carrier
      /*------------------------*/
      string carrierStatus; //busy or idle
      if (carrier[0] == 0) {
        carrierStatus = "IDLE";
      } else {
        carrierStatus = "BUSY";
      }

      //cout << "ticks: " << ticks << endl;
      /*CODE TO PRINT OUT THE CARRIER current status
         cout << "carrier: " << endl;
        for (int hi = 0; hi < cableLen; hi ++)
        {
        cout << "pos: " << hi << " src: " << carrier[hi].source
            << " len: " << carrier[hi].length
            << " dest: " << carrier[hi].destination << endl;

        }
      */

      for //(station si: stations)
      (int i = 0; i < 3; i++) {

        /*------------------------*/
        //Check status of every station
        /*------------------------*/
        int msgLen = stations[i] -> message.length;
        if (stations[i] -> message.source == stations[i] -> stationName &&
          (carrier[stations[i] -> position] -> length > 0 && carrier[stations[i] -> position + msgLen] -> length > 0)) {
          stations[i] -> currStatus = "Sending";

        } else if (stations[i] -> message.destination == stations[i] -> stationName &&
          (carrier[stations[i] -> position] -> length > 0 && carrier[stations[i] -> position + msgLen] -> length > 0)) {
          stations[i] -> currStatus = "Receiving";
          carrier[stations[i] -> position] -> success = 1;
        } else if (carrier[stations[i] -> position] -> length > 0 && carrier[stations[i] -> position + msgLen] -> length > 0) {
          stations[i] -> currStatus = "Busy";
        } else {
          stations[i] -> currStatus = "Idle";
        }

        int k;
        int j;
        packet message;
        if (stations[i] -> currStatus == "Idle") {
          //randomly generate a message
          float p = (float) arc4random() / RAND_MAX; //probability message will be sent

          j = (arc4random() % 3) + 1;

          k = (arc4random() % packLen) + 1; //size of message

          if (stations[i] -> stationNum == j || p > pVal) {
            //to remove the chance that the TO and FROM are the same station
            // j = (arc4random() % 3) + 1;
            // break;
          } else if (p < pVal) {
            // taken p value, packet is accepted
            //add the message into the carrier position at the Sj position
            message.source = stations[i] -> stationNum;
            message.length = k;
            /*------------------------*/
            //Determine if the destination is able to receive the packet
            /*------------------------*/
            if (j == 1) {
              message.destination = "s1";
              if (s1 -> currStatus == "Idle") {
                s1 -> message = message;
                s1 -> currStatus = "Receiving";
              } else {
                //sleep/sense
                continue;
              }
            } else if (j == 2) {
              message.destination = "s2";
              if (s2 -> currStatus == "Idle") {
                s2 -> message = message;
                s2 -> currStatus = "Receiving";
              } else {
                //sleep/sense
                continue;
              }
            } else if (j == 3) {
              message.destination = "s3";
              if (s3 -> currStatus == "Idle") {
                s3 -> message = message;
                s3 -> currStatus = "Receiving";
              } else {
                //sleep/sense
                continue;
              }
            }
            /*------------------------*/
            //When packet is sent, update the source station & carrier status
            /*------------------------*/
            stations[i] -> currStatus = "Initialize";
            stations[i] -> nextStatus = "Sending";
            carrierStatus = "BUSY";
            //add packet to carrier
            carrier[stations[i] -> position] = & message;
          }
          /*------------------------*/
          //print out to .CSV file and console
          /*------------------------*/
          if (stations[i] -> currStatus == "Initialize") {
            cout << ticks << ",S" << stations[i] -> stationNum << ",S" << j << "," << k << endl;

            a3_output << ticks << ",S" << stations[i] -> stationNum << ",S" << j << "," << k << endl;
          }
        } else { //carrier waiting for D paramter tick time
          // this.sleep(5);
          ticks += tickSensing;
          //goto secAtt;
        }
        /*------------------------*/
        /* Update stations status */
        /*------------------------*/
        if (stations[i] -> message.source == stations[i] -> stationName &&
          (carrier[stations[i] -> position] -> length > 0 && carrier[stations[i] -> position] -> length > 0)) {
          stations[i] -> currStatus = "Sending";

        } else if (stations[i] -> message.destination == stations[i] -> stationName &&
          (carrier[stations[i] -> position] -> length > 0 && carrier[stations[i] -> position] -> length > 0)) {
          stations[i] -> currStatus = "Receiving";
          carrier[stations[i] -> position] -> success = 1;
        } else if (carrier[stations[i] -> position] -> length > 0 && carrier[stations[i] -> position] -> length > 0) {
          stations[i] -> currStatus = "Busy";
        } else {
          stations[i] -> currStatus = "Idle";
        }

      }
      packet holder;
      /*------------------------*/
      /*Update the carrier array so packet is moved along cable*/
      /*------------------------*/
      for (int ti = 0; ti < cableLen; ti++) {

        if (carrier[ti] -> success == 1) {
          packet * temp = new packet();
          carrier[ti] = temp;
          //remove from the array
        } else {
          //if source == 2 move message up and down
          //else move message up in array
          packet * temp = new packet();
          holder = * carrier[ti];
          carrier[ti] = temp;

          if (ti + 1 < cableLen) {
            carrier[ti + 1] = & holder;
          }
          if (carrier[ti] -> source == "s2" && ti - 1 >= 0) {
            carrier[ti - 1] = & holder;
          }
        }

      }

      ticks++;
      if (ticks > maxrun) // end loop
        break;

    }

    a3_output.close();

    cout << "Output written to a3_output.csv" << endl;



}
