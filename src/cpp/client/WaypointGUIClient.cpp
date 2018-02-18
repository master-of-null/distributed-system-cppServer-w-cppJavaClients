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


using namespace jsonrpc;


WaypointLibrary *wpObjs = new WaypointLibrary();
string host = "http://127.0.0.1:8080";
// if(argc>1){
//    host = string(argv[1]);
// }
HttpClient httpclient(host);
waypointlibrarystub sc(httpclient);

class Client : public WaypointGUI {

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

   static void ClickedRemoveWP(Fl_Widget * w, void * userdata) {
      Client* anInstance = (Client*)userdata;
      Fl_Input_Choice * theWPChoice = anInstance->frWps;
      std::string selected(theWPChoice->value());
      std::cout << "You clicked the remove waypoint button with "
                << selected
                << std::endl;
      // Waypoint wp = wpObjs->get(selected);
      for (int i=0; i < theWPChoice->menubutton()->size(); i++ ) {
         const Fl_Menu_Item &item = theWPChoice->menubutton()->menu()[i];
         if(!selected.compare(item.label())){  // if they are equal
            theWPChoice->menubutton()->remove(i);
            wpObjs->remove(selected);
            std::cout << "removed " << selected << std::endl;
            anInstance->printWaypoints();
            break;
         }
      }
      if(theWPChoice->menubutton()->size()>0){
         theWPChoice->value(theWPChoice->menubutton()->menu()[0].label());
      }else{
         theWPChoice->value("");
      }
      
      sc.remove(selected);
  }

  //  static void ClickedAddWP(Fl_Widget * w, void * userdata) {
  //     Client* anInstance = (Client*)userdata;
  //     Fl_Input_Choice * fromWPChoice = anInstance->frWps;
  //     Fl_Input_Choice * toWPChoice = anInstance->toWps;
  //     Fl_Input * theLat = anInstance->latIn;
  //     Fl_Input * theLon = anInstance->lonIn;
  //     Fl_Input * theEle = anInstance->eleIn;
  //     Fl_Input * theName = anInstance->nameIn;
  //     Fl_Multiline_Input *theAddr = anInstance->addrIn;
      
  //     std::string lat(theLat->value()), lon(theLon->value()), ele(theEle->value());
  //     // what follows is not expedient, but shows how to convert to/from
  //     // double and formatted C and C++ strings.
  //     double latNum = atof(lat.c_str());  //convert from string to double
  //     double lonNum = atof(lon.c_str());
  //     double eleNum = atof(ele.c_str());
      
  //     char latFormat[10];
  //     sprintf(latFormat,"%4.4f",latNum);  //format the double into a C string
  //     std::string latCppStr(latFormat);   //convert formatted C str to C++ str

  //     std::string name(theName->value());
  //     string addr(theAddr->value());
      
  //     Waypoint newWP = Waypoint(name, addr, eleNum, latNum, lonNum);
  //     wpObjs->add(newWP);

  //     fromWPChoice->add(newWP.name.c_str());
  //     toWPChoice->add(newWP.name.c_str());
  //     fromWPChoice->value(newWP.name.c_str());
  //  }

  // static void ClickedModifyWP(Fl_Widget *w, void *userdata) {
  //     Client* anInstance = (Client*)userdata;
  //     Fl_Input_Choice * fromWPChoice = anInstance->frWps;
  //     Fl_Input_Choice * toWPChoice = anInstance->toWps;
  //     Fl_Input * theLat = anInstance->latIn;
  //     Fl_Input * theLon = anInstance->lonIn;
  //     Fl_Input * theEle = anInstance->eleIn;
  //     Fl_Input * theName = anInstance->nameIn;
  //     Fl_Multiline_Input *theAddr = anInstance->addrIn;

  //     string lat(theLat->value()), lon(theLon->value()), ele(theEle->value());
  //     // what follows is not expedient, but shows how to convert to/from
  //     // double and formatted C and C++ strings.
  //     double latNum = atof(lat.c_str());  //convert from string to double
  //     double lonNum = atof(lon.c_str());
  //     double eleNum = atof(ele.c_str());
      
  //     char latFormat[10];
  //     sprintf(latFormat,"%4.4f",latNum);  //format the double into a C string
  //     std::string latCppStr(latFormat);   //convert formatted C str to C++ str
  //     std::cout << "Clicked Modify WP" << std::endl;
  //     std::string name(theName->value());
  //     string addr(theAddr->value());
      
  //     Waypoint wp = wpObjs->get(name);
  //     wpObjs->remove(wp.name);
  //     // wpObjs->add(Waypoint(name, addr, eleNum, latNum, lonNum)); // comment
  //     wpObjs->add("{\"name\":\""+name+
  //       "\",\"address\":\""+address+"\""+
  //       "\",\"ele\":\""+eleNum+"\""+
  //       "\",\"lat\":\""+latNum+"\""+
  //       "\",\"lon\":\""+lonNum+"\"}");
  // }
  
  // static void SelectedFromWP(Fl_Widget * w, void * userdata) { // done
  //     Client* anInstance = (Client*)userdata;
  //     Fl_Input_Choice * frWps = anInstance->frWps;
  //     Fl_Input * theLat = anInstance->latIn;
  //     Fl_Input * theLon = anInstance->lonIn;
  //     Fl_Input * theEle = anInstance->eleIn;
  //     Fl_Input * theName = anInstance->nameIn;
  //     Fl_Multiline_Input *theAddr = anInstance->addrIn;
      
