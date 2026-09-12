// Menu routines for programming
//
// Minimal menu: Reference Oscillator, Frequency entry, Calculate frequency,
// and Program CMT2119A. Channel selection/switching, the external multiplier,
// and raw register view/edit have all been removed for a simple single-chip
// programmer.

void flushInput(void)
{
   while(Serial.available())
   {
     Serial.read();
   }
}

double inputFloat(void)
{
  bool done = false;
  String s;
  char ch;
  put_pixel(RED);
  flushInput();
  s = "";
    while(!done)
    {
      while(Serial.available() == 0);
      ch = Serial.read();
      if(ch == 13)
      {
        Serial.println();
        done = true;
      }
      else
      {
      Serial.print(ch);
      s += ch;

      if(((ch == 8) || (ch == 127)) && (s.length() >1))
        {
          s.remove(s.length() -2);
        }
      }
    }
  put_pixel(BLUE);
  return s.toDouble();
}

void showMenu(String *list)
{
 int i = 0;

 Serial.print("\n");
 Serial.print("Chip type is CMT2119A");
 Serial.println();
 Serial.print("Ref Osc =  ");
 Serial.print(refOsc , 10);
 Serial.println(" MHz");
 Serial.println();
  while(list[i] != "$$$")
  {
    Serial.println(list[i++]);
  }
}

char getSelection(String p)
{
 char resp;
  put_pixel(RED);
  Serial.println();
  Serial.print(p);

  while(Serial.available() == 0);
  resp = Serial.read();
   if(resp > 31) Serial.println(resp);
  delay(100);
  flushInput();

  put_pixel(BLUE);
  return resp;
}

void enterOsc(void)
{
  double oscFreq = 0;
  Serial.print("\nCurrent Reference Oscillator is ");
  Serial.print(refOsc , 10);
  Serial.print(" MHz\r\nEnter New Reference Oscillator Frequency in MHz --> ");
  oscFreq = inputFloat();
  if ((oscFreq >= CMTMINOSC) && (oscFreq <= CMTMAXOSC))
    {
      refOsc = oscFreq;
    }
}

void mainMenu(void)
{
  char resp;
  double temp;
  double mfreq;
  double error;
  String menuList[] = {"R = Read Registers from Existing CMT2119A", "F = Enter Output Frequency", "P = Program CMT2119A", "O = Set Reference Oscillator Frequency" , "A = Adjust Ref Osc.", "C = Calculate and display freq from current settings" , "X = Exit Menu" , "$$$"};

   Serial.println("");
   Serial.print("Micro_Synth (CMT2119A) Controller Version ");
   Serial.println(VERSION);
   flushInput();
   showMenu(menuList);
   do
    {
      resp = getSelection("Enter Command (? for menu) -->");
      switch(resp)
      {
        case 'F':
        case 'f':
        Serial.print("Current Frequency is ");
        Serial.print(cmtGetFrequency(),10);
        Serial.println(" MHz");

        cmtSetFrequency(0);

        cmtUpdate();
        Serial.println("\nFrequency Updated in RAM. Program chip if you want this to be permanent");
        break;

        case 'O':
        case 'o':
        temp = cmtGetFrequency();
        enterOsc();
        Serial.println("Recalculating frequency with new Ref Osc.");
        cmtSetFrequency(temp);
        cmtUpdate();
        break;
        
        case 'A':
        case 'a':
        Serial.println("\nReading registers from connected CMT2119A...");
        cmtReadFromChip();
        Serial.println("Registers read.");
        temp=cmtGetFrequency();
        Serial.print("Programmed Frequency = ");
        Serial.print(temp,10);
        Serial.println(" MHz");
        Serial.print("Current Ref Osc. Value = ");
        Serial.print(refOsc,10);       
        Serial.println(" MHz");
        Serial.print("\nEnter Measured Frequency in MHz -->");
        mfreq = inputFloat();
        error = mfreq/temp;
        if((error > 1.001) | (error < 0.999))
         {
          Serial.println("Error too large, no adjustment possible.");
          break;
         }
        Serial.println("Recalculating registers with corrected Ref Osc.");
        refOsc=refOsc*error;
        cmtSetFrequency(temp);
        cmtUpdate();
        Serial.print("New Frequency = ");
        Serial.print(cmtGetFrequency(),10);
        Serial.println(" MHz");
        Serial.print("New Ref Osc. Value = ");
        Serial.print(refOsc,10);       
        Serial.println(" MHz");
        Serial.println("\nFrequency Updated in RAM.\nProgram chip if you want this to be permanent");
        break;

        case 'C':
        case 'c':
        cmtCalcFreq();
        break;

        case 'P':
        case 'p':
        resp = getSelection("This will burn the current settings to the CMT2119A's internal EEPROM. Continue? Y or N --->");
        if((resp == 'Y') || (resp == 'y'))
          {
            cmtEepromBurn();
          }
        break;

        case 'R':
        case 'r':
        Serial.println("\nReading registers from connected CMT2119A...");
        cmtReadFromChip();
        Serial.println("Registers read.");
        Serial.print("Calculated Frequency = ");
        Serial.print(cmtGetFrequency(),10);
        Serial.println(" MHz");
        break;

        case '?':
        showMenu(menuList);
      }

    }
    while((resp != 'X')&&(resp != 'x'));
}
