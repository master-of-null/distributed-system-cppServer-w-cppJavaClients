#include "Waypoint.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>

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
 * 
 * Purpose: demonstrate Json serialization in C++
 * Ser321 Foundations of Distributed Applications
 * @author Gabriel Martinez gmarti53@asu.edu
 * @version July 2018
 */
Waypoint::Waypoint(){
   name = "Null";
   address = "Null";
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

Waypoint::~Waypoint() {
   //cout << "User destructor.\n";
   name="";
   address="";
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
