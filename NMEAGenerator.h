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

//TODO Limita rel tamaño al maximo de las tramas NMEA (creoq ue 82)
//Messages have a maximum length of 82 characters, including the $ or ! starting character and the ending <LF>
//https://en.wikipedia.org/wiki/NMEA_0183#Message_structure
//Esto es lo maximo
//$PSBWQS,53,4.92382,0.77598,0.77598,0.77598,0.77598,0.778,0.77598,0.7798,0.77*3C\r\n
//Termina con \r\n

class NMEAGenerator
{
public:
	NMEAGenerator();
	NMEAGenerator(char, char*, char);
	NMEAGenerator(char, char*, char, uint8_t);
	void getSentence(char*, bool = true); //Obtiene la trama y limpia para la siguiente
	void print(Stream&, bool = false); //Imprime la trama en el Stream pasado como parametro
	void begin(char, char*, char, uint8_t); //Fija nuevvos parametros para la trama y reinicia
	bool isReady(void); //Indica si ya tenemos una sentencia completa que devolver
	uint8_t currentField(); //Indica que campo de la trama es el ultimo que se añadio
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
	String* _tmpstr;
	char* _header;
	char _initChar;
	char _endChar;
	uint8_t _fieldCount;
	uint8_t _currentField;
	void _resetState(); //Reinicia el estado del objeto
	int _generateCRC();
};

#endif

