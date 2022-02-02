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

