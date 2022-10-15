#define LED 13  // The pin the LED is connected to
#define   BUTTON_PIN  0    // Bouton du haut : plus

bool oldSelect = LOW;

void setup() {
  // put your setup code here, to run once:
/*** Boutons***/
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT); // Declare the LED as an output
}

void loop() {
  // put your main code here, to run repeatedly:

  bool newSelect = digitalRead(BUTTON_PIN);

 if (newSelect == HIGH && oldSelect == LOW) {
    // Short delay to debounce button.
    delay(10);
    // Check if button is still high after debounce.
    newSelect = digitalRead(BUTTON_PIN);
    if (newSelect == HIGH) {
    }
    oldSelect = newSelect;
 }
 
 digitalWrite(LED, HIGH); // Turn the LED on
 delay(1000);

 if (newSelect == LOW && oldSelect == HIGH) {
    // Short delay to debounce button.
    delay(10);
    // Check if button is still high after debounce.
    newSelect = digitalRead(BUTTON_PIN);
    if (newSelect == LOW) {
    }
    oldSelect = newSelect;
 }
 
 digitalWrite(LED, LOW); // Turn the LED on
 delay(10);
}


