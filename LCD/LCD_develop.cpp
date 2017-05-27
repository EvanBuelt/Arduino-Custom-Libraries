#include "LCD_develop.h"
#include "Arduino.h"

lcd::lcd(int rs_pin, int rw_pin, int enable_pin) {
	
	_rs_pin = rs_pin;
	_rw_pin = rw_pin;
	_enable_pin = enable_pin;
}

void lcd::init(int fourbitmode) {
	
	if(fourbitmode) {
		setup(LCD_4BitMode);
	} else {
		setup(LCD_8BitMode);
	}
}

void lcd::setup(int fourbitmode) {
	functionSet(LCD_8BitMode, 0, 0);
	delayMicroseconds(50000);
	functionSet(LCD_8BitMode, 0, 0);
	delayMicroseconds(5000);
	functionSet(LCD_8BitMode, 0, 0);
	delayMicroseconds(200);
	functionSet(fourbitmode, LCD_1Line, LCD_5x8Dots);
	displayControl(0, 0, 0);
	clearDisplay();
	entrySetMode(1, 1);
}

// Direct instruction functions for LCD
void lcd::clearDisplay() {
	
	command(LCD_ClearDisplay);
	delayMicroseconds(2000); // Must wait 1.53ms, so waiting 2ms to be safe.
}

void lcd::returnHome() {
	
	command(LCD_ReturnHome);
	delayMicroseconds(2000); // Must wait 1.53ms, so waiting 2ms to be safe.
	
}

void lcd::entrySetMode(int direction, int shift_enable) {
	
	int data = LCD_EntryModeSet;
	if (direction) {
		data | LCD_DisplayRight;
	}
	if (shift_enable) {
		data | LCD_CursorRight;
	}
	
	command(data);
	delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe.
}

void lcd::displayControl(int display_on, int cursor_on, int blinking_on) {
	
	int data = LCD_DisplayControl;
	if (display_on) {
		data | LCD_DisplayOn;
	}
	if (cursor_on) {
		data | LCD_CursorOn;
	}
	if (blinking_on) {
		data | LCD_BlinkOn;
	}
	command(data);
	
	delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe
}

void lcd::cursorDisplayShift(int screen_shift, int direction) {
	
	int data = LCD_CursorShift;
	if (screen_shift) {
		data | LCD_MoveDisplay;
	}
	if (direction) {
		data | LCD_MoveRight;
	}
	command(data);
	
	delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe
}

void lcd::functionSet(int data_length, int number_lines, int display_font) {
	
	int data = LCD_CursorShift;
	if (data_length) {
		data | LCD_8BitMode;
	}
	if (number_lines) {
		data | LCD_2Line;
	}
	if (display_font) {
		data | LCD_5x10Dots;
	}
	command(data);
	
	delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe
}

void lcd::setCGRAMAddress(int CGRAM_address) {
	
	int data = LCD_SetCGRAddress;
	data | (CGRAM_address & 0x3F);
	command(data);
	
	delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe
}

void lcd::setDDRAMAddress(int DDRAM_address) {
	
	int data = LCD_SetDDRAddress;
	data | (DDRAM_address & 0x7F);
	command(data);
	
	delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe
}

// Direct data functions for LCD
int lcd::readAddress(void) {
	
	int data = 0;
	data = read(0);
	
	data = (data & 0x7F);
	return data;
}

int lcd::readBusyFlag(void) {
	
	int data = 0;
	data = read(0);
	
	data = ((data & 0x80) >> 7);
	return data;
	
}

void lcd::writeDataToRAM(int data) {
	
	write(data);
	
	delayMicroseconds(100); // Must wait 43us, so waiting 100us to be safe
}

int lcd::readDataFromRAM(void) {
	
	int data = 0;
	data = read(1);
	
	delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe
	
	return data;
}

inline void lcd::writeControl(int rs_data, int rw_data) {
	digitalWrite(_rs_pin, rs_data);
	digitalWrite(_rw_pin, rw_data);
}

void lcd::command(int data) {
	
	send(data, 0);
}

void lcd::write(int data) {
	
	send(data, 1);
}

int lcd::read(int rs_bit) {
	
	return receive(rs_bit);
}

inline void lcd::send(int value, int rs_bit) {
	
	writeControl(rs_bit, 0);
	
	if (_display_function & LCD_8BitMode) {
		write8bits(value);
	} else {
		write4bits(value>>4);
		write4bits(value);
	}
}

inline int lcd::receive(int rs_bit) {
	
	writeControl(rs_bit, 1);
	
	int data = 0;
	
	if (_display_function & LCD_8BitMode) {
		data = read8bits();
	} else {
		data = read4bits();
		data = (data << 4) | read4bits();
	}
	return data;
}

inline int lcd::read4bits() {
	int data = 0;
	DDRD = 0x00;
	
	pulseEnable();
	data = ((PORTD >> 4) & 0x0F); // Assume DB4-7 are connected.
	
	return data;
}

inline int lcd::read8bits() {
	int data = 0;
	DDRD = 0x00;
	
	pulseEnable();
	data = PORTD;
	return data;
}

inline void lcd::write4bits(int data) {
	
	DDRD = 0xFF;
	PORTD = (data & 0x0F);
	
	pulseEnable();
}
inline void lcd::write8bits(int data) {
	
	DDRD = 0xFF;
	PORTD = data;
	
	pulseEnable();
}

void lcd::pulseEnable() {
	digitalWrite(_enable_pin, LOW);
	delayMicroseconds(1);
	digitalWrite(_enable_pin, HIGH);
	delayMicroseconds(1); // Pulse width of enable high must be at least 240 ns.
	digitalWrite(_enable_pin, LOW);
}