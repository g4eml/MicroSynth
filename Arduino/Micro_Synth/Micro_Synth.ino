// Micro_Synth - CMT2119A Synthesiser controller using RP2040
//
// Minimal single-chip frequency programmer for the CMT2119A: Set Reference
// Oscillator, Enter Output Frequency, Calculate Frequency, and Program
// CMT2119A (burn to the chip's own EEPROM). No channels, no external
// multiplier, no raw register inspection, and no RP2040-side settings
// storage - the CMT2119A's own EEPROM (via the "Program CMT2119A" menu
// option) is this project's only persistence.

#define VERSION 1.00

uint32_t cmtReg[21];      //the CMT2119A's 21 registers (single set - no channels)

double refOsc = 26.000;   //reference oscillator frequency in MHz

#include "Pio_WS2812.pio.h"               //LED on the Rp2040-Zero

void setup()
{
  setup_Pio_WS2812(16);                 //Setup LED on Rp2040-Zero
  put_pixel(GREEN);
  Serial.begin();                       //USB serial port

  delay(1000);
  cmtInit();
  cmtSetDefault();                      //load the chip's default registers.
}

void loop()
{
  Serial.print("\n");
  Serial.print("CMT2119A Synthesiser programmer. Press Any Key for Menu.");
  Serial.println();

  while(1)
   {
      if(Serial.available() > 0 )          //test for USB command connected
     {
       put_pixel(BLUE);                   //BLUE = menu active
       mainMenu();                         //timing loop stops while the menu system is running.
       delay(10);
       put_pixel(GREEN);                    // Menu Exited
       cmtUpdate();
       Serial.print("\nSynthesiser programmed. Press any key for menu");
       delay(500);
       flushInput();
     }

   }

}
