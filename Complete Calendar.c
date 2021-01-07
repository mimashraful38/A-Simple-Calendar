#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

// please copy govoff.dat this file and paste same directory

struct Remainder
{
    int dd;
    int mm;
    char note[250];
};
struct Remainder R;

COORD xy = {0, 0};

void gotoxy (int x, int y)
{
    xy.X = x; xy.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
     return;
}

void ClearColor()
{
    SetColor(15);
}

int leapYear(int year)
{
    if(year % 400 == 0 || (year % 100!=0 && year % 4 ==0))
    {
        return 1;
    }
    return 0;
}

void increase_month(int *mm,  int *yy)
{
    ++*mm;
    if(*mm > 12)
    {
        ++*yy;
        *mm = *mm - 12;
    }
}

void decrease_month(int *mm,  int *yy)
{
    --*mm;
    if(*mm < 1)
    {
        --*yy;
        if(*yy<1000)
        {
            printf("No record available");
            return;
        }
        *mm = *mm + 12;
    }
}

int getNumberOfDays(int month,int year)
{
    switch(month)
    {
        case 1 : return(31);
        case 2 : if(leapYear(year)==1)
            return(29);
        else
            return(28);
        case 3 : return(31);
        case 4 : return(30);
        case 5 : return(31);
        case 6 : return(30);
        case 7 : return(31);
        case 8 : return(31);
        case 9 : return(30);
        case 10: return(31);
        case 11: return(30);
        case 12: return(31);
        default: return(-1);
   }
}

char *getName(int day)
{
    switch(day)
    {
        case 0 :return("Sunday");
        case 1 :return("Monday");
        case 2 :return("Tuesday");
        case 3 :return("Wednesday");
        case 4 :return("Thursday");
        case 5 :return("Friday");
        case 6 :return("Saturday");
        default:return("Error in getName() module.Invalid argument passed");
    }
}

