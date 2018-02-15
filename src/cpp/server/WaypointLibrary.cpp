/**
 * Copyright (c) 2018 Tim Lindquist,
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 * <p/>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * <p/>
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * <p/>
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * <p/>
 * Purpose: C++ class to represent a student. This class is part of a
 * student collection distributed application that uses JsonRPC.
 * Meant to run on OSX, Debian Linux, and Raspberry Pi Debian.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * @author  Gabriel Martinez (gmarti53@asu.edu)
 * @file    WaypointLibrary.cpp
 * @date    February, 2018
 * @license See above
 **/

#include "WaypointLibrary.hpp"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>

#define PI 3.14159265

using namespace std;
WaypointLibrary::WaypointLibrary(){
  resetFromJsonFile("waypoints.json");
}

WaypointLibrary::~WaypointLibrary() {
  //cout << "student collection destructor.\n";
  library.clear();
}

bool WaypointLibrary::resetFromJsonFile(string jsonFileName){
  bool ret = false;
  Json::Reader reader;
  Json::Value root;
  std::ifstream json(jsonFileName.c_str(), std::ifstream::binary);
  bool parseSuccess = reader.parse(json,root,false);
  if(parseSuccess){
    Json::Value::Members mbr = root.getMemberNames();
    for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
      cout << *i << " " << endl; // comment
      Json::Value jsonMedia = root[*i];
      Waypoint * aWaypoint = new Waypoint(jsonMedia);
      library[*i] = *aWaypoint;
      cout << "adding "; // comment
      aWaypoint->print(); // comment
    }
    ret = true;
  }
  return ret;
}

bool WaypointLibrary::saveToJsonFile(string jsonFileName){
  bool ret = false;
  Json::Value jsonLib;
  for(std::map<string,Waypoint>::iterator i = library.begin();
                               i != library.end(); i++){
    string key = i->first;
    //cout << key << " " << endl;
    Waypoint aWaypoint = library[key];
    Json::Value jsonStudent = aWaypoint.toJson();
    jsonLib[key] = jsonStudent;
  }
  ret = true;
  Json::StyledStreamWriter ssw("  ");
  std::ofstream jsonOutFile(jsonFileName.c_str(), std::ofstream::binary);
  ssw.write(jsonOutFile, jsonLib);
  return ret;
}

bool WaypointLibrary::add(const Json::Value& aWaypointJson){
  bool ret = false;
  Waypoint aWaypoint(aWaypointJson);
  // The map container does not allow duplicates so adding will replace existing
  // value with new Student instance.
  aWaypoint.print(); // comment
  library[aWaypoint.name] = aWaypoint;
  return true;
}

bool WaypointLibrary::remove(string aName){
  bool ret = false;
  // does the library contain this student? if so remove, if not return false
  if(library.count(aName)>0){
    library.erase(aName);
    ret = true;
  }
  return true;
}

Json::Value WaypointLibrary::get(string aName){
  Waypoint aStudent("{\"name\":\""+aName+" Unknown\"");
  if(library.count(aName)>0){
      aStudent = library[aName];
  }
  return aStudent.toJson();
}

Json::Value WaypointLibrary::getNames(){
  Json::Value ret(Json::arrayValue);
  vector<string> myVec;
  for(map<string,Waypoint>::iterator it = library.begin();
                         it != library.end(); ++it){
    myVec.push_back(it->first);
  }
  for(std::vector<string>::iterator it = myVec.begin(); it!=myVec.end();++it) {
    ret.append(Json::Value(*it));
  }
  return ret;
}

// double WaypointLibrary::distanceEarth(float fromLatDeg, float fromLonDeg, float toLatDeg, float toLonDeg) {
//   double earthRadiusKm = 6371.0;
//   double toLatRad, toLonRad, fromLatRad, fromLonRad, u, v;
  
//   fromLatRad = fromLatDeg * PI / 180;
//   fromLonRad = fromLonDeg * PI / 180;
//   toLatRad = toLatDeg * PI / 180;
//   toLonRad = toLonDeg * PI / 180;
  
//   u = sin((toLatRad - toLatRad)/2);
//   v = sin((toLonRad - fromLonRad)/2);
  
//   return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(fromLatRad) * cos(toLatRad) * v * v));
// }

// double WaypointLibrary::bearing(float fromLatDeg, float fromLonDeg, float toLatDeg, float toLonDeg) {
//     double toLatRad, toLonRad, fromLatRad, fromLonRad, y, x;
  
//   fromLatRad = fromLatDeg * PI / 180;
//   fromLonRad = fromLonDeg * PI / 180;
//   toLatRad = toLatDeg * PI / 180;
//   toLonRad = toLonDeg * PI / 180;

//   y = sin (toLonRad - fromLonRad) * cos (toLatRad);
//   x = cos (fromLatRad) * sin (toLatRad) - sin (fromLatRad) * cos (toLatRad) * cos ( toLonRad - fromLonRad );

//   double bearing = atan2 (y,x);
//   return bearing * 180 / PI;
// }

