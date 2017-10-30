#include <avr/pgmspace.h>
#include <TimerOne.h>
String inputString ="";         // 缓存字符串
boolean stringComplete = false;  // 是否string已经完成缓存
boolean isWork = false;//标志cantool虚拟装置是否在运行
String msg_rtn = "";    //共用返回字符串
boolean ledisOn = false;
const char sA[] PROGMEM="BO_ 801 HVAC_2: 8 HVAC";
const PROGMEM char ss[]  = {"BO_ 801 HVAC_2: 8 HVAC SG_ HVAC_RawCabinTemp : 7|8@0+ (0.5,-40) [-40|87.5] \"°C\"  CDU SG_ HVAC_CorrectedCabinTemp : 15|8@0+ (0.5,-40) [-40|87.5] \"°C\"  CDU SG_ HVAC_RawCabinTempVD : 19|1@0+ (1,0) [0|1] \"\"  CDU SG_ HVAC_CompressorComsumpPwr : 17|10@0+ (10,0) [0|8000] \"w\"  BCM SG_ HVAC_PTCPwrAct : 33|10@0+ (10,0) [0|8000] \"w\"  BCM  SG_ HVAC_stPTCAct : 55|3@0+ (1,0) [0|1] \"\"  BCM SG_ HVAC_CorrectedCabinTempVD : 18|1@0+ (1,0) [0|1] \"\" CDU "};
const PROGMEM char stdtt[] = {"t31D80100000000000000t320880478C2F05A1D29At360800402418E4000000t39380000381403000000t03D80D00000000000000t42B84215640000000001t3208094697860945675Dt320838D1DB1304806D85t31880300000000000000t34580000000006CA0000t31D80200000000000000t31880100000000000000t03D83000000000000000t32180F23042701722000t36489476B18400000000t39380000070701000000t36380C51C0521B0090D9t03D80200000000000000t42080332510000000000t345800000000075F0000t31D80600000000000000t393800002B3521000000t03D82800000000000000t31880100000000000000t39380000362001000000t36382150014720000009t39380000030D22000000t3638441F413B5600908Dt42082802860000000000t3588423C5015130EE000t31D80300000000000000t31880200000000000000t320810F35FB10762018At36483274950000000000t31D80600000000000000t364879328CC200000000t03D83400000000000000t31D80300000000000000t3608043D0622AE000000t03D83200000000000000t3218AF090E1602850000t3458000000002BF00000t42B81F33A30000000000t3208F0EE8D2303035783t4208E233D40000000001t393800003A0510000000t35884B10B06F17100000t31D80200000000000000t31D80500000000000000t03D83000000000000000t31D80500000000000000t3648C44D930400000000t31D80400000000000000t42084017D70000000001t42B83703C90000000001t31D80600000000000000t345800000000280B0000t3648D637328700000000t360807462D1EC7000000t42B89632F50000000001t3208B978B34B04A715C1t363819A7406546008012t31880100000000000000t3218A6F90C7300DB0000t36380C1980A01400508Ct32184FE1096F00540000t42082A34E90000000001t393800001D3320000000t3608024A323EBA000000t36480453270200000000t31D80000000000000000t31D80000000000000000t32189A25002B02042000t3588892C001B140CB000t42B87B373F0000000001t345800000000212F0000t3208615350C50C4645B6t3608073B2639A7000000t3588423C74111604F000t31D80300000000000000t42088D20800000000001t3458000000000D3A0000t31D80400000000000000t42B85F125E0000000000t03D80700000000000000t360804103E15FB000000t36382D5580BA460080F3t36080704255DAD000000t320871AD8DAD05831CC7t31880200000000000000t393800000A1723000000t31880300000000000000t42081606020000000001t3208809D240703C4869At32184CE602DC017F2000t42B8FD12570000000001t39380000302023000000"};
const PROGMEM char stdttt[] = {"t32080000000000000000t32080128000000000000t32080050000000000000t32080178000000000000t320800A0000000000000t320801FF000000000000t3608000E00009B000000t3608042B0000C3000000t360800410000EB000000t3608024A0000FF000000t3FC18400000000000000t3FC10600000000000000t11180000000000000000t11180000000000009001t11180000000000005802t0648F01732C30000882Ct0648101B32DC00006432t11180000000000009001t35880100003F000C0000t35880000007D00180000t34580000000010AA0000t393800003B0000000000t39380000330000000000t320800F0000000000000t0648131428A300008025t0648101B32DC00006432t0648401F64FF0000983At0648B00A14570000EC13"};
const PROGMEM char errortt[]={"t320800000000000,t323800000G0000000000,t323800000G0000000000,t3608024A000,Afdf34,Y34344,t3628000E00009B000000"};
const long interval = 100000; //  100000 microseconds = 100 ms = 0.1 second
int readmsg_tt = 0;
int readerrmsg_tt = 0;
char s[] =  "rdfghjklfgfydushijfguerhfdud";
String p[7];
boolean sendmsg_tt = false;
boolean senderror_tt = false;
boolean reread = false;
int timeled = 0;
float delta =0.0;
void ledblink(){

    
 digitalWrite( 13, digitalRead( 13 ) ^ 1 ); // toggle 0, 1
 
  }
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
  int numofss = sizeof(ss)/sizeof(char);
 // read back a char
 Timer1.initialize( interval ); // 初始化,  interval 以 micro sec 為單位
 Timer1.attachInterrupt( ledblink ); // attach the service routine here
