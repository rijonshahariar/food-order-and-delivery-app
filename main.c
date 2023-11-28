#include<stdio.h>
#include<string.h>
#include<process.h>
#include<windows.h>
#include<time.h>
#include <conio.h>

/// This function used to put cursor in different co-ordinates in console.
void gotoxy(int x, int y)
{
    COORD c; ///COORD is a structure to hold screen COORDinates X and Y.
    c.X=x;
    c.Y=y;
    /// SetConsoleCursorPosition function sets the cursor position in the console screen buffer.
    /// The GetStdHandle() function gives us a mechanism for retrieving(get something from somewhere) the standard input
    /// STD_OUTPUT_HANDLE is the standard output device. Initially, this is the active console screen buffer
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);     //1. HANDLE 2. COORD
}

struct User
{
    char email[100], pass[100], address[100], role[10], name[100];
};
struct User u[100];

struct Orders
{
    char email[100];
    int total, item, quant, status;
};
struct Orders orders[100];

char cur_email[100];

int ords;
int n; //global variable for count users from userDB.txt file
int current; // global variable for showing data on 'my profile' for particular user1

//This function is used for Operating Menu by upper and lower key
// It improves user experience
void menuArrow(int realPosition, int arrowPosition)
{
    if(realPosition == arrowPosition)
    {
        printf(" >> ");
    }
    else
    {
        printf("    ");
    }
}
/// Logo for app.
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
/// This function reads user informations(id, pass, role, route) from file(userdb.txt).
void getData()
{
    int i;
    FILE *fp;
    fp = fopen("db/userdb.txt", "r");

    for(i=0; fscanf(fp, "%s", u[i].email) != -1; i++)
    {
        fscanf(fp,"%s", u[i].pass);
        fscanf(fp,"%s", u[i].role);
        fscanf(fp,"%s", u[i].address);
    }
    n=i; ///global variable declared above. Used to count total users.
    fclose(fp);
}

