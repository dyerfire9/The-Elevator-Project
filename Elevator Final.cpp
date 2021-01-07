/*Muhammad Abdul Mannan & Ibrahim Kaher
June 11, 2018
Controls the step motor for the elevator summative*/

#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <windows.h>
//Kept this in case we need it. 
//#include <string>
//#include<time.h>
//#include <math.h>
//#include <cstdlib>

using namespace std;
int curfloor = 1, desirfloor, floormove;

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

//******************Input********************
int Input () //Gets input from the buttons
{
    int input;
    Out32(PPORT_BASE,0);
    do
    	input = Inp32(PPORT_INP);//Sends the button value to the input variable
    while (input == 120);
	return input;
}
//******************ButtontoFloor********************
int ButtonToFloor (int button) //Converts button value to asociated floor
{
	if(button == 56)
		 button = 1;
	else if(button == 248)
		 button = 2;
	else if(button == 88)
    	 button = 3;
	return button;
}
//******************Up********************
void Up (int numturns) //Turns the motor 4 times (and repeats that a given number of times) clockwse 
{
    for(int x = 1; x<=numturns; x++)
    {
         for (int x = 1; x <= 8; x*=2)
         {
             Out32(PPORT_BASE,x);
			 Sleep (50);
         }
         Sleep (50);         
   	}
}
//******************Counter Clockwise********************
void Down (int numturns) //Turns the motor 4 times (and repeats that a given number of times) coutnerclockwse 
{
    for(int x = 1; x<=numturns; x++)
    {     
         for (int x = 8; x >= 1; x/=2)
         {
             Out32(PPORT_BASE,x);
			 Sleep (50);
         }
         Sleep (50);         
   	}
}
//******************F1F2********************
void F1F2 (String direction) //Moves the elevator between Floor 1 and Floro 2
{
    if (direction == "DOWN") //If going down, runs the Down method a set number of times (the amount needed to go between floor 1 and 2)
        Down (8); //NOTE: CHANGE TO AMOUNT NEEDED TO GO TO F1 AND F2
    else if direction == "UP") //If going up, runs the Up method a set number of times (the amount needed to go between floor 1 and 2)
        Up (8); //NOTE: CHANGE TO AMOUNT NEEDED TO GO TO F1 AND F2
}
//******************F2F3********************
void F2F3 (String direction)
{
    if (direction == "DOWN") //If going down, runs the Down method a set number of times (the amount needed to go between floor 2 and 3)
        Down (6); //NOTE: CHANGE TO AMOUNT NEEDED TO GO TO F2 AND F3
    else if (direction == "UP") //If going up, runs the UP method a set number of times (the amount needed to go between floor 1 and 3
        Up (6); //NOTE: CHANGE TO AMOUNT NEEDED TO GO TO F2 AND F3
}
//******************ChangeFloors********************
void ChangeFloors (String direction)
{
	if(direction == "DOWN") //If going down, keeps on going from floor 3-2 or floor 2-1 until the the current floor equals the desired floor
	{
	    do
        {
  	   	 if (curfloor == 3 && (desirfloor == 2 || desirfloor == 1))
  	   	 	F2F3();
  	   	 else if(curfloor == 2 && desirfloor ==1)
            F1F2();
         curfloor--;
  	    }
  	    while(curfloor !=desirfloor);
    }
  	else if(direction == "UP") //If going up, keeps on going from floor 1-2 or floor 1-3 until the the current floor equals the desired floor
	{
        do
	    {
         if (curfloor == 1 && (desirfloor == 2 || desirfloor == 3))
         	F1F2();
       	 else if (curfloor == 2 && desirfloor == 3)
 			F2F3();
	     curfloor++;
       	}
  	    while(curfloor !=desirfloor); 
   }
}
//*************************changefloors*********************
void Choosefloors()
{
	cout <<"The current floor is "+curfloor;
	cout <<"\nChoose a floor by pressing the buttons";
	desirfloor = ButtonToFloor(Input());
	if(desirfloor == 1 || desirfloor == 2 || desirfloor == 3 )
	{
        cout <<"\nYou wish to go from floor "<<curfloor<<" to floor "<<desirfloor;
    	if(curfloor==desirfloor)
			cout<<"\nYou are already on that floor!\n";
 		else if (curfloor>desirfloor)
  	   		ChangeFloors("DOWN");
		else if (curfloor<desirfloor)
        	ChangeFloors("UP");
	}
	else
		cout << "\nInvalid floor";
}
//*************************Menu*********************
void Menu()
{
	string repeat = "";
	do
	{
        Choosefloors();
		cout << "\nDo you want to go to another floor? (Y/N) ";
		cin >> repeat;
		system("cls");
	}
	while(repeat == "Y");
}
//*************************Main*********************     
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
    Menu();
    FreeLibrary(hLib);
    return 0;
}
