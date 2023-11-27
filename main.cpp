#include<bits/stdc++.h>
#include<process.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

using namespace std;

/*
===================
UI FUNCTIONS START
===================
*/

//This function is used for Operating Menu by upper and lower key
// It improves user experience
void menuArrow(int realPosition, int arrowPosition)
{
    if(realPosition == arrowPosition)
    {
        printf("   >>   ");
    }
    else
    {
        printf("        ");
    }
}

// This function used to put cursor in different co-ordinates in console.
void gotoxy(int x, int y)
{
    COORD c; //COORD is a structure to hold screen COORDinates X and Y.
    c.X=x;
    c.Y=y;
    // SetConsoleCursorPosition function sets the cursor position in the console screen buffer.
    // The GetStdHandle() function gives us a mechanism for retrieving(get something from somewhere) the standard input
    // STD_OUTPUT_HANDLE is the standard output device. Initially, this is the active console screen buffer
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);     //1. HANDLE 2. COORD
}

// Logo for app.
void logo()
{
    gotoxy(20, 2);
    printf("    __                  _                       _                \n");
    gotoxy(20, 3);
    printf("   / _|  ___   ___   __| |_ __ ___   ___  _ __ | | _____ _   _   \n");
    gotoxy(20, 4);
    printf("   | |_ / _ \\ / _ \\ / _` | '_ ` _ \\ / _ \\| '_ \\| |/ / _ \\ | | |     \n");
    gotoxy(20, 5);
    printf("   |  _| (_) | (_) | (_| | | | | | | (_) | | | |   <  __/ |_| |    \n");
    gotoxy(20, 6);
    printf("   |_|  \\___/ \\___/ \\__,_|_| |_| |_|\\___/|_| |_|_|\\_\\___|\\__, |  \n");
    gotoxy(20, 7);
    printf("                                                          |___/   \n");
}

/*
=================
UI FUNCTIONS END
=================
*/


int main(){

    system("cls");
    printf("\e[?25l"); /// used to hide cursor in console
    //getData();
    logo();

    int a_position = 1, keyPressed = 0;

    // 13 is the ASCII value of Enter KEY
    while(keyPressed != 13)
    {
        //system("cls");
        gotoxy(45, 10);
        menuArrow(1,a_position);
        printf("1. LOGIN\n");
        gotoxy(45, 12);
        menuArrow(2,a_position);
        printf("2. REGISTER\n");

        keyPressed = getch();
        if(keyPressed == 80 && a_position != 2) a_position++;
        else if(keyPressed == 72 && a_position != 1) a_position--;
        else a_position = a_position;
    }
    switch(a_position)
    {
    case(1):
        //login();
        break;
    case(2):
        //signup();
        break;
    default:
        printf("SYSTEM ERROR!");
    }
    getchar();

}
