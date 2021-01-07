/* Input Demo
Initial set up to work with input buttons
TEJ3M
Brossard
Jan 5 16 */

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
//Kept this in case we need it. 
//#include <string>
//#include<time.h>
//#include <math.h>
//#include <cstdlib>

using namespace std;


typedef short (_stdcall *inpfuncPtr)(short portaddr);
typedef void (_stdcall *oupfuncPtr)(short portaddr, short datum);

#define PPORT_BASE 0x378
#define PPORT_INP (PPORT_BASE+1)

// Prototypes for Test functions
void test_read8(void);
void test_write(void);
void test_write_datum(short datum);

inpfuncPtr inp32fp;
oupfuncPtr oup32fp;

short  Inp32 (short portaddr)
{
    return (inp32fp)(portaddr);
}

void  Out32 (short portaddr, short datum)
{
    (oup32fp)(portaddr,datum);
}

void test_write_datum(short datum)
{
     short x;
     int i;

     i=PPORT_BASE;
     x = datum;

     /*****  Write the data register */
     Out32(i,x);

     //printf("\nPort write to 0x%X, datum=0x%2X\n" ,i ,x);

     /***** And read back to verify  */
     x = Inp32(i);
     //printf("Port read (%04X)= %04X\n",i,x);
}
//*************************example*********************
void example()//key line for ouput is Out32(PPORT_BASE,in);   
{
     cout << "Enter a number from 0 to 255" << endl;
     int in;
     cin >> in;
     cout << "The number in base two is " << in;
     Out32(PPORT_BASE,in);//outputs the variable in to the printer port     
     getch();
}

//*************************InputDemo*********************
void InputDemo ()//key line for input is input= Inp32(PPORT_INP);
{
    int choice, input;
    
    Out32(PPORT_BASE,0);
       
    system("cls");
    cout <<"Press any keyboard key to exit\n";
    cout<<"\n\n";
    
    do
    {	
    	input = Inp32(PPORT_INP);//Sends the button value to the input variable
    	cout<<input<<" - ";
    
        Sleep(1000);
    }
    while (!kbhit());

    cout<<"\n\nSay goodbye to your first input experience!";
    Sleep(3000);
}
//*************************InputDemo2*********************
void InputDemo2 ()
{
    int choice, input;
    
    Out32(PPORT_BASE,0);
       
    system("cls");
   cout <<"Press any keyboard key to exit\n";
    cout<<"\n";   
    do
    {	
    	input = Inp32(PPORT_INP);//Sends the button value to the input variable
    	cout << input<<" - ";    	
    	if (input == 56)
    	cout <<"You pressed button 1, pin 10";
    	else
    	cout <<"Not programmed";
        cout << endl;  
        Sleep(1000);
    }
    while (!kbhit());
    cout<<"\n\nSay goodbye to your second input experience!";
    Sleep(3000);
}
//*************************buttonDemo*********************
void buttonDemo(void) 
{
     int input;//Declare variable
     while (!kbhit () )
     {
   input= Inp32(PPORT_INP);//Recieve input
    cout<<input<<" ";//Display input
    Sleep(300);
         if (input == 56)
         cout << "\nButton 1 ";
         else if (input == 248)
         cout << "\nButton 2 ";
         else if (input == 88)
         cout << "\nButton 3 ";
         else if (input == 104)
         cout << "\nButton 4 ";
         else if (input == 112)
         cout << "\nButton 5 ";         
         else if (input == 184)
         cout << "\nButton 1 & 2 ";
         else if (input == 24)
         cout << "\nButton 1 & 3 ";
         else if (input == 40)
         cout << "\nButton 1 & 4 ";
         else if (input == 216)
         cout << "\nButton 2 & 3 ";
         else if (input == 232)
         cout << "\nButton 2 & 4 ";
         else if (input == 72)
         cout << "\nButton 3 & 4 ";
         else if (input == 152)
         cout << "\nButton 1, 2 & 3 ";
         else if (input == 8)
         cout << "\nButton 1, 3 & 4 ";
         else if (input == 168)
         cout << "\nButton 1, 2 & 4 ";
         else if (input == 200)
         cout << "\nButton 2, 3 & 4 ";
         else if (input == 136)
         cout << "\nButton 1, 2, 3 & 4 ";
     }
     cin.ignore();
     getch ();
     return ;
}
//*************************Menu*********************
void menu()
{
    int choice = -1;
    
    while(choice != 0)
    {
       system("cls");
       cout << ("1. Button Demo 1\n2. Input Demo 2\n3. Example\n0. End Program\n");
       cin >> choice;
       if(choice == 1)
       {
           system("cls");
            buttonDemo();             
       }
       else if(choice == 2)
       {
           system("cls");
           InputDemo2();             
       }
       else if(choice == 3)
       {
           system("cls");
           example();            
       }             
    }
    cout << "Program Terminated";
    getch();  
}
//*************************Menu*********************
int main(void)
{
    HINSTANCE hLib;
    short x;
    int i;
    /* Load the library */
    hLib = LoadLibrary("inpout32.dll");
    if (hLib == NULL) 
    {
        fprintf(stderr,"LoadLibrary Failed.\n");
        getch();
        return -1;
    }
    /* get the address of the function */
    inp32fp = (inpfuncPtr) GetProcAddress(hLib, "Inp32");

    if (inp32fp == NULL) 
    {
         fprintf(stderr,"GetProcAddress for Inp32 Failed.\n");
         getch();
         return -1;
    }
    oup32fp = (oupfuncPtr) GetProcAddress(hLib, "Out32");

    if (oup32fp == NULL) 
    {
         fprintf(stderr,"GetProcAddress for Oup32 Failed.\n");
         getch();
         return -1;
    }   
    menu();
    FreeLibrary(hLib);
     return 0;
}


