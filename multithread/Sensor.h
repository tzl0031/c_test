//
//  main.cpp
//  multithread
//
//  Created by TianLiu on 6/23/16.
//  Copyright © 2016 TianLiu. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <ios>
#include <istream>
#include <json/json.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>
#include <mutex>
#include "FileUtil.h"
#include <sys/types.h>
#include <cstring>


using namespace std;

#ifndef SENSOR_H
#define SENSOR_H



class Sensor
{
public:
    Sensor(int i);   //initialize the sensor with a index

    string getSensorID();
    void setTemperature();
    double getTemperature();
    void setClock();
    string getClock();
    void setDate();
    string getDate();

    
//    string sensorFunction();
//    void writeReading();
//    void setSensorFilePath();
//    string getSensorFilePath();
    
  
private:
    double temperature;
    string date;
    string clock;
    string sensor_id;
    string folder_name;
    int index;

};

#endif
