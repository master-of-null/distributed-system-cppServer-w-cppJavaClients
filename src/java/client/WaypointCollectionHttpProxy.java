package sample.waypoint.client;

import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;
import java.util.zip.GZIPInputStream;
import java.util.ArrayList;
import java.util.Arrays;
import org.json.JSONObject;
import org.json.JSONArray;

public class WaypointCollectionHttpProxy {

   static final boolean debugOn = false;
   private final Map<String, String> headers;
   private URL url;
   private String requestData;
   private static int callid =0;

   public WaypointCollectionHttpProxy(URL url) {
      this.url = url;
      this.headers = new HashMap<String, String>();
   }

   private JSONObject buildCall(String method){
      JSONObject jobj = new JSONObject("{\"jsonrpc\":\"2.0\",\"method\":\""+method+"\",\"id\":"+callid+"}");
      return jobj;
   }

   //Methods recognized by the server
   /*
    *saveToJsonFile()-->boolean
    */
   public boolean saveToJsonFile(){
      boolean ret = false;
      try{
         JSONObject jobj = this.buildCall("saveToJsonFile");
         JSONArray params = new JSONArray();
         jobj.put("params",params);
         String request = jobj.toString();
         String response = this.call(request);
         debug("getNames returned: "+response);
         JSONObject respObj = new JSONObject(response);
         if(!respObj.has("error")){
            ret = respObj.optBoolean("result");
         }
      }catch(Exception ex){
         System.out.println("exception in resetFromJsonFile error: "+ex.getMessage());
      }
      return ret;
   }

   /*
    *resetFromJsonFile()-->boolean
    */
   public boolean resetFromJsonFile(){
      boolean ret = false;
      try{
         JSONObject jobj = this.buildCall("resetFromJsonFile");
         JSONArray params = new JSONArray();
         jobj.put("params",params);
         String request = jobj.toString();
         System.out.println(request);
         String response = this.call(request);
         debug("getNames returned: "+response);
         JSONObject respObj = new JSONObject(response);
         if(!respObj.has("error")){
            ret = respObj.optBoolean("result");
         }
      }catch(Exception ex){
         System.out.println("exception in resetFromJsonFile error: "+ex.getMessage());
      }
      return ret;
   }


   public boolean add(Waypoint aName){
      boolean ret = false;
      try{
         JSONObject jobj = this.buildCall("add");
         JSONArray params = new JSONArray();
         params.put(aName.toJson());
         jobj.put("params",params);
         String request = jobj.toString();
         String response = this.call(request);
         debug("add returned: "+response);
      }catch(Exception ex){
         System.out.println("exception in add "+aName.toJsonString()+" error: "+ex.getMessage());
      }
      return ret;
   }

   /*
    *remove(String aWaypointName)-->boolean
    */
   public boolean remove(String aName){
      boolean ret = false;
      try{
         JSONObject jobj = this.buildCall("remove");
         JSONArray params = new JSONArray();
         params.put(aName);
         jobj.put("params",params);
         String request = jobj.toString();
         String response = this.call(request);
         debug("remove returned: "+response);
         JSONObject respObj = new JSONObject(response);
         if(!respObj.has("error")){
            ret = respObj.optBoolean("result");
         }
      }catch(Exception ex){
         System.out.println("exception in remove "+aName+" error: "+ex.getMessage());
      }
      return ret;
   }


   public Waypoint get(String aName){
      Waypoint ret = new Waypoint("unknown","unknown", 0, 0, 0);
      try{
         JSONObject jobj = this.buildCall("get");
         JSONArray params = new JSONArray();
         params.put(aName);
         jobj.put("params",params);
         String request = jobj.toString();
         String response = this.call(request);
         debug("remove returned: "+response);
         JSONObject respObj = new JSONObject(response);
         if(!respObj.has("error")){
            JSONObject obj = respObj.optJSONObject("result");
            ret = new Waypoint(obj);
         }
      }catch(Exception ex){
         System.out.println("exception in get "+aName+" error: "+ex.getMessage());
      }
      return ret;
   }

