package sample.waypoint.client;

import java.io.*;
import java.util.*;
import java.net.URL;

import org.json.*;

import javax.swing.*;
import java.io.*;
import javax.swing.event.*;
import javax.swing.text.html.*;
import java.awt.event.*;
import java.awt.*;
import java.util.*;
/**
 * Copyright (c) 2016 Tim Lindquist,
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
 * Purpose:
 * A Java class and main method demonstrating an approach to calling
 * JsonRpc methods where argument and return types are user-defined classes.
 *
 * @author Tim Lindquist (tim.lindquist@asu.edu), ASU Software Engineering
 * @version May 2016
 * @license See above
 */
public class WaypointCollectionClient extends WaypointGUI implements
                                               ActionListener, ItemListener {

   private static final boolean debugOn = true;
   private JSONObject hashi;
   

    public WaypointCollectionClient(String base) {
      super(base);
      removeWPButt.addActionListener(this);
      addWPButt.addActionListener(this);
      modWPButt.addActionListener(this);
      importButt.addActionListener(this);
      exportButt.addActionListener(this);
      distBearButt.addActionListener(this);
      frWps.addItemListener(this);
      toWps.addItemListener(this);
      hashi = importFile("waypoints.json");

      this.addWindowListener(new WindowAdapter() {
         @Override
         public void windowClosing(WindowEvent e) {
            debug("you clicked X");
            System.exit(0);
         }
      });

      setVisible(true);
   }

   public void itemStateChanged(ItemEvent event){
      if(event.getStateChange() == ItemEvent.SELECTED){
         Object comp = event.getSource();
         debug("Selection event generated by "+
                            ((comp==frWps)?"from ":"to ")+"combobox. "+
                            "Selected waypoint is: "+(String)event.getItem());
         String city = (String) event.getItem();
         JSONObject cityInfo = hashi.getJSONObject(city);

         latIn.setText(String.valueOf(cityInfo.get("lat")));
         lonIn.setText(String.valueOf(cityInfo.get("lon")));
         eleIn.setText(String.valueOf(cityInfo.get("ele")));
         nameIn.setText((String)cityInfo.get("name"));
         addrIn.setText((String)cityInfo.get("address"));
      }
   }

   public void actionPerformed(ActionEvent e) {
      if(e.getActionCommand().equals("Remove")) {
         // debug("you clicked Remove Waypoint");
         // removeWps(frWps.getSelectedItem().toString(),
         // toWps.getSelectedItem().toString());
      }else if(e.getActionCommand().equals("Add")) {
         // debug("you clicked Add Waypoint");
         // addWp();
         // frWps.addItem(nameIn.getText());
         // toWps.addItem(nameIn.getText());
         // distBearIn.setText("Added: "+nameIn.getText());
      }else if(e.getActionCommand().equals("Modify")) {
         debug("you clicked Modify Waypoint");
         // modifyWP(nameIn.getText());
      }else if(e.getActionCommand().equals("Import")) {
         debug("you clicked Import Json Library");
         hashi = importFile("waypoints.json");
      }else if(e.getActionCommand().equals("Export")) {
         debug("you clicked Export Json Library");
         exportFile();
      }else if(e.getActionCommand().equals("Distance")) {
         // debug("you clicked Distance and Bearing");
         // distBearIn.setText(String.valueOf(haversineDistance()) + "km, "
         //    + String.valueOf(haversineBearing() + " degrees"));
      }
   }

   private void debug(String message) {
      if (debugOn)
         System.out.println("debug: "+message);
   }
    
    private JSONObject importFile(String jsonFileName) {
      try {
          FileInputStream in = new FileInputStream(jsonFileName);
          JSONObject obj = new JSONObject(new JSONTokener(in));
          String [] names = JSONObject.getNames(obj);
          System.out.println("names are:");
          for(int i = 0; i < names.length; i++) {
         frWps.addItem(names[i]);
         toWps.addItem(names[i]);
          }
          return obj;
      }
      catch(FileNotFoundException ex)
      {
          System.out.println("Error uploading file " + jsonFileName);
      }
      return new JSONObject();
    }

    private void exportFile() {
      try {
          FileWriter file = new FileWriter("generatedWaypoints.json");
          file.write(hashi.toString());
          file.flush();
          file.close();
          System.out.println("done");
      } catch (IOException e) {
          e.printStackTrace();
      }
    }

    // private void addWp() {
    //   double lat, lon, ele;
    //   String name, addr;
    //   lat = Double.parseDouble(latIn.getText());
    //   lon = Double.parseDouble(lonIn.getText());
    //   ele = Double.parseDouble(eleIn.getText());
    //   name = nameIn.getText();
    //   addr = addrIn.getText();

    //   JSONObject json = new JSONObject();
    //   json.put("address", addr);
    //   json.put("name", name);
    //   json.put("lon", lon);
    //   json.put("lat", lat);
    //   json.put("ele", ele);
    //   hashi.put(name, json);
    // }

    // private void modifyWP(String name) {
    //   JSONObject json = hashi.getJSONObject(name);
    //   double lat, lon, ele;
    //   String addr;

    //   lat = Double.parseDouble(latIn.getText());
    //   lon = Double.parseDouble(lonIn.getText());
    //   ele = Double.parseDouble(eleIn.getText());
    //   name = nameIn.getText();
    //   addr = addrIn.getText();
    //   json.put("address", addr);
    //   json.put("name", name);
    //   json.put("lon", lon);
    //   json.put("lat", lat);
    //   json.put("ele", ele);
    // }

    private void removeWps(String from, String to) {
      if(!to.equals("to waypoint")){
          toWps.removeItem(toWps.getSelectedItem());
          hashi.remove(to);
      }
      if(!from.equals("from waypoint")) {
          frWps.removeItem(frWps.getSelectedItem());
          hashi.remove(from);
      }
    }

    




   public static void main(String args[]) {
      try{
         String name = "Ser321";
         if (args.length >= 1) {
            name = args[0];
         }
         Assign2Martinez sa2 = new Assign2Martinez(name);
      }catch (Exception ex){
         ex.printStackTrace();
      }
   }
}
