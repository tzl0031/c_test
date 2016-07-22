//
// Created by tian on 7/21/16.
//


#include <json/json.h>
#include <iostream>
#include <fstream>

using namespace std;

void create_json_file() {
	Json::Value root;
	Json::FastWriter fw;
	Json::StyledWriter sw;

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

	root["0000071c9ad1"] = Json::Value("E-a-01");
	root["00000729b788"] = Json::Value("E-a-02");
	root["00000729a35b"] = Json::Value("E-a-03");
	root["00000729c160"] = Json::Value("E-b-01");



//	cout << fw.write(root) << endl;
	ofstream os;
	os.open("/home/tian/c_test/multithread/config.json");
	os << sw.write(root);
	os.close();
}

