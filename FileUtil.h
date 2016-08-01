//FileUtil//
//  FileUtil.h
//  multithread
//
//  Created by TianLiu on 6/30/16.
//  Copyright © 2016 TianLiu. All rights reserved.
//


#include <vector>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <stdlib.h>
#include <json/json.h>


using namespace std;

#ifndef FILEUTIL_H
#define FILEUTIL_H
class FileUtil
{
public:
    FileUtil();
    void setFolderPath(int i);
    string getFolderPath();
    size_t getNumberOfSensor();
	void load_configuration();
	int getPort();
	string getHost();
	string getRpiID();


private:
	string host;
	int port;
	string rpi_id;
	string folder_path;
    vector<string> files;
    size_t numberOfSensor;

};


#endif