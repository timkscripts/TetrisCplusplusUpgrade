#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#define VK_A 0x41
#include <time.h>
#include <iostream>

#include <mmsystem.h>  // mciSendString()
#include <conio.h>

#include <string.h>



//#include <windows.h>    // Win32Api Header File 

using namespace std;   // std::cout, std::cin
static HWND  hConWnd;

HWND BCX_Bitmap(char*,HWND=0,int=0,int=0,int=0,int=0,int=0,int=0,int=0,int=0);
HWND GetConsoleWndHandle(void);

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.
void main_menu();
void the_board();
int main(int argc, char* argv[]) {

    // Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);

    // Change the window title:
    SetConsoleTitle("Win32 Console Control Demo");

    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, 79, 49};
    
    // Change the console window size:
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

    
    // Create a COORD to hold the buffer size:
    COORD bufferSize = {80, 50};

    // Change the internal buffer size:
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    // Set up the character buffer:
    CHAR_INFO consoleBuffer[80*50];

    // Clear the CHAR_INFO buffer:
    for (int i=0; i<80*50; ++i) {

        // Fill it with white-backgrounded spaces
        consoleBuffer[i].Char.AsciiChar = ' ';
        consoleBuffer[i].Attributes = 
            BACKGROUND_BLUE
            |BACKGROUND_GREEN
            |BACKGROUND_RED
             ;
    }

    // Set up the positions:
    COORD charBufSize = {80,50};
    COORD characterPos = {0,0};
    SMALL_RECT writeArea = {0,0,79,49}; 

    // Copy to display:
    WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);

    // How many events have happened?
    DWORD numEvents = 0;

    // How many events have we read from the console?
    DWORD numEventsRead = 0;
    
    // Boolean flag to state whether app is running or not.
    bool appIsRunning = true;

 mciSendString("play tetris.mid",NULL,0,NULL);
main_menu();
the_board();
  // If we set appIsRunning to false, the program will end!
    while (appIsRunning) {

        // Find out how many console events have happened:
        GetNumberOfConsoleInputEvents(rHnd, &numEvents);

        // If it's not zero (something happened...)
        if (numEvents!=0) {

            // Create a buffer of that size to store the events
            INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents];

            // Read the console events into that buffer, and save how
            // many events have been read into numEventsRead.
            ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);

            // Now, cycle through all the events that have happened:
            for (int i=0; i<numEventsRead; ++i) {

                // Check the event type: was it a key?
                if (eventBuffer[i].EventType==KEY_EVENT) {

                    // Yes! Was the key code the escape key?
                    if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode==VK_ESCAPE) {

                        // Yes, it was, so set the appIsRunning to false.
                        appIsRunning = false;
                    
                    // Was if the 'c' key?
                    } else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar=='c') {

                        // Yes, so clear the buffer to spaces:
                        for (int i=0; i<80*50; ++i) {
                            consoleBuffer[i].Char.AsciiChar = ' ';
                        }
                        // Redraw our buffer:
                        WriteConsoleOutput(
                            wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);

                    }
                } else if (eventBuffer[i].EventType==MOUSE_EVENT) {
                    // Set the index to our buffer of CHAR_INFO
                    int offsetPos =
                        eventBuffer[i].Event.MouseEvent.dwMousePosition.X 
                        + 80 * eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;

                    // Is it a left click?
                    if (eventBuffer[i].Event.MouseEvent.dwButtonState 
                        & FROM_LEFT_1ST_BUTTON_PRESSED) {
                        // Yep, so set with character 0xDB (solid block)
                        consoleBuffer[offsetPos].Char.AsciiChar = 0xDB;

                        // Redraw our buffer:
                        WriteConsoleOutput(
                            wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
							
                    // Is it a right click?
                    } else if (eventBuffer[i].Event.MouseEvent.dwButtonState 
                        & RIGHTMOST_BUTTON_PRESSED) {
                        // Yep, so set with character 0xB1 (50% block)
                        consoleBuffer[offsetPos].Char.AsciiChar = 0xB1;

                        // Redraw our buffer:
                        WriteConsoleOutput(
                            wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
							
                    // Is it a middle click?
                    } else if (eventBuffer[i].Event.MouseEvent.dwButtonState 
                        & FROM_LEFT_2ND_BUTTON_PRESSED) {
                        // Yep, so set with character space.
                        consoleBuffer[offsetPos].Char.AsciiChar = ' ';

                        // Redraw our buffer:
                        WriteConsoleOutput(
                            wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);						
                    }
                }
            }

            // Clean up our event buffer:
            delete[] eventBuffer;
        }
    }

    // Exit
    return 0;
}


void main_menu(){
     
      // Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);

    // Change the window title:
    SetConsoleTitle("Win32 Console Control Demoz");

    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, 79, 49};
    
    // Change the console window size:
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

    
    // Create a COORD to hold the buffer size:
    COORD bufferSize = {80, 50};

    // Change the internal buffer size:
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    // Set up the character buffer:
    CHAR_INFO consoleBuffer[80*50];

    // Clear the CHAR_INFO buffer:
    for (int i=0; i<80*50; ++i) {

        // Fill it with white-backgrounded spaces
        consoleBuffer[i].Char.AsciiChar = ' ';
        consoleBuffer[i].Attributes = 
            BACKGROUND_BLUE
            |BACKGROUND_GREEN
            |BACKGROUND_RED
             ;
    }
    int colors = 0;
    int moveme = 0;
    int stopme = 0;
    
 
                       
   
  //return 0;
