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


     
//*************************stepper******************
void stepper()
{
                 do
                 { 
                      for(int i=8;i>=1;i/=2)
                      {
                          cout<<i;
                          Out32(PPORT_BASE,i);
                          Sleep(100);
                          //test_write_datum(i);    
                      }
                      cout 
                      <<endl;
                  } while(!kbhit());
                  Out32(PPORT_BASE,0);
}
//*************************rotate******************
void move(int angle)
{
     int length = angle;
          int num = 1;
     if(angle<0){
     }
     else {
     while(!kbhit()){
     cout<<"\nRotating "<<abs(angle)<<" degrees";
     for(int i=0; i<length/7&&!kbhit();i++){
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
     }
     Out32(PPORT_BASE,0);  

}
//*************************Menu*********************
void menu()
{
    int choice = -1;
    
    while(choice != 0)
    {
       system("cls");
       cout << ("1. Example\n2. Example\n3. Example\n0. End Program\n");
       cin >> choice;
       if(choice == 1)
       {
           system("cls");
            stepper();             
       }
       else if(choice == 2)
       {
       system("cls");
       cout << ("Set angle of motor\n 0 to end End Program\n");
       cin >> choice;

       move(choice);           
       }

    }
    cout << "Program Terminated";
    getch();  
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
     menu();
     Out32(PPORT_BASE,0);//This resets the 8 leds to off or zero
     FreeLibrary(hLib);
     return 0;
}




