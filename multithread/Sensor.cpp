//
// Created by tian on 7/18/16.
//


#include "Sensor.h"
//The constructor initialize sensor_id, temperature, clock and date
Sensor::Sensor(int i):index(i)
{
    Json::Reader reader;
    Json::Value root;
    FileUtil fileUtil;
    fileUtil.setFolderPath(index);
    folder_name = fileUtil.getFolderPath();
//    cout << folder_name<< endl;
    ifstream jsonFile;
    jsonFile.open("config.json", ios::binary);
//
    if(!jsonFile.is_open()) {
        cout << "Cannot open the json file." << endl;
    }

    bool parsingSuccessful = reader.parse(jsonFile, root);
// cout << parsingSucessful << endl;
    if (parsingSuccessful)
    {
//        initialize sensor_id
        sensor_id = root[folder_name].asString();
//        cout << sensor_id << endl;
    }
    else{
        cout << "cannot parse configuration." << endl;
    };
	jsonFile.close();
	setTemperature();
	setClockDate();

}

//get sensor_id
string Sensor::getSensorID()
{
    return sensor_id;
}

//Set temperature
void Sensor::setTemperature()
{
	string path = "/sys/bus/w1/devices/28-" + folder_name + "/w1_salve";
//    string path = "/home/tian/devices/28-"+ folder_name +"/w1_slave" ;
//    cout << path << endl;
    char tempData[6];
    double temp;
    char *buf = new char[256];

    ifstream fd(path, ifstream::binary);
    if(!fd.is_open())
    {
        cerr << "Couldn't open the w1 device. Please check."<< endl;
        exit(1);
    }else
    {
        fd.read(buf, 256);
        strncpy(tempData, strstr(buf, "t=") + 2, 5);
        temp = strtof(tempData, NULL);
        temp = temp / 1000;
    }
    fd.close();
    delete[] buf;
    temperature = temp;
//    cout << temperature;
}


double Sensor::getTemperature()
{
    return temperature;
}


//setClock
void Sensor:: setClockDate()
{
    time_t nowtime;
    nowtime = time(NULL);
    struct tm *local;
    local = localtime(&nowtime);
    char buf_clock[80];
    char buf_date[80];
    strftime(buf_clock, 80, "%H:%M:%S.00", local);
    strftime(buf_date, 80, "%Y-%m-%d", local);
    clock = buf_clock;
    date = buf_date;
//    cout << clock << endl;
}

//getClock
string Sensor::getClock()
{
    return clock;
}

//getDate
string Sensor::getDate()
{
    return date;
}

