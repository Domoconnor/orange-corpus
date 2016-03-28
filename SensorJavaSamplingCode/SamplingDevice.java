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
import java.util.Arrays;
import jssc.SerialPort;
import jssc.SerialPortException;

/**
 *
 * @author Daniel
 */
public class SamplingDevice {

    private File file;
    private final String dir;
    private BufferedWriter bw;
    private int x = 1;
    private String currentDate;
    private final String deviceName;
    private final SerialPort serialPort;

    public SamplingDevice(String dir, String comPort, String name) throws IOException, SerialPortException {
        this.deviceName = name;
        this.currentDate = JavaArduinoSerialReceiver.getDate();
        this.file = new File(dir + currentDate + "-Sound (" + deviceName + ").csv");
        this.dir = dir;
        this.bw = new BufferedWriter(new FileWriter(file, true));
        serialPort = new SerialPort(comPort);
        serialPort.openPort();

    }

    public int saveToFile() throws FileNotFoundException, IOException, InterruptedException {

        /* Checks the current file date, if it needs to change then creates new file */
        if (x % 100 == 0) {
            if (!currentDate.equalsIgnoreCase(JavaArduinoSerialReceiver.getDate())) {
                currentDate = JavaArduinoSerialReceiver.getDate();
                file = new File(dir + currentDate + "-Sound (" + deviceName + ").csv");
                if (!file.exists()) {
                    bw = new BufferedWriter(new FileWriter(file, true));
                }
            }
            x = 1;
        }

        int[] data = readComPortSigned();
        bw.append(JavaArduinoSerialReceiver.getTime());

        /* Calculate the range of 50 samples */
        int i = 50;
        int max = data[0];
        int min = max;
        int range;
        int j;

        while (i-- > 1) {
            j = data[i];
            if (j > max) {
                max = j;
            }
            if (j < min) {
                min = j;
            }
        }
        range = max - min;

        bw.append(", ").append(Integer.toString(range)).append(", ").append(Integer.toString(max)).append(", ").append(Integer.toString(min));

        for (int s : data) {
            bw.append(", ").append(Integer.toString(s));
        }
        bw.newLine();
        bw.flush();

        System.out.println(deviceName + ": " + ++x + ": (" + max + "," + range + "," + min + ") " + Arrays.toString(data));
        return 1;
    }

    private int[] readComPortSigned() {

        try {
            byte[] buffer = serialPort.readBytes(100); //100 = 50 readings * 2bytes per reading

            int[] res = new int[50];

            int j = 0;
            for (int i = 0; i < 50; i++) {
                int s = (buffer[j++] & 0xFF); // 
                s |= (buffer[j++] & 0xFF) << 8;
                s -= (1 << 15);
                res[i] = s;
            }
            return res;

        } catch (SerialPortException ex) {
            ex.printStackTrace();
            return new int[50];
        }
    }

    private int[] readComPortUnsigned() {

        try {
            byte[] buffer = serialPort.readBytes(100); //100 = 50 readings * 2bytes per reading

            int[] res = new int[50];

            int j = 0;
            for (int i = 0; i < 50; i++) {
                int s = (buffer[j++]); // 
                s |= (buffer[j++]) << 8 ;
                //s -= (1 << 15);
                res[i] = s;
            }
            return res;

        } catch (SerialPortException ex) {
            ex.printStackTrace();
            return new int[50];
        }
    }

    public boolean closeComPort() throws SerialPortException {
        return serialPort.closePort();
    }

}
