#include<bits/stdc++.h>
#include<process.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<iostream>
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
        printf("  >> ");
    }
    else
    {
        printf("     ");
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

/*
=========
HOMEPAGE
=========
*/

void homepage(){
cout << "ok";
}


/*
===================
USER LOGIN & SIGNUP START
===================
*/

struct User
{
    string email, pass, name, address;
};

struct User u[100];
int n; //global variable for count users from userDB.txt file
int current; // global variable for showing data on 'my profile' for particular user1

void getData()
{
    int i;
    FILE *fp;
    fp = fopen("db/userdb.txt", "r");

    for(i=0; fscanf(fp, "%s", u[i].email) != -1; i++)
    {
        fscanf(fp,"%s", u[i].name);
        fscanf(fp,"%s", u[i].pass);
        fscanf(fp,"%s", u[i].address);
    }
    n = i; //global variable declared above. Used to count total users.
    fclose(fp);
}

// stores all data from struct user u[100] to userDB.txt file.
void writeData()
{
    ofstream userFile("db/userdb.txt", ios::app);
    if (!userFile.is_open()) {
        cerr << "Error opening file for writing.\n";
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i<n; i++)
    {
    userFile << u[i].email << "\n" << u[i].name << "\n" << u[i].pass << "\n" << u[i].address << "\n";
    }
    userFile.close();
}

// Login function. User type there username & pass correctly to log into there account.
void login()
{
    system("cls");
    logo();
    string email, password;

    int checkingIfUserfound = 0, index=0;
    gotoxy(50, 10);
    printf("  LOGIN\t\t");
    gotoxy(50, 12);
    printf("\t\t");
    gotoxy(50, 14);
    printf("\t\t\t");
    gotoxy(50, 12);
    printf("  EMAIL: ");
    cin >> email;
    gotoxy(50, 14);
    printf("  PASSWORD: ");
    cin >> password;

    ifstream userFile("db/userdb.txt");

    for(int i = 0; i < n; i++)
    {
        if(u[i].email == email && u[i].pass == password)
        {
            current = i; // here current represents the logged in user index number in userDB.txt file.
            checkingIfUserfound = 1;

            //if(u[i].role == "admin")
            //{
            //   adminPanel();
            //    break;
            //}
           // else
            //{
                homepage();
            //    break;
            //}
        }
    }

    if(checkingIfUserfound == 0)
    {
        gotoxy(52, 16);
        printf("WRONG USERNAME OR PASSWORD! TRY AGAIN");
        Sleep(1000);
        login();
    }


}
/// signup function used to register new users to the app. And there data stores in userDB.txt file.
void signup()
{
    system("cls");
    string email, name, address, password;

    logo();
    gotoxy(50, 10);
    printf("  REGISTER\t\t");
    gotoxy(50, 12);
    printf("               ");
    gotoxy(50, 14);
    printf("                   ");
    gotoxy(50, 12);
    cout<< "  FULL NAME: ";
    //cin.ignore(100, '\n');
    getline(cin, name);
    gotoxy(50, 14);
    cout <<"  EMAIL: ";
    getline(cin, email);
    gotoxy(50, 16);
    cout << "  ADDRESS: ";
    getline(cin, address);
    gotoxy(50, 18);
    cout << "  PASSWORD: ";
    getline(cin, password);

    // Save user information to the database
    u[n].email = email;
    u[n].name = name;
    u[n].pass = password;
    u[n].address = address;

    n++;
    writeData();

    gotoxy(50, 24);
    printf("ACCOUNT CREATED SUCCESSFULLY...");
    Sleep(1000);
    login();
}
/*
===================
USER LOGIN & SIGNUP END
===================
*/


int main()
{

    system("cls");
    printf("\e[?25l"); // used to hide cursor in console
    logo();

    //getData();

    int a_position = 1, keyPressed = 0;

    // 13 is the ASCII value of Enter KEY
    while(keyPressed != 13)
    {
        //system("cls");
        gotoxy(42, 10);
        menuArrow(1,a_position);
        printf("LOGIN NOW\n");
        gotoxy(42, 12);
        menuArrow(2,a_position);
        printf("CREATE ACCOUNT\n");

        keyPressed = getch();
        if(keyPressed == 80 && a_position != 2) a_position++;
        else if(keyPressed == 72 && a_position != 1) a_position--;
        else a_position = a_position;
    }
    switch(a_position)
    {
    case(1):
        login();
        break;
    case(2):
        signup();
        break;
    default:
        printf("SYSTEM ERROR!");
    }
    getchar();

}
