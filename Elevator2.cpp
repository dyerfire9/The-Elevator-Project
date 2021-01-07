/*Sean Purcell TEJ3M1 
Edited by Mr. Brossard March 23 15
8 LED Program
Controls 8 Leds with various programs.*/

#include <iostream>
#include <conio.h>
#include <windows.h>
//#include <cstdlib>
//#include <math.h>

using namespace std;
int numInput;
//int numInput(string str)
//{
//       cout << str;
//       int in;
//       
//       cin >> in;
//       return in;    
//}

/* Definitions in the build of inpout32.dll are:            */
/*   short _stdcall Inp32(short PortAddress);               */
/*   void _stdcall Out32(short PortAddress, short data);    */

/* prototype (function typedef) for DLL function Inp32: */

     typedef short (_stdcall *inpfuncPtr)(short portaddr);
     typedef void (_stdcall *oupfuncPtr)(short portaddr, short datum);

#define PPORT_BASE 0x378
// Prototypes for Test functions
void test_read8(void);
void test_write(void);
void test_write_datum(short datum);

/* After successful initialization, these 2 variables
   will contain function pointers.
 */
     inpfuncPtr inp32fp;
     oupfuncPtr oup32fp;
/* Wrapper functions for the function pointers
    - call these functions to perform I/O.
 */
     short  Inp32 (short portaddr)
     {
          return (inp32fp)(portaddr);
     }

     void  Out32 (short portaddr, short datum)
     {
          (oup32fp)(portaddr,datum);
     }     

//*************************rotate******************
void move()
{
          //Assigns color 
 	 system("color 0b ");
 	 

    	//Displays Front Menu page
    	cout<<"\n\n\n\n\n\n\n\n\n                                WELCOME TO THE ELEVATOR PROGRAM";
    	cout<<"\n\n                              By: Abdul Mannan & Ibrahim & Zaeem";
    	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    	cin.get();
        	
    system ("cls");
    
     int floor;
    cout<<"Please enter the floor number(1-3): ";
    cin>> floor;
    
    system ("cls");
    cout<<"You want to get to floor # ";
    cout << floor;
    cout<<"\nPlease Wait";
    getch();
    if(floor == 1){
             
     int angle = 650;
     int num = 1;
     
     if(angle<0){
     }
     else {

     for(int i=0; i<angle/7&&!kbhit();i++){
     Out32(PPORT_BASE,num);
     num*=2;
     if(num>8){
     num=1;
     }
          Sleep(1);
     Out32(PPORT_BASE,0);
     Sleep(1);
     }
      Out32(PPORT_BASE,0);
     Sleep(1000);
     }               
     
     Out32(PPORT_BASE,0);       
             }
      getch();
      
      
    if(floor == 2){
    int angle = 1100;
     int num = 1;
     
     if(angle<0){
     }
     else {

     for(int i=0; i<angle/7&&!kbhit();i++){
     Out32(PPORT_BASE,num);
     num*=2;
     if(num>8){
     num=1;
     }
          Sleep(1);
     Out32(PPORT_BASE,0);
     Sleep(1);
     }
      Out32(PPORT_BASE,0);
     Sleep(1000);
     }               
     
     Out32(PPORT_BASE,0);       
             }
      getch();
      
         
    
     if(floor == 3){
               }

else
{
    cout<<"Invalid Input";
}
    
}
//*************************Main*********************     
int main(void)
{
     HINSTANCE hLib;
     short x;
     int i;
     /* Load the library */
     hLib = LoadLibrary("inpout32.dll");
     if (hLib == NULL) {
          fprintf(stderr,"LoadLibrary Failed.\n");
          getch();
          return -1;                      }
    /* get the address of the function */
     inp32fp = (inpfuncPtr) GetProcAddress(hLib, "Inp32");
     if (inp32fp == NULL) {
          fprintf(stderr,"GetProcAddress for Inp32 Failed.\n");
          getch();
          return -1;
     }
     oup32fp = (oupfuncPtr) GetProcAddress(hLib, "Out32");
     if (oup32fp == NULL) {
          fprintf(stderr,"GetProcAddress for Oup32 Failed.\n");
          getch();
          return -1;
     }
    /*****  Write 0x75 to data register and verify */
    move();
     Out32(PPORT_BASE,0);//This resets the 8 leds to off or zero
     FreeLibrary(hLib);
     return 0;
}




