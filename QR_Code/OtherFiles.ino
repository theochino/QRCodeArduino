#include <stdint.h>
#include <TouchScreen.h> 
#include <TFT.h>

#define TS_MINX 140 
#define TS_MAXX 900
#define TS_MINY 120
#define TS_MAXY 940

#define DRAW Tft.fillRectangle
#define DRAW2 Tft.fillRectangleDebug

void getXY(unsigned char x1, unsigned char y1, unsigned char *x, unsigned char *y) {
	*x = (y1 / 10) - 4;
	*y = 22 - (x1 / 10);
}

void PrintDebug(unsigned char xPos, unsigned char yPos,
								unsigned char x, 
								unsigned char y, unsigned char *BitStream, int counter, byte mask, int result, int bitmask) {

	Serial.print("\nCounter: ");
	Serial.print(counter);

	Serial.print("\tMask: ");
	Serial.println(bitmask);
			
	Serial.print("xPos: ");
	Serial.print(xPos);
	Serial.print(" yPos: ");
	Serial.print(yPos);
	Serial.print(" x: ");
	Serial.print(x);
	Serial.print(" y: ");
	Serial.println(y);
	Serial.print("Bits: ");
	printBits(*BitStream);
	Serial.print("\t Mask: ");
	Serial.print(mask);
	
	Serial.print("\t=> Result: ");
	Serial.println(result);
	
}
	

