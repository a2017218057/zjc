

    returnTheInfo(1,"");

  }

  else

  {

    returnTheInfo(0,"");

  }

}



void returnTheInfo(int flag,String message)

{

  if(flag==1)

  {

      message=message+"\r";

  }

  else

  {

      message=message+(char)7;

  }

  int len=message.length();

  for(int i=0;i<len;i++)

    Serial.write(message[i]);

}