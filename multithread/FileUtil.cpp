//
// Created by tian on 7/18/16.
//
#include "FileUtil.h"


//get all folder path under base_dir
FileUtil::FileUtil()
{
    vector<string> temp;
    struct dirent *ptr;
    DIR *pDIR;
//	ubuntu dir
//    string base_dir = "/home/tian/devices";
//	raspbian dir
    string base_dir = "/sys/bus/w1/devices";

    pDIR = opendir(base_dir.c_str());

    while(NULL != (ptr = readdir(pDIR)) )
    {
        if (ptr->d_name[0] == '.')
            continue;
        temp.push_back(ptr->d_name);
    }
    closedir(pDIR);

//    for(int i = 0; i < temp.size(); i++)
//    {
//        cout << temp[i] << endl;
//    }
    files = temp;
    numberOfSensor = files.size();
	load_configuration();
}

//return the the foldername for the ith sensor
void FileUtil::setFolderPath(int i)
{
    folder_path = files[i].substr(3);
}

string FileUtil::getFolderPath()
{
    return folder_path;

}

//return the number of sensors
size_t FileUtil::getNumberOfSensor()
{
    return numberOfSensor;
}


void FileUtil::load_configuration() {
    Json::Value root;
    Json::Reader reader;
    ifstream jsonFile;
    jsonFile.open("config.json", ios::binary);
//
    if (!jsonFile.is_open()) {
        cout << "Cannot open the json file." << endl;
    }

    bool parsingSuccessful = reader.parse(jsonFile, root);
//    cout << parsingSucessful << endl;
    if (parsingSuccessful) {
//        initialize rpi_id and sensor_id
        host = root["broker_address"].asString();
        port = root["broker_port"].asInt();
        rpi_id = root["rPi_id"].asString();
    }
    else {
        cout << "cannot parse configuration." << endl;
    };
    jsonFile.close();
}

int FileUtil::getPort(){
	return port;
}

string FileUtil::getHost() {
	return host;
}

// get rpi_id
string FileUtil::getRpiID()
{
    return rpi_id;
}

