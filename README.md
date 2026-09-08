# MicroSynth
## A Tiny  160 MHz to 1297 MHz RF Synthesiser Module using the CMT2119A Chip.

## Description
The CMT2119A chip is designed as a low cost remote control transmitter operating between 240 and 960 MHz. It is software programmable and has an onboard EEPROM to store its settings. As such it can operate without a separate microcontroller and only needs a 26 MHz reference Crystal and output matching components. 
The datasheet states that the device can be programmed to operate on any frequency between 240 MHz and 960 MHz, some experimenting has shown that in practice this can be extended to aproximately 160MHz and 1297 MHz although this range may vary between chips. Some reverse engineering was done to determine the exact programming sequence needed, this is detailed in this document https://github.com/g4eml/MicroSynth/blob/main/Documents/CMT2119A%20Programming%20Notes.pdf . 

## Construction
Full schematics and PCB design are included in this repository. The CMT2119A devices are available from AliExpress. The NT3225SA 26.000 Mhz TCXO can be found from many suppliers. The remaining components are not critical. 

## Programming

Programming of the CMT2119A chip is done using a RP2040 Zero module which can be created as follows:-

1. Locate the latest compiled firmware file 'MicroSynth.uf2' which will be found here https://github.com/g4eml/MicroSynth/releases and save it to your desktop. 

2. Hold down the BOOTSEL button on the RP2040 module while connecting it to your PC using its USB port. The RP2040 should appear as a USB disk drive on your PC.

3. Copy the .uf2 file onto the USB drive. The RP2040 will recognise the file and immediately update its firmware and reboot.

4. Windows 10 and above should automatically load the necessary driver and allocate a Com Port to the RP2040.

To enter programming mode you need to connect to the USB serial port using a terminal program such as Putty or Terraterm. Pressing any key should result in the menu being displayed.

### Connections for programming

| RP2040 | CMT2119A |
| :---:  |  :---:   |
|3V3     |   VDD    |
|GND     |   GND    |
|GPO6    |  DATA    | 
|GPO7    |   CLK    | 


The Arduino Sketch is also included in this repository if you need to make any changes. 

More comprehensive control of the CMT2119A can also be done by using my RP2040_Synth Programmer which can be found here https://github.com/g4eml/RP2040_Synth .

## Tuning
The matching components may need to be selected for optimum output on your desired frequency according to the table in the schematic. Populating with the 'Wideband' components will work for any frequency but the output will contain harmonics as it is a square wave.
Ouput power in the 'Wideband' configuration ranges from approx +13 dBm at 160 MHz to approx 0dBm at 1296 MHz.  