void DrawBits(byte *BinaryMessage) {

	unsigned char x = 0, y = 0, xPos, yPos;
	byte binmask = 0x80;
	int counter = 0;
	

	//byte TypeInfomationBits[15] = { 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1 };
	byte TypeInfomationBits[15] = { 1, 1, 1, 1, 1, 0, 1,      1, 0, 1, 0, 1, 0, 1, 0 };
	PrintLongLine (BinaryMessage, 8);


	//format & version information fields
	for(int i = 210; i > 140; i-=10) {
		if(TypeInfomationBits[counter] == 1) {			
			DRAW(i, 170, 10, 10, BLACK);
			//DRAW2(i, 170, 10, 10, RED);
		} 
		counter++;
		//delay (100);
	}
	
	
		
	for(int i = 120; i > 40; i-=10){
		if( TypeInfomationBits[counter] == 1 ){
			 DRAW(90, i, 10, 10, BLACK);
			//DRAW(90, i, 10, 10, BLUE);
		}
		counter++;  
		//delay (100);
	}

	//Clear counter to display information bits again
	counter = 0;
	
	for(int i = 250; i > 190; i-=10){
		if(TypeInfomationBits[counter] == 1){
			DRAW(90,i,10,10,BLACK);
			//DRAW(90, i, 10, 10, GREEN);
		}	
		counter++;
		//delay (100);
	}

	if (TypeInfomationBits[counter] == 1) {
		DRAW(90,180,10,10,BLACK);
		//DRAW(90,180,10,10,YELLOW);
	}
	counter++;
	//delay (100);

	if (TypeInfomationBits[counter] == 1) {
		DRAW(90,170,10,10,BLACK);
			//	DRAW(90,170,10,10,CYAN);
	} 
	counter++; 
	//delay (100);

	if(TypeInfomationBits[counter] == 1) {
		DRAW(80,170,10,10,BLACK);
				//DRAW(80,170,10,10,BRIGHT_RED);
	} 
	counter++;
	//delay (100);

	for(int i = 60; i > 0; i-=10) {
		if(TypeInfomationBits[counter] == 1) {
			DRAW(i,170,10,10,BLACK);
					//DRAW(i,170,10,10,GRAY2);
		}
		counter++; 
		//delay (100);
	}



//delay(10000);

	//end format & version 
	//clear counter for message bits
	counter = 0;
	
	/*
	 for( xPos = 210; xPos > 90; xPos-=10){
    for( yPos = 50; yPos < 70; yPos+=10){
      getXY(xPos, yPos, &y, &x);
      
     
        if((y + x) % 2 == 0){
          if((*BinaryMessage & binmask) != 0) {
            //Do oposite
            Tft.fillRectangle(xPos,yPos,10,10,WHITE);
          }
           
          if((*BinaryMessage & binmask) == 0){
            //Do oposite
            Tft.fillRectangle(xPos,yPos,10,10,BLACK);
          }
          
        } else if((y + x) % 2 == 1){
          if((*BinaryMessage & binmask) != 0){
            //Do oposite
            Tft.fillRectangle(xPos,yPos,10,10,BLACK);
          }
           
          if((*BinaryMessage & binmask) == 0){
            //Do oposite
            Tft.fillRectangle(xPos,yPos,10,10,WHITE);
          }
               
        }
        
     	binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
    }
  } 
	
	
	//Write Data Bits
	//up  
	
	for(xPos = 210; xPos > 90; xPos-=10) {
		for(yPos = 50; yPos < 70; yPos+=10) {
			
			
			
		
			
			if (((((y + x) % 2) != 0) && ((*BinaryMessage & binmask) != 0)) || (((y + x) % 2) == 0 && ((*BinaryMessage & binmask) != 0))) {		
				DRAW(xPos,yPos,10,10,BLACK);
			} else { 
				DRAW(xPos,yPos,10,10,WHITE);
			}
			
		
			
			binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
		}
	}
	
	return;
*/
	

	for(int xPos = 210; xPos > 90; xPos-=10){
		for(int yPos = 50; yPos < 70; yPos+=10){
			getXY(xPos, yPos, &x, &y);

			int mask = (y + x) % 2;			
	//			int mask = x % 2;
			PrintDebug(x, y, xPos, yPos, BinaryMessage, counter, binmask, (*BinaryMessage & binmask), mask);
			
			if (mask == 0) {
				
				if((*BinaryMessage & binmask) == 0){
					//Do oposite
					Serial.println("GREEN");
					Tft.fillRectangle(xPos, yPos, 10, 10, GREEN); //WHITE
					Tft.fillRectangle(xPos, yPos, 10, 10, WHITE); //WHITE
				} 
				
				if((*BinaryMessage & binmask) != 0){
					//Do oposite
					Serial.println("RED");
					Tft.fillRectangle(xPos, yPos, 10, 10, RED); //BLACK
					//Tft.fillRectangle(xPos, yPos, 10, 10, BLACK); //WHITE

				}
				
			} else if (mask == 1) {
				
				if((*BinaryMessage & binmask) == 0){
					//Do oposite
					Serial.println("BLUE");
					Tft.fillRectangle(xPos, yPos, 10, 10, BLUE); // BLACK
					//Tft.fillRectangle(xPos, yPos, 10, 10, BLACK); // BLACK
				}
				
				if((*BinaryMessage & binmask) != 0){
					//Do oposite
					Serial.println("YELLOW");
					Tft.fillRectangle(xPos, yPos, 10, 10, YELLOW); // WHITE
					Tft.fillRectangle(xPos, yPos, 10, 10, WHITE); // WHITE
				}
				
			}
			
			// delay (00);				
			binmask >>= 1;
			
			if ( counter++ > 7  ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
				return;
			}
		}
	}
	
//down
	for(int xPos = 100; xPos < 220; xPos +=10){
		for(int yPos = 70; yPos < 90; yPos+=10){
			getXY(xPos, yPos, &x, &y);
//			int mask = (y + x) % 2;			
				int mask = x % 2;			
			if(mask == 0){
				if((*BinaryMessage & binmask) != 0){
					//Do oposite
				Tft.fillRectangle(xPos,yPos,10,10,WHITE);
				}
				if((*BinaryMessage & binmask) == 0){
					//Do oposite
				Tft.fillRectangle(xPos,yPos,10,10,BLACK);
				}
			} else if(mask == 1) {
				if((*BinaryMessage & binmask) != 0){
					//Do oposite
					Tft.fillRectangle(xPos,yPos,10,10,BLACK);
				}
				if((*BinaryMessage & binmask) == 0){
					//Do oposite
					Tft.fillRectangle(xPos,yPos,10,10,WHITE);
				}
			}
			
			binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
		}
	}
	
	
//up
for(int xPos = 210; xPos > 90; xPos-=10){
for(int yPos = 90; yPos < 110; yPos+=10){
getXY(xPos, yPos, &x, &y);
//			int mask = (y + x) % 2;			
				int mask = x % 2;
if(mask == 0){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
}else if(mask == 1){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
}
	binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
}
}
//down
for(int xPos = 100; xPos < 220; xPos +=10){
for(int yPos = 110; yPos < 130; yPos+=10){
getXY(xPos, yPos, &x, &y);
//			int mask = (y + x) % 2;			
				int mask = x % 2;
if(mask == 0){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
}else if(mask == 1){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
}
	binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
}
}
//up
for(int xPos = 210; xPos > 170; xPos-=10){
for(int yPos = 130; yPos < 150; yPos+=10){
getXY(xPos, yPos, &x, &y);
//			int mask = (y + x) % 2;			
				int mask = x % 2;
if(mask == 0){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
}else if(mask == 1){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
}
	binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
}
}
//Clear counter to begin ECC Bits
counter = 0;
//continue up
for(int xPos = 170; xPos > 70; xPos-=10){
for(int yPos = 130; yPos < 150; yPos+=10){
getXY(xPos, yPos, &x, &y);
//			int mask = (y + x) % 2;			
				int mask = x % 2;
if(mask == 0){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
}else if(mask == 1){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
}
	binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
}
}
//skip over timing pattern
//up
for(int xPos = 60; xPos > 0; xPos-=10){
for(int yPos = 130; yPos < 150; yPos+=10){
getXY(xPos, yPos, &x, &y);
//			int mask = (y + x) % 2;			
				int mask = x % 2;
if(mask == 0){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
}else if(mask == 1){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
}
	binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
}
}
//down
for(int xPos = 10; xPos < 70; xPos +=10){
for(int yPos = 150; yPos < 170; yPos+=10){
getXY(xPos, yPos, &x, &y);
//			int mask = (y + x) % 2;			
				int mask = x % 2;
if(mask == 0){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
}else if(mask == 1){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
}
	binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
}
}
//skip over timing pattern
//down
for(int xPos = 80; xPos < 220; xPos +=10){
for(int yPos = 150; yPos < 170; yPos+=10){
getXY(xPos, yPos, &x, &y);
//			int mask = (y + x) % 2;			
				int mask = x % 2;
if(mask == 0){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
}else if(mask == 1){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
}
	binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
}
}
//up
for(int xPos = 130; xPos > 90; xPos-=10){
for(int yPos = 170; yPos < 190; yPos+=10){
getXY(xPos, yPos, &x, &y);
//			int mask = (y + x) % 2;			
				int mask = x % 2;
if(mask == 0){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
}else if(mask == 1){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
}
	binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
}
}
//down
for(int xPos = 100; xPos < 140; xPos +=10){
for(int yPos = 200; yPos < 220; yPos+=10){
getXY(xPos, yPos, &x, &y);
//			int mask = (y + x) % 2;			
				int mask = x % 2;
if(mask == 0){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
}else if(mask == 1){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
}
	binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
}
}
//up
for(int xPos = 130; xPos > 90; xPos-=10){
for(int yPos = 220; yPos < 240; yPos+=10){
getXY(xPos, yPos, &x, &y);
//			int mask = (y + x) % 2;			
				int mask = x % 2;
if(mask == 0){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
}else if(mask == 1){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
}
	binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
}
}
//down
for(int xPos = 100; xPos < 140; xPos +=10){
for(int yPos = 240; yPos < 260; yPos+=10){
getXY(xPos, yPos, &x, &y);
//			int mask = (y + x) % 2;			
				int mask = x % 2;
if(mask == 0){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
}else if(mask == 1){
if((*BinaryMessage & binmask) != 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,BLACK);
}
if((*BinaryMessage & binmask) == 0){
//Do oposite
Tft.fillRectangle(xPos,yPos,10,10,WHITE);
}
}
	binmask >>= 1;
			if ( counter++ > 7 ) {
				binmask = 0x80;
				BinaryMessage++;
				counter = 0;
			}
}
}
counter = 0;
}

