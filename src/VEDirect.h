/******************************************************************
 VEDirect Arduino

 Copyright 2018, 2019, Brendan McLearie
 Distributed under MIT license - see LICENSE.txt

 See README.md

 File: VEDirect.h
 - Class / enums / API

 Updates:
 - 2019-07-14:
  	  - Rewrite of read - cleaner.
  	  - Target labels extendible with enum and PROGMEM strings
  	  - Retired copy_raw_to_serial0() code - use VE_DUMP on read
  	  - Added some tunable parameters see #defines
******************************************************************/

#ifndef VEDIRECT_H_
#define VEDIRECT_H_

#include <Arduino.h>

// Tunable parameters - defaults tested on mega2560 R3
#define VED_LINE_SIZE 30		 // Seems to be plenty. VE.Direct protocol could change
#define VED_MAX_LEBEL_SIZE 6	 // Max length of all labels of interest + '\0'. See ved_labels[]
#define VED_MAX_READ_LOOPS 60000 // How many read loops to be considered a read time-out
#define VED_MAX_READ_LINES 50	 // How many lines to read looking for a value
								 // before giving up. Also determines lines for diag dump
#define VED_BAUD_RATE 19200

#define VED_NODATA -2147483648

// https://github.com/SignalK/vedirect-serial-usb/blob/master/lib/fields.js

// Extend this and ved_labels[] for needed inclusions
enum VE_DIRECT_DATA {
	VE_DUMP = 0,
	VE_SOC,
	VE_VOLTAGE,
	VE_POWER,
	VE_CURRENT,
	VE_ALARM,
	VE_VOLTAGE_STARTER,
	VE_PANEL_VOLTAGE,
	VE_PANEL_POWER,
	VE_LAST_LABEL,
};

const char ved_labels[VE_LAST_LABEL][VED_MAX_LEBEL_SIZE] PROGMEM = {
		"Dump",	// a string that won't match any label
		"SOC",
		"V",
		"P",
		"I",
		"Alarm",
		"VS",
		"VPV",
		"PPV"
};

class VEDirect {
public:
	VEDirect(HardwareSerial& port);
	virtual ~VEDirect();
	uint8_t begin(int8_t rxPin = -1);
	int32_t read(uint8_t target, int8_t rxPin = -1);
	void copy_raw_to_serial0(); // kept for backwards compatibility
private:
	HardwareSerial& VESerial;
};

#endif /* VEDIRECT_H_ */
