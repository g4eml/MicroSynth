# MicroSynth
## A Tiny  160 MHz to 1297 MHz RF Synthesiser Module using the CMT2119A Chip.

## Description
The CMT2119A chip is designed as a low cost remote control transmitter operating between 240 and 960 MHz. It is software programmable and has an onboard EEPROM to store its settings. As such it can operate without a separate microcontroller and only needs a 26 MHz reference Crystal and output matching components. 
The datasheet states that the device can be programmed to operate on any frequency between 240 MHz and 960 MHz, some experimenting has shown that in practice this can be extended to aproximately 160MHz and 1297 MHz although this range may vary between chips. Some reverse engineering was done to determine the exact programming sequence needed, this is detailed in this document https://github.com/g4eml/MicroSynth/blob/main/Documents/CMT2119A%20Programming%20Notes.pdf . 

## Construction
Full schematics and PCB design are included in this repository. The CMT2119A devices are available from AliExpress. The NT3225SA 26.000 Mhz TCXO can be found from many suppliers. The remaining components are not critical. 

## Programming
Progamming can be done with my RP2040_Synth Programmer which can be found here https://github.com/g4eml/RP2040_Synth .

## Tuning
The matching components may need to be selected for optimum output on your desired frequency according to the table in the schematic. Populating with the 'Wideband' components will work for any frequency but the output will contain harmonics as it is a square wave.
Ouput power in the 'Wideband' configuration ranges from approx +13 dBm at 160 MHz to approx 0dBm at 1296 MHz.  

