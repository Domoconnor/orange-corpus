/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaarduinoserialreceiver;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import jssc.SerialPort;

/**
 *
 * @author Daniel
 */
public class SamplingDeviceOld {
    
    private File file;
    private String dir;
    private BufferedWriter bw;
    private String comPort;
    private int x = 1;
    private String currentDate;
    private String deviceName;
         
    public SamplingDeviceOld(String dir, String comPort, String name) throws IOException{
        this.comPort = comPort;
        this.deviceName = name;
        this.currentDate = JavaArduinoSerialReceiver.getDate();
        this.file = new File(dir + currentDate + "-Sound (" + deviceName + ").csv");
        this.dir = dir;
        this.bw = new BufferedWriter(new FileWriter(file, true));
    }
    
    public int saveToFile() throws FileNotFoundException, IOException, InterruptedException{  
        
            String data = "";
            
            if(x % 100 == 0){
                if (!currentDate.equalsIgnoreCase(JavaArduinoSerialReceiver.getDate())){
                    currentDate = JavaArduinoSerialReceiver.getDate();
                    file = new File(dir + currentDate + "-Sound (" + deviceName + ").csv");
                    if(!file.exists())
                    bw = new BufferedWriter(new FileWriter(file, true)); 
                }
                x=1;
            }
            
            try{
            
             data = readComPort(comPort);
            
            }catch(Exception e){
                e.printStackTrace();
                return -1;
            }
        
            data = data.replaceAll(" ", "").replaceAll("\n\r", "");
            
            if(data.isEmpty()) return 0;
            
            System.out.println(deviceName + ": " + data);
            
            bw.write(JavaArduinoSerialReceiver.getTime() + "," + data);
            bw.newLine();
            
            bw.flush();
            
            x++;
                  
            return 1;
    
    }  
        
    private String readComPort(String comPort){
        
        SerialPort serialPort = new SerialPort(comPort);
        try {
            serialPort.openPort();//Open serial port
            serialPort.setParams(9600, 8, 1, 0);//Set params.
            byte[] buffer = serialPort.readBytes(5);
            serialPort.closePort();//Close serial port
            return new String(buffer, "UTF-8");
        }
        catch (Exception ex) {
            System.out.println(ex);
            ex.printStackTrace();
        }
        return "INVALID";
    }
    
}