   public String[] getNames(){
      String[] ret = new String[]{};
      try{
         JSONObject jobj = this.buildCall("getNames");
         JSONArray params = new JSONArray();
         jobj.put("params",params);
         String request = jobj.toString();
         String response = this.call(request);
         debug("getNames returned: "+response);
         JSONObject respObj = new JSONObject(response);
         if(!respObj.has("error")){
            ArrayList<String> al = new ArrayList<String>();
            JSONArray ja = respObj.optJSONArray("result");
            for(int i=0; i<ja.length(); i++){
               String aName = ja.optString(i);
               if(aName!=""){
                  al.add(aName);
               }
            }
            ret = al.toArray(new String[]{});
            Arrays.sort(ret);
         }
      }catch(Exception ex){
         System.out.println("exception in getNames error: "+ex.getMessage());
      }
      return ret;
   }

   public double distanceEarth(double fromLat, double fromLon, double toLat, double toLon){
      double fromLatRad,toLatRad, deltaLat, deltaLng, a, c, d;

      fromLatRad = Math.toRadians(fromLat);
      toLatRad = Math.toRadians(toLat);
      deltaLat = Math.toRadians(toLat - fromLat);
      deltaLng = Math.toRadians(toLon - fromLon);
      a = Math.pow(Math.sin(deltaLat/2), 2) +
      Math.cos(fromLatRad) * Math.cos(toLatRad) *
      Math.pow(Math.sin(deltaLng/2), 2);
      c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
      d = 6371 * c;
      d = Math.round(d * 100) / 100;
      return d;
   }

   public double bearing(double fromLat, double fromLon, double toLat, double toLon) {
      double fromLatRad, toLatRad, deltaLngRad, y, x, bearing;

      deltaLngRad = Math.toRadians(toLon - fromLon);
      fromLatRad = Math.toRadians(fromLat);
      toLatRad = Math.toRadians(toLat);

      y = Math.sin(deltaLngRad) * Math.cos(toLatRad);
      x = Math.cos(fromLatRad) * Math.sin(toLatRad) -
      Math.sin(fromLatRad) * Math.cos(toLatRad) * Math.cos(deltaLngRad);
      bearing = Math.toDegrees(Math.atan2(y, x));
      bearing = Math.round(bearing * 100) / 100;
   
      return bearing;
   }

   public void setHeader(String key, String value) {
      this.headers.put(key, value);
   }

   public String call(String requestData) throws Exception {
      System.out.println('new yak');
      debug("in call, url: "+url.toString()+" requestData: "+requestData);
      String respData = post(url, headers, requestData);
      return respData;
   }

   private String post(URL url, Map<String, String> headers, String data) throws Exception {
      HttpURLConnection connection = (HttpURLConnection) url.openConnection();
      this.requestData = data;
      if (headers != null) {
         for (Map.Entry<String, String> entry : headers.entrySet()) {
            connection.addRequestProperty(entry.getKey(), entry.getValue());
         }
      }
      connection.addRequestProperty("Accept-Encoding", "gzip");
      connection.setRequestMethod("POST");
      connection.setDoOutput(true);
      connection.connect();
      OutputStream out = null;
      try {
         out = connection.getOutputStream();
         out.write(data.getBytes());
         out.flush();
         out.close();
         int statusCode = connection.getResponseCode();
         if (statusCode != HttpURLConnection.HTTP_OK) {
            throw new Exception(
               "Unexpected status from post: " + statusCode);
         }
      } finally {
         if (out != null) {
            out.close();
         }
      }
      String responseEncoding = connection.getHeaderField("Content-Encoding");
      responseEncoding = (responseEncoding == null ? "" : responseEncoding.trim());
      ByteArrayOutputStream bos = new ByteArrayOutputStream();
      InputStream in = connection.getInputStream();
      try {
         in = connection.getInputStream();
         if ("gzip".equalsIgnoreCase(responseEncoding)) {
            in = new GZIPInputStream(in);
         }
         in = new BufferedInputStream(in);
         byte[] buff = new byte[1024];
         int n;
         while ((n = in.read(buff)) > 0) {
            bos.write(buff, 0, n);
         }
         bos.flush(); 
         bos.close();
      } finally {
         if (in != null) {
            in.close();
         }
      }
      debug("post: json rpc request via http returned string "+bos.toString());
      return bos.toString();
   }

   private static void debug(String message) {
      if (debugOn)
         System.out.println("debug: "+message);
   }

}