void getOrder()
{
    int i;
    FILE *fw;
    fw = fopen("db/orders.txt", "r");

    for(i=0; fscanf(fw, "%s", orders[i].email) != -1; i++)
    {
        fscanf(fw,"%d", &orders[i].item);
        fscanf(fw, "%d\n", &orders[i].total);
        fscanf(fw, "%d\n", &orders[i].quant);
        fscanf(fw, "%d\n", &orders[i].status);
    }
    ords=i; ///global variable declared above.
    fclose(fw);
}
/// Login function. User type there username & pass correctly to log into there account.
void login()
{
    system("cls");
    logo();
    char u_email[100], password[100], ch;
    int checkingIfUserfound = 0, index=0;

    gotoxy(50, 10);
    printf("  LOGIN\t\t");
    gotoxy(50, 12);
    printf("\t\t");
    gotoxy(50, 14);
    printf("\t\t\t");
    gotoxy(50, 12);
    printf("  ENTER EMAIL: ");
    scanf("%s", u_email);
    gotoxy(50, 14);
    printf("  PASSWORD: ");
    /* 13 is ASCII value of Enter key */
    while((ch = getch()) != 13)
    {
        if(index < 0) index = 0;
        /* 8 is ASCII value of BACKSPACE character */
        if(ch == 8 && index!= 0)
        {
            putch('\b');
            putch(' ');
            putch('\b');
            index--;
            continue;
        }
        password[index++] = ch;
        putch('*');
    }
    password[index] = '\0';
    /// the below loop will continue upto total user number in userDB.txt file
    for(int i = 0; i<n; i++)
    {
        if(strcmp(u_email,u[i].email) == 0 && strcmp(password, u[i].pass) == 0)
        {
            current = i; /// here current represents the logged in user index number in userDB.txt file.
            checkingIfUserfound = 1;
            strcpy(cur_email, u_email);

            if(strcmp("admin",u[i].role) == 0)
            {
                adminPanel();
                break;
            }
            else
            {
                homepage();
                break;
            }
        }
    }

    if(checkingIfUserfound == 0)
    {
        gotoxy(52, 16);
        printf("WRONG USERNAME OR PASSWORD! TRY AGAIN");
        sleep(1);
        login();
    }
}
/// signup function used to register new users to the app. And there data stores in userDB.txt file.
void signup()
{
    system("cls");
    logo();
    int x, a_position =1, keyPressed = 0;
    char uid[100], key[100], route[100], name[100];
    gotoxy(50, 10);
    printf("  REGISTER\t\t");
    gotoxy(50, 12);
    printf("               ");
    gotoxy(50, 14);
    printf("                   ");

    gotoxy(50, 12);
    printf("  ENTER EMAIL: ");
    scanf("%s", uid);
    gotoxy(50, 14);
    printf("  PASSWORD: ");
    scanf("%s", key);
    gotoxy(50, 16);
    printf("  ADDRESS: ");
    scanf("%s", route);


    /// Here u is a user structure array which has datatypes(id, pass, route, role);
    strcpy(u[n].email, uid); /// n(global variable) is new user index number.
    strcpy(u[n].pass,key);
    strcpy(u[n].role, "user");
    strcpy(u[n].address,route);

    n++;
    writeData();
    gotoxy(50, 24);
    printf("ACCOUNT CREATED SUCCESSFULLY");
    sleep(1);
    login();
}
/// stores all data from struct user u[100] to userDB.txt file.
void writeData()
{
    FILE *fr = fopen("db/userdb.txt", "w");
    /// below loop is used to put data in userDB.txt file.
    for(int i = 0; i<n; i++)
    {
        fprintf(fr, "%s\n", u[i].email);
        fprintf(fr, "%s\n", u[i].pass);
        fprintf(fr, "%s\n", u[i].role);
        fprintf(fr, "%s\n", u[i].address);
    }
    fclose(fr);
}
/// adminpanel function is the homepage for admin users. This function used to -
/// 1. view all users data except passwords.
/// 2. can add new users to the app.
/// 3. delete and update user data.
/// 4. manage bus schedule & bus related other functionalities.
void adminPanel()
{
    system("cls");
    logo();
    getOrder();
    int a_position = 1, keyPressed = 0;

    // 13 is the ASCII value of Enter KEY

    while(keyPressed != 13)
    {
        gotoxy(24, 12);
        menuArrow(1,a_position);
        printf(" CONFIRM ORDER");
        gotoxy(24, 14);
        menuArrow(2,a_position);
        printf(" CANCEL ORDER");
        gotoxy(24, 16);
        keyPressed = getch();

        if(keyPressed == 80 && a_position != 2)
        {
            a_position++;
        }
        else if(keyPressed == 72 && a_position != 1)
        {
            a_position--;
        }
        else
        {
            a_position = a_position;
        }
    }
    int conf;

    if(a_position==1)
    {
        int x = 16;
        for(int i = 0; i < ords; i++)
        {
            gotoxy(24, x);
            printf("%d . ", i + 1);
            printf("%d", orders[i].quant);
            if(orders[i].item == 1)
            {
                printf(" Porota ");
            }
            else if(orders[i].item == 2)
            {
                printf(" Bhaji ");
            }
            else if(orders[i].item == 3)
            {
                printf(" Singara ");
            }
            else if(orders[i].item == 4)
            {
                printf(" Lacchi ");
            }
            else if(orders[i].item == 5)
            {
                printf(" Chapathi ");
            }
            else if(orders[i].item == 6)
            {
                printf(" Fried Rice ");
            }
            else if(orders[i].item == 7)
            {
                printf(" Noodle ");
            }
            else if(orders[i].item == 8)
            {
                printf(" Sandwich ");
            }
            else if(orders[i].item == 9)
            {
                printf(" Barfi ");
            }
            else if(orders[i].item == 10)
            {
                printf(" Meats ");
            }
            else if(orders[i].item == 11)
            {
                printf(" Seasonal Juice ");
            }
            else if(orders[i].item == 12)
            {
                printf(" Custard ");
            }

            printf("Taka %d.", orders[i].total);
            if(orders[i].status == 0)
            {
                printf("     PENDING     ");
            }
            else
            {
                printf("     DELIVERED    ");
            }

            x+=2;
        }

        gotoxy(24, 14);
        printf("ENTER INDEX TO CONFIRM ORDER: ");
        scanf("%d", &conf);

        orders[conf - 1].status = 1;
        FILE *fx = fopen("db/orders.txt", "w");

        for(int i = 0; i < ords; i++)
        {
            fprintf(fx, "%s\n", orders[i].email);
            fprintf(fx, "%d\n", orders[i].item);
            fprintf(fx, "%d\n", orders[i].total);
            fprintf(fx, "%d\n", orders[i].quant);
            fprintf(fx, "%d\n", orders[i].status);
        }
        fclose(fx);
        gotoxy(24, 14);
        printf("                                        ");
        printf("ORDER CONFIRMED.");
        sleep(1);
        adminPanel();

    }
    else
    {
        int x = 16;
        for(int i = 0; i < ords; i++)
        {
            gotoxy(24, x);

            printf("%d . ", i + 1);

            printf("%d", orders[i].quant);
            if(orders[i].item == 1)
            {
                printf(" Porota ");
            }
            else if(orders[i].item == 2)
            {
                printf(" Bhaji ");
            }
            else if(orders[i].item == 3)
            {
                printf(" Singara ");
            }
            else if(orders[i].item == 4)
            {
                printf(" Lacchi ");
            }
            else if(orders[i].item == 5)
            {
                printf(" Chapathi ");
            }
            else if(orders[i].item == 6)
            {
                printf(" Fried Rice ");
            }
            else if(orders[i].item == 7)
            {
                printf(" Noodle ");
            }
            else if(orders[i].item == 8)
            {
                printf(" Sandwich ");
            }
            else if(orders[i].item == 9)
            {
                printf(" Barfi ");
            }
            else if(orders[i].item == 10)
            {
                printf(" Meats ");
            }
            else if(orders[i].item == 11)
            {
                printf(" Seasonal Juice ");
            }
            else if(orders[i].item == 12)
            {
                printf(" Custard ");
            }

            printf("Taka %d.", orders[i].total);
            if(orders[i].status == 0)
            {
                printf("     PENDING     ");
            }
            else if(orders[i].status == 1)
            {
                printf("     DELIVERED    ");
            }
            else{
                printf("     CANCELLED    ");
            }

            x+=2;
        }

        gotoxy(24, 14);
        printf("ENTER INDEX TO CANCEL ORDER: ");
        scanf("%d", &conf);

        orders[conf - 1].status = 2;
        FILE *fx = fopen("db/orders.txt", "w");

        for(int i = 0; i < ords; i++)
        {
            fprintf(fx, "%s\n", orders[i].email);
            fprintf(fx, "%d\n", orders[i].item);
            fprintf(fx, "%d\n", orders[i].total);
            fprintf(fx, "%d\n", orders[i].quant);
            fprintf(fx, "%d\n", orders[i].status);
        }
        fclose(fx);
        gotoxy(24, 14);
        printf("                                        ");
        printf("ORDER CANCELLED.");
        sleep(1);
        adminPanel();

    }

}

