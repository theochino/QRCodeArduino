#include <TFT.h>

/*
This program takes the current time & displays it as an QR code
So far this program is capable of converting numbers 0-9, & 
characters : and (space) into QR code format. Then displays 
that information as a QR code on the screen.
*/


/* http://www.thonky.com/qr-code-tutorial/data-encoding */

#include <stdint.h>
#include <TFT.h>
#include <SPI.h>

#ifdef SEEEDUINO
  #define YP A2   // must be an analog pin, use "An" notation!
  #define XM A1   // must be an analog pin, use "An" notation!
  #define YM 14   // can be a digital pin, this is A0
  #define XP 17   // can be a digital pin, this is A3 
#endif

#ifdef MEGA
  #define YP A2   // must be an analog pin, use "An" notation!
  #define XM A1   // must be an analog pin, use "An" notation!
  #define YM A0   // can be a digital pin, this is A0
  #define XP A3   // can be a digital pin, this is A3 
#endif 

//Set to true to enable serial debug information
#define DEBUG 1

#define TS_MINX 140 
#define TS_MAXX 900
#define TS_MINY 120
#define TS_MAXY 940

//TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //init TouchScreen port pins

/*
	Error Correction Level	Error Correction Capability
	L	Recovers 7% of data
	M	Recovers 15% of data
	Q	Recovers 25% of data
	H	Recovers 30% of data
*/

byte TempBytes;

char MyMessageToEncode[] = "HELLO WORLD";
byte MessageToPush[40] = "";
byte MyDataString[150];
byte WholeWord[2];
unsigned int LocBytes = 0;

// Information about the QR	
byte DataMode = 2;
byte Version = 1;

// ToggleBinome
char ToggleBinome = 1;

void setup() {
	char BinomeCount;
	
	// Create the pointers.
	byte *pWholeWord 			= WholeWord;
	byte *pMessageToPush 	= MessageToPush;
	byte *pMyDataString 	= MyDataString;
	
	//unsigned int length, myLength;      

	/*
		Mode Name					Mode Indicator
		Numeric Mode			0001
		Alphanumeric Mode	0010
		Byte Mode					0100
		Kanji Mode				1000
		ECI Mode					0111
	*/
	 
	//Start Serial at 9600 baud
	Serial.begin(115200);
	Serial.print("\n\nStarting debug\n");
  
  //Init LCD
  Tft.init();
  //Tft.paintScreenBlack();
  Tft.fillRectangle(0, 0, 240,320, WHITE);
  //Tft.background(0,0,0);
  

	// First, add the version number
	ConcaternateBytes(pMyDataString, &DataMode, 4);		

	// Second, add the 	
	TempBytes = (byte) (strlen(MyMessageToEncode));		
	ConcaternateBytes(pMyDataString, &TempBytes, CalculateVersion(DataMode, Version));

	// All the binary data is appended into dataString
	// Cicle trought the letters.
 	int i = 0;
	for (i = 0; i < TempBytes; i++){		
		// This is the toggle.
		if ( ToggleBinome == 1 ) {
			BinomeCount = (ReturnCharEncoded(MyMessageToEncode[i]) * 45);
			ToggleBinome = 2;
						
		} else {
			BinomeCount += ReturnCharEncoded(MyMessageToEncode[i]);
			ToggleBinome = 1;
			
			// Need to find 11 bits.						
			*(pWholeWord+1)  = BinomeCount & 0xFF;  // Take just the lowest 8 bits.
			*pWholeWord = BinomeCount >> 8;  // Shift the integer right 8 bits.
			
	  	ConcaternateBytes(pMyDataString, pWholeWord, 11);
		}	
	}	
	
	if ( ToggleBinome == 2) {
			i--;
			BinomeCount = (ReturnCharEncoded(MyMessageToEncode[i]));
			*pWholeWord = BinomeCount & 0xFF;  // Take just the lowest 8 bits.		
			 ConcaternateBytes(pMyDataString, pWholeWord, 6);
	}
	
	*pWholeWord = 0x00;
	ConcaternateBytes(pMyDataString, pWholeWord, (8 - (LocBytes & 7)));
	
	for (int k = 0; k < (104 - LocBytes) / 8; k++) {
		
		if ( k % 2 == 0) {
			*pWholeWord = 236;
		} else {
			*pWholeWord = 17;
		}
		
		ConcaternateBytes(pMyDataString, pWholeWord, 8);		
	}
	
	LocBytes = decimal(pMyDataString, LocBytes);
	DrawBits(pMyDataString);
	drawTemplate();
}

void loop() {
  
}