  //     std::string selected(frWps->value());
  //     std::cout << "You selected from waypoint "
  //               << selected
  //               << std::endl;
  //     Waypoint wp = wpObjs->get(selected);
      
  //     theName->value(wp.name.c_str());
  //     theAddr->value(wp.address.c_str());
      
  //     char latFormat[10], lonFormat[10], eleFormat[10];
  //     sprintf(latFormat,"%4.4f",wp.lat);
  //     sprintf(lonFormat,"%4.4f",wp.lon);
  //     sprintf(eleFormat,"%4.4f",wp.ele);
  //     theLat->value(latFormat);
  //     theLon->value(lonFormat);
  //     theEle->value(eleFormat);     
  //  }

  //  static void SelectedToWP(Fl_Widget * w, void * userdata) {
  //     Client* anInstance = (Client*)userdata;
  //     Fl_Input_Choice * toWps = anInstance->toWps;
  //     Fl_Input * theLat = anInstance->latIn;
  //     Fl_Input * theLon = anInstance->lonIn;
  //     Fl_Input * theEle = anInstance->eleIn;
  //     Fl_Input * theName = anInstance->nameIn;
  //     Fl_Multiline_Input *theAddr = anInstance->addrIn;
      
  //     std::string selected(toWps->value());
  //     std::cout << "You selected from waypoint "
  //               << selected
  //               << std::endl;
  //     Waypoint wp = wpObjs->get(selected);
      
  //     theName->value(wp.name.c_str());
  //     theAddr->value(wp.address.c_str());
      
  //     char latFormat[10], lonFormat[10], eleFormat[10];
  //     sprintf(latFormat,"%4.4f",wp.lat);
  //     sprintf(lonFormat,"%4.4f",wp.lon);
  //     sprintf(eleFormat,"%4.4f",wp.ele);
  //     theLat->value(latFormat);
  //     theLon->value(lonFormat);
  //     theEle->value(eleFormat);
  //  }



   static void printWaypoints() {
    Json::Value names = wpObjs->getNames();
    // for(string n : names) {
    //   Json::Value wp = wpObjs->get(n);
    //   std::cout << "Name: " << n << "Address: " << wp["address"] << "Ele: "
    //   << wp["ele"] << "Lat: " << wp["lat"] << "Lon: " << wp["lon"] << std::endl;
      
    // }
    std::cout << names << std::endl;
   }

  // static void ClickedImportFile(Fl_Widget *w, void * userdata) {
  //   Client* anInstance = (Client*)userdata;
  //   Fl_Input_Choice * frWps = anInstance->frWps;
  //   Fl_Input_Choice * toWps = anInstance->toWps;
  //   std::cout << "Starting import from waypoints.json file" << std::endl;
  //   wpObjs->initWaypointsFromJsonFile("waypoints.json");
  //   vector<string> names = wpObjs->getNames();
  //   for(string n : names) {
  //     frWps->add(n.c_str());
  //     toWps->add(n.c_str());
      
  //   }
  //   std::cout << "Done initializing from waypoints.json" << std::endl;
  // }

  // static void ClickedExportFile(Fl_Widget *w, void *userdata) {
  //   wpObjs->toJsonFile("waypoints_out.json");
  //   std::cout << "Exported to file: waypoints.json" << std::endl;
  // }

  // static void getDistanceAndBearing(Fl_Widget *w, void *userdata) {
  //   Client* anInstance = (Client*)userdata;
  //   Fl_Input_Choice * frWps = anInstance->frWps;
  //   Fl_Input_Choice * toWps = anInstance->toWps;
  //   Fl_Input * distBear = anInstance->distBearIn;

  //   Waypoint frWp = wpObjs->get(frWps->value());
  //   Waypoint toWp = wpObjs->get(toWps->value());

  //   double distance = wpObjs->distanceEarth(frWp.lat, frWp.lon, toWp.lat, toWp.lon);
  //   char distFormat[10];
  //   sprintf(distFormat,"%4.2f",distance);
  //   string dist(distFormat);
  //   double degree = wpObjs->bearing(frWp.lat, frWp.lon, toWp.lat, toWp.lon);
  //   char degFormat[10];
  //   sprintf(degFormat, "%4.2f", degree);
  //   string deg(degFormat);

  //   string whole = dist + "km at " + deg + " degrees";
    
  //   distBear->value(whole.c_str());
    
  // }



public:
  Client(const char * name = 0) : WaypointGUI(name) {
    // connect to server

    std::cout << "Connecting to host " << host << std::endl;


    removeWPButt->callback(ClickedRemoveWP, (void*)this);
    // addWPButt->callback(ClickedAddWP, (void*)this);
    // modWPButt->callback(ClickedModifyWP, (void*)this);
    // frWps->callback(SelectedFromWP, (void*)this);
    // toWps->callback(SelectedToWP, (void*)this);
    // getLatLonButt->callback(ClickedImportFile, (void*)this);
    // exportJson->callback(ClickedExportFile, (void*)this);
    // distBearButt->callback(getDistanceAndBearing, (void*)this);
    callback(ClickedX);
  }
};

int main(int argc, char*argv[]) {



  ::Client cm("C++ Waypoint Browser");
  return (Fl::run());
}

