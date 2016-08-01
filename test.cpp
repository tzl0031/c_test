//
//  test.cpp
//  multithread
//
//  Created by TianLiu on 6/30/16.
//  Copyright © 2016 TianLiu. All rights reserved.
//



#include "mosquittopp.h"
#include <iostream>
#include "Communicator.h"
#include "FileUtil.h"
#include "Sensor.h"
#include <sys/time.h>
#include "create_json.h"



using namespace std;

class Communicator* comm = NULL;

Json::StreamWriterBuilder fw;


int main(int argc, char *argv[]) {
	int port;
	int numberOfSensor;
	int msg_count;
	struct timeval start;
	struct timeval end;
	__time_t diff;
	FileUtil fileUtil;
//	convert string to const char
	const char *host = fileUtil.getHost().c_str();
	port = fileUtil.getPort();
//	convert size_t to int
	numberOfSensor = static_cast<int>(fileUtil.getNumberOfSensor());
	const char *rpi_id = fileUtil.getRpiID().c_str();
//	create_json_file();
	comm = new Communicator(rpi_id, host, port);
	msg_count = 1;
	while(1) {
		
		for (int i = 0; i < numberOfSensor; i++) {
//instantiate sensor objectg
Json::Value root;
			gettimeofday(&start, NULL);
			Sensor mySensor(i);
//	store data in json
			root["rPi_id"] = fileUtil.getRpiID();
			root["temperature"] = mySensor.getTemperature();
			root["sensor_id"] = mySensor.getSensorID();
			root["clock"] = mySensor.getClock();
			root["date"] = mySensor.getDate();
			root["rod_id"] = "unassigned";
			root["msg_index"] = msg_count;
			cout << fw.write(root);
//			cout << sizeof(root) << endl;
			string json = fw.write(root);
			msg_count++;
			const char *j = json.c_str();
//			publish to broker
			comm->send_message(j);
			gettimeofday(&end, NULL);
			diff = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
			cout << "the difference is " << diff << "ms" << endl;
			cout << comm->send_message(j) << endl;
		}
			sleep(1);
	}
	return 0;
}