while(stopme == 0)
{
        if (moveme >= 2765)
        moveme = 0;
        for (int i=0; i<80*50; ++i) {
        consoleBuffer[i].Attributes = 
            FOREGROUND_BLUE;
            }
        Beep(50,100);
        colors++;
        moveme ++;
        if (colors == 1)
        {
                   for (int i=1554; i<1561; ++i) {
        consoleBuffer[i].Attributes = 
            FOREGROUND_BLUE;
            }
            } else if (colors == 2)
        {
                   for (int i=1554; i<1561; ++i) {
        consoleBuffer[i].Attributes = 
            FOREGROUND_GREEN
            | FOREGROUND_BLUE;
            }
            }
            else if (colors == 3)
        {
                   for (int i=1554; i<1561; ++i) {
        consoleBuffer[i].Attributes = 
            FOREGROUND_RED
            | FOREGROUND_BLUE
            | FOREGROUND_GREEN;
            colors = 0;
            }
            }
            
            for (int i=0; i<80*50; ++i) {
                            consoleBuffer[i].Char.AsciiChar = ' ';
                        }
 consoleBuffer[1+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[81+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[161+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[241+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[322+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[323+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[324+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[243+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[85+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[165+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[245+moveme].Char.AsciiChar = 0xDB;

                                 consoleBuffer[327+moveme].Char.AsciiChar = 'e';
                                 consoleBuffer[328+moveme].Char.AsciiChar = 'l';
                                 consoleBuffer[329+moveme].Char.AsciiChar = 'c';
                                 consoleBuffer[330+moveme].Char.AsciiChar = 'o';
                                 consoleBuffer[331+moveme].Char.AsciiChar = 'm';
                                 consoleBuffer[332+moveme].Char.AsciiChar = 'e';
                                 
                                 consoleBuffer[492+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[493+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[494+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[573+moveme].Char.AsciiChar = 0xDB; 
                                 consoleBuffer[575+moveme].Char.AsciiChar = 'o';
                                 
                                 consoleBuffer[740+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[741+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[742+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[821+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[823+moveme].Char.AsciiChar = 'i';
                                 consoleBuffer[824+moveme].Char.AsciiChar = 'm';
                                 consoleBuffer[825+moveme].Char.AsciiChar = '"';
                                 consoleBuffer[826+moveme].Char.AsciiChar = 's';
                                 
                                 consoleBuffer[1065+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[1066+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[1067+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[1068+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[1069+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[1147+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[1227+moveme].Char.AsciiChar = 0xDB;
                                 consoleBuffer[1230+moveme].Char.AsciiChar = 'e';
                                 consoleBuffer[1231+moveme].Char.AsciiChar = 't';
                                 consoleBuffer[1232+moveme].Char.AsciiChar = 'r';
                                 consoleBuffer[1233+moveme].Char.AsciiChar = 'i';
                                 consoleBuffer[1234+moveme].Char.AsciiChar = 's';
                                 
                                 consoleBuffer[1554].Char.AsciiChar = 'P';
                                 consoleBuffer[1555].Char.AsciiChar = 'r';
                                 consoleBuffer[1556].Char.AsciiChar = 'e';
                                 consoleBuffer[1557].Char.AsciiChar = 's';
                                 consoleBuffer[1558].Char.AsciiChar = 's';
                                 consoleBuffer[1559].Char.AsciiChar = ' ';
                                 consoleBuffer[1560].Char.AsciiChar = 'A';
           
                                     
    // Set up the positions:
    COORD charBufSize = {80,50};
    COORD characterPos = {0,0};
    SMALL_RECT writeArea = {0,0,79,49}; 

    // Copy to display:
    WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);

    // How many events have happened?
    DWORD numEvents = 0;

    // How many events have we read from the console?
    DWORD numEventsRead = 0;
    
    // Boolean flag to state whether app is running or not.
    bool appIsRunning = true;


      GetNumberOfConsoleInputEvents(rHnd, &numEvents);

        // If it's not zero (something happened...)
        if (numEvents!=0) {

            // Create a buffer of that size to store the events
            INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents];

            // Read the console events into that buffer, and save how
            // many events have been read into numEventsRead.
            ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);

            // Now, cycle through all the events that have happened:
     WriteConsoleOutput(
                            wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                            }
                            
        

                   if (GetKeyState('A') & 0x80) {
                                                                    stopme = 1;       
                                                                           
                                                                           }
                                                                          
                            
                            
                            
}

}


void  the_board()
{
      
      
     wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);

    // Change the window title:
    SetConsoleTitle("Win32 Console Control Demo");

    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, 79, 49};
    
    // Change the console window size:
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

    
    // Create a COORD to hold the buffer size:
    COORD bufferSize = {80, 50};

    // Change the internal buffer size:
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    // Set up the character buffer:
    CHAR_INFO consoleBuffer[80*50];

    // Clear the CHAR_INFO buffer:
   
  for (int e=0; e<40; ++e)
    for (int i=1; i<21; ++i) {

        // Fill it with white-backgrounded spaces
       consoleBuffer[i+(80*e)].Char.AsciiChar = ' ';
        consoleBuffer[i+(80*e)].Attributes = 
            BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ;
    }   
    
    
    for (int e=0; e<40; ++e)
    for (int i=59; i<79; ++i) {

        // Fill it with white-backgrounded spaces
       consoleBuffer[i+(80*e)].Char.AsciiChar = ' ';
        consoleBuffer[i+(80*e)].Attributes = 
            BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ;
    }   
          
  
                                                   hConWnd = GetConsoleWndHandle();
                if (hConWnd)
  {
    // select a bitmap file you have or use one of the files in the Windows folder
    // filename, handle, ID, ulcX, ulcY, width, height   0,0 auto-adjusts
	 // BCX_Bitmap("C:\\Documents and Settings\\Timmyy\\My Documents\\Downloads\\winbmp\\tet.bmp",hConWnd,125,170,40,0,0);
	  
    //getchar();  // wait
  }			

           

/*
for (int i=0; i<80*50; ++i) {
            consoleBuffer[i].Char.AsciiChar = ' ';
        consoleBuffer[i].Attributes = 0;
          
          
            }
            */

      COORD charBufSize = {80,50};
    COORD characterPos = {0,0};
    SMALL_RECT writeArea = {0,0,79,49}; 

    // Copy to display:
    WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);

    // How many events have happened?
    DWORD numEvents = 0;

    // How many events have we read from the console?
    DWORD numEventsRead = 0;
    
    // Boolean flag to state whether app is running or not.
    bool appIsRunning = true;


      GetNumberOfConsoleInputEvents(rHnd, &numEvents);

        // If it's not zero (something happened...)
        if (numEvents!=0) {

            // Create a buffer of that size to store the events
            INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents];

            // Read the console events into that buffer, and save how
            // many events have been read into numEventsRead.
            ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);

            // Now, cycle through all the events that have happened:
     
    
    
      WriteConsoleOutput(
                            wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
            //                 getchar();
         
}  
	  int hmm =0;
	    int meme = 0;
	    int peice = 2;
	   int peicestart = 0;
	   int peiceleft = 0;
	  int leftmove1=0;
	   int leftmove2=0;
	  int leftmove3=168;
	   int leftmove4=248;
	   int topagain = 0;
	   int rotation;
	 //  int starter1, starter2, starter3, starter4, starter5, starter6, starter7, starter8, starter9, starter10, starter11, starter12, starter13, starter 14, starter15, starter16;
//BCX_Bitmap("C:\\Documents and Settings\\Timmyy\\My Documents\\Downloads\\winbmp\\example.bmp",hConWnd,123,0,40,0,0);
                       int     starter1 = 251 + 1;
                         int starter2 = 8 + 1;
                         int starter3 = 9 + 1;
                         int starter4 = 10 + 1;
                         int starter5 = 11 + 1;
                         int starter6 = 88 + 1;
                         int starter7 = 89 + 1;
                         int starter8 = 90 + 1;
                         int starter9 = 91 + 1;
                         int starter10 = 168 + 1;
                         int starter11 = 169 + 1;
                         int starter12 = 170 + 1;
                         int starter13 = 171 + 1;
                         int starter14 = 248 + 1;
                         int starter15 = 249 + 1;
                         int starter16 = 250 + 1;
                         int tetris = 0;
       srand ( time(NULL) );

  /* generate secret number: */
 // iSecret = rand() % 10 + 1;
  peice = rand() % 3 + 1;




if (peice == 1)
{
      consoleBuffer[starter1].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE;
          
          
          
          
          
          }
     rotation = 0;
     
    int i = 0;
    int e = 0;
    int f = 0;
    int g = 0;
    //height variables
    int h1 = 0;
    int h2 = 0;
    int h3 = 0;
    int h4 = 0;
    int h5 = 0;
    int h6 = 0;
    int h7 = 0;
    int h8 = 0;
    int h9 = 0;
    int h10 = 0;
    int h11 = 0;
    int h12 = 0;
    int h13 = 0;
    int h14 = 0;
    int h15 = 0;
    int h16 = 0;
    int h17 = 0;
    int h18 = 0;
    int h19 = 0;
    int h20 = 0;
    int heightmove = 0;
    //good choice bonuses
    int g1 = 0;
    int g3 = 0;
    int g5 = 0;
    int g7 = 0;
    int g9 = 0;
    int g11 = 0;
    int g13 = 0;
    int g15 = 0;
    int g17 = 0;
    int g19 = 0;
    
    int beforepeicespawns = 0;
    
         while(1)    //****************************************************************************************************************************************
{                    //*************************************************************************************************************
 
 /*9090909090909000000000000000000000000000000000000000000000000000000000000000
                                                                               Bot program
 */
 /*
if (beforepeicespawns == 0)
{
                      
beforepeicespawns = 1;
//get height of board
 for (g = 39; g > 1; g=g-2)
 {
 for (f = 1; f < 21; f=f+2)
 {
 if (f == 1)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h1 = 40-g;
            
 if (f == 2)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h2 = 40-g;
 
  if (f == 10)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h10 = 40-g;
            
   
    if (f == 3)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h3 = 40-g;
            
   
    if (f == 4)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h4 = 40-g;
            
   
    if (f == 5)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h5 = 40-g;
            
   
    if (f == 6)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h6 = 40-g;
            
   
    if (f == 7)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h7 = 40-g;
            
   
    if (f == 8)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h8 = 40-g;
            
   
    if (f == 9)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h9 = 40-g;
            
      if (f == 11)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h11 = 40-g; 
            
        if (f == 13)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h13 = 40-g; 
            
                  if (f == 15)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h15 = 40-g; 
                          if (f == 17)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h17 = 40-g; 
            
                          if (f == 19)
 if ( ! (consoleBuffer[f+(80*g)].Attributes ==  (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            h19 = 40-g; 
 }
}
for (i = 0; i < 40; i++)
{
if (h1 == i)
consoleBuffer[5].Char.AsciiChar = i;

if (h3 == i)
consoleBuffer[7].Char.AsciiChar = i;

if (h5 == i)
consoleBuffer[9].Char.AsciiChar = i;

if (h7 == i)
consoleBuffer[11].Char.AsciiChar = i;

if (h9 == i)
consoleBuffer[13].Char.AsciiChar = i;

if (h11 == i)
consoleBuffer[15].Char.AsciiChar = i;

if (h13 == i)
consoleBuffer[17].Char.AsciiChar = i;

if (h15 == i)
consoleBuffer[19].Char.AsciiChar = i;

if (h17 == i)
consoleBuffer[21].Char.AsciiChar = i;

if (h19 == i)
consoleBuffer[22].Char.AsciiChar = i;
}




          if((h1 >= h3 && h1 >= h5 && h1 >= h7 && h1 >= h9 && h1 >= h11 && h1 >= h13 && h1 >= h15 && h1 >= h17 && h1 >= h19 ))
        {  
                   consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;  
        starter1 = starter1 - 2;
        starter2 = starter2 - 2;
        starter3 = starter3 - 2;
        starter4 = starter4 - 2;
        starter5 = starter5- 2;
        starter6 = starter6 - 2;
        starter7 = starter7 - 2;
        starter8 = starter8 - 2;
        starter9 = starter9 - 2;
        starter10 = starter10 - 2;
        starter11 = starter11 - 2;
        starter12 = starter12 - 2;
        starter13 = starter13 - 2;
        starter14 = starter14 - 2;
        starter15 = starter15 - 2;
        starter16 = starter16 - 2;
                     
                          
     consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
          WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);   
                         
        Beep(50,50);
         
         
         
         
         } 
         }
for (i = 0; i < 40; i++)
{
if (h1 == i)
consoleBuffer[5].Char.AsciiChar = i;

if (h3 == i)
consoleBuffer[7].Char.AsciiChar = i;

if (h5 == i)
consoleBuffer[9].Char.AsciiChar = i;

if (h7 == i)
consoleBuffer[11].Char.AsciiChar = i;

if (h9 == i)
consoleBuffer[13].Char.AsciiChar = i;

if (h11 == i)
consoleBuffer[15].Char.AsciiChar = i;

if (h13 == i)
consoleBuffer[17].Char.AsciiChar = i;

if (h15 == i)
consoleBuffer[19].Char.AsciiChar = i;

if (h17 == i)
consoleBuffer[21].Char.AsciiChar = i;

if (h19 == i)
consoleBuffer[22].Char.AsciiChar = i;
}
*/
  // tetris = 0;
for (i = 39; i > 0; i --)
       if (   peicestart == 0 && ! (consoleBuffer[1+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))   && ! (consoleBuffer[2+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[3+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[4+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[5+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[6+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[7+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[8+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[9+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[10+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[11+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[12+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[13+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[14+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[15+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[16+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[17+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[18+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[19+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[20+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
             {     tetris = 20;
             if (tetris >= 20)
            {
            for (g = i; g > 1; g--)
            for (f = 1; f < 21; f++)
            {
         //  consoleBuffer[f+(80*i)+80].Attributes = consoleBuffer[f+(80*i)+80 - 160].Attributes; 
           consoleBuffer[f+(80*i)].Attributes = consoleBuffer[f+(80*i) - 160].Attributes;
           i = g;
           }
           // consoleBuffer[f+(80*(0+g))].Attributes = consoleBuffer[f+(80*(0+g))-80].Attributes;
          /*  
          consoleBuffer[f+(80*i)].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ;
            */
            }
            } 
             
           
            if (tetris == 0)
             consoleBuffer[3].Char.AsciiChar = 'a';
             else
             consoleBuffer[3].Char.AsciiChar = 'B';
             if (tetris >= 20)
             consoleBuffer[3].Char.AsciiChar = 'c';
             
             
if (peicestart == 0)
	  {
                        if(peice == 2){  
                          starter2 = 8 + 1;
                          starter3 = 9 + 1;
                          
                         starter4 = 10 + 1 + 80 + 80 - 4;
                          starter5 = 11 + 1  + 80 + 80 - 4; 
                          
                          starter6 = 88 + 1; 
                          starter7 = 89 + 1;
                          
                          starter8 = 90 + 1 + 80 + 80 - 4;
                          starter9 = 91 + 1 + 80 + 80 - 4;
                          
                          starter10 = 168 + 1;
                          starter11 = 169 + 1;
                          
                          starter12 = 170 + 1;
                          starter13 = 171 + 1;
                          
                          starter14 = 248 + 1;
                          starter15 = 249 + 1;
                          
                          starter16 = 250 + 1;    
                          starter1 = 251 + 1;  
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);   
                          }
                          if(peice == 3){  
                          starter2 = 8 + 1 +2;
                          starter3 = 9 + 1 +2;
                          
                         starter4 = 10 + 1 + 80 + 80 - 4;
                          starter5 = 11 + 1  + 80 + 80 - 4; 
                          
                          starter6 = 88 + 1+2; 
                          starter7 = 89 + 1+2;
                          
                          starter8 = 90 + 1 + 80 + 80 - 4;
                          starter9 = 91 + 1 + 80 + 80 - 4;
                          
                          starter10 = 168 + 1;
                          starter11 = 169 + 1;
                          
                          starter12 = 170 + 1;
                          starter13 = 171 + 1;
                          
                          starter14 = 248 + 1;
                          starter15 = 249 + 1;
                          
                          starter16 = 250 + 1;    
                          starter1 = 251 + 1;  
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);   
                          }
                     }
    


         //for (i = 138; i < 150; i++)
        // consoleBuffer[650+i].Char.AsciiChar = 0x278 + 138;
      Beep(40,40);
         if (GetKeyState('K') & 0x80 && peicestart != 0)
         {
                              
                              
                //     Beep(50,50);
                  rotation++;            
              
                    
                  if (rotation >= 4)
                  rotation = 0;
                  
                        if (peice == 3 && rotation == 4)
                  {
            consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;  
           /*                                                             starter2 = starter10 + 8 + 1 + 2;
                                                                        starter3 = starter10 + 9 + 1  + 2;
                                                                        starter6 = starter10 + 88 + 1  + 2; 
                                                                       starter7 = starter10 + 89 + 1  + 2;
                          
            starter4 = starter10 + 10 + 1 + 80 + 80 - 4;                  starter10 = starter10 + 168 + 1;    starter12 = 0 + 170 + 1;
            starter5 = starter10 + 11 + 1  + 80 + 80 - 4;                 starter11 = starter10 + 169 + 1;    starter13 = 0 + 171 + 1;
            starter8 = starter10 + 90 + 1 + 80 + 80 - 4;                  starter14 = starter10 + 248 + 1;    starter16 = 250 + 1; 
            starter9 = starter10 + 91 + 1 + 80 + 80 - 4;                  starter15 = starter10 + 249 + 1;    starter1 = 251 + 1;
                                                                      
                       */
                          starter4 = starter4  + 2 - 160;
                          starter5 = starter5 + 2 - 160;
                          
                      
                          
                          starter8 = starter8  + 2 - 160;
                          starter9 = starter9  + 2 - 160;   
                          
                          starter2 = starter2     + 160 + 160;
                          starter3 = starter3  + 160 + 160;
                          
                      
                          
                          starter6 = starter6  + 160 + 160;
                          starter7 = starter7  + 160 + 160;
                          
                          starter16 = starter16  - 2 + 160;
                          starter1 = starter1 - 2 + 160;
                          
                      
                          
                          starter12 = starter12  - 2 + 160;
                          starter13 = starter13  - 2 + 160;
                         
                          
                          
                          
     consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                          
                      WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);              
                        
                        } else if (peice == 3 && rotation == 1)
                  {
            consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;  
           /*                                                             starter2 = starter10 + 8 + 1 + 2;
                                                                        starter3 = starter10 + 9 + 1  + 2;
                                                                        starter6 = starter10 + 88 + 1  + 2; 
                                                                       starter7 = starter10 + 89 + 1  + 2;
                          
            starter4 = starter10 + 10 + 1 + 80 + 80 - 4;                  starter10 = starter10 + 168 + 1;    starter12 = 0 + 170 + 1;
            starter5 = starter10 + 11 + 1  + 80 + 80 - 4;                 starter11 = starter10 + 169 + 1;    starter13 = 0 + 171 + 1;
            starter8 = starter10 + 90 + 1 + 80 + 80 - 4;                  starter14 = starter10 + 248 + 1;    starter16 = 250 + 1; 
            starter9 = starter10 + 91 + 1 + 80 + 80 - 4;                  starter15 = starter10 + 249 + 1;    starter1 = 251 + 1;
                                                                      
                       */
                          starter4 = starter4  + 2 + 160;
                          starter5 = starter5 + 2 + 160;
                          
                      
                          
                          starter8 = starter8  + 2 + 160;
                          starter9 = starter9  + 2 + 160;   
                          
                          starter2 = starter2   - 4; //  + 160 + 160;
                          starter3 = starter3  - 4;  //+ 160 + 160;
                          
                      
                          
                          starter6 = starter6  - 4; //+ 160 + 160;
                          starter7 = starter7  - 4; //+ 160 + 160;
                          
                          starter16 = starter16 - 2 - 160;
                          starter1 = starter1  - 2 - 160;
                          
                      
                          
                          starter12 = starter12  - 2 - 160;
                          starter13 = starter13  - 2 - 160;
                         
                          
                          
                          
     consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                          
                      WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);              
                        
                        } 
                        
                        
                        /////////////////////////////////////////////////////////////////////////
                        if (peice == 2 && rotation == 0)
                  {
                                                            
                                                      if (        consoleBuffer[starter4  + 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[starter5  + 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[starter8  + 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[starter9  + 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[ starter2  - 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[ starter3  - 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[ starter6  - 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[ starter7  - 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[starter16  - 2 - 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[starter1  - 2 - 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[starter12  - 2 - 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[starter13  - 2 - 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[starter16  - 2 - 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[starter1  - 2 - 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[starter12  - 2 - 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[starter13  - 2 - 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) )
            {          
         consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;  
           /*                                                             starter2 = starter10 + 8 + 1;
                                                                        starter3 = starter10 + 9 + 1;
                                                                        starter6 = starter10 + 88 + 1; 
                                                                       starter7 = starter10 + 89 + 1;
                          
            starter4 = starter10 + 10 + 1 + 80 + 80 - 4;                  starter10 = starter10 + 168 + 1;    starter12 = 0 + 170 + 1;
            starter5 = starter10 + 11 + 1  + 80 + 80 - 4;                 starter11 = starter10 + 169 + 1;    starter13 = 0 + 171 + 1;
            starter8 = starter10 + 90 + 1 + 80 + 80 - 4;                  starter14 = starter10 + 248 + 1;    starter16 = 250 + 1; 
            starter9 = starter10 + 91 + 1 + 80 + 80 - 4;                  starter15 = starter10 + 249 + 1;    starter1 = 251 + 1;
                                                                      
                       */
                        starter4 = starter4  - 2 - 160;
                          starter5 = starter5 - 2 - 160;
                          
                      
                          
                          starter8 = starter8  - 2 - 160;
                          starter9 = starter9  - 2 - 160;   
                          
                       starter2 = starter2  + 2 - 160;
                          starter3 = starter3 + 2 - 160;
                          
                      
                          
                          starter6 = starter6  + 2 - 160;
                          starter7 = starter7  + 2 - 160;
                          
                          starter16 = starter16  + 2 + 160;
                          starter1 = starter1 + 2 + 160;
                          
                      
                          
                          starter12 = starter12  + 2 + 160;
                          starter13 = starter13  + 2 + 160;
                         
                          
                          
                          
     consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                          
                      WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                      } else
                      rotation = 3;
                      
                      
                      
                      }
                else  if (peice == 2 && rotation == 1)
                  {
                                         
                                                      if (        consoleBuffer[starter4  + 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) &&
            consoleBuffer[starter5  + 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) &&
            consoleBuffer[starter8  + 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) &&
            consoleBuffer[starter9  + 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) )
            {
         consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;  
            
         
                 
            
                         starter4 = starter4  + 2 + 160;
                          starter5 = starter5 + 2 + 160;
                          
                      
                          
                          starter8 = starter8  + 2 + 160;
                          starter9 = starter9  + 2 + 160;
                          
                          
     consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                          
                      WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                      } else
                      rotation = 0;
                      } else  if (peice == 2 && rotation == 2)
                  {
                                              if (consoleBuffer[ starter2  - 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[ starter3  - 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[ starter6  - 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) && consoleBuffer[ starter7  - 2 + 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) )
            {
         consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;  
            
       
                          starter2 = starter2  - 2 + 160;
                          starter3 = starter3 - 2 + 160;
                          
                      
                          
                          starter6 = starter6  - 2 + 160;
                          starter7 = starter7  - 2 + 160;
                   /*      starter16 = starter16  - 4;
                          starter1 = starter1 - 4;
                          
                      
                          
                          starter12 = starter12  - 4;
                          starter13 = starter13  - 4;
                          */
     consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                          
                      WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                      } else
                      rotation = 1;
                      }
                  
                  else  if (peice == 2 && rotation == 3)
                  {
                                if (        consoleBuffer[starter16  - 2 - 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) &&
            consoleBuffer[starter1  - 2 - 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) &&
            consoleBuffer[starter12  - 2 - 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) &&
            consoleBuffer[starter13  - 2 - 160].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ) )
            {                      
         consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;  
                      /*    starter2 = starter2  - 2 + 160;
                          starter3 = starter3 - 2 + 160;
                          
                      
                          
                          starter6 = starter6  - 2 + 160;
                          starter7 = starter7  - 2 + 160;
                          */
                       starter16 = starter16  - 2 - 160;
                          starter1 = starter1 - 2 - 160;
                          
                      
                          
                          starter12 = starter12  - 2 - 160;
                          starter13 = starter13  - 2 - 160;
                          
     consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                          
                      WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                      }
                  
                  }else rotation = 2;
                  
                  
                  
                              }
         
    mciSendString("play tetris.mid",NULL,0,NULL);
    
         /*                                                             starter2 = starter10 + 8 + 1;
                                                                        starter3 = starter10 + 9 + 1;
                                                                        starter6 = starter10 + 88 + 1; 
                                                                       starter7 = starter10 + 89 + 1;
                          
            starter4 = starter10 + 10 + 1 + 80 + 80 - 4;                  starter10 = starter10 + 168 + 1;    starter12 = 0 + 170 + 1;
            starter5 = starter10 + 11 + 1  + 80 + 80 - 4;                 starter11 = starter10 + 169 + 1;    starter13 = 0 + 171 + 1;
            starter8 = starter10 + 90 + 1 + 80 + 80 - 4;                  starter14 = starter10 + 248 + 1;    starter16 = 250 + 1; 
            starter9 = starter10 + 91 + 1 + 80 + 80 - 4;                  starter15 = starter10 + 249 + 1;    starter1 = 251 + 1;
                                                                      
                       */     /*                                                             starter2 = starter10 + 8 + 1;
                                                                        starter3 = starter10 + 9 + 1;
                                                                        starter6 = starter10 + 88 + 1; 
                                                                       starter7 = starter10 + 89 + 1;
                          
            starter4 = starter10 + 10 + 1 + 80 + 80 - 4;                  starter10 = starter10 + 168 + 1;    starter12 = 0 + 170 + 1;
            starter5 = starter10 + 11 + 1  + 80 + 80 - 4;                 starter11 = starter10 + 169 + 1;    starter13 = 0 + 171 + 1;
            starter8 = starter10 + 90 + 1 + 80 + 80 - 4;                  starter14 = starter10 + 248 + 1;    starter16 = 250 + 1; 
            starter9 = starter10 + 91 + 1 + 80 + 80 - 4;                  starter15 = starter10 + 249 + 1;    starter1 = 251 + 1;
                                                                      
                       */     /*                                                             starter2 = starter10 + 8 + 1;
                                                                        starter3 = starter10 + 9 + 1;
                                                                        starter6 = starter10 + 88 + 1; 
                                                                       starter7 = starter10 + 89 + 1;
                          
            starter4 = starter10 + 10 + 1 + 80 + 80 - 4;                  starter10 = starter10 + 168 + 1;    starter12 = 0 + 170 + 1;
            starter5 = starter10 + 11 + 1  + 80 + 80 - 4;                 starter11 = starter10 + 169 + 1;    starter13 = 0 + 171 + 1;
            starter8 = starter10 + 90 + 1 + 80 + 80 - 4;                  starter14 = starter10 + 248 + 1;    starter16 = 250 + 1; 
            starter9 = starter10 + 91 + 1 + 80 + 80 - 4;                  starter15 = starter10 + 249 + 1;    starter1 = 251 + 1;
                                                                      
                       */
        
  if (peice == 3 && rotation == 0)
  {
       //      if (consoleBuffer[starter15+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter14+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter16+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter1+80].Attributes == BACKGROUND_BLUE)
 //  peicestart =  0;
  if ( !(consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter14+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter15+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            {
          peicestart = 0;
          beforepeicespawns = 0;
 // tetris = 0;
for (i = 39; i > 0; i --)
       if (   ! (consoleBuffer[1+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))   && ! (consoleBuffer[2+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[3+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[4+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[5+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[6+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[7+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[8+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[9+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[10+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[11+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[12+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[13+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[14+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[15+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[16+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[17+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[18+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[19+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[20+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
             {     tetris = 20;
             if (tetris >= 20)
            {
            for (g = i; g > 1; g--)
            for (f = 1; f < 21; f++)
            {
         //  consoleBuffer[f+(80*i)+80].Attributes = consoleBuffer[f+(80*i)+80 - 160].Attributes; 
           consoleBuffer[f+(80*i)].Attributes = consoleBuffer[f+(80*i) - 160].Attributes;
           i = g;
           }
           // consoleBuffer[f+(80*(0+g))].Attributes = consoleBuffer[f+(80*(0+g))-80].Attributes;
          /*  
          consoleBuffer[f+(80*i)].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ;
            */
            }
            } 
             
           
            if (tetris == 0)
             consoleBuffer[3].Char.AsciiChar = 'a';
             else
             consoleBuffer[3].Char.AsciiChar = 'B';
             if (tetris >= 20)
             consoleBuffer[3].Char.AsciiChar = 'c';
             
             
   peice = rand() % 3 + 1;
   rotation = 0;
  

            
         
         }
	   if (peice == 3)
  {
	       /*                                                             starter2 = starter10 + 8 + 1;
                                                                        starter3 = starter10 + 9 + 1;
                                                                        starter6 = starter10 + 88 + 1; 
                                                                       starter7 = starter10 + 89 + 1;
                          
            starter4 = starter10 + 10 + 1 + 80 + 80 - 4;                  starter10 = starter10 + 168 + 1;    starter12 = 0 + 170 + 1;
            starter5 = starter10 + 11 + 1  + 80 + 80 - 4;                 starter11 = starter10 + 169 + 1;    starter13 = 0 + 171 + 1;
            starter8 = starter10 + 90 + 1 + 80 + 80 - 4;                  starter14 = starter10 + 248 + 1;    starter16 = 250 + 1; 
            starter9 = starter10 + 91 + 1 + 80 + 80 - 4;                  starter15 = starter10 + 249 + 1;    starter1 = 251 + 1;
                                                                      
                       */
                      
	  if (GetKeyState('S') & 0x80)
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 3 && consoleBuffer[starter14+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter15+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) )
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
                            starter1 = starter1 + 80 + 80;
                           starter2 = starter2 + 80 + 80;
                           starter3 = starter3 + 80 + 80;
                         starter4 = starter4 + 80 + 80;
                         starter5 = starter5 + 80 + 80;
                         starter6 = starter6 + 80 + 80; 
                         starter7 = starter7 + 80 + 80;
                         starter8 = starter8 + 80 + 80;
                         starter9 = starter9 + 80 + 80; 
                         starter10 = starter10 + 80 + 80;
                         starter11 = starter11 + 80 + 80;
                         starter12 = starter12 + 80 + 80;
                         starter13 = starter13 + 80 + 80;
                         starter14 = starter14 + 80 + 80;
                         starter15 = starter15 + 80 + 80;
                         starter16 = starter16 + 80 + 80;    
                           
       consoleBuffer[starter1].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes =    BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                           	  if (GetKeyState('A') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 3 && consoleBuffer[starter4-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter8-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )  && consoleBuffer[starter2-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 - 2;
                           starter2 = starter2 - 2;
                           starter3 = starter3 - 2;
                         starter4 = starter4 - 2;
                         starter5 = starter5 - 2;
                         starter6 = starter6 - 2;
                         starter7 = starter7 - 2;
                         starter8 = starter8 - 2;
                         starter9 = starter9 - 2;
                         starter10 = starter10 - 2;
                         starter11 = starter11 - 2;
                         starter12 = starter12 - 2;
                         starter13 = starter13 - 2;
                         starter14 = starter14 - 2;
                         starter15 = starter15 - 2;
                         starter16 = starter16 - 2;    
                         
                           
       consoleBuffer[starter1].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes =    BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;  
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                          
                           
                           
                           
                                           	  if (GetKeyState('D') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 3 && consoleBuffer[starter3+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter7+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )&& consoleBuffer[starter16+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 + 2;
                           starter2 = starter2 + 2;
                           starter3 = starter3 + 2;
                         starter4 = starter4 + 2;
                         starter5 = starter5 + 2;
                         starter6 = starter6 + 2;
                         starter7 = starter7 + 2;
                         starter8 = starter8 + 2;
                         starter9 = starter9 + 2;
                         starter10 = starter10 + 2;
                         starter11 = starter11 + 2;
                         starter12 = starter12 + 2;
                         starter13 = starter13 + 2;
                         starter14 = starter14 + 2;
                         starter15 = starter15 + 2;
                         starter16 = starter16 + 2;    
                         
                           
     consoleBuffer[starter1].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes =    BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                                      
                           
                           
                           
                           
                           
                           
                           }             
                           
                           
                           
                           
                           }  
                           ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  else  if (peice == 3 && rotation == 1)
  {
       //      if (consoleBuffer[starter15+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter14+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter16+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter1+80].Attributes == BACKGROUND_BLUE)
 //  peicestart =  0;
  if (  !(consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            {
          peicestart = 0;
          beforepeicespawns = 0;
 // tetris = 0;
for (i = 39; i > 0; i --)
       if (   ! (consoleBuffer[1+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))   && ! (consoleBuffer[2+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[3+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[4+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[5+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[6+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[7+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[8+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[9+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[10+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[11+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[12+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[13+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[14+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[15+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[16+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[17+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[18+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[19+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[20+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
             {     tetris = 20;
             if (tetris >= 20)
            {
            for (g = i; g > 1; g--)
            for (f = 1; f < 21; f++)
            {
         //  consoleBuffer[f+(80*i)+80].Attributes = consoleBuffer[f+(80*i)+80 - 160].Attributes; 
           consoleBuffer[f+(80*i)].Attributes = consoleBuffer[f+(80*i) - 160].Attributes;
           i = g;
           }
           // consoleBuffer[f+(80*(0+g))].Attributes = consoleBuffer[f+(80*(0+g))-80].Attributes;
          /*  
          consoleBuffer[f+(80*i)].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ;
            */
            }
            } 
             
           
            if (tetris == 0)
             consoleBuffer[3].Char.AsciiChar = 'a';
             else
             consoleBuffer[3].Char.AsciiChar = 'B';
             if (tetris >= 20)
             consoleBuffer[3].Char.AsciiChar = 'c';
             
             
   peice = rand() % 3 + 1;
   rotation = 0;
  

         
         }
	   if (peice == 3)
  {
	  
                          
         
                     
	  if (GetKeyState('S') & 0x80)
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 3 && consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) )
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
                            starter1 = starter1 + 80 + 80;
                           starter2 = starter2 + 80 + 80;
                           starter3 = starter3 + 80 + 80;
                         starter4 = starter4 + 80 + 80;
                         starter5 = starter5 + 80 + 80;
                         starter6 = starter6 + 80 + 80; 
                         starter7 = starter7 + 80 + 80;
                         starter8 = starter8 + 80 + 80;
                         starter9 = starter9 + 80 + 80; 
                         starter10 = starter10 + 80 + 80;
                         starter11 = starter11 + 80 + 80;
                         starter12 = starter12 + 80 + 80;
                         starter13 = starter13 + 80 + 80;
                         starter14 = starter14 + 80 + 80;
                         starter15 = starter15 + 80 + 80;
                         starter16 = starter16 + 80 + 80;    
                           
     consoleBuffer[starter1].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes =    BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                           	  if (GetKeyState('A') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 3 && consoleBuffer[starter4-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter2-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter10-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter14-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter8-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 - 2;
                           starter2 = starter2 - 2;
                           starter3 = starter3 - 2;
                         starter4 = starter4 - 2;
                         starter5 = starter5 - 2;
                         starter6 = starter6 - 2;
                         starter7 = starter7 - 2;
                         starter8 = starter8 - 2;
                         starter9 = starter9 - 2;
                         starter10 = starter10 - 2;
                         starter11 = starter11 - 2;
                         starter12 = starter12 - 2;
                         starter13 = starter13 - 2;
                         starter14 = starter14 - 2;
                         starter15 = starter15 - 2;
                         starter16 = starter16 - 2;    
                         
                           
   consoleBuffer[starter1].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes =    BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                          
                           
                           
                           
                                           	  if (GetKeyState('D') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter3+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter7+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )&& consoleBuffer[starter16+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter5+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 + 2;
                           starter2 = starter2 + 2;
                           starter3 = starter3 + 2;
                         starter4 = starter4 + 2;
                         starter5 = starter5 + 2;
                         starter6 = starter6 + 2;
                         starter7 = starter7 + 2;
                         starter8 = starter8 + 2;
                         starter9 = starter9 + 2;
                         starter10 = starter10 + 2;
                         starter11 = starter11 + 2;
                         starter12 = starter12 + 2;
                         starter13 = starter13 + 2;
                         starter14 = starter14 + 2;
                         starter15 = starter15 + 2;
                         starter16 = starter16 + 2;    
                         
                           
     consoleBuffer[starter1].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes =    BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                                      
                           
                           
                           
                           
                           
                           
                           }             
                           
                           
                           
                           
                           }  else  if (peice == 3 && rotation == 2)
  {//2 3 6 7
       //      if (consoleBuffer[starter15+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter14+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter16+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter1+80].Attributes == BACKGROUND_BLUE)
 //  peicestart =  0;
  if (  !(consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter6+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter7+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            {
          peicestart = 0;
          beforepeicespawns = 0;
 // tetris = 0;
for (i = 39; i > 0; i --)
       if (   ! (consoleBuffer[1+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))   && ! (consoleBuffer[2+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[3+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[4+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[5+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[6+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[7+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[8+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[9+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[10+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[11+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[12+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[13+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[14+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[15+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[16+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[17+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[18+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[19+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[20+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
             {     tetris = 20;
             if (tetris >= 20)
            {
            for (g = i; g > 1; g--)
            for (f = 1; f < 21; f++)
            {
         //  consoleBuffer[f+(80*i)+80].Attributes = consoleBuffer[f+(80*i)+80 - 160].Attributes; 
           consoleBuffer[f+(80*i)].Attributes = consoleBuffer[f+(80*i) - 160].Attributes;
           i = g;
           }
           // consoleBuffer[f+(80*(0+g))].Attributes = consoleBuffer[f+(80*(0+g))-80].Attributes;
          /*  
          consoleBuffer[f+(80*i)].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ;
            */
            }
            } 
             
           
            if (tetris == 0)
             consoleBuffer[3].Char.AsciiChar = 'a';
             else
             consoleBuffer[3].Char.AsciiChar = 'B';
             if (tetris >= 20)
             consoleBuffer[3].Char.AsciiChar = 'c';
             
             
   peice = rand() % 3 + 1;
   rotation = 0;
  

         
         }
	   if (peice == 3)
  {
	  
                          
         
                     
	  if (GetKeyState('S') & 0x80)
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter7+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) )
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
                            starter1 = starter1 + 80 + 80;
                           starter2 = starter2 + 80 + 80;
                           starter3 = starter3 + 80 + 80;
                         starter4 = starter4 + 80 + 80;
                         starter5 = starter5 + 80 + 80;
                         starter6 = starter6 + 80 + 80; 
                         starter7 = starter7 + 80 + 80;
                         starter8 = starter8 + 80 + 80;
                         starter9 = starter9 + 80 + 80; 
                         starter10 = starter10 + 80 + 80;
                         starter11 = starter11 + 80 + 80;
                         starter12 = starter12 + 80 + 80;
                         starter13 = starter13 + 80 + 80;
                         starter14 = starter14 + 80 + 80;
                         starter15 = starter15 + 80 + 80;
                         starter16 = starter16 + 80 + 80;    
                           
     consoleBuffer[starter1].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes =    BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                           	  if (GetKeyState('A') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 3 && consoleBuffer[starter4-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter2-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter8-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 - 2;
                           starter2 = starter2 - 2;
                           starter3 = starter3 - 2;
                         starter4 = starter4 - 2;
                         starter5 = starter5 - 2;
                         starter6 = starter6 - 2;
                         starter7 = starter7 - 2;
                         starter8 = starter8 - 2;
                         starter9 = starter9 - 2;
                         starter10 = starter10 - 2;
                         starter11 = starter11 - 2;
                         starter12 = starter12 - 2;
                         starter13 = starter13 - 2;
                         starter14 = starter14 - 2;
                         starter15 = starter15 - 2;
                         starter16 = starter16 - 2;    
                         
                           
      consoleBuffer[starter1].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes =    BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                          
                           
                           
                           
                                           	  if (GetKeyState('D') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 3 && consoleBuffer[starter16+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter5+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 + 2;
                           starter2 = starter2 + 2;
                           starter3 = starter3 + 2;
                         starter4 = starter4 + 2;
                         starter5 = starter5 + 2;
                         starter6 = starter6 + 2;
                         starter7 = starter7 + 2;
                         starter8 = starter8 + 2;
                         starter9 = starter9 + 2;
                         starter10 = starter10 + 2;
                         starter11 = starter11 + 2;
                         starter12 = starter12 + 2;
                         starter13 = starter13 + 2;
                         starter14 = starter14 + 2;
                         starter15 = starter15 + 2;
                         starter16 = starter16 + 2;    
                         
          consoleBuffer[starter1].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes =    BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                                      
                           
                           
                           
                           
                           
                           
                           }                                    
                           
                           }  else  if (peice == 3 && rotation == 3)
  {//2 3 6 7
       //      if (consoleBuffer[starter15+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter14+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter16+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter1+80].Attributes == BACKGROUND_BLUE)
 //  peicestart =  0;
  if (  !(consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter6+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter7+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  )
            {
                                     
          peicestart = 0;
          beforepeicespawns = 0;
 // tetris = 0;
for (i = 39; i > 0; i --)
       if (   ! (consoleBuffer[1+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))   && ! (consoleBuffer[2+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[3+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[4+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[5+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[6+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[7+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[8+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[9+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[10+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[11+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[12+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[13+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[14+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[15+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[16+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[17+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[18+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[19+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[20+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
             {     tetris = 20;
             if (tetris >= 20)
            {
            for (g = i; g > 1; g--)
            for (f = 1; f < 21; f++)
            {
         //  consoleBuffer[f+(80*i)+80].Attributes = consoleBuffer[f+(80*i)+80 - 160].Attributes; 
           consoleBuffer[f+(80*i)].Attributes = consoleBuffer[f+(80*i) - 160].Attributes;
           i = g;
           }
           // consoleBuffer[f+(80*(0+g))].Attributes = consoleBuffer[f+(80*(0+g))-80].Attributes;
          /*  
          consoleBuffer[f+(80*i)].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ;
            */
            }
            } 
             
           
            if (tetris == 0)
             consoleBuffer[3].Char.AsciiChar = 'a';
             else
             consoleBuffer[3].Char.AsciiChar = 'B';
             if (tetris >= 20)
             consoleBuffer[3].Char.AsciiChar = 'c';
             
             
   peice = rand() % 3 + 1;
   rotation = 0;
  

         
         }
	   if (peice == 3)
  {
	  
                          
         
                     
	  if (GetKeyState('S') & 0x80)
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 3 && consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter7+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) ){
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
                            starter1 = starter1 + 80 + 80;
                           starter2 = starter2 + 80 + 80;
                           starter3 = starter3 + 80 + 80;
                         starter4 = starter4 + 80 + 80;
                         starter5 = starter5 + 80 + 80;
                         starter6 = starter6 + 80 + 80; 
                         starter7 = starter7 + 80 + 80;
                         starter8 = starter8 + 80 + 80;
                         starter9 = starter9 + 80 + 80; 
                         starter10 = starter10 + 80 + 80;
                         starter11 = starter11 + 80 + 80;
                         starter12 = starter12 + 80 + 80;
                         starter13 = starter13 + 80 + 80;
                         starter14 = starter14 + 80 + 80;
                         starter15 = starter15 + 80 + 80;
                         starter16 = starter16 + 80 + 80;    
     consoleBuffer[starter1].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes =    BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                           	  if (GetKeyState('A') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 3 && consoleBuffer[starter4-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter2-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter8-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 - 2;
                           starter2 = starter2 - 2;
                           starter3 = starter3 - 2;
                         starter4 = starter4 - 2;
                         starter5 = starter5 - 2;
                         starter6 = starter6 - 2;
                         starter7 = starter7 - 2;
                         starter8 = starter8 - 2;
                         starter9 = starter9 - 2;
                         starter10 = starter10 - 2;
                         starter11 = starter11 - 2;
                         starter12 = starter12 - 2;
                         starter13 = starter13 - 2;
                         starter14 = starter14 - 2;
                         starter15 = starter15 - 2;
                         starter16 = starter16 - 2;    
                         
                           
       consoleBuffer[starter1].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes =    BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                          
                           
                           
                           
                                           	  if (GetKeyState('D') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 3 && consoleBuffer[starter16+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter5+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )&& consoleBuffer[starter11+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )&& consoleBuffer[starter15+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )  )
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 + 2;
                           starter2 = starter2 + 2;
                           starter3 = starter3 + 2;
                         starter4 = starter4 + 2;
                         starter5 = starter5 + 2;
                         starter6 = starter6 + 2;
                         starter7 = starter7 + 2;
                         starter8 = starter8 + 2;
                         starter9 = starter9 + 2;
                         starter10 = starter10 + 2;
                         starter11 = starter11 + 2;
                         starter12 = starter12 + 2;
                         starter13 = starter13 + 2;
                         starter14 = starter14 + 2;
                         starter15 = starter15 + 2;
                         starter16 = starter16 + 2;    
                         
                           
       consoleBuffer[starter1].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes =  BACKGROUND_RED |   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes =  BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes =   BACKGROUND_RED|   BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes =    BACKGROUND_RED|   BACKGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes =   BACKGROUND_RED |   BACKGROUND_INTENSITY;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           }    
                           
                           
                           
                           
                           }        
                           
                           
                             
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
 ////////////////////////////////////////////////////////////
 ///
 ///
 ///
 ///
 ///
 ///
 ///
 ///
 ///
 ///
 ///
 ///
 ///
 ///                     T PEICE
 ///
 ///
 ///
 ///
 //
 //
 //
 //
 //
 //
 //
 //
 //
 //
 //
 //
 //
 //
 //
 //////////////////////////////////////////////       
  if (peice == 2 && rotation == 0)
  {
       //      if (consoleBuffer[starter15+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter14+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter16+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter1+80].Attributes == BACKGROUND_BLUE)
 //  peicestart =  0;
  if ( !(consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter14+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter15+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            {
          peicestart = 0;
          beforepeicespawns = 0;
 // tetris = 0;
for (i = 39; i > 0; i --)
       if (   ! (consoleBuffer[1+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))   && ! (consoleBuffer[2+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[3+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[4+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[5+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[6+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[7+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[8+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[9+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[10+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[11+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[12+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[13+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[14+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[15+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[16+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[17+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[18+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[19+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[20+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
             {     tetris = 20;
             if (tetris >= 20)
            {
            for (g = i; g > 1; g--)
            for (f = 1; f < 21; f++)
            {
         //  consoleBuffer[f+(80*i)+80].Attributes = consoleBuffer[f+(80*i)+80 - 160].Attributes; 
           consoleBuffer[f+(80*i)].Attributes = consoleBuffer[f+(80*i) - 160].Attributes;
           i = g;
           }
           // consoleBuffer[f+(80*(0+g))].Attributes = consoleBuffer[f+(80*(0+g))-80].Attributes;
          /*  
          consoleBuffer[f+(80*i)].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ;
            */
            }
            } 
             
           
            if (tetris == 0)
             consoleBuffer[3].Char.AsciiChar = 'a';
             else
             consoleBuffer[3].Char.AsciiChar = 'B';
             if (tetris >= 20)
             consoleBuffer[3].Char.AsciiChar = 'c';
             
             
   peice = rand() % 3 + 1;
   rotation = 0;
  

            
         
         }
	   if (peice == 2)
  {
	  
	  if (GetKeyState('S') & 0x80)
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter14+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter15+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) )
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
                            starter1 = starter1 + 80 + 80;
                           starter2 = starter2 + 80 + 80;
                           starter3 = starter3 + 80 + 80;
                         starter4 = starter4 + 80 + 80;
                         starter5 = starter5 + 80 + 80;
                         starter6 = starter6 + 80 + 80; 
                         starter7 = starter7 + 80 + 80;
                         starter8 = starter8 + 80 + 80;
                         starter9 = starter9 + 80 + 80; 
                         starter10 = starter10 + 80 + 80;
                         starter11 = starter11 + 80 + 80;
                         starter12 = starter12 + 80 + 80;
                         starter13 = starter13 + 80 + 80;
                         starter14 = starter14 + 80 + 80;
                         starter15 = starter15 + 80 + 80;
                         starter16 = starter16 + 80 + 80;    
                           
       consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                           	  if (GetKeyState('A') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter4-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter8-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )  && consoleBuffer[starter2-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 - 2;
                           starter2 = starter2 - 2;
                           starter3 = starter3 - 2;
                         starter4 = starter4 - 2;
                         starter5 = starter5 - 2;
                         starter6 = starter6 - 2;
                         starter7 = starter7 - 2;
                         starter8 = starter8 - 2;
                         starter9 = starter9 - 2;
                         starter10 = starter10 - 2;
                         starter11 = starter11 - 2;
                         starter12 = starter12 - 2;
                         starter13 = starter13 - 2;
                         starter14 = starter14 - 2;
                         starter15 = starter15 - 2;
                         starter16 = starter16 - 2;    
                         
                           
       consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                          
                           
                           
                           
                                           	  if (GetKeyState('D') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter3+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter7+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )&& consoleBuffer[starter16+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 + 2;
                           starter2 = starter2 + 2;
                           starter3 = starter3 + 2;
                         starter4 = starter4 + 2;
                         starter5 = starter5 + 2;
                         starter6 = starter6 + 2;
                         starter7 = starter7 + 2;
                         starter8 = starter8 + 2;
                         starter9 = starter9 + 2;
                         starter10 = starter10 + 2;
                         starter11 = starter11 + 2;
                         starter12 = starter12 + 2;
                         starter13 = starter13 + 2;
                         starter14 = starter14 + 2;
                         starter15 = starter15 + 2;
                         starter16 = starter16 + 2;    
                         
                           
      consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;   
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                                      
                           
                           
                           
                           
                           
                           
                           }             
                           
                           
                           
                           
                           }  
                           ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  else  if (peice == 2 && rotation == 1)
  {
       //      if (consoleBuffer[starter15+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter14+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter16+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter1+80].Attributes == BACKGROUND_BLUE)
 //  peicestart =  0;
  if (  !(consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            {
          peicestart = 0;
          beforepeicespawns = 0;
 // tetris = 0;
for (i = 39; i > 0; i --)
       if (   ! (consoleBuffer[1+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))   && ! (consoleBuffer[2+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[3+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[4+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[5+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[6+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[7+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[8+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[9+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[10+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[11+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[12+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[13+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[14+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[15+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[16+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[17+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[18+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[19+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[20+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
             {     tetris = 20;
             if (tetris >= 20)
            {
            for (g = i; g > 1; g--)
            for (f = 1; f < 21; f++)
            {
         //  consoleBuffer[f+(80*i)+80].Attributes = consoleBuffer[f+(80*i)+80 - 160].Attributes; 
           consoleBuffer[f+(80*i)].Attributes = consoleBuffer[f+(80*i) - 160].Attributes;
           i = g;
           }
           // consoleBuffer[f+(80*(0+g))].Attributes = consoleBuffer[f+(80*(0+g))-80].Attributes;
          /*  
          consoleBuffer[f+(80*i)].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ;
            */
            }
            } 
             
           
            if (tetris == 0)
             consoleBuffer[3].Char.AsciiChar = 'a';
             else
             consoleBuffer[3].Char.AsciiChar = 'B';
             if (tetris >= 20)
             consoleBuffer[3].Char.AsciiChar = 'c';
             
             
   peice = rand() % 3 + 1;
   rotation = 0;
  

         
         }
	   if (peice == 2)
  {
	  
                          
         
                     
	  if (GetKeyState('S') & 0x80)
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) )
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
                            starter1 = starter1 + 80 + 80;
                           starter2 = starter2 + 80 + 80;
                           starter3 = starter3 + 80 + 80;
                         starter4 = starter4 + 80 + 80;
                         starter5 = starter5 + 80 + 80;
                         starter6 = starter6 + 80 + 80; 
                         starter7 = starter7 + 80 + 80;
                         starter8 = starter8 + 80 + 80;
                         starter9 = starter9 + 80 + 80; 
                         starter10 = starter10 + 80 + 80;
                         starter11 = starter11 + 80 + 80;
                         starter12 = starter12 + 80 + 80;
                         starter13 = starter13 + 80 + 80;
                         starter14 = starter14 + 80 + 80;
                         starter15 = starter15 + 80 + 80;
                         starter16 = starter16 + 80 + 80;    
                           
      consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                           	  if (GetKeyState('A') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter4-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter2-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter10-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter14-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter8-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 - 2;
                           starter2 = starter2 - 2;
                           starter3 = starter3 - 2;
                         starter4 = starter4 - 2;
                         starter5 = starter5 - 2;
                         starter6 = starter6 - 2;
                         starter7 = starter7 - 2;
                         starter8 = starter8 - 2;
                         starter9 = starter9 - 2;
                         starter10 = starter10 - 2;
                         starter11 = starter11 - 2;
                         starter12 = starter12 - 2;
                         starter13 = starter13 - 2;
                         starter14 = starter14 - 2;
                         starter15 = starter15 - 2;
                         starter16 = starter16 - 2;    
                         
                           
                          consoleBuffer[starter1].Attributes = BACKGROUND_BLUE;
	   consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                          
                           
                           
                           
                                           	  if (GetKeyState('D') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter3+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter7+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )&& consoleBuffer[starter16+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter5+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 

	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 + 2;
                           starter2 = starter2 + 2;
                           starter3 = starter3 + 2;
                         starter4 = starter4 + 2;
                         starter5 = starter5 + 2;
                         starter6 = starter6 + 2;
                         starter7 = starter7 + 2;
                         starter8 = starter8 + 2;
                         starter9 = starter9 + 2;
                         starter10 = starter10 + 2;
                         starter11 = starter11 + 2;
                         starter12 = starter12 + 2;
                         starter13 = starter13 + 2;
                         starter14 = starter14 + 2;
                         starter15 = starter15 + 2;
                         starter16 = starter16 + 2;    
                         
                           
         consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                                      
                           
                           
                           
                           
                           
                           
                           }             
                           
                           
                           
                           
                           }  else  if (peice == 2 && rotation == 2)
  {//2 3 6 7
       //      if (consoleBuffer[starter15+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter14+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter16+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter1+80].Attributes == BACKGROUND_BLUE)
 //  peicestart =  0;
  if (  !(consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter6+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter7+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
            {
          peicestart = 0;
          beforepeicespawns = 0;
 // tetris = 0;
for (i = 39; i > 0; i --)
       if (   ! (consoleBuffer[1+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))   && ! (consoleBuffer[2+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[3+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[4+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[5+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[6+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[7+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[8+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[9+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[10+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[11+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[12+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[13+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[14+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[15+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[16+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[17+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[18+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[19+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[20+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
             {     tetris = 20;
             if (tetris >= 20)
            {
            for (g = i; g > 1; g--)
            for (f = 1; f < 21; f++)
            {
         //  consoleBuffer[f+(80*i)+80].Attributes = consoleBuffer[f+(80*i)+80 - 160].Attributes; 
           consoleBuffer[f+(80*i)].Attributes = consoleBuffer[f+(80*i) - 160].Attributes;
           i = g;
           }
           // consoleBuffer[f+(80*(0+g))].Attributes = consoleBuffer[f+(80*(0+g))-80].Attributes;
          /*  
          consoleBuffer[f+(80*i)].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ;
            */
            }
            } 
             
           
            if (tetris == 0)
             consoleBuffer[3].Char.AsciiChar = 'a';
             else
             consoleBuffer[3].Char.AsciiChar = 'B';
             if (tetris >= 20)
             consoleBuffer[3].Char.AsciiChar = 'c';
             
             
   peice = rand() % 3 + 1;
   rotation = 0;
  

         
         }
	   if (peice == 2)
  {
	  
                          
         
                     
	  if (GetKeyState('S') & 0x80)
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter7+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) )
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
                            starter1 = starter1 + 80 + 80;
                           starter2 = starter2 + 80 + 80;
                           starter3 = starter3 + 80 + 80;
                         starter4 = starter4 + 80 + 80;
                         starter5 = starter5 + 80 + 80;
                         starter6 = starter6 + 80 + 80; 
                         starter7 = starter7 + 80 + 80;
                         starter8 = starter8 + 80 + 80;
                         starter9 = starter9 + 80 + 80; 
                         starter10 = starter10 + 80 + 80;
                         starter11 = starter11 + 80 + 80;
                         starter12 = starter12 + 80 + 80;
                         starter13 = starter13 + 80 + 80;
                         starter14 = starter14 + 80 + 80;
                         starter15 = starter15 + 80 + 80;
                         starter16 = starter16 + 80 + 80;    
                           
      consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                           	  if (GetKeyState('A') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter4-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter2-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter8-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 - 2;
                           starter2 = starter2 - 2;
                           starter3 = starter3 - 2;
                         starter4 = starter4 - 2;
                         starter5 = starter5 - 2;
                         starter6 = starter6 - 2;
                         starter7 = starter7 - 2;
                         starter8 = starter8 - 2;
                         starter9 = starter9 - 2;
                         starter10 = starter10 - 2;
                         starter11 = starter11 - 2;
                         starter12 = starter12 - 2;
                         starter13 = starter13 - 2;
                         starter14 = starter14 - 2;
                         starter15 = starter15 - 2;
                         starter16 = starter16 - 2;    
                         
                           
                          consoleBuffer[starter1].Attributes = BACKGROUND_BLUE;
	   consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                          
                           
                           
                           
                                           	  if (GetKeyState('D') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter16+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter5+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 + 2;
                           starter2 = starter2 + 2;
                           starter3 = starter3 + 2;
                         starter4 = starter4 + 2;
                         starter5 = starter5 + 2;
                         starter6 = starter6 + 2;
                         starter7 = starter7 + 2;
                         starter8 = starter8 + 2;
                         starter9 = starter9 + 2;
                         starter10 = starter10 + 2;
                         starter11 = starter11 + 2;
                         starter12 = starter12 + 2;
                         starter13 = starter13 + 2;
                         starter14 = starter14 + 2;
                         starter15 = starter15 + 2;
                         starter16 = starter16 + 2;    
                         
                           
         consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                                      
                           
                           
                           
                           
                           
                           
                           }                                    
                           
                           }  else  if (peice == 2 && rotation == 3)
  {//2 3 6 7
       //      if (consoleBuffer[starter15+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter14+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter16+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter1+80].Attributes == BACKGROUND_BLUE)
 //  peicestart =  0;
  if (  !(consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter6+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter7+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  )
            {
                                     
          peicestart = 0;
          beforepeicespawns = 0;
 // tetris = 0;
for (i = 39; i > 0; i --)
       if (   ! (consoleBuffer[1+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))   && ! (consoleBuffer[2+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[3+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[4+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[5+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[6+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[7+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[8+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[9+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[10+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[11+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[12+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[13+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[14+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[15+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[16+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[17+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[18+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[19+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[20+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
             {     tetris = 20;
             if (tetris >= 20)
            {
            for (g = i; g > 1; g--)
            for (f = 1; f < 21; f++)
            {
         //  consoleBuffer[f+(80*i)+80].Attributes = consoleBuffer[f+(80*i)+80 - 160].Attributes; 
           consoleBuffer[f+(80*i)].Attributes = consoleBuffer[f+(80*i) - 160].Attributes;
           i = g;
           }
           // consoleBuffer[f+(80*(0+g))].Attributes = consoleBuffer[f+(80*(0+g))-80].Attributes;
          /*  
          consoleBuffer[f+(80*i)].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ;
            */
            }
            } 
             
           
            if (tetris == 0)
             consoleBuffer[3].Char.AsciiChar = 'a';
             else
             consoleBuffer[3].Char.AsciiChar = 'B';
             if (tetris >= 20)
             consoleBuffer[3].Char.AsciiChar = 'c';
             
             
   peice = rand() % 3 + 1;
   rotation = 0;
  

         
         }
	   if (peice == 2)
  {
	  
                          
         
                     
	  if (GetKeyState('S') & 0x80)
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter8+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter7+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) ){
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
                            starter1 = starter1 + 80 + 80;
                           starter2 = starter2 + 80 + 80;
                           starter3 = starter3 + 80 + 80;
                         starter4 = starter4 + 80 + 80;
                         starter5 = starter5 + 80 + 80;
                         starter6 = starter6 + 80 + 80; 
                         starter7 = starter7 + 80 + 80;
                         starter8 = starter8 + 80 + 80;
                         starter9 = starter9 + 80 + 80; 
                         starter10 = starter10 + 80 + 80;
                         starter11 = starter11 + 80 + 80;
                         starter12 = starter12 + 80 + 80;
                         starter13 = starter13 + 80 + 80;
                         starter14 = starter14 + 80 + 80;
                         starter15 = starter15 + 80 + 80;
                         starter16 = starter16 + 80 + 80;    
                           
      consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                           	  if (GetKeyState('A') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter4-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter2-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter8-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 - 2;
                           starter2 = starter2 - 2;
                           starter3 = starter3 - 2;
                         starter4 = starter4 - 2;
                         starter5 = starter5 - 2;
                         starter6 = starter6 - 2;
                         starter7 = starter7 - 2;
                         starter8 = starter8 - 2;
                         starter9 = starter9 - 2;
                         starter10 = starter10 - 2;
                         starter11 = starter11 - 2;
                         starter12 = starter12 - 2;
                         starter13 = starter13 - 2;
                         starter14 = starter14 - 2;
                         starter15 = starter15 - 2;
                         starter16 = starter16 - 2;    
                         
                           
                          consoleBuffer[starter1].Attributes = BACKGROUND_BLUE;
	   consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                          
                           
                           
                           
                                           	  if (GetKeyState('D') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 2 && consoleBuffer[starter16+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter5+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )&& consoleBuffer[starter11+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )&& consoleBuffer[starter15+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )  )
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 + 2;
                           starter2 = starter2 + 2;
                           starter3 = starter3 + 2;
                         starter4 = starter4 + 2;
                         starter5 = starter5 + 2;
                         starter6 = starter6 + 2;
                         starter7 = starter7 + 2;
                         starter8 = starter8 + 2;
                         starter9 = starter9 + 2;
                         starter10 = starter10 + 2;
                         starter11 = starter11 + 2;
                         starter12 = starter12 + 2;
                         starter13 = starter13 + 2;
                         starter14 = starter14 + 2;
                         starter15 = starter15 + 2;
                         starter16 = starter16 + 2;    
                         
                           
         consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | BACKGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE  | BACKGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | BACKGROUND_RED;  
                           
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           }    
                           
                           
                           
                           
                           }        
                           
                           
                           
                           
                           
                           
                           
                           
                           
                           
                           
                           
                           
                           
                           
                           
                           
                                       
   if (peice == 1)
{      
         
         
         
         
         
         
         

   if (consoleBuffer[starter15+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter14+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter16+80].Attributes == BACKGROUND_BLUE || consoleBuffer[starter1+80].Attributes == BACKGROUND_BLUE)
  { //peicestart =  0;
//peice = rand() % 3 + 1;
//rotation = 0;
}
  if ( !(consoleBuffer[starter15+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter14+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) || !(consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
	  |BACKGROUND_RED
            |BACKGROUND_GREEN
             )))
            {
          peicestart = 0;
          beforepeicespawns = 0;
peice = rand() % 3 + 1;
 // tetris = 0;
for (i = 39; i > 0; i --)
       if (   ! (consoleBuffer[1+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))   && ! (consoleBuffer[2+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[3+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[4+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[5+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[6+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[7+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[8+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[9+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[10+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[11+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[12+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[13+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[14+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[15+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[16+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[17+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[18+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[19+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ))  && ! (consoleBuffer[20+(80*i)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             )) )
             {     tetris = 20;
             if (tetris >= 20)
            {
            for (g = i; g > 1; g--)
            for (f = 1; f < 21; f++)
            {
         //  consoleBuffer[f+(80*i)+80].Attributes = consoleBuffer[f+(80*i)+80 - 160].Attributes; 
           consoleBuffer[f+(80*i)].Attributes = consoleBuffer[f+(80*i) - 160].Attributes;
           i = g;
           }
           // consoleBuffer[f+(80*(0+g))].Attributes = consoleBuffer[f+(80*(0+g))-80].Attributes;
          /*  
          consoleBuffer[f+(80*i)].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
             ;
            */
            }
            } 
             
           
            if (tetris == 0)
             consoleBuffer[3].Char.AsciiChar = 'a';
             else
             consoleBuffer[3].Char.AsciiChar = 'B';
             if (tetris >= 20)
             consoleBuffer[3].Char.AsciiChar = 'c';
             
             
rotation = 0;
         }
	    if (peice == 1)
{ 
	  if (peicestart == 0)
	  {
                       starter1 = 251 + 1;
                          starter2 = 8 + 1;
                          starter3 = 9 + 1;
                          starter4 = 10 + 1;
                          starter5 = 11 + 1; 
                          starter6 = 88 + 1; 
                          starter7 = 89 + 1;
                          starter8 = 90 + 1;
                          starter9 = 91 + 1;
                          starter10 = 168 + 1;
                          starter11 = 169 + 1;
                          starter12 = 170 + 1;
                          starter13 = 171 + 1;
                          starter14 = 248 + 1;
                          starter15 = 249 + 1;
                          starter16 = 250 + 1;         
                     
                     }
	  if (GetKeyState('S') & 0x80)
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 1 && consoleBuffer[starter14+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter15+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter16+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+80].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            /*
               consoleBuffer[starter1].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter2].Char.AsciiChar = ' ';
                           consoleBuffer[starter3].Char.AsciiChar = ' ';
                           consoleBuffer[starter4].Char.AsciiChar = ' ';
                           consoleBuffer[starter5].Char.AsciiChar = ' ';
                           consoleBuffer[starter6].Char.AsciiChar = ' ';
                           consoleBuffer[starter7].Char.AsciiChar = ' ';
                           consoleBuffer[starter8].Char.AsciiChar = ' ';
                           consoleBuffer[starter9].Char.AsciiChar = ' ';
                           consoleBuffer[starter10].Char.AsciiChar = ' ';
                           consoleBuffer[starter11].Char.AsciiChar = ' ';
                           consoleBuffer[starter12].Char.AsciiChar = ' ';
                           consoleBuffer[starter13].Char.AsciiChar = ' ';
                           consoleBuffer[starter14].Char.AsciiChar = ' ';
                           consoleBuffer[starter15].Char.AsciiChar = ' ';
                           consoleBuffer[starter16].Char.AsciiChar = ' ';
            */
            
                            starter1 = starter1 + 80 + 80;
                           starter2 = starter2 + 80 + 80;
                           starter3 = starter3 + 80 + 80;
                         starter4 = starter4 + 80 + 80;
                         starter5 = starter5 + 80 + 80;
                         starter6 = starter6 + 80 + 80; 
                         starter7 = starter7 + 80 + 80;
                         starter8 = starter8 + 80 + 80;
                         starter9 = starter9 + 80 + 80; 
                         starter10 = starter10 + 80 + 80;
                         starter11 = starter11 + 80 + 80;
                         starter12 = starter12 + 80 + 80;
                         starter13 = starter13 + 80 + 80;
                         starter14 = starter14 + 80 + 80;
                         starter15 = starter15 + 80 + 80;
                         starter16 = starter16 + 80 + 80;    
                  /*         consoleBuffer[starter1].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter2].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter3].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter4].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter5].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter6].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter7].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter8].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter9].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter10].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter11].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter12].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter13].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter14].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter15].Char.AsciiChar = 0x278 + 138;
                           consoleBuffer[starter16].Char.AsciiChar = 0x278 + 138;
                           */
                           
/*
    if (i == 0)
    {
                       consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | FOREGROUND_RED;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | FOREGROUND_RED;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | FOREGROUND_RED;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | FOREGROUND_RED;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | FOREGROUND_RED; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | FOREGROUND_RED;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | FOREGROUND_RED;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | FOREGROUND_RED;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | FOREGROUND_RED; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | FOREGROUND_RED;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | FOREGROUND_RED; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | FOREGROUND_RED;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | FOREGROUND_RED;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | FOREGROUND_RED;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE | FOREGROUND_RED; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | FOREGROUND_RED;  
                           
     
     }
   if (i == 1)
    {
                       consoleBuffer[starter1].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY; 
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY; 
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY; 
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;  
                           
     
     }
    
    i++; 
     if (i==3)
     i = 0;
                           
               */            
                        consoleBuffer[starter1].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter11].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter13].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter8].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY; 
                       
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                           	  if (GetKeyState('A') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 1 && consoleBuffer[starter2-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter6-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )&& consoleBuffer[starter10-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter14-2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 - 2;
                           starter2 = starter2 - 2;
                           starter3 = starter3 - 2;
                         starter4 = starter4 - 2;
                         starter5 = starter5 - 2;
                         starter6 = starter6 - 2;
                         starter7 = starter7 - 2;
                         starter8 = starter8 - 2;
                         starter9 = starter9 - 2;
                         starter10 = starter10 - 2;
                         starter11 = starter11 - 2;
                         starter12 = starter12 - 2;
                         starter13 = starter13 - 2;
                         starter14 = starter14 - 2;
                         starter15 = starter15 - 2;
                         starter16 = starter16 - 2;    
                         
                   consoleBuffer[starter1].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter11].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter13].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter8].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY; 
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                           
                          
                           
                           
                           
                                           	  if (GetKeyState('D') & 0x80 )
	  { peicestart++;
                           WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                          	if (peice == 1 && consoleBuffer[starter5+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter9+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    )&& consoleBuffer[starter13+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ) && consoleBuffer[starter1+2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
                consoleBuffer[starter1].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter3].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter4].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter7].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter8].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[starter9].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter10].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter11].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter12].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[starter13].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter14].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[starter15].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[starter16].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;           
            
                            starter1 = starter1 + 2;
                           starter2 = starter2 + 2;
                           starter3 = starter3 + 2;
                         starter4 = starter4 + 2;
                         starter5 = starter5 + 2;
                         starter6 = starter6 + 2;
                         starter7 = starter7 + 2;
                         starter8 = starter8 + 2;
                         starter9 = starter9 + 2;
                         starter10 = starter10 + 2;
                         starter11 = starter11 + 2;
                         starter12 = starter12 + 2;
                         starter13 = starter13 + 2;
                         starter14 = starter14 + 2;
                         starter15 = starter15 + 2;
                         starter16 = starter16 + 2;    
                         
                           
                   consoleBuffer[starter1].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter2].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter3].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter4].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
 
	  consoleBuffer[starter5].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY; 
	  consoleBuffer[starter6].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter7].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter9].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
      
      consoleBuffer[starter10].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter11].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter12].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter13].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  
	  consoleBuffer[starter14].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter15].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter16].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY;
	  consoleBuffer[starter8].Attributes = BACKGROUND_RED  | BACKGROUND_GREEN   | BACKGROUND_INTENSITY; 
                           }
                            WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                           }
                                      
                           
                           
                           }
                           
                           
                           
                           
                           
                           
                           
                           
                           }           
                           
                           
                           
                           
	  //consoleBuffer[5].Attributes = 1;
/*	  
  
	  if (GetKeyState('D') & 0x80)
	  {  
              leftmove2++;   WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);           
                                            	if (peice == 1 && consoleBuffer[251+80*(peicestart)].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
              
            
              leftmove2 = leftmove2-1;
      consoleBuffer[(8+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(9+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(10+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(11+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[(88+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[(89+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(90+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(91+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[(168+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[(169+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(170+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[(171+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[(248+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(249+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(250+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[(251+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  
              
              leftmove2 = leftmove2+1;
	  consoleBuffer[(8+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(9+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(10+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(11+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
 
	  consoleBuffer[(88+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[(89+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(90+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(91+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
      
      consoleBuffer[(168+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[(169+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(170+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[(171+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  
	  consoleBuffer[(248+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(249+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(250+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[(251+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  
	  
	  
	  
	  
   }
   WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);   
  
                      
                           }
                           
                           
 if (GetKeyState('A') & 0x80)
	  {  
                    leftmove1++;    
                    	                  	if (peice == 1 && consoleBuffer[(248+80*peicestart)-leftmove1+leftmove2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
              //peicestart = peicestart-1;
            
              leftmove1 = leftmove1-1;
      consoleBuffer[(8+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(9+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(10+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(11+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[(88+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[(89+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(90+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(91+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[(168+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[(169+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(170+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[(171+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[(248+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(249+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(250+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[(251+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  
             // peicestart = peicestart+1;
              leftmove1 = leftmove1+1;
	  consoleBuffer[(8+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(9+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(10+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(11+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
 
	  consoleBuffer[(88+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[(89+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(90+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(91+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
      
      consoleBuffer[(168+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[(169+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(170+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[(171+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  
	  consoleBuffer[(248+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(249+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(250+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[(251+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  
	  
	  
	  
	  
   }
 WriteConsoleOutput(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);   
                           }



     

	  if (GetKeyState('S') & 0x80)
	  {  
                           
                    peicestart++;  
                    	if (peice == 1 && consoleBuffer[(248+80*peicestart)-leftmove1+leftmove2].Attributes == (BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
                    ))
	{
              peicestart = peicestart-1;
            
              //leftmove1 = leftmove1-1;
      consoleBuffer[(8+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(9+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(10+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(11+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
 
	  consoleBuffer[(88+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[(89+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(90+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(91+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
      
      consoleBuffer[(168+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[(169+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(170+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[(171+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  
	  consoleBuffer[(248+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(249+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ;
	  consoleBuffer[(250+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  consoleBuffer[(251+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE
            |BACKGROUND_RED
            |BACKGROUND_GREEN
              ; 
	  
              peicestart = peicestart+1;
              //leftmove1 = leftmove1+1;
	  consoleBuffer[(8+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(9+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(10+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(11+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
 
	  consoleBuffer[(88+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[(89+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(90+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(91+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
      
      consoleBuffer[(168+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[(169+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(170+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[(171+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  
	  consoleBuffer[(248+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(249+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE;
	  consoleBuffer[(250+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  consoleBuffer[(251+80*peicestart)-leftmove1+leftmove2].Attributes = BACKGROUND_BLUE; 
	  
	  
	  
	  
	  
   }
                         
                           }

	*/


	 
}

}














// put a bitmap image on a Windows Console display
// BCX basic original by Joe Caverly and Kevin Diggins
// BCX generated C code modified for PellesC/Dev-C++
 





// draw the bitmap
HWND BCX_Bitmap(char* Text,HWND hWnd,int id,int X,int Y,int W,int H,int Res,int Style,int Exstyle)
{
  HWND A;
  HBITMAP hBitmap;
  
  // set default style
  if (!Style) Style = WS_CLIPSIBLINGS|WS_CHILD|WS_VISIBLE|SS_BITMAP|WS_TABSTOP;
  
  // form for the image
  A = CreateWindowEx(Exstyle,"static",NULL,Style,X,Y,0,0,hWnd,(HMENU)id,GetModuleHandle(0),NULL);
                      
  // Text contains filename
  hBitmap=(HBITMAP)LoadImage(0,Text,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);

  // auto-adjust width and height
  if (W || H) hBitmap = (HBITMAP)CopyImage(hBitmap,IMAGE_BITMAP,W,H,LR_COPYRETURNORG);
  SendMessage(A,(UINT)STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hBitmap);
  if (W || H) SetWindowPos(A,HWND_TOP,X,Y,W,H,SWP_DRAWFRAME);
  return A;
}


// tricking Windows just a little ...
HWND GetConsoleWndHandle(void)
{
  HWND hConWnd;
  OSVERSIONINFO os;
  char szTempTitle[64], szClassName[128], szOriginalTitle[1024];

  os.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
  GetVersionEx( &os );
  // may not work on WIN9x
  if ( os.dwPlatformId == VER_PLATFORM_WIN32s ) return 0;

  GetConsoleTitle( szOriginalTitle, sizeof ( szOriginalTitle ) );
  sprintf( szTempTitle,"%u - %u", GetTickCount(), GetCurrentProcessId() );
  SetConsoleTitle( szTempTitle );
  Sleep( 1);
  // handle for NT and XP
  hConWnd = FindWindow( NULL, szTempTitle );
  SetConsoleTitle( szOriginalTitle );

  // may not work on WIN9x
  if ( os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
  {
    hConWnd = GetWindow( hConWnd, GW_CHILD );
    if ( hConWnd == NULL ) return 0;
    GetClassName( hConWnd, szClassName, sizeof ( szClassName ) );
    // while ( _stricmp( szClassName, "ttyGrab" ) != 0 )
    while ( strcmp( szClassName, "ttyGrab" ) != 0 )
    {
      hConWnd = GetNextWindow( hConWnd, GW_HWNDNEXT );
      if ( hConWnd == NULL ) return 0;
      GetClassName( hConWnd, szClassName, sizeof( szClassName ) );
    }
  }
  return hConWnd;
}