void go_back_user(int j)
{
    gotoxy(24, j+8);
    printf("Press 0 to Return ");
    int q = getch();
    if(q==48) homepage();
    else go_back_user(j);
}

void go_back(int j)
{
    gotoxy(24, j+7);
    printf("Press 0 to return ");
    int q = getch();
    if(q==48) adminPanel();
    else go_back(j);
}

void Myprofile(int r)
{

}

void payment(int quant, int item, int total)
{
    getOrder();

    system("cls");
    int bkashnumber, paid = 0, pin;

    logo();
    gotoxy(24, 10);
    printf("TOTAL PAYABLE: %d", total);

    int a_position = 1, keyPressed = 0;

    // 13 is the ASCII value of Enter KEY

    while(keyPressed != 13)
    {
        gotoxy(24, 12);
        menuArrow(1,a_position);
        printf(" PAY NOW");
        gotoxy(24, 14);
        menuArrow(2,a_position);
        printf(" CANCEL ORDER");
        gotoxy(24, 16);
        keyPressed = getch();

        if(keyPressed == 80 && a_position != 2)
        {
            a_position++;
        }
        else if(keyPressed == 72 && a_position != 1)
        {
            a_position--;
        }
        else
        {
            a_position = a_position;
        }
    }
    if(a_position==1)
    {
        gotoxy(24, 14);
        printf("ENTER BKASH NUMBER: ");
        scanf("%d", &bkashnumber);
        gotoxy(24, 16);
        printf("ENTER AMOUNT: ");
        scanf("%d", &paid);
        gotoxy(24, 18);
        printf("ENTER PINCODE: ");
        scanf("%d", &pin);

        strcpy(orders[ords].email, cur_email);
        orders[ords].item = item;
        orders[ords].total = total;
        orders[ords].quant = quant;
        orders[ords].status = 0;

        ords++;

        FILE *fx = fopen("db/orders.txt", "w");

        for(int i = 0; i < ords; i++)
        {
            fprintf(fx, "%s\n", orders[i].email);
            fprintf(fx, "%d\n", orders[i].item);
            fprintf(fx, "%d\n", orders[i].total);
            fprintf(fx, "%d\n", orders[i].quant);
            fprintf(fx, "%d\n", orders[i].status);
        }
        fclose(fx);

        gotoxy(24, 20);
        printf("ORDER PLACED SUCCESSFULLY.");
        sleep(1);
        homepage();

    }
    else
    {
        gotoxy(24, 14);
        printf(" CANCELLING...");
        sleep(1);
        homepage();
    }
}


