#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int ledPin = 13; 
int numRuns = 1;   // execution count, so this doesn't run forever
int maxRuns = 10;   // maximum number of times the Choreo should be executed

void setup() {
  Serial.begin(9600);
  
     // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);

  
  // For debugging, wait until a serial console is connected.
  delay(4000);
  while(!Serial);
  Bridge.begin();
}
void loop()
{
  if (numRuns <= maxRuns) {
    Serial.println("Running Tweets - Run #" + String(numRuns++));
    
    TembooChoreo TweetsChoreo;

    // invoke the Temboo client
    TweetsChoreo.begin();
    
    // set Temboo account credentials
    TweetsChoreo.setAccountName(TEMBOO_ACCOUNT);
    TweetsChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    TweetsChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // Set credential to use for execution
    TweetsChoreo.setCredential("username");
    
    // set choreo inputs
    TweetsChoreo.addInput("Query", "#hashtag");
    
    // identify choreo to run
    TweetsChoreo.setChoreo("/Library/Twitter/Search/Tweets");
    
    // run choreo; when results are available, print them to serial
    TweetsChoreo.run();
    
    while(TweetsChoreo.available()) {
      char c = TweetsChoreo.read();
      Serial.print(c);
      
      //new manipulated code to make the LED light
       digitalWrite(ledPin, HIGH);   // sets the LED on
  delay(10000);                  // waits for 10 seconds
  digitalWrite(ledPin, LOW);    // sets the LED off
  delay(10000);                  // waits for 10 seconds
      
    }
  
  }

  Serial.println("Waiting...");
  delay(30000); // wait 30 seconds between Tweets calls
}
