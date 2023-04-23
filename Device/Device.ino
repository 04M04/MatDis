// created by 04M04
// version: V1.0.1

/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <DMD32.h>
#include "fonts/myFont_16x16.h"
#include "fonts/myFont_16x32.h"

//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 3
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

//init buttons
int BTN_RESET_TEAM1_POINTS_PIN = 5;
int BTN_ADD_TEAM1_POINTS_PIN = 17;
int BTN_SUB_TEAM1_POINTS_PIN = 16;
int BTN_RESET_TEAM2_POINTS_PIN = 11;
int BTN_ADD_TEAM2_POINTS_PIN = 10;
int BTN_SUB_TEAM2_POINTS_PIN = 9;
int BTN_RESET_TEAM1_PLAYS_PIN = 13;
int BTN_ADD_TEAM1_PLAYS_PIN = 12;
int BTN_SUB_TEAM1_PLAYS_PIN = 14;
int BTN_RESET_TEAM2_PLAYS_PIN = 27;
int BTN_ADD_TEAM2_PLAYS_PIN = 26;
int BTN_SUB_TEAM2_PLAYS_PIN = 25;

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;
unsigned long last_button_time = 0;
#define debounceDelay 250  // the debounce time; increase if the output flickers

//Timer setup
//create a hardware timer  of ESP32
hw_timer_t * timer = NULL;

int team1_points = 0;
int team2_points = 0;
int team1_plays = 0;
int team2_plays = 0;

int last_btnPressedState = 0;
/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}

void drawCount(int team1_points, int team2_points, int team1_plays, int team2_plays)
{
  char buffer[100];

  dmd.selectFont(myFont_16x32);

  sprintf(buffer, "%02d", team1_points);
  dmd.drawChar( 0, 0, buffer[0], GRAPHICS_NORMAL );
  dmd.drawChar(16, 0, buffer[1], GRAPHICS_NORMAL );
  sprintf(buffer, "%02d", team2_points);
  dmd.drawChar(32, 0, buffer[0], GRAPHICS_NORMAL );
  dmd.drawChar(48, 0, buffer[1], GRAPHICS_NORMAL );

  dmd.selectFont(myFont_16x16);
  
  sprintf(buffer, "%02d", team1_plays);
  dmd.drawChar( 0, 32, buffer[0], GRAPHICS_NORMAL );
  dmd.drawChar(16, 32, buffer[1], GRAPHICS_NORMAL );
  sprintf(buffer, "%02d", team2_plays);
  dmd.drawChar(32, 32, buffer[0], GRAPHICS_NORMAL );
  dmd.drawChar(48, 32, buffer[1], GRAPHICS_NORMAL );
}

