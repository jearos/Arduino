/*
  SinusLedFader

  Fades the LED with a sinus.
  The PWM frequency is set to 50 Hz. This should be faster than your eye
  could detect.
  The duty cycle is calculated from the sin() function.
  One complete sinus is 2*Pi radians.
  The number of ticks to complete one sinus period is then
  UPDATE_FREQ_HZ
  The resulting sinus is between -1 and 1 and should correspond to
  our duty cycle 0 to PERIOD_TIME_MS.
  I.e. offset by 1.0 then divide by 2 and multiply by PERIOD_TIME_MS
 
  Led connected to pin 13.
  
  Created 2014-11-19
  By Jean Rostrom
  
 */

#define UPDATE_FREQ_HZ       60
#define PERIOD_TIME_MS       (1000/UPDATE_FREQ_HZ)
#define BLINK_FREQUENCY_HZ   1.0
#define LED_PIN              12

unsigned int get_pulse_width(unsigned int Tick) {
float pulse_width;
  pulse_width = 1.0 + sin( ( (float) Tick * 2.0 * PI * BLINK_FREQUENCY_HZ ) / UPDATE_FREQ_HZ );
  pulse_width = (PERIOD_TIME_MS*pulse_width)/2; 
  return( (unsigned int) pulse_width );
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
unsigned int pulse_width = 0;
static unsigned int ticks = 0;

  pulse_width = get_pulse_width(ticks++);              // get the pulse width in ms

  digitalWrite(LED_PIN, HIGH);                         // turn the LED on (HIGH is the voltage level)
  delay(pulse_width);                                  // wait for pulse width on time

  digitalWrite(LED_PIN, LOW);                          // turn the LED off by making the voltage LOW
  delay(PERIOD_TIME_MS - pulse_width);                 // wait for the remaining off time

  if(ticks >= UPDATE_FREQ_HZ / BLINK_FREQUENCY_HZ ) {  // get the number of ticks in one cycle
    ticks = 0;                                         // reset the ticks counter
  }
}
