/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaarduinoserialreceiver;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 *
 * @author Daniel
 */
public class JavaArduinoSerialReceiver {

    private static final String ARDUINO_COM_PORT = "COM5";
    private static final String FRDM_K64F_COM_PORT = "COM30";
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception {
        
        //SamplingDevice arduino = new SamplingDevice("H:\\University\\Test\\", ARDUINO_COM_PORT, "Ardunio");
        SamplingDevice mbed = new SamplingDevice("Z:\\Test\\18.11.2015\\", FRDM_K64F_COM_PORT, "FRDM_K64F_MBED");
        
        //int a = 1;
        int b = 1;
        int samples = 1;
        
        while(true){
            
            //if(a != -1)
             //a = arduino.saveToFile();
            if(b != -1)
             b = mbed.saveToFile();
            
            //System.out.println("A: " + a + ", B: " + b + " Cycles: " + samples);
            System.out.println("B: " + b + " Cycles: " + samples);
            
            //if(a == -1 && b == -1){
            if(b == -1){
                System.out.println("Both devices ports were busy, finishing.");
                break;
            }
            
            samples++;
            
        }
        
        System.out.println("Finished.");
    }
    
    public static String getDate(){
    
        final SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy");
	String date = sdf.format(new Date(System.currentTimeMillis()));
		
	return date;
    
    }
    
    public static String getTime(){
        final SimpleDateFormat sdf = new SimpleDateFormat("h:mm:ss a");
	String time = sdf.format(new Date(System.currentTimeMillis()));
        
        return time;
    }
    
}
