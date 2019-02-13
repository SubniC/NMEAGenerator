// 
// 
// 

#include "NMEAGenerator.h"



NMEAGenerator::NMEAGenerator()
{
}

NMEAGenerator::NMEAGenerator(char initChar, char* header, char endChar)
{
	begin(initChar, header, endChar, 1);
}

NMEAGenerator::NMEAGenerator(char initChar, char* header, char endChar, uint8_t fieldCount)
{
	begin(initChar, header, endChar, fieldCount);
}

void NMEAGenerator::begin(char initChar, char* header, char endChar, uint8_t fieldCount)
{
	_header = header;
	_fieldCount = fieldCount;
	_initChar = initChar;
	_endChar = endChar;
	_currentField = 0;
	//Inicializamos la cadena
	_sentence = new String(initChar);
	_sentence->reserve(MAX_NMEA_SENTENCE_LENGTH);
	_sentence->concat(header);
}

void NMEAGenerator::clear()
{
	_resetState();
}

void NMEAGenerator::getSentence(char* buffer, bool reset)
{
	char crchex[2] = { 0 };

	_sentence->concat(_endChar);

	if (reset)
	{
		int _crc = _generateCRC();
		//if (_crc < 0x10)
		//{
		//	_sentence->concat('0');
		//}
		sprintf(crchex, "%02X", _crc);
		_sentence->concat(crchex);
	}


	_sentence->toCharArray(buffer, MAX_NMEA_SENTENCE_LENGTH);

	if (reset)
		_resetState();
}

void NMEAGenerator::print(Stream& out_stream, bool reset)
{
	char crchex[2] = { 0 };

	if (reset)
	{
		_sentence->concat(_endChar);


		int _crc = _generateCRC();
		sprintf(crchex, "%02X", _crc);
		_sentence->concat(crchex);
		//if (_crc < 0x10)
		//{
		//	_sentence += '0';
		//}
		//*_sentence += String(_crc, HEX);
	}

	out_stream.printf("%s", _sentence);

	if (reset)
		_resetState();
}


bool NMEAGenerator::isReady()
{
	return (_currentField == _fieldCount);
}

void NMEAGenerator::_resetState()
{
	free(_sentence);
	_sentence = new String(_initChar);
	_sentence->concat(_header);
	_currentField = 0;
}

uint8_t NMEAGenerator::currentField()
{
	return _currentField;
}

int NMEAGenerator::_generateCRC()
{
	int crc = 0;
	uint_fast8_t i;
	//Serial.print(_sentence.substring(1, _sentence.length() - 1));
	// the first $ sign and the last two bytes of original CRC + the * sign
	for (i = 1; i < _sentence->length() - 1; i++) {
		//Serial.println(_sentence[i]);
		crc ^= (*_sentence)[i];
	}
	return crc;
}

void NMEAGenerator::appendEmpty()
{
	_currentField++;
	_sentence->concat(',');
}

void NMEAGenerator::append(const String &str)
{
	_currentField++;
	_sentence->concat(',');
	_sentence->concat(str);
}
void NMEAGenerator::append(const char *cstr)
{
	_currentField++;
	_sentence->concat(',');
	_sentence->concat(cstr);
}
void NMEAGenerator::append(char c)
{
	_currentField++;
	_sentence->concat(',');
	_sentence->concat(c);
}
void NMEAGenerator::append(unsigned char c)
{
	_currentField++;
	_sentence->concat(',');
	_sentence->concat(c);
}
void NMEAGenerator::append(int num)
{
	_currentField++;
	_sentence->concat(',');
	_sentence->concat(num);
}
void NMEAGenerator::append(unsigned int num)
{
	_currentField++;
	_sentence->concat(',');
	_sentence->concat(num);
}
void NMEAGenerator::append(long num)
{
	_currentField++;
	_sentence->concat(',');
	_sentence->concat(num);
}
void NMEAGenerator::append(unsigned long num)
{
	_currentField++;
	_sentence->concat(',');
	_sentence->concat(num);
}
void NMEAGenerator::append(float num)
{
	_currentField++;
	_sentence->concat(',');
	_sentence->concat(num);
}
void NMEAGenerator::append(double num)
{
	_currentField++;
	_sentence->concat(',');
	_sentence->concat(num);
}
