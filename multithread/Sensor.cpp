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

    bool parsingSucessful = reader.parse(jsonFile, root);
// cout << parsingSucessful << endl;
    if (parsingSucessful)
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
	setClock();
	setDate();

}

//get sensor_id
string Sensor::getSensorID()
{
    return sensor_id;
}

//Set temperature

void Sensor::setTemperature()
{
//    string path = fileutil.getSensorFilePath(index) + "/w1_slave";
    string path = "/home/tian/devices/28-"+ folder_name +"/w1_slave" ;
//    cout << path << endl;
    char tempData[6];
    double temp;
    char *buf = new char[256];

    ifstream fd(path, ifstream::binary);
    if(!fd.is_open())
    {
        cerr << "Couldn't open the w1 device. Please check."<< endl;
        exit(1);
    }

    else
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
void Sensor:: setClock()
{
    time_t nowtime;
    nowtime = time(NULL);
    struct tm *local;
    local=localtime(&nowtime);
    char buf[80];
    strftime(buf, 80, "%H:%M:%S.00", local);
    clock = buf;
//    cout << clock << endl;
}
//
////getClock
string Sensor::getClock()
{
    return clock;
}

//setDate
void Sensor::setDate()
{
    time_t nowtime;
    nowtime = time(NULL);
    struct tm *local;
    local=localtime(&nowtime);
    char buf[80];
    strftime(buf, 80, "%Y-%m-%d", local);
    date = buf;
//    cout<< date << endl;
}

//getDate
string Sensor::getDate()
{
    return date;
}




//
//void Sensor::writeReading()
//{
//
//    ofstream sensorReadingFile(sensorFilePath, ios_base::out|ios_base::app);
//    if(sensorReadingFile.is_open())
//    {
//    sensorReadingFile << setw(5) << rpi_id << setw(5) << sensor_id << setprecision(3) << getTemperature() << setw(20) << getClock() << setw(20) << getDate() << endl;
//    }
//
//    if (sensorReadingFile.fail())
//    {
//        cerr << "Error on attempted write" << endl;
//        exit(1);
//    }
//
//}

//put into a JSON object and write to a json file.


//convert to JSON and write to a file
//void FileUtil::writeReading(int rpi_id, int sensor_id, string date, string clock, double temperature, string rod_id)
//{
//    mutex mutex;
//    Json::Value root;
//    Json::StyleWriter writer;
//
//    root["rpi_id"] = Json::value(rpi_id);
//    root["sensor_id"] = Json::value(sensor_id);
//    root["temperature"] = Json::value(temperature);
//    root["clock"] = Json::value(clock);
//    root["date"] = Json::value(date);
//    ofstream sensorReadingFile(sensorFilePath, ios_base::out|ios_base::app);
////lock, others wait
//    mutex.lock();
//    wrtier.write(sensorReadingFile, root);
//
//    //    else cout << "Error. Unable to open" << fname << endl;
//    mutex.unlock();
//    lock_guard<mutex> block_threads_until_finish_this_job(mutex);
//    f.close();
//}
//