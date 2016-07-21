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



using namespace std;

class Communicator* comm = NULL;
void create_json_file();
Json::Value root;
Json::FastWriter fw;
Json::StyledWriter sw;


int main(int argc, char *argv[]) {
	int port;
	int numberOfSensor;
	int msg_count;
	FileUtil fileUtil;
//	convert string to const char
	const char *host = fileUtil.getHost().c_str();

	port = fileUtil.getPort();
//	convert size_t to int
	numberOfSensor = static_cast<int>(fileUtil.getNumberOfSensor());


//define a struct
//	struct record {
//		string rpi_id;
//		string sensor_id;
//		double temperature;
//		string clock;
//		string date;
//	};
	const char *rpi_id = fileUtil.getRpiID().c_str();
	comm = new Communicator(rpi_id, host, port);
	msg_count = 1;
	while(1) {
		for (int i = 0; i < numberOfSensor; i++) {
//instantiate sensor object
			Sensor mySensor(i);
// store data in struct
//		record myRecord;
//		myRecord.clock = mySensor.getClock();
//		myRecord.date = mySensor.getDate();
//		myRecord.rpi_id = mySensor.getRpiID();
//		myRecord.sensor_id = mySensor.getSensorID();
//		myRecord.temperature = mySensor.getTemperature();
//
////		cout << myRecord.clock << endl;
////		cout << myRecord.date << endl;
////		cout << myRecord.rpi_id << endl;
////	}   //


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
//			cout << comm->send_message(j) << endl;
		}
			sleep(1);
	}
	return 0;
}




void create_json_file() {


	root["rPi_id"] = Json::Value("1");
	root["broker_address"] = Json::Value("131.204.27.59");
	root["broker_port"] = Json::Value("1883");
	root["0000071ca298"] = Json::Value("A-a-01");
	root["0115725e36ff"] = Json::Value("A-a-02");
	root["02150396cfff"] = Json::Value("A-a-03");
	root["011564a36fff"] = Json::Value("A-b-01");
	root["0215034deaff"] = Json::Value("A-b-02");
	root["02150307f3ff"] = Json::Value("A-b-03");
	root["000007291b96"] = Json::Value("A-c-01");
	root["011572c7b4ff"] = Json::Value("b-a-01");
	root["011572598eff"] = Json::Value("b-a-02");
	root["0215038ee0ff"] = Json::Value("b-a-03");
	root["011572595bff"] = Json::Value("b-b-01");
	root["011563ded9ff"] = Json::Value("b-b-02");
	root["02150394f9ff"] = Json::Value("b-b-03");
	root["0215034f82ff"] = Json::Value("b-c-01");
	root["021564a871ff"] = Json::Value("C-a-01");
	root["031563c69bff"] = Json::Value("C-a-02");
	root["011572e07eff"] = Json::Value("C-a-03");
	root["0115729670ff"] = Json::Value("C-b-01");
	root["011572cf16ff"] = Json::Value("C-b-02");
	root["011572e059ff"] = Json::Value("C-b-03");
	root["011572de44ff"] = Json::Value("C-c-01");
	root["0115729867ff"] = Json::Value("D-a-01");
	root["021564a81cff"] = Json::Value("D-a-02");
	root["011572601eff"] = Json::Value("D-a-03");
	root["0215038da6ff"] = Json::Value("D-b-01");
	root["021503975bff"] = Json::Value("D-b-02");
	root["0215039444ff"] = Json::Value("D-b-03");
	root["02150397cfff"] = Json::Value("D-c-01");

	cout << fw.write(root) << endl;
	ofstream os;
	os.open("config.json");
	os << sw.write(root);
	os.close();
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
