//LIBRERIA DE lectura y escritura  V1.0 -CONFIRMADA 25/01/2022
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


uint16_t baudrate = 19200;
int TX =2;//DE y RE-HABILITACION O DESACTIVACION DE LA TX
///////////////////////////////
uint8_t  address=  0x02;
uint16_t reg=      1219;
uint16_t msg=      1084;//solo se usa en Write EN message el valor no importa es Fx=0x03 read
///////////////////////////////

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // put your setup code here, to run once:
  SerialModbus_initialize(ModbusSerial1,baudrate);
  pinMode(TX,OUTPUT);
}

void loop() {
  
  //Modbus_Write_function(address,reg,msg);
  
  uint16_t valor= Modbus_Read_function(address,reg);
  Serial.println("voltaje: ");
  Serial.println(valor);
  
  delay(1000);
}