//String id = canmsg(ss);
 //Serial.print("id"+id);
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
  if(isWork){
    int n =digitalRead(2);                   
    //创建一个变量n，将2号数字口的状态采集出来赋值给他。
  if (n==LOW)                             //判断n是否为高电平，如果是执行下面的语句，不是则跳过。
  {
    delay(1000);//避免颤抖
    //这里假装总线发了一个标准帧
    //Serial.println("something happened");
    //sendStdFrame_ctapp();
    sendmsg_tt = !sendmsg_tt;
  //  Serial.println(sendmsg_tt);
    digitalWrite(2,HIGH);
  }

  int m =digitalRead(5);                   
    //创建一个变量n，将2号数字口的状态采集出来赋值给他。
  if (m==LOW)                             //判断n是否为高电平，如果是执行下面的语句，不是则跳过。
  {
    delay(1000);//避免颤抖
    //这里假装总线发了一个标准帧
    //Serial.println("something happened");
    //sendExdFrame_ctapp();
    senderror_tt = !senderror_tt;
    digitalWrite(5,HIGH);
  }
/****************************************************/
if(sendmsg_tt){
  delay(1000);
  sendStdFrame_ctapp(stdttt);
  //Serial.println(readmsg_tt);
  }
 if(senderror_tt){
  //delay(1000);
  sendExdFrame_ctapp(errortt);
  //Serial.println(readmsg_tt);
  } 
  if(ledisOn){
 
  //Serial.print(delta/100.0 * interval );
  
  Timer1.setPeriod( delta/100.0 * interval );
//  Timer1.attachInterrupt(delta/100.0 * interval);
  //digitalWrite(LED_BUILTIN, LOW);
//  continue;
 //ledisOn =false;
  }else{
 //   Timer1.detachInterrupt(); // 停止閃爍
    Timer1.stop();
    timeled =0;
    ledisOn =false;
    }
  
/*if(ledisOn){
  if(timeled<30)
  timeled+=1;
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delta);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(delta);  
  }else{
    timeled =0;
    ledisOn =false;
    }
    }
  
*/
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
void sendStdFrame_ctapp(const char tt[]){
  
  int tlen = strlen_P(tt);
  //Serial.println(tlen);
  String msg = "";
  for(;readmsg_tt<tlen;readmsg_tt++){
      int next = readmsg_tt+1;
      char currentC =  pgm_read_byte_near(tt + readmsg_tt);
    if(next<tlen){
     
       char nextC =  pgm_read_byte_near(tt + next);

       if(nextC=='t'){
          msg += currentC;
          readmsg_tt++;   
          //Serial.println(readmsg_tt);
          break;
          }else{
            msg += currentC; 
            }
      }else{
        msg += currentC;
        readmsg_tt=0;
       // reread = true;
       break;
        }

     
   
    }
  
 // String stdmsg = "t12380011121314151617";
  serial_return(msg+"\r");
  }
//处理板子上的电平变化,一个标准帧发送,一个扩展帧发送 给App  或者拆开写两个函数在loop里直接调用
void sendExdFrame_ctapp(const char tt[]){
  String msg = "";
  
  int tlen = strlen_P(tt);
   for(;readerrmsg_tt<tlen;readerrmsg_tt++){
    int next = readerrmsg_tt+1;
    char currentC =  pgm_read_byte_near(tt + readerrmsg_tt);
    if(next<tlen){
       char nextC =  pgm_read_byte_near(tt + next);
       if(nextC==','){
          msg += currentC;
          readerrmsg_tt = readerrmsg_tt +2;   
          //Serial.println(readmsg_tt);
          break;
        }else{
           msg += currentC; 
          }
      }else{
        msg += currentC;
        readerrmsg_tt=0;
       // reread = true;
       break;
        }
    }
    serial_return(msg+"\r");
  }
  
//接收cantoolapp的标准帧
void rec_stdfrm_rtn(String message){
  msg_rtn = "\r";
  serial_return(msg_rtn);
  //delay(100);//总感觉发太快
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
  delta = t;
 // loopled(t);               //循环播放灯
 // Serial.println(t);
 serial_return(" ");
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
     Serial.print(message[i]);
    }
    Serial.println();
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
   /*for ( int i = 0;i<30;i++){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delta);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(delta);   
      } */
     
    }
         
  }


