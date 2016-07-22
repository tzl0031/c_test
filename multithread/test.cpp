//
//  test.cpp
//  multithread
//
//  Created by TianLiu on 6/30/16.
//  Copyright © 2016 TianLiu. All rights reserved.
//



#include <mosquittopp.h>
#include <iostream>
#include "Communicator.h"
#include "FileUtil.h"
#include "Sensor.h"
#include <sys/time.h>
//#include "create_json.h"



using namespace std;

class Communicator* comm = NULL;
Json::Value root;
Json::FastWriter fw;


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
		gettimeofday(&start, NULL);
		for (int i = 0; i < numberOfSensor; i++) {
//instantiate sensor object
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
//			cout << comm->send_message(j) << endl;
		}
			sleep(1);
	}
	return 0;
}


















//    }













//RaspberryOSIOClient * client = 0;
//
//
///*
// * Handler for incoming messages.
// */
//void onMessage(char* topic, char* payload, unsigned int length)
//{
//  char* clearMessage = new char[length + 1];
//  memset(clearMessage, 0, length + 1);
//  memcpy(clearMessage, payload, length);
//
//  cout << "Topic: " << topic << ", message: " << clearMessage;
//
//  // Break communication cycle when receive "exit".
//  if (strcmp(clearMessage, "exit") == 0)
//  {
//    client->disconnect();
//  }
//}
//
//int main()
//{
//  // Our raspberry MQTT client instance.
//  client = new RaspberryOSIOClient("gizz", "80", "7E4ZHOQJ", onMessage());
//
//  cout << "Client started. When \"exit\" message is received, the program will publish test message to topic and finish its work." << endl;
//
//  // Subscribe for topic.
//  bool result = client->subscribe("/users/gizz/test");
//
//  cout << "Subscribing result: " << (result == true ? "success" : "error") << endl;
//
//  // Main communication loop to process messages.
//  do
//  {
//    // Save loop iteration state (TRUE if all ok).
//    result = client->loop();
//    // Just show that we are alive.
//    cout << ".\r\n";
//    // Wait 1 second.
//    sleep(1);
//  }
//  while(result == true); // Break if loop returned FALSE.
//
//  cout << "Publishing \"hi!\" message: ";
//  result = client->publish("/users/gizz/test", "hi!");
//
//  cout << (result == true ? "success" : "error") << endl;
//
//  delete client;
//
//  cout << "Bye!" << endl;
//
//  return 0;
//}
