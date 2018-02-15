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
 * @file    Waypoint.cpp
 * @date    February, 2018
 * @license See above
 **/

#include "Waypoint.hpp"
#include <iostream>
#include <stdlib.h>
Waypoint::Waypoint(){
   name = "";
   address = "";
   ele = 0;
   lat = 0;
   lon = 0;
}

Waypoint::Waypoint(string aName, string aAddress, float aEle, float aLat, float aLon) {
   name = aName;
   address = aAddress;
   ele = aEle;
   lat = aLat;
   lon = aLon;
}

Waypoint::Waypoint(const Json::Value& jsonObj){
   string nameStr = "name";
   string address = "address";
   string eleStr = "ele";
   string latStr = "lat";
   string lonStr = "lon";
   Json::Value::Members mbr = jsonObj.getMemberNames();
   for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
      Json::Value jsonM = jsonObj[*i];
      if(nameStr.compare(*i)==0){
         name = jsonM.asString();
      }else if(address.compare(*i)==0){
         address = jsonM.asInt();
      }else if(eleStr.compare(*i)==0){
         ele = jsonM.asInt();
      }else if(latStr.compare(*i)==0){
         lat = jsonM.asInt();
      }else if(lonStr.compare(*i)==0){
         lon = jsonM.asInt();
      }
   }
}

Waypoint::Waypoint(string jsonString){
   string nameStr = "name";
   string addressStr = "address";
   string eleStr = "ele";
   string latStr = "lat";
   string lonStr = "lon";
   Json::Reader reader;
   Json::Value root;
   bool parseSuccess = reader.parse(jsonString,root,false);
   if(parseSuccess){
      Json::Value::Members mbr = root.getMemberNames();
      for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
         Json::Value jsonM = root[*i];
         if(nameStr.compare(*i)==0){
            name = jsonM.asString();
         }else if(addressStr.compare(*i)==0){
            address = jsonM.asString();
         }else if(eleStr.compare(*i)==0){
            ele = jsonM.asInt();
         }else if(latStr.compare(*i)==0){
            lat = jsonM.asInt();
         }else if(lonStr.compare(*i)==0){
            lon = jsonM.asInt();
         }
      }
   }else{
      cout << "Student constructor parse error with input: " << jsonString
           << endl;
   }
}

Waypoint::~Waypoint() {
   name = "";
   address = "";
}

string Waypoint::toJsonString(){
   string ret = "{}";
   Json::Value jsonLib;
   jsonLib["name"] = name;
   jsonLib["address"] = address;
   jsonLib["ele"] = ele;
   jsonLib["lat"] = lat;
   jsonLib["lon"] = lon;
   ret = jsonLib.toStyledString();
   return ret;
}

Json::Value Waypoint::toJson(){
   Json::Value jsonLib;
   jsonLib["name"] = name;
   jsonLib["address"] = address;
   jsonLib["ele"] = ele;
   jsonLib["lat"] = lat;
   jsonLib["lon"] = lon;

   return jsonLib;
}

void Waypoint::setValues(string aName, string aAddress,
           float aEle, float aLat, float aLon) {
   name = aName;
   address = aAddress;
   ele = aEle;
   lat = aLat;
   lon = aLon;
}

void Waypoint::print(){
  cout << "City " << name << " @ " << address << " lat: " << lat << " long: "
       << lon << " elevation: " << ele << endl;
}
