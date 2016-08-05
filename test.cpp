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
#include <pthread.h>


using namespace std;
void *worker(void *arguments);

pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;	
int msg_count = 1;
class Communicator* comm = NULL;
FileUtil fileUtil;
const char *rpi_id = fileUtil.getRpiID().c_str();
Json::FastWriter fw;
Json::Value root;


int main(int argc, char *argv[]) {
	int port;
	int numberOfSensor;
//	struct timeval start;
//	struct timeval end;
//	convert string to const char
	const char *host = fileUtil.getHost().c_str();
	port = fileUtil.getPort();
//	convert size_t to int
	numberOfSensor = static_cast<int>(fileUtil.getNumberOfSensor());

	comm = new Communicator(rpi_id, host, port);
	pthread_t tid[numberOfSensor];


	while(msg_count < 1001) {
		for (int i=0; i<numberOfSensor; i++) {	
			int int_i = i;
			pthread_create(&tid[i], NULL, worker, (void*)int_i);
			}
		for(int i=0; i<numberOfSensor; i++){
			pthread_join(tid[i], NULL);			
			}
//	sleep(1);
	}
//	gettimeofday(&end, NULL);
//	diff = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec) /1000;
//	cout << "the difference is " << diff << "ms" << endl;
	return 0;
}


void *worker(void *arg)
{
	Sensor mySensor((int)arg);
	string temp_string = to_string(mySensor.getTemperature());
	root["rPi_id"] = rpi_id;
	root["temperature"] = temp_string;
	root["sensor_id"] = mySensor.getSensorID();
	root["clock"] = mySensor.getClock();
	root["date"] = mySensor.getDate();
	root["rod_id"] = "unassigned";
	root["msg_index"] = msg_count;
//	cout << fw.write(root);
	string json = fw.write(root);
	cout << mySensor.getMilisecond() << endl;
	const char *j = json.c_str();
//	publish to broker
	comm->send_message(j);
	pthread_mutex_lock(&qlock);
	msg_count++;
	pthread_mutex_unlock(&qlock);
	return NULL;
}





