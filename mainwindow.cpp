
/*
#include "mainwindow.h"
#include <QListWidget>
#include <QPushButton>
#include <fstream>

#include <iostream>

#include <array>

#include <string>
 //#define M 7
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{
}


void MainWindow::clicked()
{

    //create station struct



      struct packet {
        string source;
        string destination;
        int length;
      };

      struct station {
        string stationName;
        int stationNum;
        string currStatus;
        string nextStatus;
        int position;
        packet message;
      };
      int cableLen; //cable length variable (A)
      int ticks = 0;
      int maxrun = 4000;//numticks;//4000; //execute for at least 3000 ticks (E)
      int msgLen = 5; //k value random (B)
      float pVal = .1; //proability of generating message (C)
      int minTicksSensing; //(D)
      int maxTicksSensing; //(D)
      //postion1 = activity, postion2 = message
      //initiate data structures and input for each station and the carrier
      //structure per station, another structure for carrier(array)

      //int M = 7; //cable length
      //packet carrierLeft [7];
      //packet carrierRight [7];
      packet carrier[7]; //7 is the cable length variable (A)
      //declare station1-3 structs
      station s1; // = new station("s1", 1, "", "", 0, NULL);//pos. 0 in carrier array
      station s2; // = new station("s2", 2, "", "", 3, NULL);//pos. 3 in carrier array
      station s3; // = new station("s3", 3, "", "", 6, NULL);//pos. 6 in carrier array

      s1.position = 0;
      s1.stationName = "s1";
      s1.stationNum = 1;
      s2.position = 3;
      s2.stationName = "s2";
      s2.stationNum = 2;
      s3.position = 6;
      s3.stationName = "s3";
      s3.stationNum = 3;

      station stations[3] = {
        s1,
        s2,
        s3
      };

      ofstream a1p2_output;
      a1p2_output.open("a1p2_output.csv");

      while (ticks < maxrun) {
        //update the carrier array so that each message packet is moved over 1
        packet emptyMessage;

        packet msg;
        //make another array and copy the items over into the correct position
        //sensing the carrier
        packet carrierTemp[7];
        for (int c = 0; c < sizeof(carrier) / sizeof(packet) - 1; c++) {
          msg = carrier[c];
          msg.length = msg.length - 1;
          //  cout << "msg : src " << msg.source << " dest " << msg.destination << endl;
          //check to see if something in the array, if so, do the below movements
          if (msg.source != "") {

            if (msg.source == "s1") {
              //    carrierTemp[c] = emptyMessage;
              carrierTemp[c + 1] = msg;
              if (msg.length > 1) {
                carrierTemp[c] = msg;
              }

            } else if (msg.source == "s3") {
              //   carrierTemp[c] = emptyMessage;
              carrierTemp[c - 1] = msg;
              if (msg.length > 1) {
                carrierTemp[c] = msg;
              }

            } else if (msg.source == "s2") {
              // carrierTemp[c] = emptyMessage;
              carrierTemp[c + 1] = msg;
              carrierTemp[c - 1] = msg;
              if (msg.length > 1) {
                carrierTemp[c] = msg;
              }

            }
          }
        }

        std::copy(carrierTemp, carrierTemp + 7, carrier);
        //  cout << "ticks: " << ticks << endl;
        /*CODE TO PRINT OUT THE CARRIER current status
           cout << "carrier: " << endl;
          for (int hi = 0; hi < sizeof(carrier) / sizeof(packet) - 1; hi ++)
          {
          cout << "pos: " << hi << " src: " << carrier[hi].source
              << " len: " << carrier[hi].length
              << " dest: " << carrier[hi].destination << endl;

          }


        for (station si: stations)
        //(int i = 0; i < stations.len(); i++)
        {
          //cout << "in foreach loop: " << si.stationName << endl;
          if (si.message.source.empty()) {
            si.currStatus = "Idle";
          } else if (si.message.source == si.stationName) {
            si.currStatus = "Sending";
          } else if (si.message.destination == si.stationName) {
            si.currStatus = "Receiving";
          }

          if (carrier[si.position].source.empty()) {
            si.currStatus = "Idle";
          } else if (carrier[si.position].source == si.stationName) {
            si.currStatus = "Sending";
          } else if (carrier[si.position].destination == si.stationName) {
            si.currStatus = "Receiving";
          }

          //          si.currStatus = nextStatus;

          int k;
          int j;
          packet message;
          if (si.currStatus == "Idle") {
            //randomly generate a message
            float p = (float) rand() / RAND_MAX; //probability a message will be sent?
            j = (rand() % 3) + 1; //Sj Pretend this is S1, how do we know where it is going to? (this is the starting station)
            //  int f = rand() % 4;  // is this also random number too? finishing station?
            k = (rand() % msgLen) + 1; //size of message; should this be a ratio of p to j?

            if (si.stationNum == j || p > pVal) //to remove the chance that the TO and FROM are the same station
              // j = (rand() % 3) + 1;
              // break;
              continue;

            if (p < pVal) {
              // taken
              //add the message into the carrier position at the Sj position
              //  carrier[stoi(stations[j])] = "s" + j + " - s" + f;
              // carrier[stoi(station[0])] =  's' + i +' - s' + j;
              message.source = si.stationNum; //(si.stationNum, j, k);
              message.length = k;

              if (j == 1) {
                message.destination = "s1";
              } else if (j == 2) {
                message.destination = "s2";
              } else if (j == 3) {
                message.destination = "s3";
              }
              si.currStatus = "Initialize";
              si.nextStatus = "Sending";
              carrier[si.position] = message;
            }

            //print out
            if (si.currStatus == "Initialize") {
              cout << ticks << ",S" << si.stationNum << ",S" << j << "," << k << endl;

              a1p2_output << ticks << ",S" << si.stationNum << ",S" << j << "," << k << endl;
            }
          }
          ///update messages on the carrier array
          if (si.stationNum == 2) {
            carrier[si.position + 1] = message;
            carrier[si.position - 1] = message;

          } else if (si.stationNum == 1) {
            carrier[si.position + 1] = message;
          } else if (si.stationNum == 3) {
            carrier[si.position - 1] = message;
          }

          /////update nextStatus  on stations
          ///

          if (carrier[si.position + 1].source.empty() ||
            carrier[si.position - 1].source.empty()) {
            si.nextStatus = "Idle";
          } else if (carrier[si.position + 1].source == si.stationName ||
            carrier[si.position - 1].source == si.stationName) {
            si.nextStatus = "Sending";
          } else if (carrier[si.position + 1].destination == si.stationName ||
            carrier[si.position - 1].destination == si.stationName) {
            si.nextStatus = "Receiving";
          }

          if (si.stationNum == 1) {
            s1 = si;
          } else if (si.stationNum == 2) {
            s2 = si;
          } else if (si.stationNum == 3) {
            s3 = si;
          }
        }
        ticks++;
        if (ticks > maxrun) // end loop
          break;

      }

      a1p2_output.close();

      cout << "Output written to a1p2_output.csv" << endl;

}
 */
