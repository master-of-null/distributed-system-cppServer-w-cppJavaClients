/**
 * Copyright (c) 2018 Gabriel Martinez,
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
 * Purpose: C++ command line student collection client using json-rpc-cpp.
 * Meant to run on OSX, Debian Linux, and Raspberry Pi Debian.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author  Gabriel Martinez (gmarti53@asu.edu)
 * @file    WaypointTerminalClient.cpp
 * @date    January, 2018
 * @license See above
 **/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <json/json.h>
#include "waypointlibrarystub.h"
#include "../server/WaypointLibrary.hpp"

#include "WaypointGUI.cpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Multiline_Input.H>


// using namespace jsonrpc;



class Client : public WaypointGUI {

  static waypointlibrarystub wc;

   /** ClickedX is one of the callbacks for GUI controls.
    * Callbacks need to be static functions. But, static functions
    * cannot directly access instance data. This program uses "userdata"
    * to get around that by passing the instance to the callback
    * function. The callback then accesses whatever GUI control object
    * that it needs for implementing its functionality.
    */
 static void ClickedX(Fl_Widget * w, void * userdata) {
  std::cout << "You clicked Exit" << std::endl;
  exit(1);
}

static void ClickedRemoveWP(Fl_Widget * w, void * userdata, waypointlibrarystub wc) {
  Client* anInstance = (Client*)userdata;
  Fl_Input_Choice * theWPChoice = anInstance->frWps;
  std::string selected(theWPChoice->value());

  for (int i=0; i < theWPChoice->menubutton()->size(); i++ ) {
   const Fl_Menu_Item &item = theWPChoice->menubutton()->menu()[i];
         if(!selected.compare(item.label())){  // if they are equal
          theWPChoice->menubutton()->remove(i);
          std::cout << "removed " << selected << std::endl;
          break;
        }
      }
      if(theWPChoice->menubutton()->size()>0){
       theWPChoice->value(theWPChoice->menubutton()->menu()[0].label());
     }else{
       theWPChoice->value("");
     }
     wc.remove(selected);
   }

   static void ClickedAddWP(Fl_Widget * w, void * userdata) {
      Client* anInstance = (Client*)userdata;
      Fl_Input_Choice * fromWPChoice = anInstance->frWps;
      Fl_Input_Choice * toWPChoice = anInstance->toWps;
      Fl_Input * theLat = anInstance->latIn;
      Fl_Input * theLon = anInstance->lonIn;
      Fl_Input * theEle = anInstance->eleIn;
      Fl_Input * theName = anInstance->nameIn;
      Fl_Multiline_Input *theAddr = anInstance->addrIn;

      std::string lat(theLat->value()), lon(theLon->value()), ele(theEle->value());
      double latNum = atof(lat.c_str());  //convert from string to double
      double lonNum = atof(lon.c_str());
      double eleNum = atof(ele.c_str());

      std::string name(theName->value());
      string addr(theAddr->value());
      
      std::string jsonStr = "{\"name\":\""+name+
        "\",\"address\":\""+addr+"\""+
        "\",\"ele\":\"\""+
        "\",\"lat\":\"\""+
        "\",\"lon\":\"\"}";

      Json::Value root;
      Json::Reader reader;
      reader.parse(jsonStr.c_str(), root);

      root["ele"] = eleNum;
      root["lat"] = latNum;
      root["lon"] = lonNum;

      wc.add(root);

      fromWPChoice->add(name.c_str());
      toWPChoice->add(name.c_str());
      fromWPChoice->value(name.c_str());
   }

  static void ClickedModifyWP(Fl_Widget *w, void *userdata) {
      Client* anInstance = (Client*)userdata;
      Fl_Input_Choice * fromWPChoice = anInstance->frWps;
      Fl_Input_Choice * toWPChoice = anInstance->toWps;
      Fl_Input * theLat = anInstance->latIn;
      Fl_Input * theLon = anInstance->lonIn;
      Fl_Input * theEle = anInstance->eleIn;
      Fl_Input * theName = anInstance->nameIn;
      Fl_Multiline_Input *theAddr = anInstance->addrIn;

      std::string lat(theLat->value()), lon(theLon->value()), ele(theEle->value());
      double latNum = atof(lat.c_str());  //convert from string to double
      double lonNum = atof(lon.c_str());
      double eleNum = atof(ele.c_str());

      std::string name(theName->value());
      string addr(theAddr->value());
      
      std::string jsonStr = "{\"name\":\""+name+
        "\",\"address\":\""+addr+"\""+
        "\",\"ele\":\"\""+
        "\",\"lat\":\"\""+
        "\",\"lon\":\"\"}";

      Json::Value root;
      Json::Reader reader;
      reader.parse(jsonStr.c_str(), root);

      root["ele"] = eleNum;
      root["lat"] = latNum;
      root["lon"] = lonNum;

      wc.add(root);

      fromWPChoice->add(name.c_str());
      toWPChoice->add(name.c_str());
      fromWPChoice->value(name.c_str());
  }