void orderFood()
{
    system("cls");
    logo();

    printf("\n      *******************---------------------FOOD MENU------------------*************************");
    printf("\n      --------------------------------------------------------------------------------------------");
    printf("\n      |	  1)Porota	 |	 2)Bhaji	|	3)Singara	|	4)Lacchi   |");
    printf("\n      |	     20tk  	 |	   25tk 	|	   10tk 	|	   30tk	   |");
    printf("\n      --------------------------------------------------------------------------------------------");
    printf("\n      --------------------------------------------------------------------------------------------");
    printf("\n      |	  5)Chapathi     |    6)Fried rice      |	7)Noodles	|   8)Sandwich     |");
    printf("\n      |	     30tk        |     	     40tk       |	   35tk   	|      50tk        |");
    printf("\n      --------------------------------------------------------------------------------------------");
    printf("\n      --------------------------------------------------------------------------------------------");
    printf("\n      |	   9)Barfi       |      10)Meats        | 11)Seasonal Juice	|   12)Custard     |");
    printf("\n      |       55tk       |       60tk           |	       40tk    	|         35tk     |");
    printf("\n      --------------------------------------------------------------------------------------------");

    while(1)
    {
        gotoxy(24, 24);
        int item, quant, price, total = 0;
        printf("ENTER ITEM NUMBER: ");
        scanf("%d", &item);
        gotoxy(24, 26);
        printf("ENTER QUANTITY: ");
        scanf("%d",&quant);

        switch(item)
        {
        case 1:
            price= 20 * quant;
            break;
        case 2:
            price=25 * quant;
            break;
        case 3:
            price=10 * quant;
            break;
        case 4:
            price=30 * quant;
            break;
        case 5:
            price=30 * quant;
            break;
        case 6:
            price=40*quant;
            break;
        case 7:
            price=35*quant;
            break;
        case 8:
            price=50*quant;
            break;
        case 9:
            price=55*quant;
            break;
        case 10:
            price=60*quant;
            break;
        case 11:
            price=40*quant;
            break;
        case 12:
            price=35*quant;
            break;
        }

        total = total+ price;

        gotoxy(24, 28);
        printf("TOTAL PAYMENT: %d TK", total);

        sleep(1);
        gotoxy(24, 30);
        printf("REDIRECTING TO PAYMENT PAGE...");
        sleep(1);
        payment(quant, item, total);
    }

}


void myOrders()
{
    system("cls");
    logo();
    getOrder();
    gotoxy(24, 14);
    printf("YOUR ORDERS: ");
    int x = 16;
    for(int i = 0; i < ords; i++)
    {
        if(strcmp(cur_email,orders[i].email) == 0)
        {
            gotoxy(24, x);
            printf("You ordered %d", orders[i].quant);
            if(orders[i].item == 1)
            {
                printf(" Porota ");
            }
            else if(orders[i].item == 2)
            {
                printf(" Bhaji ");
            }
            else if(orders[i].item == 3)
            {
                printf(" Singara ");
            }
            else if(orders[i].item == 4)
            {
                printf(" Lacchi ");
            }
            else if(orders[i].item == 5)
            {
                printf(" Chapathi ");
            }
            else if(orders[i].item == 6)
            {
                printf(" Fried Rice ");
            }
            else if(orders[i].item == 7)
            {
                printf(" Noodle ");
            }
            else if(orders[i].item == 8)
            {
                printf(" Sandwich ");
            }
            else if(orders[i].item == 9)
            {
                printf(" Barfi ");
            }
            else if(orders[i].item == 10)
            {
                printf(" Meats ");
            }
            else if(orders[i].item == 11)
            {
                printf(" Seasonal Juice ");
            }
            else if(orders[i].item == 12)
            {
                printf(" Custard ");
            }

            printf("and paid Taka %d.", orders[i].total);
        }
        x+=2;
    }

    go_back_user(16);
}

