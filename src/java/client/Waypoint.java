package sample.waypoint.client;
/*
 * Copyright 2016 Tim Lindquist,
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
 * Purpose: Example Java JsonRPC server for collection of students.
 *
 * Ser321 Distributed Apps, and Ser423 Mobile Apps
 * see http://pooh.poly.asu.edu/Mobile
 * @author Tim Lindquist Tim.Lindquist@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @version June 2016
 */

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.Vector;
import java.util.Arrays;

public class Waypoint {

   private static final boolean debugOn = false;

   public String name, address;
   public double ele, lat, lon;

   public Waypoint(String aName, String aAddress, double aEle, double aLat, double aLon){
      name = aName;
      address = aAddress;
      ele = aEle;
      lat = aLat;
      lon = aLon;
   }

   public Waypoint(String jsonStr){
      try{
         JSONObject jo = new JSONObject(jsonStr);
         name = jo.getString("name");
         address = jo.getString("address");
         ele = jo.getDouble("ele");
         lat = jo.getDouble("lat");
         lon = jo.getDouble("lon");

      }catch (Exception ex){
         System.out.println(this.getClass().getSimpleName()+
                            ": error converting from json string");
      }
   }

   public Waypoint(JSONObject jsonObj){
      try{
         debug("constructor from json received: " + jsonObj.toString());
         name = jsonObj.optString("name","unknown");
         address = jsonObj.optString("address","unknown");
         ele = jsonObj.optDouble("ele",0);
         lat = jsonObj.optDouble("lat",0);
         lon = jsonObj.optDouble("lon",0);

      }catch(Exception ex){
         System.out.println(this.getClass().getSimpleName()+
                            ": error converting from json string");
      }
   }

   public JSONObject toJson(){
      JSONObject jo = new JSONObject();
      try{
         jo.put("name",name);
         jo.put("address",address);
         jo.put("ele",ele);
         jo.put("lat",lat);
         jo.put("lon",lon);
      }catch (Exception ex){
         System.out.println(this.getClass().getSimpleName()+
                            ": error converting to json");
      }
      return jo;
   }

   public String toJsonString(){
      String ret = "";
      try{
         ret = this.toJson().toString();
      }catch (Exception ex){
         System.out.println(this.getClass().getSimpleName()+
                            ": error converting to json string");
      }
      return ret;
   }

   public String toString(){
      StringBuilder sb = new StringBuilder();
      sb.append("City: ").append(name).append(" address: ");
      sb.append(address).append(" ele:  ").append(ele);
      sb.append(" latitude: ").append(lat).append(" longitude: ").append(lon);

      return sb.toString();
   }

   private void debug(String message) {
      if (debugOn)
         System.out.println("debug: "+message);
   }

}
