//LIBRERIA DE lectura V1-CONFIRMADA 25/01/2022
#define ModbusSerial1 1
#define ModbusSerial2 2
#define ModbusSerial3 3

#define Modbus_Read 0x03

uint8_t regHI_=0;
uint8_t msgHI_=0;
uint8_t CRC_intHI_=0;

char buff[30];

uint8_t address=0x02;
uint8_t fx=Modbus_Read;//diferencia
uint16_t reg=1219;
uint16_t msg=1;//EN message el valor no importa es Fx=0x03 read

uint16_t baudrate=19200;

int TX =2;//DE y RE- HABILITACION O DESACTIVACION DE LA TX


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  SerialModbus_initialize(ModbusSerial1,baudrate);
  pinMode(TX,OUTPUT);
}

void loop() 
{
  
  Modbus_transmision(address,reg,msg);
  delay(16);//wait to response RX OJO PONER DELAY para envio
  
  const int BUFFER_SIZE = 50;
  char buf[BUFFER_SIZE];
  if (Serial1.available() > 0) 
  {
    // read the incoming bytes:
    int rlen = Serial1.readBytes(buf, BUFFER_SIZE);

    // prints the received data
    for(int i = 0; i < rlen; i++)
    Serial.println(buf[4]& 0xFF ,HEX);//0xFF operador Bit


    uint16_t buf_message_int=0;
    buf_message_int= strtol(buf[4]& 0xFF , NULL, 16);
    Serial.println(buf_message_int,DEC);  
  }
   delay(1000);//CADA SEGUNDO LECTURA
}


void Modbus_transmision(uint8_t address_,uint16_t reg_,uint16_t msg_)
{
  
  if(reg_>99)
  {
    regHI_= reg_ >> 8; // MSB
    reg_=reg_& 0xFF; // LSB
  }
  
  if(msg_>99)
  {
    msgHI_= msg_ >> 8; // MSB
    msg_=msg_& 0xFF; // LSB
  }
  /*
  address_
  0x06
  regHI_
  reg_
  msgHI_
  msg_
  */  
   sprintf(buff,"%02X%02X%04X%04X",address_,fx,reg,msg);
   //020604C300DE
   String buff_string = String(buff);
   
   String CRC_string= ModRTU_CRC(buff_string);
   
   char CRC_char[5]; //n+1
   CRC_string.toCharArray(CRC_char,5);

   uint16_t CRC_int=0;
   CRC_int= strtol(CRC_char, NULL, 16);
    
  if(CRC_int>99)
  {
    CRC_intHI_= CRC_int >> 8; // MSB
    CRC_int=CRC_int& 0xFF; // LSB
  }    

  delay(500);
  //delay(3000);//MODFICACIONES CONSIDERAR BORRAR
  digitalWrite(TX,1);//escritura
  
  Serial1.write(address_);//ADDRESS ID SLAVE
  Serial1.write(fx);//funcion escritura0X03+++++++++++++++++++

  //REGISTER
  Serial1.write(regHI_);
  Serial1.write(reg_);

  //MESSAGE
  Serial1.write(msgHI_);//00
  Serial1.write(msg_);//C8

  //CRC
  Serial1.write(CRC_intHI_);
  Serial1.write(CRC_int);
  
  delay(6);//NO BORRAR
  digitalWrite(TX,0);//lectura  
}


void SerialModbus_initialize(int Serial_input,uint16_t Baud)
{
    if(Serial_input==1)
    {
      Serial1.begin(Baud,SERIAL_8E1);
            
    }
    if(Serial_input==2)
    {
      Serial2.begin(Baud,SERIAL_8E1);      
    }
    /*
    *AÑADIR PARA DEMAS SERIALES.....
    */
}



// ************Compute the MODBUS RTU CRC*********************
String ModRTU_CRC(String raw_msg_data) {
  //Calc raw_msg_data length
  byte raw_msg_data_byte[raw_msg_data.length()/2];
  //Convert the raw_msg_data to a byte array raw_msg_data
  for (int i = 0; i < raw_msg_data.length() / 2; i++) {
    raw_msg_data_byte[i] = StrtoByte(raw_msg_data.substring(2 * i, 2 * i + 2));
  }

  //Calc the raw_msg_data_byte CRC code
  uint16_t crc = 0xFFFF;
  String crc_string = "";
  for (int pos = 0; pos < raw_msg_data.length()/2; pos++) {
    crc ^= (uint16_t)raw_msg_data_byte[pos];          // XOR byte into least sig. byte of crc
    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)

  //Become crc byte to a capital letter String 
  crc_string = String(crc, HEX);
  crc_string.toUpperCase();
  
  //The crc should be like XXYY. Add zeros if need it
  if(crc_string.length() == 1){
    crc_string = "000" + crc_string;
  }else if(crc_string.length() == 2){
    crc_string = "00" + crc_string;
  }else if(crc_string.length() == 3){
    crc_string = "0" + crc_string;
  }else{
    //OK
  }

  //Invert the byte positions
  crc_string = crc_string.substring(2, 4) + crc_string.substring(0, 2);
  return crc_string;  
}

//String to byte --> Example: String = "C4" --> byte = {0xC4}
byte StrtoByte (String str_value){
  char char_buff[3];
  str_value.toCharArray(char_buff, 3);
  byte byte_value = strtoul(char_buff, NULL, 16);
  return byte_value;  
}
