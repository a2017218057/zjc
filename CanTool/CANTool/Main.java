package CanTool;

import gnu.io.SerialPort;
import sendfile.Icantool;
import serialPort.SerialTool;

public class Main {

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		SerialPort serialPort = SerialTool.openPort("COM6", 115200);
		Icantool tool = new Icantool(serialPort);
		SerialListener listener = new SerialListener(serialPort,tool);
		tool.addListener(listener);
	}

}
