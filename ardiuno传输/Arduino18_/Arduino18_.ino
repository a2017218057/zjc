String inputString = "";         // 缓存字符串
boolean stringComplete = false;  // 是否string已经完成缓存
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);//cantoolApp要求的频率
 // 初始化串口:
  // 将inputString反转200个字符:
  Serial.println("hello");
  pinMode(2,INPUT);                 //将2号数字口设置为输入状态，13号数字口设置为输出状态
                                    //(板上连接GND__D2两个点模拟总线发送标准帧和扩展帧的事件)
  digitalWrite(2,HIGH);
  inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:
 // 如果缓存string接收完成:
  if (stringComplete) {
    Serial.println(inputString);
    // 清空String:
    inputString = "";
    stringComplete = false;
  }
    int n =digitalRead(2);                   
    //创建一个变量n，将2号数字口的状态采集出来赋值给他。
  if (n==LOW)                             //判断n是否为高电平，如果是执行下面的语句，不是则跳过。
  {

    delay(1000);
    Serial.println("something happened");
    digitalWrite(2,HIGH);
}


}

/*
  SerialEvent在arduino板上的RX引脚收到数据时会被系统自动调用。
  在系统内部，它是在每次loop函数执行时连带执行的。因此如果再loop使用delay,serialEvent的调用也会被延迟，
  这样就有可能一次收到>=2个字符。
 */
void serialEvent() {
  while (Serial.available()) {
    // 获取新的字符:
    char inChar = (char)Serial.read();
    // 将它加到inputString中:
    inputString += inChar;
    //在cantool工具中,指令都是使用"\r"作为结尾,同时,如果收到了回车符，
    //就将一个“旗标”变量设置为true，这样loop函数就知道inputString已经缓存完成了:
    if (inChar == '\r') {
      stringComplete = true;
    }
  }
}
