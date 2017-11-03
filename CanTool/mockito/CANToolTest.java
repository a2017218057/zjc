package mockito;

import static org.junit.Assert.*;
import gnu.io.SerialPort;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import sendfile.Icantool;
import serialPort.SerialTool;
import static org.mockito.Mockito.*;  

public class CANToolTest {
	private Icantool cantool,spy;
	private SerialPort Port;
	@Before
	public void setUp() throws Exception {
		Port=mock(SerialPort.class);
		cantool = new Icantool(Port);
		spy = spy(cantool);
		
	}

	@After
	public void tearDown() throws Exception {
	}
	
	// 正常开机
	@Test
	public void Test1() {
		
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		spy.readCommand("O1\r");
		verify(spy,times(1)).returnTheInfo(1,"");
		verify(spy,times(1)).open();
		
		
	}
	
	
	// 正常关机
	@Test
	public void Test2() {
		
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		spy.readCommand("O1r");
		spy.readCommand("C\r");
		verify(spy,times(2)).returnTheInfo(1,"");
		verify(spy,times(1)).open();
		verify(spy,times(1)).close();
		
	}
	
	// 返回版本信息
	@Test
	public void Test3() {
		
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		spy.readCommand("V\r");
		verify(spy,times(1)).returnTheInfo(1,"SV2.5-HV2.0");
		
	}
	

	// 连续调节速度
	@Test
	public void Test4() {
		
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		spy.readCommand("S1\r");
		spy.readCommand("S2\r");
		verify(spy,times(1)).changeSpeed('1');
		verify(spy,times(1)).changeSpeed('2');
		verify(spy,times(2)).returnTheInfo(1,"");
		
	}
	
	
        // 关机状态下调节速度
	@Test
	public void Test5() {
		
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		spy.readCommand("S3\r");
		verify(spy,times(1)).changeSpeed('3');
		verify(spy,times(1)).returnTheInfo(1,"");
		
	}
	
	// 关机状态下调节速度
	@Test
	public void Test6() {
		
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		spy.readCommand("O1\r");
		spy.readCommand("S3\r");
		verify(spy,times(1)).changeSpeed('3');
		verify(spy,times(1)).returnTheInfo(1,"");
		verify(spy,times(1)).returnTheInfo(0,"");
		
	}

	// 发送1次扩展帧
	@Test
	public void Test7() {
		
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		spy.readCommand("O1\r");
		spy.readCommand("T0000036380000000100000F100010\r");
		verify(spy,times(1)).open();
		try {
			verify(spy,times(1)).sendExtendedFrame("T0000036380000000100000F100010");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		verify(spy,times(2)).returnTheInfo(1,"");
		//verify(spy,times(1)).returnTheInfo(0,"");
		
	}
	
	// 发送扩展帧错误
	@Test
	public void Test8() {
		
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		spy.readCommand("O1\r");
		spy.readCommand("T000003F380000000100000F100010\r");
		verify(spy,times(1)).open();
		try {
			verify(spy,times(1)).sendExtendedFrame("T000003F380000000100000F100010");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		verify(spy,times(1)).returnTheInfo(1,"");
		verify(spy,times(1)).returnTheInfo(0,"");
		
	}
	
	// 未开机发送扩展帧错误
	@Test
	public void Test9() {
		
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		//spy.readCommand("O1\r");
		spy.readCommand("T00000359800301513034014880010\r");
		try {
			verify(spy,times(1)).sendExtendedFrame("T00000359800301513034014880010");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//verify(spy,times(1)).returnTheInfo(1,"");
		verify(spy,times(1)).returnTheInfo(0,"");
		
	}
	
	// 未开机发送标准帧错误
	@Test
	public void Test10() {
			
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		spy.readCommand("t3F380000000100000F100010\r");
		try {
			verify(spy,times(1)).sendStandardFrame("t3F380000000100000F100010");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		verify(spy,times(1)).returnTheInfo(0,"");			
	}
	
	// 发送指令错误
	@Test
	public void Test11() {
			
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		spy.readCommand("SS\r");
		verify(spy,times(1)).returnTheInfo(0,"");
			
	}
	
	// 发送1次标准帧
	@Test
	public void Test12() {
		
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		spy.readCommand("O1\r");
		spy.readCommand("t36380030050106020F100010\r");
		verify(spy,times(1)).open();
		try {
			verify(spy,times(1)).sendStandardFrame("t36380030050106020F100010");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		verify(spy,times(2)).returnTheInfo(1,"");
		//verify(spy,times(1)).returnTheInfo(0,"");
		
	}

	
	// 发送标准帧错误
	@Test
	public void Test13() {
		
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		spy.readCommand("O1\r");
		spy.readCommand("t33380000000100000F100010\r");
		verify(spy,times(1)).open();
		try {
			verify(spy,times(1)).sendStandardFrame("t33380000000100000F100010");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		verify(spy,times(1)).returnTheInfo(1,"");
		verify(spy,times(1)).returnTheInfo(0,"");
		
	}
	
	// 未开机发送标准帧
	@Test
	public void Test14() {
		
		doNothing().when(spy).returnTheInfo(anyInt(),anyString());
		//spy.readCommand("O1\r");
		spy.readCommand("t359800301513034014880010\r");
		//verify(spy,times(1)).returnTheInfo(1,"");
		try {
			verify(spy,times(1)).sendStandardFrame("t359800301513034014880010");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		verify(spy,times(1)).returnTheInfo(0,"");
		
	}
	
}