void IRAM_ATTR trigger_BTN_RESET_TEAM1_POINTS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_RESET_TEAM1_POINTS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_ADD_TEAM1_POINTS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_ADD_TEAM1_POINTS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_SUB_TEAM1_POINTS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_SUB_TEAM1_POINTS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_RESET_TEAM2_POINTS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_RESET_TEAM2_POINTS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_ADD_TEAM2_POINTS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_ADD_TEAM2_POINTS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_SUB_TEAM2_POINTS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_SUB_TEAM2_POINTS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_RESET_TEAM1_PLAYS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_RESET_TEAM1_PLAYS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_ADD_TEAM1_PLAYS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_ADD_TEAM1_PLAYS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_SUB_TEAM1_PLAYS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_SUB_TEAM1_PLAYS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_RESET_TEAM2_PLAYS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_RESET_TEAM2_PLAYS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_ADD_TEAM2_PLAYS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_ADD_TEAM2_PLAYS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_SUB_TEAM2_PLAYS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_SUB_TEAM2_PLAYS_PIN;
    last_button_time = button_time;
  }
}

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
--------------------------------------------------------------------------------------*/
void setup(void)
{
  // return the clock speed of the CPU
  uint8_t cpuClock = ESP.getCpuFreqMHz();
  
  // Use 1st timer of 4 
  // devide cpu clock speed on its speed value by MHz to get 1us for each signal  of the timer
  timer = timerBegin(0, cpuClock, true);
  // Attach triggerScan function to our timer 
  timerAttachInterrupt(timer, &triggerScan, true);
  // Set alarm to call triggerScan function  
  // Repeat the alarm (third parameter) 
  timerAlarmWrite(timer, 300, true);

  // Start an alarm 
  timerAlarmEnable(timer);

   //clear/init the DMD pixels held in RAM
  dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)

  

  pinMode(BTN_RESET_TEAM1_POINTS_PIN, INPUT_PULLUP);
  pinMode(BTN_ADD_TEAM1_POINTS_PIN, INPUT_PULLUP);
  pinMode(BTN_SUB_TEAM1_POINTS_PIN, INPUT_PULLUP);
  pinMode(BTN_RESET_TEAM2_POINTS_PIN, INPUT_PULLUP);
  pinMode(BTN_ADD_TEAM2_POINTS_PIN, INPUT_PULLUP);
  pinMode(BTN_SUB_TEAM2_POINTS_PIN, INPUT_PULLUP);
  pinMode(BTN_RESET_TEAM1_PLAYS_PIN, INPUT_PULLUP);
  pinMode(BTN_ADD_TEAM1_PLAYS_PIN, INPUT_PULLUP);
  pinMode(BTN_SUB_TEAM1_PLAYS_PIN, INPUT_PULLUP);
  pinMode(BTN_RESET_TEAM2_PLAYS_PIN, INPUT_PULLUP);
  pinMode(BTN_ADD_TEAM2_PLAYS_PIN, INPUT_PULLUP);
  pinMode(BTN_SUB_TEAM2_PLAYS_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BTN_RESET_TEAM1_POINTS_PIN), trigger_BTN_RESET_TEAM1_POINTS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_ADD_TEAM1_POINTS_PIN), trigger_BTN_ADD_TEAM1_POINTS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_SUB_TEAM1_POINTS_PIN), trigger_BTN_SUB_TEAM1_POINTS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_RESET_TEAM2_POINTS_PIN), trigger_BTN_RESET_TEAM2_POINTS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_ADD_TEAM2_POINTS_PIN), trigger_BTN_ADD_TEAM2_POINTS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_SUB_TEAM2_POINTS_PIN), trigger_BTN_SUB_TEAM2_POINTS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_RESET_TEAM1_PLAYS_PIN), trigger_BTN_RESET_TEAM1_PLAYS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_ADD_TEAM1_PLAYS_PIN), trigger_BTN_ADD_TEAM1_PLAYS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_SUB_TEAM1_PLAYS_PIN), trigger_BTN_SUB_TEAM1_PLAYS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_RESET_TEAM2_PLAYS_PIN), trigger_BTN_RESET_TEAM2_PLAYS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_ADD_TEAM2_PLAYS_PIN), trigger_BTN_ADD_TEAM2_PLAYS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_SUB_TEAM2_PLAYS_PIN), trigger_BTN_SUB_TEAM2_PLAYS_PIN, FALLING);

  // Serial.begin(115200);
  // Serial.println("created by 04M04");
  // Serial.println("version: V1.0.1");
}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
void loop(void)
{
  // Serial.print(last_btnPressedState);
 
  //Team 1 points--------------------------------------------------
  if (last_btnPressedState == BTN_RESET_TEAM1_POINTS_PIN) {
    team1_points = 0;
  }
  if (last_btnPressedState == BTN_ADD_TEAM1_POINTS_PIN) {
    if (team1_points < 99){
      team1_points++;
    }
  }
  if (last_btnPressedState == BTN_SUB_TEAM1_POINTS_PIN) {
    if (team1_points > 0){
      team1_points--;
    }
  }
  //Team 2 points--------------------------------------------------
  if (last_btnPressedState == BTN_RESET_TEAM2_POINTS_PIN) {
    team2_points = 0;
  }
  if (last_btnPressedState == BTN_ADD_TEAM2_POINTS_PIN) {
    if (team2_points < 99){
      team2_points++;
    }
  }
  if (last_btnPressedState == BTN_SUB_TEAM2_POINTS_PIN) {
    if (team2_points > 0){
      team2_points--;
    }
  }
  //Team 1 plays--------------------------------------------------
  if (last_btnPressedState == BTN_RESET_TEAM1_PLAYS_PIN) {
    team1_plays = 0;
  }
  if (last_btnPressedState == BTN_ADD_TEAM1_PLAYS_PIN) {
    if (team1_plays < 99){
      team1_plays++;
    }
  }
  if (last_btnPressedState == BTN_SUB_TEAM1_PLAYS_PIN) {
    if (team1_plays > 0){
      team1_plays--;
    }
  }
  //Team 2 plays--------------------------------------------------
  if (last_btnPressedState == BTN_RESET_TEAM2_PLAYS_PIN) {
    team2_plays = 0;
  }
  if (last_btnPressedState == BTN_ADD_TEAM2_PLAYS_PIN) {
    if (team2_plays < 99){
      team2_plays++;
    }
  }
  if (last_btnPressedState == BTN_SUB_TEAM2_PLAYS_PIN) {
    if (team2_plays > 0){
      team2_plays--;
    }
  }

  last_btnPressedState = 0;

  // Serial.print("team1_points: ");
  // Serial.println(team1_points);
  // Serial.print("team2_points: ");
  // Serial.println(team2_points);
  // Serial.print("team1_plays: ");
  // Serial.println(team1_plays);
  // Serial.print("team2_plays: ");
  // Serial.println(team2_plays);
  // Serial.println();

  
  drawCount(team1_points, team2_points, team1_plays, team2_plays);
}
