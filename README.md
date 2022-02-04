# ModBus-RS845
Repositorio para libreria Mobdus para el control de variador Danfoss VLTMicro Drive FC51
![Danfoss-VLT-Micro-Drive-FC-51](https://user-images.githubusercontent.com/60046999/151054598-30cce8a7-47bf-4690-aabd-436097909bcd.jpg)


## LIBRERIA MODBUS

FUNCIONES PARA LA TRAMA DE MODBUS

![Captura](https://user-images.githubusercontent.com/60046999/150897983-f6116731-2717-47e0-88e3-dfd131dd2289.JPG)

## SCHEMATIC

CONEXION USANDO EL SERIAL1 

#### R0->RX1

#### RE->D2

#### DE->D2

#### DI->TX1

![schematic1](https://user-images.githubusercontent.com/60046999/151057889-2bdd6713-3509-4b3c-bdde-0428be71959a.png)

## DE-RE PIN DIGITAL
```
int TX =2;
pinMode(TX,OUTPUT);
```

## FUNCION DE INICIALIZACION

Iniciamos la comunicacion serial1 y seleccionamos el baudrate(19200 ModBus)
```
SerialModbus_initialize(ModbusSerial1,baudrate);
```

## FUNCION DE ESCRITURA 
Primer parametro Address Slave(0x02);
Segundo parametro Registro;
Tercer parametro Mensaje;
```
void Modbus_Write_function(uint8_t address1,uint16_t reg1,uint16_t msg1);
```

## FUNCION DE LECTURA
Primer parametro Address Slave(0x02);
Segundo parametro Registro;
El mensaje por defecto enviado es 0x01;
```
int Modbus_Read_function(uint8_t address2,uint16_t reg2);
```


## EJEMPLO DE ESCRITURA REGISTRO 1-22- SELECCION VOLTAJE MOTOR
```
uint8_t  address=  0x02;///
uint16_t reg=      1219;
uint16_t msg=      0x01;/
int TX =2;
void setup() {
  Serial.begin(9600);
  SerialModbus_initialize(ModbusSerial1,baudrate);
  pinMode(TX,OUTPUT);
  //unica vez de escritura 
  Modbus_Write_function(address_write,reg_write,msg_write);
  delay(2000);
}
```
