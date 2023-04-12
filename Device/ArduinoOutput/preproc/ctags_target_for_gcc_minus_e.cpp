# 1 "C:\\Users\\micsc\\Documents\\big projects\\MatDis\\Device\\Device.ino"
// created by 04M04

/*--------------------------------------------------------------------------------------

  Includes

--------------------------------------------------------------------------------------*/
# 6 "C:\\Users\\micsc\\Documents\\big projects\\MatDis\\Device\\Device.ino"
# 7 "C:\\Users\\micsc\\Documents\\big projects\\MatDis\\Device\\Device.ino" 2
# 8 "C:\\Users\\micsc\\Documents\\big projects\\MatDis\\Device\\Device.ino" 2
# 9 "C:\\Users\\micsc\\Documents\\big projects\\MatDis\\Device\\Device.ino" 2

//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 3
DMD dmd(2, 3);

   //Timer setup
  //create a hardware timer  of ESP32
  hw_timer_t * timer = 
# 17 "C:\\Users\\micsc\\Documents\\big projects\\MatDis\\Device\\Device.ino" 3 4
                      __null
# 17 "C:\\Users\\micsc\\Documents\\big projects\\MatDis\\Device\\Device.ino"
                          ;

/*--------------------------------------------------------------------------------------

  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets

  called at the period set in Timer1.initialize();

--------------------------------------------------------------------------------------*/
# 23 "C:\\Users\\micsc\\Documents\\big projects\\MatDis\\Device\\Device.ino"
void __attribute__((section(".iram1" "." "16"))) triggerScan()
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
# 54 "C:\\Users\\micsc\\Documents\\big projects\\MatDis\\Device\\Device.ino"
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
  dmd.clearScreen( true ); //true is normal (all pixels off), false is negative (all pixels on)

}

/*--------------------------------------------------------------------------------------

  loop

  Arduino architecture main loop

--------------------------------------------------------------------------------------*/
# 81 "C:\\Users\\micsc\\Documents\\big projects\\MatDis\\Device\\Device.ino"
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
  dmd.drawChar( 0, 0, team1_points, 0 );
  dmd.drawChar(16, 0, team2_points, 0 );
  dmd.drawChar(32, 0, team1_plays, 0 );
  dmd.drawChar(48, 0, team2_plays, 0 );
}