  static void SelectedFromWP(Fl_Widget * w, void * userdata) { // done
    Client* anInstance = (Client*)userdata;
    Fl_Input_Choice * frWps = anInstance->frWps;
    Fl_Input * theLat = anInstance->latIn;
    Fl_Input * theLon = anInstance->lonIn;
    Fl_Input * theEle = anInstance->eleIn;
    Fl_Input * theName = anInstance->nameIn;
    Fl_Multiline_Input *theAddr = anInstance->addrIn;

    std::string selected(frWps->value());
    std::cout << "You selected from waypoint "
    << selected
    << std::endl;
    Json::Value wp = wc.get(selected);

    theName->value(wp["name"].asString().c_str());
    theAddr->value(wp["address"].asString().c_str());

    char latFormat[10], lonFormat[10], eleFormat[10];
    sprintf(latFormat,"%4.4f",wp["lat"].asDouble());
    sprintf(lonFormat,"%4.4f",wp["lon"].asDouble());
    sprintf(eleFormat,"%4.4f",wp["ele"].asDouble());
    theLat->value(latFormat);
    theLon->value(lonFormat);
    theEle->value(eleFormat);     
  }

  static void SelectedToWP(Fl_Widget * w, void * userdata) {
    Client* anInstance = (Client*)userdata;
    Fl_Input_Choice * toWps = anInstance->toWps;
    Fl_Input * theLat = anInstance->latIn;
    Fl_Input * theLon = anInstance->lonIn;
    Fl_Input * theEle = anInstance->eleIn;
    Fl_Input * theName = anInstance->nameIn;
    Fl_Multiline_Input *theAddr = anInstance->addrIn;

    std::string selected(toWps->value());
    std::cout << "You selected from waypoint "
    << selected
    << std::endl;
    Json::Value wp = wc.get(selected);

    theName->value(wp["name"].asString().c_str());
    theAddr->value(wp["address"].asString().c_str());

    char latFormat[10], lonFormat[10], eleFormat[10];
    sprintf(latFormat,"%4.4f",wp["lat"].asDouble());
    sprintf(lonFormat,"%4.4f",wp["lon"].asDouble());
    sprintf(eleFormat,"%4.4f",wp["ele"].asDouble());
    theLat->value(latFormat);
    theLon->value(lonFormat);
    theEle->value(eleFormat);
  }



  static void printWaypoints() {
    Json::Value names = wc.getNames();
    std::cout << names << std::endl;
  }

  static void ClickedImportFile(Fl_Widget *w, void * userdata) {
    resetNames((void*) userdata);
    std::cout << "Starting import from waypoints.json file from Server" << std::endl;
  }

  static void ClickedExportFile(Fl_Widget *w, void *userdata) {
    if(wc.saveToJsonFile())
      std::cout << "Exported to file: waypoints.json" << std::endl;
  }

  static void getDistanceAndBearing(Fl_Widget *w, void *userdata) {
    Client* anInstance = (Client*)userdata;
    Fl_Input_Choice * frWps = anInstance->frWps;
    Fl_Input_Choice * toWps = anInstance->toWps;
    Fl_Input * distBear = anInstance->distBearIn;
    double fromLat, fromLon, toLat, toLon;
    Json::Value frWp = wc.get(frWps->value());
    Json::Value toWp = wc.get(toWps->value());

    fromLat = frWp["lat"].asDouble();
    fromLon = frWp["lon"].asDouble();
    toLat = toWp["lat"].asDouble();
    toLon = toWp["lon"].asDouble();

    double distance = wc.distanceEarth(fromLat, fromLon, toLat, toLon);
    char distFormat[10];
    sprintf(distFormat,"%4.2f",distance);
    string dist(distFormat);
    double degree = wc.bearing(fromLat, fromLon, toLat, toLon);
    char degFormat[10];
    sprintf(degFormat, "%4.2f", degree);
    string deg(degFormat);

    string whole = dist + "km at " + deg + " degrees";
    
    distBear->value(whole.c_str());
    
  }

  static void resetNames(void * userdata) {
    Json::Value names = wc.getNames();
    Client* anInstance = (Client*)userdata;
    Fl_Input_Choice * fromWPChoice = anInstance->frWps;
    Fl_Input_Choice * toWPChoice = anInstance->toWps;

    for(auto itr : names)
    { // for each JSON Value do:
      std::cout << "hey there " << itr.asString() << endl;
      toWPChoice->add(itr.asString().c_str());
      fromWPChoice->add(itr.asString().c_str());
    }
  }


public:
  Client(const char * name = 0, string host = "http://127.0.0.1:8080") : WaypointGUI(name) {
    // connect to server
    jsonrpc::HttpClient httpclient(host);
    waypointlibrarystub wc(httpclient);
    std::cout << "Connecting to host " << host << std::endl;
    resetNames((void*)this);

    removeWPButt->callback(ClickedRemoveWP, (void*)this, wc);
    addWPButt->callback(ClickedAddWP, (void*)this);
    modWPButt->callback(ClickedModifyWP, (void*)this);
    frWps->callback(SelectedFromWP, (void*)this);
    toWps->callback(SelectedToWP, (void*)this);
    getLatLonButt->callback(ClickedImportFile, (void*)this);
    exportJson->callback(ClickedExportFile, (void*)this);
    distBearButt->callback(getDistanceAndBearing, (void*)this);
    callback(ClickedX);
  }
};

int main(int argc, char*argv[]) {

  string host = "http://127.0.0.1:8080";
  if(argc>1){
     host = string(argv[1]);
  }
  // jsonrpc::HttpClient httpclient(host);
  // waypointlibrarystub wc(httpclient);


  Client cm("C++ Waypoint Browser", host);
  return (Fl::run());
}

