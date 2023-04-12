// created by 04M04

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

   //Timer setup
  //create a hardware timer  of ESP32
  hw_timer_t * timer = NULL;

/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}

// void drawCount()
// {
//   //int to string
//   int team1_points = 1;
//   int team2_points = 2;
//   int team1_plays = 3;
//   int team2_plays = 4;

//   //draw Count
//   dmd.selectFont(myFont_16x32);
//   dmd.drawChar( 0, 0, char(team1_points), GRAPHICS_NORMAL );
//   dmd.drawChar(16, 0, char(team2_points), GRAPHICS_NORMAL );
//   dmd.drawChar(32, 0, char(team1_plays), GRAPHICS_NORMAL );
//   dmd.drawChar(48, 0, char(team2_plays), GRAPHICS_NORMAL );

//   dmd.selectFont(myFont_16x16);
//   dmd.drawChar( 0, 32, char(team1_points), GRAPHICS_NORMAL );
//   dmd.drawChar(16, 32, char(team2_points), GRAPHICS_NORMAL );
//   dmd.drawChar(32, 32, char(team1_plays), GRAPHICS_NORMAL );
//   dmd.drawChar(48, 32, char(team2_plays), GRAPHICS_NORMAL );
// }

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

}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
void loop(void)
{
  //drawCount();

  //int to string
  int team1_points = 1;
  int team2_points = 2;
  int team1_plays = 3;
  int team2_plays = 4;

  //draw Count
  dmd.selectFont(myFont_16x32);
  dmd.drawChar( 0, 0, team1_points, GRAPHICS_NORMAL );
  dmd.drawChar(16, 0, team2_points, GRAPHICS_NORMAL );
  dmd.drawChar(32, 0, team1_plays, GRAPHICS_NORMAL );
  dmd.drawChar(48, 0, team2_plays, GRAPHICS_NORMAL );
}
