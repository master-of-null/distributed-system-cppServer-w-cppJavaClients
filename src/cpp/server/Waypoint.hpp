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
 * @file    Waypoint.hpp
 * @date    February, 2018
 * @license See above
 **/

#include <string>
#include <cmath>
#include <json/json.h>
#include <vector>

using namespace std;

class Waypoint {
protected:
public:

   // string name;
   string name, address;
   // int studentid;
   float ele, lat, lon;

   // vector<string> takes;

   Waypoint();
   Waypoint(const Json::Value& jsonObj);
   Waypoint(string jsonString);
   Waypoint(string aName, string aAddress, float aEle, float aLat, float aLon);
   ~Waypoint();
   string toJsonString();
   Json::Value toJson();
   void fromJson(Json::Value json);
   void setValues(string aName, string aAddress,
                  float aEle, float aLat, float aLon);
   void print();
};
