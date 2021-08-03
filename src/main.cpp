#include <Q2HX711.h>
#include<BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial AndroidBT;

const byte hx711_data_pin = 26;
const byte hx711_clock_pin = 25;

Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);
float zero;
int numb;
float weight;
void setup() {
  Serial.begin(9600);
  AndroidBT.begin("eGripper"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  delay(100);
  zero = hx711.read();
  Serial.print("Zero:");
  Serial.println(zero);
}

void loop() {
  weight = zero - hx711.read();
  numb = (int)(weight/1000);
  
    AndroidBT.println(numb);
  
  Serial.print("Force: ");
  Serial.print(weight);
  Serial.print("  Number: " );
  Serial.println(numb);
  delay(50);
}