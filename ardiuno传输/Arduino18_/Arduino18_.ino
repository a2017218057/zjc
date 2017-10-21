String inputString ="";         // 缓存字符串
boolean stringComplete = false;  // 是否string已经完成缓存
boolean isWork = false;//标志cantool虚拟装置是否在运行
String msg_rtn = "";    //共用返回字符串
boolean ledisOn = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);//cantoolApp要求的频率
 // 初始化串口:
  // 将inputString反转200个字符:
  Serial.println("hello");
  pinMode(2,INPUT);                 //将2号数字口设置为输入状态，13号数字口设置为输出状态
                                    //(板上连接GND__D2两个点模拟总线发送标准帧和扩展帧的事件)
  digitalWrite(2,HIGH);
  pinMode(5,INPUT);                 //将2号数字口设置为输入状态，13号数字口设置为输出状态
                                    //(板上连接GND__D2两个点模拟总线发送标准帧和扩展帧的事件)
  digitalWrite(5,HIGH);
  inputString.reserve(200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 // 如果缓存string接收完成:
  if (stringComplete) {
   // serial_return(inputString);
  // rec_stdfrm_rtn(inputString);
    chooseFunction(inputString);
    //Serial.println(inputString.length());
    // 清空String:
    inputString ="";
    stringComplete = false;
    
  }
 
  /******这部分就是希望使用板子上的电平变化来模拟总线输入信息
          需要考虑标准帧和扩展帧两种情况需要两个数字口的变化(都与GND)           待写
  ******/
  int n =digitalRead(2);                   
    //创建一个变量n，将2号数字口的状态采集出来赋值给他。
  if (n==LOW)                             //判断n是否为高电平，如果是执行下面的语句，不是则跳过。
  {
    delay(1000);//避免颤抖
    //这里假装总线发了一个标准帧
    //Serial.println("something happened");
    sendStdFrame_ctapp();
    digitalWrite(2,HIGH);
  }

  int m =digitalRead(5);                   
    //创建一个变量n，将2号数字口的状态采集出来赋值给他。
  if (m==LOW)                             //判断n是否为高电平，如果是执行下面的语句，不是则跳过。
  {
    delay(1000);//避免颤抖
    //这里假装总线发了一个标准帧
    //Serial.println("something happened");
    sendExdFrame_ctapp();
    digitalWrite(5,HIGH);
  }
/****************************************************/


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
    // Serial.println(inChar);
    // 将它加到inputString中:
    inputString += inChar;
    //在cantool工具中,指令都是使用"\r"作为结尾,同时,如果收到了回车符，
    //就将一个“旗标”变量设置为true，这样loop函数就知道inputString已经缓存完成了:
    if (inChar == '\r') {
      stringComplete = true;
    }
  }
}

//对从cantoolapp传入的信息的处理,判断程序需要调用哪个功能的函数
void chooseFunction(String message){
  
    char order = message[0];
    if(order != 'O'){
      if(isWork == true){
        switch(order){
        case 'V':
        if(message[1]=='\r'){
          ledisOn = false;
          version_return();
          }
        
        break;
        case 'C':
        if(message[1]=='\r'){
          ledisOn = false;
          close_cantool();
          }
        
        break;
        case 'S':
        
        if(message[2]=='\r'){ //这里判断n是不是数字也可以感觉
          ledisOn = false;
          change_rate();
          }
        break;
        case 't':
        rec_stdfrm_rtn(message);
        break;
        case 'T':
        rec_exdfrm_rtn(message);
        break;
        }
        }
      }else if(order == 'O'){
        ledisOn = false;
        open_cantool();
        }
   
    
    
 }
 
//处理板子上的电平变化,一个标准帧发送,一个扩展帧发送 给App  或者拆开写两个函数在loop里直接调用
void sendStdFrame_ctapp(){
  String stdmsg = "t12380011121314151617";
  serial_return(stdmsg+"\r");
  }
//处理板子上的电平变化,一个标准帧发送,一个扩展帧发送 给App  或者拆开写两个函数在loop里直接调用
void sendExdFrame_ctapp(){
  String exdmsg = "T1234567F81122334455667788";
  serial_return(exdmsg+"\r");
  }
//接收cantoolapp的标准帧
void rec_stdfrm_rtn(String message){
  msg_rtn = "\r";
  serial_return(msg_rtn);
  delay(100);//总感觉发太快
  int len = message.length();
  String send_canmsg = "";
  String timenum = "";
  
  for(int i = 0;i<len-5;i++){ //取出要发送给总线的字符串。。虽然并没有地方发送
    send_canmsg = send_canmsg + message[i];
    }
 //   Serial.println(send_canmsg);
  int k = 0;
  for(int i = 5;i>0;i--){    //取出时间频率
    k = len - i;
    timenum = timenum + message[k];
    }
  int t = Str_to_num(timenum);
  ledisOn = true;
  loopled(t);               //循环播放灯
 // Serial.println(t);
  }

  //接收cantoolapp的扩展帧 复用标准帧的代码
void rec_exdfrm_rtn(String message){
  rec_stdfrm_rtn(message);
  }
  
//发送字符串函数(通用) 这里要考虑串口通讯使用一个一个字符传输,时刻牢记字符串最后有个\r
void serial_return(String message){

  int msg_length = message.length();
//  message.ToCharArray();
  for(int i=0;i<msg_length;i++){
     Serial.println(message[i]);
    }
   // Serial.println(msg_length);
  }
  
//返回cantool装置信息
void version_return(){
  //serial_return();
  msg_rtn = "SV2.5-HV2.0\r";
  serial_return(msg_rtn);
  }
  
//打开装置,开始工作 isWork作为flag表示cantool装置是否在运行  
void open_cantool(){
  if(isWork == false)
  isWork = true;
  msg_rtn = "\r";
  serial_return(msg_rtn);
  //返回\r
  }
//关闭装置 
void close_cantool(){
  if(isWork == true)
  isWork = false;
  msg_rtn = "\r";
  serial_return(msg_rtn);
  }
//Sn 改变通信速率 ,这里在考虑要不要结合硬件做一做总线的改变但是苦于板子上没有灯
void change_rate(){
  msg_rtn = "\r";
  serial_return(msg_rtn);
  }

//工具函数,用来将带有时间的16进制字符串转化为数字再转化为10进制
//将十六进制的字符串转换成整数  
int Str_to_num(String s)  
{  
    int i;  
    int n = 0;  
    if (s[0] == '0' && (s[1]=='x' || s[1]=='X'))  
    {  
        i = 2;  
    }  
    else  
    {  
        i = 0;  
    }  
    for (; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >='A' && s[i] <= 'Z');++i)  
    {  
        if (tolower(s[i]) > '9')  
        {  
            n = 16 * n + (10 + tolower(s[i]) - 'a');  
        }  
        else  
        {  
            n = 16 * n + (tolower(s[i]) - '0');  
        }  
    }  
    return n;  
}  

//控制板子上的灯
void closeLed(){
   ledisOn = false;
   digitalWrite(LED_BUILTIN, LOW);   // 关灯
  }
//循环播放灯 参数为时间间隔
void loopled(int delta){
  if(ledisOn == true){
   for ( int i = 0;i<30;i++){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delta);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(delta);   
      }
     
    }
         
  }



  
