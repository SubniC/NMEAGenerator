/*
 * NMEAGenerator — BasicSentence
 *
 * Builds a 2-field NMEA sentence and prints it over Serial once per second.
 * Output looks like: $PSBWQS,53,4.92*<checksum>
 */

#include <NMEAGenerator.h>

// Start char '$', header "PSBWQS", end char '*', 2 fields.
NMEAGenerator nmea('$', "PSBWQS", '*', 2);

char buffer[128];

void setup() {
  Serial.begin(9600);
}

void loop() {
  nmea.append(53);        // field 1
  nmea.append(4.92382f);  // field 2

  if (nmea.isReady()) {
    // getSentence() appends the checksum and resets for the next sentence
    nmea.getSentence(buffer);
    Serial.println(buffer);
  }

  delay(1000);
}