void orderStatus()
{
    system("cls");
    logo();
    getOrder();

    printf("  ----------------------------------------------");
    printf("  FOOD    |   QUANTITY   |   PRICE   | STATUS ");
    printf("  -----------------------------------------------");
    int x = 18;
    for(int i = 0; i < ords; i++)
    {
        if(strcmp(cur_email,orders[i].email) == 0)
        {
            gotoxy(24, x);
            if(orders[i].item == 1)
            {
                printf(" Porota ");
            }
            else if(orders[i].item == 2)
            {
                printf(" Bhaji ");
            }
            else if(orders[i].item == 3)
            {
                printf(" Singara ");
            }
            else if(orders[i].item == 4)
            {
                printf(" Lacchi ");
            }
            else if(orders[i].item == 5)
            {
                printf(" Chapathi ");
            }
            else if(orders[i].item == 6)
            {
                printf(" Fried Rice ");
            }
            else if(orders[i].item == 7)
            {
                printf(" Noodle ");
            }
            else if(orders[i].item == 8)
            {
                printf(" Sandwich ");
            }
            else if(orders[i].item == 9)
            {
                printf(" Barfi ");
            }
            else if(orders[i].item == 10)
            {
                printf(" Meats ");
            }
            else if(orders[i].item == 11)
            {
                printf(" Seasonal Juice ");
            }
            else if(orders[i].item == 12)
            {
                printf(" Custard ");
            }

            printf("     %d    ", orders[i].quant);
            printf("     %d    ", orders[i].total);
            if(orders[i].status == 0)
            {
                printf("     PENDING     ");
            }
            else if(orders[i].status == 1)
            {
                printf("     DELIVERED     ");
            }
            else{
                printf("     CANCELLED     ");
            }
        }
        x+=2;
    }

    go_back_user(16);
}

void credits()
{
    system("cls");
    logo();

    gotoxy(45,10);
    printf("==:DEVELOPED BY:==");
    gotoxy(45,12);
    printf("   SARWAR JAHIN");
    gotoxy(45,13);
    printf("     C223143");
    gotoxy(45,15);
    printf("  SHAHARIAR RIJON");
    gotoxy(45,16);
    printf("     C223155");
    gotoxy(45,18);
    printf("   ANAYET ULLAH");
    gotoxy(45,19);
    printf("     C2231xx");
    gotoxy(45,21);
    printf("    MAINUR RAHAT");
    gotoxy(45,22);
    printf("     C2231xx");

    go_back_user(16);
}


void homepage()
{
    system("cls");
    logo();

    printf("\n      *******************---------------------FOOD MENU------------------*************************");
    printf("\n      --------------------------------------------------------------------------------------------");
    printf("\n      |	  1)Porota	 |	 2)Bhaji	|	3)Singara	|	4)Lacchi   |");
    printf("\n      |	     20tk  	 |	   25tk 	|	   10tk 	|	   30tk	   |");
    printf("\n      --------------------------------------------------------------------------------------------");
    printf("\n      --------------------------------------------------------------------------------------------");
    printf("\n      |	  5)Chapathi     |    6)Fried rice      |	7)Noodles	|   8)Sandwich     |");
    printf("\n      |	     30tk        |     	     40tk       |	   35tk   	|      50tk        |");
    printf("\n      --------------------------------------------------------------------------------------------");
    printf("\n      --------------------------------------------------------------------------------------------");
    printf("\n      |	    9)Barfi      |      10)Meats        | 11)Seasonal Juice	|   12)Custard     |");
    printf("\n      |       55tk       |       60tk           |	       40tk    	|         35tk     |");
    printf("\n      --------------------------------------------------------------------------------------------");

    int a_position = 1, keyPressed = 0;

    // 13 is the ASCII value of Enter KEY

    while(keyPressed != 13)
    {
        gotoxy(24, 22);
        menuArrow(1,a_position);
        printf(" ORDER FOOD");
        gotoxy(24, 24);
        menuArrow(2,a_position);
        printf(" MY ORDERS");
        gotoxy(24, 26);
        menuArrow(3,a_position);
        printf(" ORDER STATUS");
        gotoxy(24, 28);
        menuArrow(4,a_position);
        printf(" PROFILE");
        gotoxy(24, 30);
        menuArrow(5,a_position);
        printf(" LOG OUT");
        gotoxy(24,32);
        keyPressed = getch();

        if(keyPressed == 80 && a_position != 5)
        {
            a_position++;
        }
        else if(keyPressed == 72 && a_position != 1)
        {
            a_position--;
        }
        else
        {
            a_position = a_position;
        }
    }
    if(a_position==1) orderFood();
    if(a_position==2) myOrders();
    if(a_position==3) orderStatus();
    //if(a_position==4) Cancelseat();
    //if(a_position==5) credits();
    //if(a_position==6) main();

}

int search_by_id()
{

}

void delete_user()
{

}

void update_user()
{

}

/// Initiate page of the app. Users can register or login from here.
int main()
{
    system("cls");
    printf("\e[?25l"); /// used to hide cursor in console
    getData();
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