void drawTemplate(void) {
	
	int ii;
	
	//TOP LEFT CORNER OUTER BOX 
	for (ii = 250; ii > 180; ii -= 10)
		DRAW(10, ii, 10, 10, BLACK);
	
	for (ii = 20; ii < 80; ii += 10)
		DRAW(ii, 250, 10, 10, BLACK);
	
	for (ii = 240; ii > 180; ii -= 10)
		DRAW(70, ii, 10, 10, BLACK);
	
	for (ii = 60; ii > 10; ii -= 10)
		DRAW(ii, 190, 10, 10, BLACK);
	//TOP LEFT CORNER OUTER BOX END  
	
	//TOP LEFT CORNER iiNSiiDE BOX START  
	for (ii = 210; ii < 240; ii += 10) {
		for (int j = 30; j < 60; j += 10) {
			DRAW(j, ii, 10, 10, BLACK);
		}
	}  
	//TOP LEFT CORNER iiNSiiDE BOX END
	
	//TOP RiiGHT OUTER BOX START
	for (ii = 50; ii < 120; ii += 10)
		DRAW(10, ii, 10, 10, BLACK);

	for (int j = 20; j < 80; j += 10) {
		DRAW(j, 50, 10, 10, BLACK);
		if ( j < 70) 
			DRAW(j, 110, 10, 10, BLACK);
	}

	for (ii = 60; ii < 120; ii += 10)
		DRAW(70, ii, 10, 10, BLACK);
	//TOP RiiGHT OUTER BOX END
	
	//TOP RiiGHT iiNNER BOX START
	for (ii = 70; ii < 100; ii += 10) {
		for (int j = 30; j < 60; j += 10) {
			DRAW(j, ii, 10, 10, BLACK);
		}
	}  
	//TOP RiiGHT iiNNER BOX END
	
	//BOTTOM RiiGHT OUTER BOX START
	for (int j = 150; j < 220; j += 10) {		
		DRAW(j, 250, 10, 10, BLACK);
		if ( j < 210) 
			DRAW(j, 190, 10, 10, BLACK);
	}
	
	for (ii = 190; ii < 250; ii += 10) {	
		DRAW(210, ii, 10, 10, BLACK);
		if (ii > 190) {
			DRAW(150, ii, 10, 10, BLACK);
		}
	}
	//BOTTOM RiiGHT OUTER BOX END
	
	//BOTTOM RiiGHT iiNNER BOX START
	for (ii = 210; ii < 240; ii += 10) {
		for (int j = 170; j < 200; j += 10) {
			DRAW(j, ii, 10, 10, BLACK);
		}
	}  
	//BOTTOM RiiGHT iiNNER BOX END
	
	//Tiimiing Pattern
	for (ii = 130; ii < 180; ii += 20)
		DRAW(70, ii, 10, 10, BLACK);

	for (int j = 90; j < 140; j += 20)
		DRAW(j, 190, 10, 10, BLACK);
	
	DRAW(140,170,10,10,BLACK);
	//end Tiimiing Pattern
}
