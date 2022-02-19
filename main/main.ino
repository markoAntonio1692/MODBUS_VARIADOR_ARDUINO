//LIBRERIA DE lectura y escritura  V1.3 -CONFIRMADA 14/02/2022
//LIBRERIA DE lectura y escritura  V1.4 -CONFIRMADA 14/02/2022 19:30 PM 
//CODIGO PRUEBA ESP32
#define ModbusSerial1 1
#define ModbusSerial2 2
#define ModbusSerial3 3

#define Modbus_Read 0x03
#define Modbus_Write 0x06

char buff[30];
uint8_t regHI_=0;
uint8_t msgHI_=0;
uint8_t CRC_intHI_=0;
uint16_t msg_buffer=0;
uint16_t reg_buffer=0;

int i=0;
uint16_t baudrate = 19200;
int TX_pin =2;//DE y RE-HABILITACION O DESACTIVACION DE LA TX
///////////////////////////////
uint8_t  address=  0x02;
uint16_t reg_WRITE_c=      122;//122-voltaje 1613-frecuencia
uint16_t reg_WRITE=      2809;//(reg_WRITE_c*10)-1
uint16_t reg_READ_c=     122;//122-voltaje 1613-frecuencia-1672 prueba counter A
uint16_t reg_READ=      (reg_READ_c*10)-1;
uint16_t msg=      1148;//solo se usa en Write EN message el valor no importa es Fx=0x03 read
uint16_t msg2=      1084;
///////////////////////////////
unsigned long tiempoactual=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // put your setup code here, to run once:
  SerialModbus_initialize(ModbusSerial2,baudrate);
  //Serial2.setTimeout(1);
  pinMode(TX_pin,OUTPUT);
}

void loop() {
  //Modbus_Write_Read_function(uint8_t address_,uint16_t reg_WRITE_ ,uint16_t reg_READ2_ ,uint16_t msg12)
  /*
  uint16_t valora=Modbus_Write_Read_function(address,reg_WRITE,reg_READ,msg);
  Serial.print("voltaje motor1 = ");
  Serial.println(valora);
  delay(100);
  */
  /*
  Modbus_Write_function(address,reg_WRITE,msg);
  delay(5000);
  */
  
  //uint16_t valor= Modbus_Read_function(address,reg_READ);
  //Serial.println("voltaje motor ");
  //Serial.println(valor);  
  //delay(1000);
  
    uint16_t valora=Modbus_Write_Read_function(address,reg_WRITE,reg_READ,msg);
  Serial.print("ON- voltaje motor1 = ");
  Serial.println(valora);
  delay(5000);

  uint16_t voltaje=Modbus_Write_Read_function(address,reg_WRITE,reg_READ,msg2);
  Serial.print("OFF- voltaje motor2 = ");
  Serial.println(voltaje);
  delay(5000);
  
}
