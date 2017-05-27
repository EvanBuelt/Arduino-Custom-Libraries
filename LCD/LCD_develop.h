#ifndef LCD_develop_h
#define LCD_develop_h

#include "Arduino.h"

// Commands
#define LCD_ClearDisplay 0x01
#define LCD_ReturnHome 0x02
#define LCD_EntryModeSet 0x04
#define LCD_DisplayControl 0x08
#define LCD_CursorShift 0x10
#define LCD_FunctionSet 0x20
#define LCD_SetCGRAddress 0x40
#define LCD_SetDDRAddress 0x80

// Entry Mode Data
#define LCD_CursorLeft 0x00
#define LCD_CursorRight 0x01
#define LCD_DisplayLeft 0x00
#define LCD_DisplayRight 0x02

// Display Control Data
#define LCD_BlinkOff 0x00
#define LCD_BlinkOn 0x01
#define LCD_CursorOff 0x00
#define LCD_CursorOn 0x02
#define LCD_DisplayOff 0x00
#define LCD_DisplayOn 0x04

// Cursor Shift Data
#define LCD_MoveLeft 0x00
#define LCD_MoveRight 0x04
#define LCD_MoveCursor 0x00
#define LCD_MoveDisplay 0x08

// Function Set Data
#define LCD_5x8Dots 0x00
#define LCD_5x10Dots 0x04
#define LCD_1Line 0x00
#define LCD_2Line 0x08
#define LCD_4BitMode 0x00
#define LCD_8BitMode 0x10

class lcd {
	public:
	
	// Assuming db0-7 are connected to pins 0-7 (for port D operations on data).  Will update later
	lcd(int rs_pin, int rw_pin, int enable_pin);
	
	void init(int fourbitmode);
	
	// Direct instruction functions for LCD
	void clearDisplay();
	void returnHome();
	void entrySetMode(int, int);
	void displayControl(int, int, int);
	void cursorDisplayShift(int, int);
	void functionSet(int, int, int);
	void setCGRAMAddress(int);
	void setDDRAMAddress(int);
	
	// Direct data functions for LCD
	int readAddress();
	int readBusyFlag();
	void writeDataToRAM(int);
	int readDataFromRAM();
	
	// Eight commands, one write, and two read functions
	void command(int);
	void write(int);
	int read(int);
	
	private:
	
	// Support functions for writing to and reading from LCD
	void writeControl(int, int);
	void send(int, int);
	int receive(int);
	
	void write4bits(int);
	void write8bits(int);
	
	int read4bits();
	int read8bits(); 
	
	void pulseEnable();
	
	// First time setup for LCD
	void setup(int);
	
	int _rs_pin; // Low: Command.  High: Data
	int _rw_pin; // Low: Write.  High: Read
	int _enable_pin; // Pulse High for function
	
	int _display_function; // Sets data length (4-bit or 8-bit), number of display lines (1 or 2), and display font (5x8 or 5x11)
	int _display_control; // Sets Display, Cursor, and cursor Blinking on or off
	int _display_mode; // Cursor direction and enable shifting of display
};

#endif