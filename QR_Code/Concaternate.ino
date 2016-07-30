#include <stdint.h>
#include <TouchScreen.h> 
#include <TFT.h>

// This add the bits to the end of the string. 	
// Make sure that the two first variable have enough room, there is no check
// inside the function.

// byte low =  BinomeCount & 0xFF;  // Take just the lowest 8 bits.
// byte high = BinomeCount >> 8;  // Shift the integer right 8 bits.

// BytesString = 	        The string we are building
// BytesToPush = 	        Bytes to copy to the BytesString
// LocBytes = 						Pointer of bits Already done.
// SizePerBlock = 				Size of the Block we are building.
// NumberOfBytesBlocks = 	Input Number of Blocks of size SizePerBlock that 
//												is included in the copy BytesToPush (How many bytes is Bytes to Push.)

// byte low =  BinomeCount & 0xFF;  // Take just the lowest 8 bits.
// byte high = BinomeCount >> 8;  // Shift the integer right 8 bits.

// BytesString = 	        The string we are building
// BytesToPush = 	        Bytes to copy to the BytesString
// LocBytes = 						Pointer of bits Already done.
// SizePerBlock = 				Size of the Block we are building.
// NumberOfBytesBlocks = 	Input Number of Blocks of size SizePerBlock that 
//												is included in the copy BytesToPush (How many bytes is Bytes to Push.)

void ConcaternateBytes(byte *BytesString, byte *BytesToPush, int SizePerBlock) {
																							
	byte i, bit = 0;
	int FirstTime = 0;
	byte *tempBytesString = BytesString;
	int TotalBits = SizePerBlock;
	
	byte mask = 0x80;
	
	int BytesToDo;
	int MoveBy;
	int BitsLeftOnGroup;
	int DoneInside = 0;
	
	int Blocker = 31;
	
	// Need to calculate how to work the BytesToPush
	int MoveBytesToPush = (int) (((SizePerBlock ) / 8));
	// Count the number of byte to grab from it
	int BitsFromLeftFromMove = ((SizePerBlock & 7));
		
	do {
		
		if ( FirstTime == 0 ) {
			
			// Need to move the pointer to the place where ByteString is located
			MoveBy = (int) ((LocBytes / 8));
			
			BitsLeftOnGroup = (8 - (LocBytes & 7));
			
			if ( BitsLeftOnGroup > SizePerBlock) {
				BitsLeftOnGroup = SizePerBlock;
				BytesToDo =  SizePerBlock & 7;
				
			} else if ( BitsFromLeftFromMove == 0) {
				BitsFromLeftFromMove = 8;
				MoveBytesToPush--;
			}
			
			BytesString += MoveBy;

			// First time, we set all the numbers.
			mask >>= (8 - BitsFromLeftFromMove);
			FirstTime = 1;

		} else {
			// This is where I count
			BitsLeftOnGroup = SizePerBlock - DoneInside;
		}		
		
		TotalBits -= BitsLeftOnGroup;

		do {
			
			// Mouve the mask for the BytesToPush.
			
			
			bit = 0;
			if ( (*BytesToPush & mask) != 0) bit = 1;
				
			mask >>= 1;
			*BytesString <<= 1;
			*BytesString += bit;
		
			// Carefull, can't go back more than what it was before.
			if ( mask == 0x00 ) {
				mask = 0x80;	
				BytesToPush++;
			}
					
			DoneInside++;
		} while ( (BitsLeftOnGroup--)   > 1  );

		// Move to the next Bytes.
		BytesString++;

	} while ( TotalBits > 1);


	// This will need to be done for speed sake
	// LocBytes += BytesToDo;

	LocBytes += DoneInside;
 
	return;
}


