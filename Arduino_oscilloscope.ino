
#include <U8glib.h> 
U8GLIB_ST7920_128X64_4X u8g(13, 12, 11); 
 int Input = A0;  
 int Key_add = 8; 
 int Key_sub = 9;
 int Key_hold = 10;
 int x,y; //声明坐标
 int i,i1,i2,V_min,V_max,V_mid,t,t0,t1,sta,Key=1,hold=0; 
 long Freq;
 float Vpp;
 int Y[96]; //声明信号值储存数组
 int Buffer[192]; 


 void setup( ) 
 { 
   pinMode(Key_add,INPUT); 
   digitalWrite(Key_add,HIGH); 
   pinMode(Key_sub,INPUT);
   digitalWrite(Key_sub,HIGH); 
   pinMode(Key_hold,INPUT);
   digitalWrite(Key_hold,HIGH); 
   ADMUX=0xe0;  
   ADCSRA=0xe2; 
   u8g.setFont(u8g_font_5x7); 
    u8g.firstPage();  
   do {
    } while( u8g.nextPage() );
   delay(2000); 
 } 
 
void loop( ) 
 { 
   sample( );
   Measure( ); 
   Transform( );
   Key_scan( );
   if(hold==0)
   {
     u8g.firstPage( );  
     do
     {
       draw( ); 
     }
     while( u8g.nextPage( ));
   }
 } 
 
 void sample( )  
{  for(i = 0;i < 192;i++)
   {  
    Buffer[i] = ADCH;
    switch(Key)
     {
       case 1:
       break;
       case 2:
       delayMicroseconds(4);  
       break;
       case 3:
       delayMicroseconds(10);
       break;
       case 4:
       delayMicroseconds(23);
       break;
       case 5:
       delayMicroseconds(60);
       break;
       case 6:
       delayMicroseconds(123); 
       break;
       case 7:
       delayMicroseconds(248);
       break;
       case 8:
       delayMicroseconds(623);
       break;
       case 9:
       delayMicroseconds(1247);
       break;
       default:break;
     }
   }
}

void Measure()
{
  V_max=Buffer[0];
  V_min=Buffer[0];      
  for(i=0;i<192;i++)
  { 
    if(Buffer[i]>V_max) 
    V_max=Buffer[i];
    if(Buffer[i]<V_min) 
    V_min=Buffer[i];
  }
  V_mid=(V_max+V_min)/2;  
  Vpp=(V_max-V_min)*1.1/255;
  for(i=0;i<97;i++)
  {
    if(Buffer[i]<V_mid&&Buffer[i+1]>=V_mid)  
    {
      i1=i;
      break;
    }
  }
  for(i=i1+1;i<98+i1;i++)
  {
    if(Buffer[i]<V_mid&&Buffer[i+1]>=V_mid)  
    {
      i2=i;
      break;
    }
  }
  t=i2-i1;
  if(t>0)
  Freq=8000/t;
  else
  Freq=0;
}

 void Transform( )  
{ 
  for(sta=0;sta<96;sta++)
  {
    if(Buffer[sta]<128&&Buffer[sta+2]>128)  
    break;
  } 
  for(i = 0;i < 96;i++)  
  Y[i] =  63-(Buffer[i+sta]>>2);     
}

void draw( )  
{  
for(x = 0;x < 95;x++)  
  u8g.drawLine(x,Y[x],x,Y[x+1]); //画线  
 
//画边框
u8g.drawFrame(0,0,97,64);
// 画坐标轴
 u8g.drawLine(48,0,48,63); 
 u8g.drawLine(0,32,96,32);
 for(x=0;x<96;x+=8)
   u8g.drawLine(x,31,x,33);
 for(y=0;y<64;y+=8)
   u8g.drawLine(47,y,49,y);
//画网格
for(x=8;x<96;x+=8)
 {
    for(y=8;y<64;y+=8)
    u8g.drawPixel(x,y);
 }
//显示参数 
 u8g.drawStr(98,7,"MS/div");
 u8g.drawStr(98,23,"V/div");
 u8g.drawStr(98,30,"0.324");
 u8g.drawStr(98,40,"Vpp");
 u8g.setPrintPos( 98, 47);
 u8g.print(Vpp);
 u8g.drawStr(118,47,"V");
 u8g.drawStr(98,55,"F(HZ)");
 switch(Key)
 {
      case  1:
      u8g.drawStr(98,14,"0.02");
      u8g.setPrintPos( 98, 62);
      u8g.print(Freq*50);
      break;
      case  2:
      u8g.drawStr(98,14,"0.05");
      u8g.setPrintPos( 98, 62);
      u8g.print(Freq*20);
      break;
      case  3:
      u8g.drawStr(98,14," 0.1");
      u8g.setPrintPos( 98, 62);
      u8g.print(Freq*10);
      break;
      case  4:
      u8g.drawStr(98,14," 0.2");
      u8g.setPrintPos( 98, 62);
      u8g.print(Freq*5);
      break;
      case  5:
      u8g.drawStr(98,14," 0.5");
      u8g.setPrintPos( 98, 62);
      u8g.print(Freq*2);
      break;
     case  6:
      u8g.drawStr(98,14,"  1");
      u8g.setPrintPos( 98, 62);
      u8g.print(Freq);
      break;
     case  7:
      u8g.drawStr(98,14,"  2");
      u8g.setPrintPos( 98, 62);
      u8g.print(Freq/2);
      break;
     case  8:
      u8g.drawStr(98,14,"  5");
      u8g.setPrintPos( 98, 62);
      u8g.print(Freq/5);
      break;
      case  9:
      u8g.drawStr(98,14," 10");
      u8g.setPrintPos( 98, 62);
      u8g.print(Freq/10);
      break;
    default:break;
   }
}

//键盘扫描
void Key_scan()
{
    if(digitalRead(Key_add)==LOW) 
	{
	  while(digitalRead(Key_add)==LOW);
	  Key++;
	  if(Key==10)
	  Key=9;
	  delay(10);
	}
	if(digitalRead(Key_sub)==LOW) 
	{
	  while(digitalRead(Key_sub)==LOW);
	  Key--;
	  if(Key==0)
	  Key=1;
	  delay(10);
        }
        if(digitalRead(Key_hold)==LOW) 
	{
	  while(digitalRead(Key_hold)==LOW);
          hold=~hold;
	  delay(10);
        }
}


 

