/**
 * Copyright 2018 Gabriel Martinez,
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * <p/>
 * Purpose: C++ class which serves as server for a collection of students. This
 * class is part of a student collection distributed application that uses JsonRPC.
 * Meant to run on OSX, Debian Linux, and Raspberry Pi Debian.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author  Gabriel Martinez (gmarti53@asu.edu)
 * @version July 2016
 */

#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <json/json.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <csignal>

#include "waypointserverstub.h"
#include "WaypointLibrary.hpp"

using namespace jsonrpc;
using namespace std;

class WaypointServer : public waypointserverstub {
public:
   WaypointServer(AbstractServerConnector &connector, int port);
   virtual std::string serviceInfo();
   virtual bool saveToJsonFile();
   virtual bool resetFromJsonFile();
   virtual bool add(const Json::Value& mediaName);
   virtual bool remove(const std::string& mediaName);
   virtual Json::Value get(const std::string& mediaName);
   virtual Json::Value getNames();
   virtual double distanceEarth(double fromLatDeg, double fromLonDeg, double toLatDeg, double toLonDeg);
   virtual double bearing(double fromLatDeg, double fromLonDeg, double toLatDeg, double toLonDeg);
   
private:
   WaypointLibrary * library;
   int portNum;
};

WaypointServer::WaypointServer(AbstractServerConnector &connector, int port) :
                             waypointserverstub(connector){
   library = new WaypointLibrary();
   library->resetFromJsonFile("waypoints.json");
   portNum = port;
}

string WaypointServer::serviceInfo(){
   std::string msg =
                "Student collection management service.";
   stringstream ss;
   ss << portNum;
   cout << "serviceInfo called. Returning: Student collection management service."
        << endl;
   return  msg.append(ss.str());
}

bool WaypointServer::saveToJsonFile(){
   cout << "saving collection to waypoints.json" << endl;
   bool ret = library->saveToJsonFile("waypoints.json");
   return ret;
}

bool WaypointServer::resetFromJsonFile(){
   cout << "restoring collection from waypoints.json" << endl;
   bool ret = library->resetFromJsonFile("waypoints.json");
   return ret;
}

bool WaypointServer::add(const Json::Value& cityName) {
   cout << "Adding " << cityName << endl;
   bool ret = library->add(cityName);
   return ret;
}

bool WaypointServer::remove(const string& cityName) {
   cout << "Removing " << cityName << endl;
   bool ret = library->remove(cityName);
   return ret;
}

Json::Value WaypointServer::get(const string& cityName){
   cout << "Getting " << cityName << endl;
   return library->get(cityName);
}

Json::Value WaypointServer::getNames(){
   Json::FastWriter fw;
   std::string names = fw.write(library->getNames());
   cout << "Get names returning: " << names  << endl;
   return library->getNames();
}

double WaypointServer::distanceEarth(double fromLatDeg, double fromLonDeg, double toLatDeg, double toLonDeg){
   return library->distanceEarth(fromLatDeg, fromLonDeg, toLatDeg, toLonDeg);
}

double WaypointServer::bearing(double fromLatDeg, double fromLonDeg, double toLatDeg, double toLonDeg){
   return library->bearing(fromLatDeg, fromLonDeg, toLatDeg, toLonDeg);
}

void exiting(){
   std::cout << "Server has been terminated. Exiting normally" << endl;
   //ss.StopListening();
}

int main(int argc, char * argv[]) {
   // invoke with ./bin/studentRPCServer 8080
   int port = 8080;
   if(argc > 1){
      port = atoi(argv[1]);
   }
   HttpServer httpserver(port);
   WaypointServer ss(httpserver, port);
   std::atexit(exiting);
   auto ex = [] (int i) {cout << "server terminating with signal " << i << endl;
                         // ss.StopListening();
                         exit(0);
                         //return 0;
                        };
   // ^C
   std::signal(SIGINT, ex);
   // abort()
   std::signal(SIGABRT, ex);
   // sent by kill command
   std::signal(SIGTERM, ex);
   // ^Z
   std::signal(SIGTSTP, ex);
   cout << "Student collection server listening on port " << port
      //<< " press return/enter to quit." << endl;
        << " use ps to get pid. To quit: kill -9 pid " << endl;
   ss.StartListening();
   while(true){
   }
   //int c = getchar();
   ss.StopListening();
   return 0;
}