//处理字符的巨大数组
String canmsg(const char msg[]){
 int pause = 4;
 String id = "";
 int len = strlen_P(msg);
 //求ID
  for (int k = 4; k < len; k++)
  {
    char myChar =  pgm_read_byte_near(msg + k);
    //Serial.print(myChar);
    if(isDigit(myChar)){
      id += myChar;
      }else{
       
        break;
        }
  }
//BO_ 801 HVAC_2: 8 HVAC SG_ HVAC_RawCabinTemp : 7|8@0+ (0.5,-40) [-40|87.5] 
//SG_ HVAC_RawCabinTemp : 7|8@0+ (0.5,-40) [-40|87.5] \"°C\"  CDU
  //处理语句
 // String x = "";
 for(;pause<len;pause++){
  if(pause<len-1){
    int next = pause+1;
    char myChar =  pgm_read_byte_near(msg + pause);
    char myChar1 =  pgm_read_byte_near(msg + next);
    if((myChar == 'S')&&(myChar1 == 'G')){
      for(;pause<len;pause++){
        char myChar22 =  pgm_read_byte_near(msg + pause);
          if(myChar22 ==':'){
         Serial.println(pause);
         dotheline(pause,len,msg);
         Serial.println(p[3]);
      }
        }
    
      }
    }

    
  }
 //dotheline(114,len,msg);
//dotheline(45,len,msg); 
 return id; 
 
  }

  //
  void dotheline(int pause,int len,const char msg[]){
    
  /*String start = "";
  String lenn = "";
  String A = "";
  String B = "";
  String suanfa = "";
  String left = "";
  String right = "";*/
  for(int i = 0;i<7;i++){
    p[i]="";
    }
//  pause = 20;
  for(;pause<len;pause++){
   // Serial.print("pause");
    
    char myChar4 =  pgm_read_byte_near(msg + pause);
    if(isDigit(myChar4)){
     // Serial.print(myChar4);
      p[0] += myChar4;
      int next = pause+1;
      char myChar44 =  pgm_read_byte_near(msg + next);
      if(isDigit(myChar44)){
        }else{
          pause++;
          break;
          }
      }
    }
   
//pause = 14;
  for(;pause<len;pause++){
     char myChar =  pgm_read_byte_near(msg + pause);
     if(isDigit(myChar)){
      p[1] += myChar;
      int next = pause+1;
      char myChar55 =  pgm_read_byte_near(msg + next);
      if(isDigit(myChar55)){
        }else{
          pause++;
          break;
          }
      }
    }
   for(;pause<len;pause++){
     char myChar =  pgm_read_byte_near(msg + pause);
     if(isDigit(myChar)){
      p[2] += myChar;
      int next = pause+1;
      char myChar66 =  pgm_read_byte_near(msg + next);
      if(isDigit(myChar66)){
        }else{
          pause++;
          break;
          }
      }

    }
   // Serial.print(pause);
   int finish2 = 0;
   int finish1 = 0;
    for(;pause<len;pause++){
     char myChar =  pgm_read_byte_near(msg + pause);
     if(myChar == '('){
      
      pause =pause+1;
      for( ;pause<len;pause++){
        char myChar1 =  pgm_read_byte_near(msg + pause);
        if(myChar1 == ','){
         //Serial.print("p"+pause);
         pause++;         
         break;
          }else{
         //   Serial.print(myChar1);
            p[3] += myChar1;
            } 
        }
     //  Serial.print("pse"+pause);
      for( ;pause<len;pause++){
       // Serial.print(pause);
        char myChar2 =  pgm_read_byte_near(msg + pause);
        if(myChar2 == ')'){
            pause++;
            finish2 = 1;
            break;
          }else{
            p[4] += myChar2;
            } 
        }
        
      }else if(finish2 == 1){
        break;
        }
      
    } 
//求 区间
  for(;pause<len;pause++){
     char myChar =  pgm_read_byte_near(msg + pause);
     if(myChar == '['){
      
      pause =pause+1;
      for( ;pause<len;pause++){
        char myChar1 =  pgm_read_byte_near(msg + pause);
        if(myChar1 == '|'){
         //Serial.print("p"+pause);
         pause++;         
         break;
          }else{
         //   Serial.print(myChar1);
            p[5] += myChar1;
            } 
        }
     //  Serial.print("pse"+pause);
      for( ;pause<len;pause++){
       // Serial.print(pause);
        char myChar2 =  pgm_read_byte_near(msg + pause);
        if(myChar2 == ']'){
            pause++;
            finish1 = 1;
            break;
          }else{
            p[6] += myChar2;
            } 
        }
        
      }else if(finish1 == 1){
        break;
        }
      
    } 
      
   

  //  return pause;
    }