void print_date(int mm, int yy)
{
    SetColor(10);
    gotoxy(0,5);
    today();
    ClearColor();
    SetColor(0);
    gotoxy(40,7);
    printf("*************************\n");
    ClearColor();
    SetColor(1);
    gotoxy(45,8);
    switch(mm)
    {
        case 1: printf("January"); break;
        case 2: printf("February"); break;
        case 3: printf("March"); break;
        case 4: printf("April"); break;
        case 5: printf("May"); break;
        case 6: printf("June"); break;
        case 7: printf("July"); break;
        case 8: printf("August"); break;
        case 9: printf("September"); break;
        case 10: printf("October"); break;
        case 11: printf("November"); break;
        case 12: printf("December"); break;
    }
    printf(" - %d", yy);
    ClearColor();
    SetColor(0);
    gotoxy(40,9);
    printf("*************************\n");
    ClearColor();
}
int getDayNumber(int d,int m,int y)
{

    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

char *getDay(int dd,int mm,int yy)
{
    int day;
    if(!(mm>=1 && mm<=12))
    {
        return("Invalid month value");
    }
    else if(!(dd>=1 && dd<=getNumberOfDays(mm,yy)))
    {
        return("Invalid date");
    }
    else if(yy>=1000)
    {
        day = getDayNumber(dd,mm,yy);
        return(getName(day));
    }
    else
    {
        return("Please give year more than 1000");
    }
}


void printMonth(int mon,int year,int x,int y)
{
    int nod, day, cnt, d = 1, x1 = x, y1 = y;    SetColor(0);
    if(!(mon>=1 && mon<=12))
    {
        printf("INVALID MONTH");
        getch();
        system("cls");
    }
    if(!(year>=1000))
    {
        printf("INVALID YEAR");
        getch();
        return;
        system("cls");
    }
    gotoxy(x,y);
    SetColor(1);
    printf("S   M   T   W   T   F   S   ");
    y++;
    ClearColor();
    nod = getNumberOfDays(mon,year);
    day = getDayNumber(d,mon,year);
    switch(day)
    {
        case 0 :
            x=x;
            cnt=1;
            break;
        case 1 :
            x=x+4;
            cnt=2;
            break;
        case 2 :
            x=x+8;
            cnt=3;
            break;
        case 3 :
            x=x+12;
            cnt=4;
            break;
        case 4 :
            x=x+16;
            cnt=5;
            break;
        case 5 :
            x=x+20;
            cnt=6;
            break;
        case 6 :
            x=x+24;
            cnt=7;
            break;
        default :
            printf("INVALID DATA FROM THE getOddNumber()MODULE");
            return;
    }
    gotoxy(x,y);

      if(cnt==6 || cnt==7)
        {
            SetColor(12);
        }
      else
        {
            ClearColor();
        }
    if(checkNote(d,mon)==1)
    {
            SetColor(12);
    }

    printf("%02d",d);

     for(d=2;d<=nod;d++)
    {
        if(cnt%7==0)
        {
            y++;
            cnt=0;
            x=x1-4;
        }
        x = x+4;
        cnt++;
        gotoxy(x,y);
        if(cnt==6 || cnt==7)
        {
            SetColor(12);
        }
        else
        {
            ClearColor();
        }

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        if(d==tm.tm_mday && mon==tm.tm_mon+1 && year==tm.tm_year+1900)
            {
                SetColor(10);
            }

        if(checkoffday(d,mon)==1)
        {
            SetColor(12);
        }
        if(checkNote(d,mon)==1)
        {
            SetColor(0);
        }

        printf("%02d",d);

    }

}
void wholeCal(int yy)

{
    int x=15,y=3;
    gotoxy(x,y);
    SetColor(1);
    printf("January");
    ClearColor();
    printMonth(1,yy,x-10,y+2);

    gotoxy(x+35,y);
    SetColor(1);
    printf("February");
    ClearColor();
    if((yy)%4==0)
    printMonth(2,yy,x+25,y+2);
     else
    printMonth(2,yy,x+25,y+2);

    gotoxy(x+70,y);
    SetColor(1);
    printf("March");
    ClearColor();
    printMonth(3,yy,x+60,y+2);

    gotoxy(x,y+10);
    SetColor(1);
    printf("April");
    ClearColor();
    printMonth(4,yy,x-10,y+12);

    gotoxy(x+35,y+10);
    SetColor(1);
    printf("May");
    ClearColor();
    printMonth(5,yy,x+25,y+12);

    gotoxy(x+70,y+10);
    SetColor(1);
    printf("June");
    ClearColor();
    printMonth(6,yy,x+60,y+12);

    gotoxy(x,y+20);
    SetColor(1);
    printf("July");
    ClearColor();
    printMonth(7,yy,x-10,y+22);

    gotoxy(x+35,y+20);
    SetColor(1);
    printf("August");
    ClearColor();
    printMonth(8,yy,x+25,y+22);

    gotoxy(x+70,y+20);
    SetColor(1);
    printf("September");
    ClearColor();
    printMonth(9,yy,x+60,y+22);

    gotoxy(x,y+30);
    SetColor(1);
    printf("October");
    ClearColor();
    printMonth(10,yy,x-10,y+32);

    gotoxy(x+35,y+30);
    SetColor(1);
    printf("November");
    ClearColor();
    printMonth(11,yy,x+25,y+32);

    gotoxy(x+70,y+30);
    SetColor(1);
    printf("December");
    ClearColor();
    printMonth(12,yy,x+60,y+32);

}


int checkoffday(int dd, int mm)
{
    FILE *fp;
    fp = fopen("govoff.dat","rb");
    if(fp == NULL){
        printf("Error in Opening the file");
    }
    while(fread(&R,sizeof(R),1,fp) == 1){
        if(R.dd == dd && R.mm == mm){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void addNote()
{
FILE *fp;
    fp = fopen("note.dat","ab+");
    printf("Enter the date(DD/MM): ");
    scanf("%d%d",&R.dd, &R.mm);
    printf("\t\t\t\t\tEnter the Note ");
    fflush(stdin);
    scanf("%[^\n]",R.note);
    if(fwrite(&R,sizeof(R),1,fp))
    {
        puts("\t\t\t\t\tNote is saved successfully");
        fclose(fp);
    }


    else
    {
        puts("\t\t\t\t\aFail to save!!\a");

    }
    printf("\n\t\t\t\tPress b For Back");
    getch();
    fclose(fp);
}


void showNote(int mm)
{
    FILE *fp;
    int i = 0, isFound = 0;
    system("cls");
    fp = fopen("note.dat","rb");
    if(fp == NULL){
        printf("Error in opening the file");
    }
    while(fread(&R,sizeof(R),1,fp) == 1){
        if(R.mm == mm)
        {
            gotoxy(10,5+i);
            printf("Note %d Day = %d: %s", i+1, R.dd,  R.note);
            isFound = 1;
            i++;
        }
    }
    if(isFound == 0)
    {
        printf("This Month contains no note");
    }

    printf("\nPress b For Back");
    getch();

}

int checkNote(int dd, int mm)
{
    FILE *fp;
    fp = fopen("note.dat","rb");
    if(fp == NULL){
        printf("Error in Opening the file");
    }
    while(fread(&R,sizeof(R),1,fp) == 1){
        if(R.dd == dd && R.mm == mm){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void today()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\t\t\t\t Today Is: %02d-%02d-%d   Time: %02d:%02d\n", tm.tm_mday, tm.tm_mon+1,tm.tm_year+1900, tm.tm_hour, tm.tm_min);

}



int main()
{
    gotoxy(40,7);
    system("color 3F");
    int dd,mm,yy,y=1,x=20;
    int choice;
    char ch = 'a';

    Menu:
    system("cls");
    while(1)
    {
        SetColor(10);
        printf("\n\t\t\t\t********Welcome To Our Calendar*******\n");
        today();
        ClearColor();
        printf("\n\n\t\t\t\t\t***Menu***");
        printf("\n\t\t\t1. Find the day");
        printf("\n\t\t\t2. Print Calendar of a Month");
        printf("\n\t\t\t3. Print Whole calendar");
        printf("\n\t\t\t4. Add Note");
        printf("\n\t\t\t5. Exit");
        printf("\n\t\t\tEnter your choice: ");
        scanf("\n%d", &choice);
        system("cls");
        switch(choice)
        {
            case 1:
                SetColor(10);
                today();
                ClearColor();
                printf("\n\t\t\tFind the day\n\t\t\tEnter date (DD MM YYYY) : ");
                scanf("%d %d %d",&dd,&mm,&yy);
                printf("\n\t\t\tDay is : %s",getDay(dd,mm,yy));
                printf("\n\n\t\t\tPress m For Main Menu");
                getch();
                system("cls");
                break;
            case 2 :
                SetColor(10);
                today();
                ClearColor();
                printf("\n\n\t\t\tEnter month and year (MM YYYY) : ");
                scanf("%d %d",&mm,&yy);
                system("cls");
                while(1)
                {
                    print_date(mm,yy);
                    printMonth(mm,yy,40,10);
                    SetColor(15);
                    printf("\n\n\tPress 'n'  For Next, Press 'p' For Previous, Press 'm' For Main Menu and Press 's' For Note:");
                    ClearColor();
                    ch = getch();
                    if(ch == 'n')
                    {
                        increase_month(&mm,&yy);
                        system("cls");
                        print_date(mm,yy);
                        printMonth(mm,yy,40,10);
                    }
                    else if(ch == 'p')
                    {
                        decrease_month(&mm,&yy);
                        system("cls");
                        print_date(mm,yy);
                        printMonth(mm,yy,40,10);

                    }

                    else if(ch == 'm')
                    {
                       goto Menu;
                    }
                    else if(ch == 's')
                    {
                        showNote(mm);
                        system("cls");
                    }
                }
                getch();
                break;
            case 3:
                SetColor(10);
                today();
                ClearColor();
                SetColor(15);
                printf("\n\t\t\t\t\t\tEnter Year: ");
                ClearColor();
                scanf("%d",&yy);
                while(1)
                {

                    wholeCal(yy);
                    SetColor(15);
                    printf("\n\n\tPress 'n'  For Next, Press 'p' For Previous, Press 'm' For Main Menu");
                    ClearColor();
                    ch = getch();

                    if(ch == 'n')
                    {
                        ++yy;
                        system("cls");
                        SetColor(10);
                        today();
                        ClearColor();
                        printf("\n\t\t\t\t\t\tEnter Year: %d",yy);
                        wholeCal(yy);
                    }
                    else if(ch == 'p')
                    {
                        --yy;
                        system("cls");
                        SetColor(10);
                        today();
                        ClearColor();
                        printf("\n\t\t\t\t\t\tEnter Year: %d",yy);
                        wholeCal(yy);

                    }
                    else if(ch == 'm')
                    {
                       goto Menu;
                    }
                }

                break;
            case 4:
                gotoxy(40,2);
                addNote();
                system("cls");
                break;
            case 5:
                gotoxy(40,2);
                printf("Bye, Have a good Day\n");
                exit(0);
                break;

        }
   }
    return 0;
}
