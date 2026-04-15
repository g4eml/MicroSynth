# MicroSynth
## A Tiny  150 MHz to 1297 MHz Rf Synthesiser Module using the CMT2119A Chip.

## Description
The CMT2119A chip is designed as a low cost remote control transmitter operating between 240 and 960 MHz. It is software programmable and has an onboard EEPROm to store its settings. As such it can operate without a separate microcontroller and only needs a 26 MHz reference Crystal and output matching components. 
The datasheet states that the device can be programmed to operate on any frequency between 240 MHz and 960 MHz, some experimenting has shown that in practice this can be extended to 150MHz and 1297 MHz. Some reverse engineering was done to determine the exact programming sequence needed, this is detailed in this document. 

## Construction
Full schematics and PCB design are included in this repository. The CMT2119A devices are available from AliExpress. The NT3225SA 26.000 Mhz TCXO can be found from many suppliers. The remainign components are not critical. 

## Programming
Progamming can be done with my RP2040_Synth Programmer which can be found here.

## Tuning
The matching components may need to be selected for optimum output on you rdesired frequency according to the table in the schematic. Populating with the 'Wideband' components will work for any frequency but the ouptut level may be reduced and will contain harmonics as it is a square wave. 

