
void Modbus_Write_function(uint8_t address1,uint16_t reg1,uint16_t msg1)
{
  Modbus_transmision_trama(address1,Modbus_Write,reg1,msg1);
} 

uint16_t Modbus_Read_function(uint8_t address2,uint16_t reg2)
{
  Modbus_transmision_trama(address2,Modbus_Read,reg2,0x01);//msg esta 0x01 por defecto
  delay(16);//wait to response RX OJO PONER DELAY para envio
    
    const int BUFFER_SIZE = 50;
    char buf[BUFFER_SIZE];
    if (Serial2.available() > 0) 
    {
      // read the incoming bytes:
      int rlen = Serial2.readBytes(buf, BUFFER_SIZE);
      
      //Serial.println(buf[4],HEX);
      
      uint16_t valor_two=buf[3]<<8;//MSB
      char valor=buf[4];//LSB
      
      uint16_t valor_changue= valor & 0xFF;//0xFF operador Bit
      uint16_t valor_total=valor_two+valor_changue;
      //Serial.println(valor_changue,HEX); 
      //Serial.println(valor_changue,DEC);
      return valor_total;  
    }
}

void Modbus_transmision_trama(uint8_t address_,uint8_t funcion_,uint16_t reg_,uint16_t msg_)
{
 
  msg_buffer=msg_;
  reg_buffer=reg_;
   
  if(reg_buffer>99)
  {
    regHI_= reg_buffer >> 8; // MSB
    reg_buffer=reg_buffer& 0xFF; // LSB
  }
  
  if(msg_buffer>99)
  {
    msgHI_= msg_buffer >> 8; // MSB
    msg_buffer=msg_buffer& 0xFF; // LSB
  }
  /*
  address_
  0x06
  regHI_
  reg_
  msgHI_
  msg_
  */  
   sprintf(buff,"%02X%02X%04X%04X",address_,funcion_,reg_,msg_);//fx se cambio por funcion_ , msg se cambio por msg__
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

  delay(100);//estaba en 500
  //delay(3000);//MODFICACIONES CONSIDERAR BORRAR
  digitalWrite(TX_pin,1);//escritura
  
  Serial2.write(address_);//ADDRESS ID SLAVE
  Serial2.write(funcion_);//funcion escritura0X03+++++++++++++++++++

  //REGISTER
  Serial2.write(regHI_);
  Serial2.write(reg_buffer);

  //MESSAGE
  Serial2.write(msgHI_);//00
  Serial2.write(msg_buffer);//C8

  //CRC
  Serial2.write(CRC_intHI_);
  Serial2.write(CRC_int);
  
  delay(6);//NO BORRAR
  digitalWrite(TX_pin,0);//lectura  
}

void SerialModbus_initialize(int Serial_input,uint16_t Baud)
{
    if(Serial_input==1)
    {
      //Serial1.begin(Baud,SERIAL_8E1);     
    }
    if(Serial_input==2)
    {
      Serial2.begin(Baud, SERIAL_8N1,16, 17);     
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
