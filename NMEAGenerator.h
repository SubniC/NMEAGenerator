// NMEAGenerator.h

#ifndef _NMEAGENERATOR_h
#define _NMEAGENERATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <WString.h>

#define MAX_NMEA_SENTENCE_LENGTH 128

// NMEA 0183 messages have a maximum length of 82 characters, including the
// leading '$' (or '!') and the trailing <CR><LF>. See:
// https://en.wikipedia.org/wiki/NMEA_0183#Message_structure
// Example: $PSBWQS,53,4.92382,0.77598,0.77598,0.77598,0.778,0.77598,0.77*3C\r\n

class NMEAGenerator
{
public:
	NMEAGenerator();
	NMEAGenerator(char, char*, char);
	NMEAGenerator(char, char*, char, uint8_t);
	void getSentence(char*, bool = true); // Copy the sentence to a buffer; optionally append CRC and reset
	void print(Stream&, bool = false);    // Print the sentence to the given Stream
	void begin(char, char*, char, uint8_t); // Set new sentence parameters and reset
	bool isReady(void);                   // True when all expected fields have been appended
	uint8_t currentField();               // Index of the last appended field
	void appendEmpty(void);
	void append(const String &);
	void append(const char *);
	void append(char);
	void append(unsigned char);
	void append(int);
	void append(unsigned int);
	void append(long);
	void append(unsigned long);
	void append(float);
	void append(double);
	void clear(void);
private:
	String* _sentence;
	char* _header;
	char _initChar;
	char _endChar;
	uint8_t _fieldCount;
	uint8_t _currentField;
	void _resetState(); // Reset the object to start a new sentence
	int _generateCRC();
};

#endif
