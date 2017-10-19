
package test;
import static org.junit.Assert.*;
import gnu.io.SerialPort;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import serialPort.Serialtool1;
import static org.mockito.Mockito.*;
import CANtool1.CANtool1;
public class CANtool1Test {
private CANtool1 tool1,spy4;
private SerialPort serialPort;
private Serialtool1 serialtool1;
@Before
public void setUp() throws Exception {
	serialPort=mock(SerialPort.class);
	tool1 = new CANtool1(serialPort);
	spy4 = spy(tool1);
}
@After
public void tearDown() throws Exception {
}
@Test
public void readCommandTest1() {
	doNothing().when(spy4).returnTheInfo(1,"SV2.5-HV2.0");
	spy4.readCommand("V\r");
	verify(spy4,times(1)).returnTheInfo(1,"SV2.5-HV2.0");
}
@Test
public void readCommandTest2() {
	doNothing().when(spy4).returnTheInfo(1,"");
	spy4.readCommand("O1\r");
	verify(spy4,times(1)).open();
	verify(spy4,times(1)).returnTheInfo(1,"");
}

@Test
public void readCommandTest5() {
	doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
	spy4.readCommand("C\r");
	verify(spy4,times(1)).close();
	verify(spy4,times(1)).returnTheInfo(0,"");
}
@Test
public void readCommandTest6() {
	doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
	spy4.readCommand("S1\r");
	verify(spy4,times(1)).changeSpeed('1');
	verify(spy4,times(1)).returnTheInfo(1,"");
}
@Test
public void readCommandTest7() {
	doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
	spy4.readCommand("O1r");
	spy4.readCommand("S1\r");
	verify(spy4,times(1)).changeSpeed('1');
	verify(spy4,times(1)).returnTheInfo(1,"");
	verify(spy4,times(1)).returnTheInfo(0,"");
}
@Test
public void readCommandTest8() {
doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
spy4.readCommand("S1\r");
spy4.readCommand("S2\r");
spy4.readCommand("S3\r");
verify(spy4,times(1)).changeSpeed('1');
verify(spy4,times(1)).changeSpeed('2');
verify(spy4,times(1)).changeSpeed('3');
verify(spy4,times(3)).returnTheInfo(1,"");
}

@Test
public void readCommandTest10() {
doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
spy4.readCommand("O1\r");
spy4.readCommand("t36380000000300000D500010\r");
verify(spy4,times(1)).open();
try {
verify(spy4,times(1)).sendStandardFrame("t36380000000300000D500010");
} catch (Exception e) {
// TODO Auto-generated catch block
e.printStackTrace();
}
verify(spy4,times(2)).returnTheInfo(1,"");
//verify(spy4,times(1)).returnTheInfo(0,"");
}
@Test
public void readCommandTest3() {
	doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
	spy4.readCommand("O1\r");
	spy4.readCommand("O1\r");
	verify(spy4,times(2)).open();
	verify(spy4,times(1)).returnTheInfo(1,"");
	verify(spy4,times(1)).returnTheInfo(0,"");
}
@Test
public void readCommandTest4() {
	doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
	spy4.readCommand("O1r");
	spy4.readCommand("C\r");
	verify(spy4,times(1)).open();
	verify(spy4,times(1)).close();
	verify(spy4,times(2)).returnTheInfo(1,"");
}
@Test
public void readCommandTest11() {
doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
spy4.readCommand("O1\r");
spy4.readCommand("t3F380000000300000D500010\r");
verify(spy4,times(1)).open();
try {
verify(spy4,times(1)).sendStandardFrame("t3F380000000300000D500010");
} catch (Exception e) {
// TODO Auto-generated catch block
e.printStackTrace();
}
verify(spy4,times(1)).returnTheInfo(1,"");
verify(spy4,times(1)).returnTheInfo(0,"");
}

@Test
public void readCommandTest12() {
doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
//spy4.readCommand("O1\r");
spy4.readCommand("t359800301513034014880010\r");
//verify(spy4,times(1)).returnTheInfo(1,"");
try {
verify(spy4,times(1)).sendStandardFrame("t359800301513034014880010");
} catch (Exception e) {
// TODO Auto-generated catch block
e.printStackTrace();
}
verify(spy4,times(1)).returnTheInfo(0,"");
}
@Test
public void readCommandTest13() {
doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
spy4.readCommand("O1\r");
spy4.readCommand("T0000036380000000300000D500000\r");
verify(spy4,times(1)).open();
try {
verify(spy4,times(1)).sendExtendedFrame("T0000036380000000300000D500000");
} catch (Exception e) {
// TODO Auto-generated catch block
e.printStackTrace();
}
verify(spy4,times(2)).returnTheInfo(1,"");
//verify(spy4,times(1)).returnTheInfo(0,"");
}
@Test
public void readCommandTest14() {
doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
spy4.readCommand("O1\r");
spy4.readCommand("T0000036380000000300000D500010\r");
verify(spy4,times(1)).open();
try {
verify(spy4,times(1)).sendExtendedFrame("T0000036380000000300000D500010");
} catch (Exception e) {
// TODO Auto-generated catch block
e.printStackTrace();
}
verify(spy4,times(2)).returnTheInfo(1,"");
//verify(spy4,times(1)).returnTheInfo(0,"");
}

@Test
public void readCommandTest9() {
doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
spy4.readCommand("O1\r");
spy4.readCommand("t36380000000300000D500000\r");
verify(spy4,times(1)).open();
try {
verify(spy4,times(1)).sendStandardFrame("t36380000000300000D500000");
} catch (Exception e) {
// TODO Auto-generated catch block
e.printStackTrace();
}
verify(spy4,times(2)).returnTheInfo(1,"");
//verify(spy4,times(1)).returnTheInfo(0,"");
}
@Test
public void readCommandTest15() {
doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
spy4.readCommand("O1\r");
spy4.readCommand("T000003F380000000300000D500010\r");
verify(spy4,times(1)).open();
try {
verify(spy4,times(1)).sendExtendedFrame("T000003F380000000300000D500010");
} catch (Exception e) {
// TODO Auto-generated catch block
e.printStackTrace();
}
verify(spy4,times(1)).returnTheInfo(1,"");
verify(spy4,times(1)).returnTheInfo(0,"");
}
@Test
public void readCommandTest16() {
doNothing().when(spy4).returnTheInfo(anyInt(),anyString());
//spy4.readCommand("O1\r");
spy4.readCommand("T00000359800301513034014880010\r");
try {
verify(spy4,times(1)).sendExtendedFrame("T00000359800301513034014880010");
} catch (Exception e) {
// TODO Auto-generated catch block
e.printStackTrace();
}
//verify(spy4,times(1)).returnTheInfo(1,"");
verify(spy4,times(1)).returnTheInfo(0,"");
}
}