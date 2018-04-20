#include <SPI.h>          //SPI is used to talk to the CAN Controller
#include <mcp_can.h>

MCP_CAN CAN(10);          //set SPI Chip Select to pin 10

unsigned int array_1[] = {0x423};
unsigned int array_2[] = {0x367, 0x394, 0x3d3};
unsigned int array_3[] = {0x228, 0x351, 0x3bb, 0xba};
unsigned int array_4[] = {0x262, 0x2e4, 0x3e6};
unsigned int array_5[] = {0x1aa, 0x384, 0x386,};
unsigned int array_6[] = {0x283, 0x365, 0x366, 0x3e7};
unsigned int array_7[] = {0x24, 0x25, 0xaa, 0xb4, 0x1c4, 0x1d0, 0x1d2, 0x1d3, 0x223, 0x224, 0x260, 0x2c1, 0x320, 0x343, 0x344, 0x380, 0x381, 0x389, 0x38f, 0x399, 0x3a5, 0x3b0, 0x3b1, 0x3b7, 0x3bc, 0x3e8, 0x3e9, 0x3f9, 0x411, 0x412, 0x413, 0x414, 0x420, 0x45a, 0x489, 0x48a, 0x48b, 0x4ac, 0x4cb, 0x4d3, 0x4ff, 0x610, 0x611, 0x614, 0x615, 0x619, 0x61a, 0x620, 0x621, 0x622, 0x623, 0x624, 0x638, 0x63c, 0x63d, 0x640, 0x680, 0x6f3, 0x770, 0x778, 0x7c6, 0x7ce, 0x7e0, 0x7e1, 0x7e2, 0x7e3, 0x7e4, 0x7e5, 0x7e6, 0x7e7, 0x7e8};

void setup()
{
  //tries to initialize, if failed --> it will loop here for ever
START_INIT:

  if (CAN_OK == CAN.begin(CAN_500KBPS))     //setting CAN baud rate to 500Kbps
  {
    //Serial.println("CAN BUS Shield init ok!");
  }
  else
  {
    goto START_INIT;
  }
}

//loading the data bytes of the message. Up to 8 bytes

void loop()
{
  unsigned int len2 = 3;
  unsigned int len3 = 4;
  unsigned int len4 = 3;
  unsigned int len5 = 3;
  unsigned int len6 = 4;
  unsigned int len7 = 71;



  unsigned char data1[1] = {0x00};
  unsigned char data2[2] = {0x0, 0x0};
  unsigned char data3[4] = {0x0, 0x0, 0x0, 0x0};
  unsigned char data4[5] = {0x0, 0x0, 0x0, 0x0, 0x0};
  unsigned char data5[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  unsigned char data6[7] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  unsigned char data7[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x90, 0x0};


  unsigned int temp1 = 0;
  unsigned int temp2 = 0;
  unsigned int temp3 = 0;
  unsigned int temp4 = 0;
  unsigned int temp5 = 0;
  unsigned int temp6 = 0;
  unsigned int temp7 = 0;
  CAN.sendMsgBuf(0x423, 0, 1, data1);
  for (int i = 0; i < len2; i++)
  {
    temp2 = array_2[i];
    CAN.sendMsgBuf(temp2, 0, 2, data2);
  }
  
  for (int i = 0; i < len3; i++)
  {
    temp3 = array_3[i];
    CAN.sendMsgBuf(temp3, 0, 4, data3);
  }
  
  for (int i = 0; i < len4; i++)
  {
    temp4 = array_4[i];
    CAN.sendMsgBuf(temp4, 0, 5, data4);
  }

  for (int i = 0; i < len5; i++)
  {
    temp5 = array_5[i];
    CAN.sendMsgBuf(temp5, 0, 6, data5);
  }

  for (int i = 0; i < len6; i++)
  {
    temp6= array_6[i];
    CAN.sendMsgBuf(temp6, 0, 7, data6);
  }

  for (int i = 0; i < len7; i++)
  {
    temp7 = array_7[i];
    CAN.sendMsgBuf(temp7, 0, 8, data7);
  }
}


