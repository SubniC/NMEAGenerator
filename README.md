# NMEAGenerator

Arduino C++ library to **assemble and emit NMEA 0183 sentences** in an
object-oriented way.

You configure the start character, the talker/sentence header, the end
character and the number of fields. Then you `append()` values of any common
type, and the library builds the comma-separated sentence and computes the
NMEA checksum (XOR) for you.

> **Legacy library (2019).** Kept for reference; docs refreshed in 2026,
> library behavior unchanged.

## Features

- Build NMEA sentences field by field with overloaded `append()` for
  `String`, C-strings, `char`, integers (signed/unsigned), `long`, `float`
  and `double`.
- Automatic NMEA checksum generation (XOR over the payload, two hex digits).
- `getSentence()` to copy the result into a buffer, or `print()` to send it to
  any `Stream` (e.g. `Serial`).
- `isReady()` / `currentField()` to track how many fields have been added.
- Append empty fields with `appendEmpty()`.

## Installation

- **Manual**: copy this folder into your Arduino `libraries/` directory and
  restart the IDE.
- **PlatformIO**: add the repository to `lib_deps`.

## Usage

```cpp
#include <NMEAGenerator.h>

// Sentence: starts with '$', header "PSBWQS", ends with '*', 2 fields.
NMEAGenerator nmea('$', "PSBWQS", '*', 2);

char buffer[128];

void setup() {
  Serial.begin(9600);
}

void loop() {
  nmea.append(53);        // field 1
  nmea.append(4.92382f);  // field 2

  if (nmea.isReady()) {
    // Copy to a buffer (appends checksum and resets for the next sentence)
    nmea.getSentence(buffer);
    Serial.println(buffer);   // e.g. $PSBWQS,53,4.92*<XX>

    // Or print directly to a Stream:
    // nmea.print(Serial, true);
  }

  delay(1000);
}
```

See [`examples/BasicSentence`](examples/BasicSentence) for the full sketch.

## API

```cpp
NMEAGenerator();
NMEAGenerator(char initChar, char* header, char endChar);
NMEAGenerator(char initChar, char* header, char endChar, uint8_t fieldCount);

void begin(char initChar, char* header, char endChar, uint8_t fieldCount);

void append(const String&);
void append(const char*);
void append(char);
void append(unsigned char);
void append(int);
void append(unsigned int);
void append(long);
void append(unsigned long);
void append(float);
void append(double);
void appendEmpty();

bool    isReady();          // true when currentField() == fieldCount
uint8_t currentField();     // index of the last appended field

void getSentence(char* buffer, bool reset = true); // copy out (+CRC when reset)
void print(Stream& out, bool reset = false);       // print to a Stream
void clear();               // discard the current sentence and start over
```

## License

[MIT](LICENSE) © 2019–2026 mdps

---

_Un proyecto de mdps · 2026 · desarrollado en Murcia._
