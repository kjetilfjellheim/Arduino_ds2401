#include <OneWire.h>

/**
 * Pin the DS2401 is connected to.
 */
#define ONEWIRE_PIN             10
/**
 * Address size.
 */
#define ONE_WIRE_ADDRESS_SIZE   8
/**
 * Serial baud speed.
 */
#define SERIAL_BAUD             9600
/**
   Object for communicating with the OneWire bus.
*/
OneWire onewire(ONEWIRE_PIN);

/**
   Address of the component found.
*/
byte owAddr[ONE_WIRE_ADDRESS_SIZE];

void setup() {
  /**
     Serial communication speed. This is only for serial information back.
  */
  Serial.begin(SERIAL_BAUD);

  /**
     Initalize onewire.
  */
  onewire.reset();

}

void loop() {
  /**
   * Verify that component is present.
   */
  boolean present = onewire.search(owAddr);
  printPresent(present);  
  if (present) {
    /**
     * Print component address.
     */
    printData();
    /**
     * Calculate crc code. It should be equal to the last byte.
     */
    byte crc = OneWire::crc8(owAddr, 7);
    printCrc(crc);
  } 
}

/**
 * Print present result.
 */
void printPresent(int present) {
  Serial.print("Present: ");
  Serial.println(present);
}

/**
   Print data.
*/
void printData() {
  Serial.print("Data: ");
  for (int i = 0; i < ONE_WIRE_ADDRESS_SIZE; i++) {
    Serial.print(owAddr[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

/**
   Print crc result.
*/
void printCrc(byte crc) {
  Serial.print("CRC: ");
  Serial.println(crc, HEX);
}