/*
  Alphanumeric mode: 9 bits
  Alphanumeric mode: 11 bits
  Alphanumeric mode: 13 bits
  
  Byte mode: 8 bits
  Byte mode: 16
 	Byte mode: 16 bits

  Japanese mode: 8 bits    
  Japanese mode: 10 bits
  Japanese mode: 12 bits
  
  Numeric mode: 10 bits - Versions 1 through 9
  Numeric mode: 12 bits - Versions 10 through 26
  Numeric mode: 14 bits - Versions 27 through 40
*/

char CalculateVersion(char datamode, char version) {

	switch (datamode) {
		case 1:
			if (version < 10) return 10;
			else if (version > 9 && version < 27) return 12;
			else return 14;
			break;
			
		case 2:
			if (version < 10) return 9;
			else if (version > 9 && version < 27) return 11;
			else return 13;
			break;
			
		case 4:
			if (version < 10) return 8;
			else if (version > 9) return 16;
			break;
			
		case 8:
			if (version < 10) return 8;
			else if (version > 9 && version < 27) return 10;
			else return 12;
			break;
	}
}

int ReturnCharEncoded(char CharacterToReturn) {
	
	switch(CharacterToReturn) {
		case '0': return 0; break;
		case '1': return 1; break;
		case '2': return 2; break;
		case '3': return 3; break;
		case '4': return 4; break;
		case '5': return 5; break;
		case '6': return 6; break;
		case '7': return 7; break;
		case '8': return 8; break;
		case '9': return 9; break;
		case 'A': return 10; break;
		case 'B': return 11; break;
		case 'C': return 12; break;
		case 'D': return 13; break;
		case 'E': return 14; break;
		case 'F': return 15; break;
		case 'G': return 16; break;
		case 'H': return 17; break;
		case 'I': return 18; break;
		case 'J': return 19; break;
		case 'K': return 20; break;
		case 'L': return 21; break;
		case 'M': return 22; break;
		case 'N': return 23; break;
		case 'O': return 24; break;
		case 'P': return 25; break;
		case 'Q': return 26; break;
		case 'R': return 27; break;
		case 'S': return 28; break;
		case 'T': return 29; break;
		case 'U': return 30; break;
		case 'V': return 31; break;
		case 'W': return 32; break;
		case 'X': return 33; break;
		case 'Y': return 34; break;		
		case 'Z': return 35; break;
		case ' ': return 36; break;
		case '$': return 37; break;
		case '%': return 38; break;
		case '*': return 39; break;
		case '+': return 40; break;
		case '-': return 41; break;
		case '.': return 42; break;
		case '/': return 43; break;
		case ':': return 44; break;
		
	}
}

#ifdef DEBUG

void PrintLongLine (byte *pMyDat, int Loc) {
	
	Serial.print("Loc: ");
	Serial.print(Loc);
	Serial.print("\t- ");
	
	for (int i=0; i < Loc; i++) {
    printBits(*(pMyDat + i));
    Serial.print(" ");
  }
  Serial.print("\n");
}

void printBits( byte a ) {
  int i;

  /*            76543210  */
  byte mask = 0b10000000;           

  for ( i = 0; i <8; i++ ) {
		if ( (a & mask) != 0 )
    	Serial.print('1');
 		else
    	Serial.print('0');

		mask >>= 1;     /* Shift mask bit to right */
  }
  
}

void DebugPrintBytes(byte *BytesString, int SizeDone) {
	int Blocks = (SizeDone / 8) + 1;
	
	Serial.print ("\n################## Start DEBUG PRINT BYTES ####################################\n");
	Serial.print ("# Number of Blocks: ");
	Serial.print (Blocks);
	Serial.print ("\n");
	
	for (int i = 0; i < Blocks; i++) {
		Serial.print ("#\tBlock\t");
		Serial.print (i);
		Serial.print ("\tBytesString:\t");
		printBits(BytesString[i]);
		Serial.print ("\n");
	}
	
	Serial.print ("#\n# SizeDone : ");
	Serial.print (SizeDone);
	
	int Rest = (SizeDone / 8);
	int BlockRest = (Rest * 8);
	int WhereWeAre = SizeDone - BlockRest;
	
	Serial.print ("\tRest: ");
	Serial.print (Rest);
	
	Serial.print ("\tBlockRest (");
	Serial.print (Rest);
	Serial.print (" * 8) = ");
	Serial.print (BlockRest);
	
	Serial.print ("\tWhereWeAre (");
	Serial.print (SizeDone);
	Serial.print (" - ");
	Serial.print (BlockRest);
	Serial.print (") = ");
	Serial.print (WhereWeAre);
	
	Serial.print ("\n");
	
	Serial.print ("################## End DEBUG PRINT BYTES ######################################\n\n");
}

#endif
