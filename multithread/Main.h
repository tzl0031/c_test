//
//  Main.cpp
//  multithread
//
//  Created by TianLiu on 6/27/16.
//  Copyright © 2016 TianLiu. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <io.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <istream>
#include <dirent.h>
#include <stdlib.h>
#include "file.h"
#include <thread>
#include <mutex>

using namespace std;


//
//void getFolders(string path, vector<string>& files);
//
//
//vector<string> getFolders (const string &path)


//instantiate Sensor and Communicator class

// init with default values

void sensor::init()
{
    index = 1
}


Communicator * Comm;
comm = new Communicator("1", );
dest_path = "/Users/TianLiu/devices/28-02150307f3ff/w1_slave";

void com_function()
{
    while(1)
    {
    ifstream fd (dest_path, ifstream::binary);	// Open Shared Memory
//    res	= read(fd, tstr, FILE_LENGTH);
        while(getline(fd, record))
        {
            comm->publish(NULL, "sensors", strlen(record), record);
        }
        
//    for (i=0; i<FILE_LENGTH; ++i)					// Read data from shared memory
//    {
//        if ((tstr[i]==':') && (i<100))
//        {
////            copy first i characters of tstr to strCounter
//            strncpy(strCounter, tstr, i);
//            Counter = atol(strCounter);
//            break;
//        }
        
    }
//    
//    if (Counter != preCounter)					// Check whether this data is new
//    {
//        cout << ("%s", tstr);
//        preCounter=Counter;
//        
//        comm->publish(NULL, "sensors", strlen(tstr), tstr);	// Publish the data to MQTT topic "IGoT/sensors"
//    }
//    
    
    res = comm->loop();						// Keep MQTT connection
    if (res)
        comm->reconnect();
        usleep(1e5);
        }
}


//    create object
Sensor::sensor()
{
    init();
}

static mutex mutex;

int main(int argc, char *argv[])
{
// load file path
// instanciate sensors
    Sensor sensor();
    vector<thread> t;
    
//number of threads
    thread t(num_thread);
    num_thread = vector.len();
//    
    thread *t = new thread[num_thread - 1]
    //Launch a group of sensor threads
    for(int i = 0; i < num_thread; ++i)
    {

        t.push_back(thread(writeReading,i));
    }
//    launch a communicator thread
    t[num_thread].push_back(thread(com_function());
//    Use the main thread to do part of the work
    for (int i = num_thread -1, i < num_thread, ++i)
    {
        writeReading();
    }
    
    cout << "Launched from the main\n";
    for (auto &t : t)
    {
        t.join();
    }
    
    
//    write to file
//    clear memory
    delete [] t;
    

    return 0;
}


