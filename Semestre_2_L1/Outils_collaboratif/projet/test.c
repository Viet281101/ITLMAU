#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
 
 
//          CAC BIEN TOAN CUC
 
const int size=13,n=2*size+1;       //THAY DOI size DE DUOC KICH THUOC MOI
const hpos=(80-n)/2-10,     vpos=10;
int top=vpos,bottom=vpos+n-1;
int left=hpos,right=hpos+n-1;
struct STEP
{
    int x,y;
};
 
 
void board();                 //        VE KHUNG
void setMouse();                    //      KHOI DONG MOUSE
void showMouse();               //    HIEN MOUSE
void hideMouse();                   //      AN MOUSE
int  clickMouse(int*,int*); //      NHAN MOUSE
void control();               //        HAM DIEU KHIEN CHINH
void reset(int [20][20],int);   //      KHOI TAO MA TRAN KIEM TRA
int  check(int [20][20],int,int,int);   //  KIEM TRA THANG THUA
void pos(int&,int&);                //  DOI TOA DO THUC SANG TOA DO MA TRAN
void whereXY(int&,int&);        //      LAY TOA DO (X,Y)
void option();                //        MENU TUY CHON LUC CHOI
void time();                       //       HAM LAY THOI GIAN
void menu();                  //        MENU TUY CHON LUC BAT DAU CHOI
void intro();                       //  GIOI THIEU VE LUAT CHOI
 
 
 
 
//              CHUONG TRINH CHINH
//              (CAC HAM O BEN DUOI)
void main()
{
    clrscr();
    textcolor(11);
    setMouse();
    menu();
    control();
    hideMouse();
    setMouse();
}
 
void control()      //  HAM DIEU KHIEN CHINH CUA CHUONG TRINH
{
//do{
    start:
    int x,y,t,color,a[20][20],x1,y1,f,j=-1;
    char c,ch,c1;
    struct STEP step[(size+1)*(size+1)];
 
    textbackground(0);
    window(1,1,80,50);
    showMouse();
    reset(a,size+3);    //  SIZE OF MANG KT = SIZE + 1 + 2
    gotoxy(hpos,vpos);
    gotoxy(60,26);
    textcolor(YELLOW+128);
    cprintf("X di truoc");
    while (1)
    {
 
        if (j==-1) f=0;
        showMouse();
        t=clickMouse(&x,&y);
        x1=x;   y1=y;
        pos(x1,y1);
        x1++;   y1++;
 
                            /*  SU KIEN MOUSE */
        if(t!=0&&x%2==0&&y%2==0&&y>=top&&y<=bottom&&x>=left&&x<=right&&a[x1][y1]==2)
        {
            j++;
            step[j].x=x;    step[j].y=y;a[x1][y1]=1;
 
        /******* GHI GIA TRI VAO MANG KIEM TRA (QUI UOC: X:1,O:0) ******/
 
            hideMouse();
            gotoxy(x,y);
            textcolor(YELLOW);
            cprintf("X");
            gotoxy(1,42);
            cprintf("Khung    : %2d:%2d",x1,y1);
            gotoxy(1,40);
            cprintf("Man hinh : %2d:%2d",x,y);
            gotoxy(1,44);
            textcolor(11);
            cprintf("So nuoc di: %d",j+1);
            textcolor(LIGHTGREEN+128);
            gotoxy(60,26);
            cprintf("Toi luot O");
            textcolor(11);
            gotoxy(52,28);
            cprintf("( BAN PHIM dieu khien )");
            showMouse();
 
            if (check(a,1,x1,y1)==1)
            {
                c='X';
                break;
            }
            f=1;
            gotoxy(x,y);
        }
 
        if (f==1)                   //  SU KIEN BAN PHIM
        {
         kb:
          {
            hideMouse();
            do{
                whereXY(x,y);
                ch=getch();
                switch (ch)
 
                    /*****  CAC BUOC DI CHUYEN CUA BAN PHIM  *****/
 
                {
                    case 77:    gotoxy(x+2,y);  break;  /* CAC HUONG DI CHUYEN */
                    case 75: gotoxy(x-2,y); break;
                    case 72:    gotoxy(x,y-2);  break;
                    case 80: gotoxy(x,y+2); break;
                    case 8 :    goto back;                  /* BACKSPACE : LUI 1 NUOC */
                    case 9 :    if (j>1)
                                    goto back2;             /* TAB : LUI 2 NUOC */
                                break;
                    case 27:    {
                                    showMouse();         /* ESC  :  THOAT     */
                                    goto exit;
                                }
                }
 
            }
while(ch!=13);
 
            whereXY(x,y);
            x1=x;   y1=y;
            pos(x1,y1);
            x1++;   y1++;
          }
        if(a[x1][y1]==2&&x>=left&&x<=right&&y>=top&&y<=bottom)
 
            /*****  CHI DANH KHI O CHUA CO GI VA O TRONG KHUNG  *****/
 
            {
                j++;
                step[j].x=x;    step[j].y=y;
 
                a[x1][y1]=0;
                textcolor(LIGHTGREEN);
                cprintf("O");
                gotoxy(1,42);
                cprintf("Khung    : %2d:%2d",x1,y1);
                gotoxy(1,40);
                cprintf("Man hinh : %2d:%2d",x,y);
                gotoxy(1,44);
                textcolor(11);
                cprintf("So nuoc di: %d",j+1);
                gotoxy(60,26);
                textcolor(YELLOW+128);
                cprintf("Toi luot X");
                textcolor(11);
                gotoxy(52,28);
                cprintf("(  MOUSE dieu khien   )");
                if (check(a,0,x1,y1)==0)
                {
                    c='O';
                    showMouse();
                    break;
                }
                f=0;
                gotoxy(x,y);
            }   else goto kb;       //  QUAY LAI kb
        }
 
        if (t==1&&x>=60&&x<=70)
            if (y==20)      //  CLICK MOUSE VAO VI TRI THOAT
                goto exit;
            else if (y==16)
                goto Continue;
            else if (y==18)
            {
                hideMouse();
                menu();
            }
            else if (y==14&&j>=0)   goto back2;
            else if (y==12&&j>=0)
            {
                goto back;
 
        /*******************    LUI LAI 2 NUOC DI **********************/
 
             back2:
                x1=x=step[j].x; y1=y=step[j].y;
                pos(x1,y1);
                x1++;   y1++;
                a[x1][y1]=2;
                gotoxy(step[j].x,step[j].y);
                if (x1>1&&x1<size+1&&y1>1&&y1<size+1)   c1='Å';
                if (x1==1&&y1>1&&y1<size+1)             c1='Ã';
                if (x1==size+1&&y1>1&&y1<size+1)            c1='´';
                if  (x1>1&&x1<size+1&&y1==1)                c1='Â';
                if (x1>1&&x1<size+1&&y1==size+1)            c1='Á';
                if (x1==1&&y1==1)                               c1='Ú';
                if (x1==1&&y1==size+1)                      c1='À';
                if (x1==size+1&&y1==1)                      c1='¿';
                if (x1==size+1&&y1==size+1)             c1='Ù';
                cprintf("%c",c1);
                j--;
                gotoxy(1,44);
                textcolor(11);
                cprintf("So nuoc di: %d",j);
                f=1-f;
                gotoxy(x,y);
 
        /*******************    LUI LAI 1 NUOC DI**********************/
 
             back:
                x1=x=step[j].x; y1=y=step[j].y;
                pos(x1,y1);
                x1++;   y1++;
                a[x1][y1]=2;
                gotoxy(step[j].x,step[j].y);
                if (x1>1&&x1<size+1&&y1>1&&y1<size+1)   c1='Å';
                if (x1==1&&y1>1&&y1<size+1)             c1='Ã';
                if (x1==size+1&&y1>1&&y1<size+1)            c1='´';
                if  (x1>1&&x1<size+1&&y1==1)                c1='Â';
                if (x1>1&&x1<size+1&&y1==size+1)            c1='Á';
                if (x1==1&&y1==1)                               c1='Ú';
                if (x1==1&&y1==size+1)                      c1='À';
                if (x1==size+1&&y1==1)                      c1='¿';
                if (x1==size+1&&y1==size+1)             c1='Ù';
                cprintf("%c",c1);
                j--;
                gotoxy(1,44);
                textcolor(11);
                cprintf("So nuoc di: %d",j+1);
                f=1-f;
                gotoxy(x,y);
 
            }
 
    }
 
 
    if (c=='X'||c=='O')
    {
        gotoxy(1,40);
        textcolor(YELLOW+BLINK);
        cprintf("Co %c da gianh chien thang",c);
        gotoxy(50,48);
        cprintf("An phim bat ki de tiep tuc");
 
    }
    else
    {
        gotoxy(1,40);
        textcolor(YELLOW+BLINK);
        cprintf("Ket thuc");
    }
    getch();
 
    Continue:
    hideMouse();
    //clrscr();
    textbackground(15);
    textcolor(0);
    window(20,18,40,28);
    clrscr();
    textcolor(BLACK);
    cprintf("\n Moi ban chon : ...");
    textbackground(BLUE);
    window(25,21,35,23);
    clrscr();
    textcolor(WHITE);
    cprintf("\n  TIEP TUC");
    textbackground(BLUE);
    window(25,25,35,27);
    clrscr();
    textcolor(WHITE);
    cprintf("\n   THOAT");  textcolor(GREEN);
    showMouse();
    while (1)
    {
        t=clickMouse(&x,&y);
        if (t==1&&x>=25&&x<=35)
        {
            if  ((y>=21)&&(y<=23))
            {       clrscr();
                textbackground(BLACK);
                window(25,21,35,23);
                clrscr();
                textcolor(WHITE);
                cprintf("\n  TIEP TUC");
                delay(120);
                hideMouse();
                textbackground(0);
                window(1,1,80,50);
                clrscr();
                board();
                option();
                goto start;
            }
            else if ((y>=25)&&(y<=27))
            {
                clrscr();
                textbackground(BLACK);
                window(25,25,35,27);
                clrscr();
                textcolor(WHITE);
                cprintf("\n   THOAT");
                delay(120);
                hideMouse();
                exit(0);
            }
        }
    }
 
    exit:
    hideMouse();
    //clrscr();
    textbackground(15);
    window(30,10,50,16);
    clrscr();
    textcolor(BLUE);
    cprintf("\n Thoat khoi TRO CHOI");
    textbackground(BLUE);
    window(35,13,45,13);
    clrscr();
    textcolor(WHITE);
    cprintf("  DONG Y");
    textbackground(BLUE);
    window(35,15,45,15);
    clrscr();
    textcolor(WHITE);
    cprintf("  HUY BO");
    showMouse();
    while (1)
    {
        t=clickMouse(&x,&y);
        if (t==1&&x>=35&&x<=45)
            if  (y==15)
            {
                hideMouse();
                textbackground(0);
                window(1,1,80,50);
                clrscr();
                board();
                option();
                goto start;
            }
            else if (y==13)
            {
                hideMouse();
                exit(0);
            }
    }
 
 
//}while(getch()!=27);
 
 
 
}
 
 
//              VE KHUNG
 
void board()
{
 
    int i,j;
 
    /* CAC KY TU DAC BIET :
 
                197 :Å ; 196 :Ä ; 195 :Ã
 
                194 :Â ; 192 :À ; 191 :¿
 
                180 :´ ; 218 :Ú ; 217 :Ù
 
                193 :Á ; 179 :³   */
 
 
    textcolor(11);
    //              GIOI THIEU VE LUAT CHOI
 
    gotoxy(8,1);
    cprintf("*** DE TAI 5 : CHUONG TRINH DANH CARO GIUA NGUOI VA NGUOI ***");
    gotoxy(23,3);
    cprintf("<--- LOP 051102 - KHOA CNTT --->");
    gotoxy(33,5);
    cprintf("*** (^_^) ***");
    gotoxy(9,7);
    cprintf("--- Nho danh vao giao diem cua cac duong nha _THANK YOU_ ---");
 
 
            /*****          VE KHUNG                *****/
 
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
        {
            gotoxy(hpos+j,vpos+i);
            if (i==0&&j==0)     cprintf("Ú");
            if (i==0&&j==n-1)   cprintf("¿");
            if (i==n-1&&j==0)       cprintf("À");
            if (i==n-1&&j==n-1)     cprintf("Ù");
            if (i%2==0&&j%2!=0) cprintf("Ä");
            if (i%2!=0&&j%2==0) cprintf("³");
            if (i==n-1&&j%2==0&&j>0&&j<n-1)     cprintf("Á");
            if (i%2==0&&j==n-1&&i>0&&i<n-1)     cprintf("´");
            if (i==0&&j%2==0&&j<n-1&&j>0)       cprintf("Â");
            if (i%2==0&&j==0&&i>0&&i<n-1)       cprintf("Ã");
            if (i>0&&i<n-1&&i%2==0&j>0&&j<n-1&&j%2==0) cprintf("Å");
        }
 
            /*****        TEXT CHAY QUANG CAO           *****/
 
    char str[]={'C','h','a','o',' ','m','u','n','g',' ','c','a','c',' ','b','a','n',
                     ' ','d','e','n',' ','v','o','i',' ','t','r','o',' ','c','h','o','i',' ',
                     'C','A','R','O',NULL};
 
 
    delay(250);
    i=0;
    while (str[i]!=NULL)
    {
    delay(20);
    gotoxy(1+i,50);
    cprintf("%c",str[i]);
    i++;
    }
 
}
 
void option()
{
    textbackground(WHITE);
    window(58,10,72,22);
    clrscr();
 
    textbackground(GREEN);
    window(60,12,70,12);
    clrscr();
    textcolor(12);
    cprintf("LUI 1 NUOC");
 
    textbackground(GREEN);
    window(60,14,70,14);
    clrscr();
    textcolor(12);
    cprintf("LUI 2 NUOC");
 
    textbackground(GREEN);
    window(60,16,70,16);
    clrscr();
    textcolor(12);
    cprintf("  VAN MOI");
 
    textbackground(GREEN);
    window(60,18,70,18);
    clrscr();
    textcolor(12);
    cprintf("    MENU");
 
    textbackground(GREEN);
    window(60,20,70,20);
    clrscr();
    textcolor(12);
    cprintf("   THOAT");
 
    textbackground(WHITE);
    window(50,30,76,45);
    clrscr();
    textcolor(BLUE);
    gotoxy(6,2);
    cprintf("*** BAN PHIM ***");
    gotoxy(2,4);
    cprintf("- BACKSPACE : LUI 1 NUOC");
    gotoxy(2,6);
    cprintf("- TAB       : LUI 2 NUOC");
    gotoxy(2,8);
    cprintf("- ESC       : THOAT");
    textcolor(BLUE+128);
    gotoxy(2,10);
    cprintf("* DUNG AN PHIM HAY NHAP *");
    gotoxy(2,11);
    cprintf("*   CHUOT KHI CHUA TOI  *");
    gotoxy(2,12);
    cprintf("*    LUOT DIEU KHIEN    *");
    gotoxy(2,14);
    cprintf("- dac biet la ENTER va  -");
    gotoxy(2,15);
    cprintf("- cac nut o tren        -");
    delay(1500);
    textcolor(BLUE);
    gotoxy(2,10);
    cprintf("* DUNG AN PHIM HAY NHAP *");
    gotoxy(2,11);
    cprintf("*   CHUOT KHI CHUA TOI  *");
    gotoxy(2,12);
    cprintf("*    LUOT DIEU KHIEN    *");
    gotoxy(2,14);
    cprintf("- dac biet la ENTER va  -");
    gotoxy(2,15);
   cprintf("- cac nut o tren        -");
 
 
    textbackground(0);
    window(1,1,80,50);
}
 
void time()
{
 
    struct time t;
 
    textbackground(0);
    window(55,18,75,18);
    clrscr();
    textcolor(11);
    gettime(&t);
    clrscr();
    textcolor(11);
    textbackground(0);
    window(1,1,80,50);
}
 
            /*****      MENU TUY CHON CHINH       *****/
 
void menu()
{
    menu:
    int i,x,y,t;
    char s[50];
    textbackground(0);
    window(1,1,80,50);
    clrscr();
    textbackground(15);
    printf("\n                   _______     ________     ________     ________\n");
    printf("                  / _____/\\   / ____  /\\   / ____  /\\   / ____  /\\\n");
    printf("                 / /\\____\\/  / /\\__/ / /  / /___/ / /  / /\\__/ / /\n");
    printf("                / / /       / /_/_/ / /  / _   __/ /  / / / / / /\n");
    printf("               / /_/__     / ____  / /  / / \\ \\__\\/  / /_/_/ / /\n");
    printf("              /______/\\   /_/\\__/_/ /  /_/ / \\_\\    /_______/ /\n");
    printf("              \\______\\/   \\_\\/  \\_\\/   \\_\\/   \\_\\   \\_______\\/\n");
    window(20,15,60,32);
    clrscr();
    sprintf(s,"\n Chao mung cac ban den voi tro choi CARO");
    textcolor(BLUE);
    delay(300);
    i=0;
    while (s[i]!=NULL)
    {
        delay(22);
        gotoxy(1+i,50);
        cprintf("%c",s[i]);
        i++;
    }
    textbackground(9);
    window(30,20,50,22);
    clrscr();
    textcolor(12);
    cprintf("\n    Bat dau choi");
    textbackground(9);
    window(30,24,50,26);
    clrscr();
    textcolor(12);
    cprintf("\n    Xem luat choi");
    textbackground(9);
    window(30,28,50,30);
    clrscr();
    textcolor(12);
    cprintf("\n        Thoat");
    showMouse();
    while (1)
    {
        t=clickMouse(&x,&y);
        if (t==1&&x>=30&&x<=50)
            if  ((y>=20)&&(y<=22))
            {
                clrscr();
                textbackground(BLACK);
                window(30,20,50,22);
                clrscr();
                textcolor(WHITE);
                cprintf("\n    Bat dau choi");
                delay(120);
                hideMouse();
                textbackground(0);
                window(1,1,80,50);
                clrscr();
                board();
                option();
                gotoxy(hpos,vpos);
                textcolor(11);
                break;  //  goto start;
            }
            else if ((y>=28)&&(y<=30))
            {
                clrscr();
                textbackground(BLACK);
                window(30,28,50,30);
                clrscr();
                textcolor(WHITE);
                cprintf("\n        Thoat");
                delay(120);
                hideMouse();
                exit(0);
            }
            else if ((y>=24)&&(y<=26))
            {
                clrscr();
                textbackground(BLACK);
                window(30,24,50,26);
                clrscr();
                textcolor(WHITE);
                cprintf("\n    Xem luat choi");
                delay(120);
                hideMouse();
                textbackground(0);
                window(1,1,80,50);
                clrscr();
                intro();
                goto menu;
            }
 
        showMouse();
    }
 
}
 
            /*****      GIOI THIEU LUAT CHOI            *****/
 
void intro()
{
    int x,y,i=0,t;
    char s[50];
    textbackground(0);
    window(1,1,80,50);
    clrscr();
    textbackground(WHITE);
    window(10,10,70,22);
    clrscr();
    textcolor(BLUE);
    gotoxy(1,2);    cprintf("     ***  Luat choi co CARO (GOMOKU) rat don gian ***");
    gotoxy(1,4);    cprintf(" - Tran dau dien ra giua 2 quan co : X va O.");
    gotoxy(1,6);    cprintf(" - Ben chien thang la ben di duoc 5 quan co lien tiep theo   hang ngang, doc, hay cheo ma khong bi doi phuong chan truoc 2 dau.");
    sprintf(s,"* Danh lien tiep 6 quan co tro len khong tinh thang *");
 
    while (s[i]!=NULL)
    {
        delay(25);
        gotoxy(5+i,10);
        cprintf("%c",s[i]);
        i++;
    }
    delay(200);
    gotoxy(5,10);
    textcolor(BLUE+128);
    cprintf(s);
    textbackground(GREEN);
    window(20,21,30,21);
    clrscr();
    textcolor(RED);
    cprintf("    Choi");
    textbackground(GREEN);
    window(35,21,45,21);
    clrscr();
    textcolor(RED);
    cprintf("    Menu");
    textbackground(GREEN);
    window(50,21,60,21);
    clrscr();
    textcolor(RED);
    cprintf("   Thoat");
    showMouse();
    while (1)
    {
        t=clickMouse(&x,&y);
        if (t==1&&y==21)
            if  (x>=20&&x<=30)
            {
                hideMouse();
                textbackground(0);
                window(1,1,80,50);
                clrscr();
                board();
                option();
                control();  //  goto start;
            }
            else if (x>=35&&x<=45)
            {
                hideMouse();
                break;
            }
            else if (x>=50&&x<=60)
            {
                hideMouse();
                exit(0);
            }
 
 
        showMouse();
    }
 
 
 
 
}
 
void setMouse()                 //  KHOI DONG MOUSE
{
    union REGS reg;
    reg.x.ax=0x0000;
    int86(0x33,&reg,&reg);
}
 
void showMouse()                //  HIEN MOUSE
{
    union REGS reg;
    reg.x.ax=0x0001;
    int86(0x33,&reg,&reg);
}
 
void hideMouse()                //  AN MOUSE
{
    union REGS reg;
    reg.x.ax=0x0002;
    int86(0x33,&reg,&reg);
}
 
int clickMouse(int *x,int *y)   // NHAN MOUSE
{
    union REGS reg;
    unsigned i;
    reg.x.ax=0x05;
    reg.x.bx=0;
    int86(0x33,&reg,&reg);
    *x=reg.x.cx/8+1;
    *y=reg.x.dx/8+1;
    i=reg.x.bx&1;
    return i;
}
 
void reset(int a[20][20],int size)  //  KHOI TAO MA TRAN KIEM TRA
{
    int i,j;
    for (i=0;i<size;i++)
        for (j=0;j<size;j++)
            a[i][j]=2;
}
 
            /*****      KIEM TRA THANG THUA     *****/
 
int check(int a[20][20],int n,int x,int y)
{
    int i,j,k1=0,k2=0,k3=0,k4=0;
 
    i=j=0;
    while (a[x][y+i]==n)    i++;        //  KIEM TRA HANG DOC
    while (a[x][y-j]==n)    j++;
    if (a[x][y+i]==2 || a[x][y-j]==2)   //  5 QUAN CO BI CHAN 2 DAU KHONG AN
        k1=i+j-1;
 
 
    i=j=0;
    while (a[x+i][y]==n) i++;     //    KIEM TRA HANG NGANG
    while (a[x-j][y]==n)    j++;
    if (a[x+i][y]==2 || a[x-j][y]==2)
        k2=i+j-1;
 
 
    i=j=0;
    while (a[x+i][y+i]==n)  i++;    //  KIEM TRA DUONG "\"
    while   (a[x-j][y-j]==n)    j++;
    if (a[x+i][y+i]==2 || a[x-j][y-j]==2)
        k3=i+j-1;
 
 
    i=j=0;
    while (a[x+i][y-i]==n)  i++;    //  KIEM TRA DUONG "/"
    while   (a[x-j][y+j]==n)    j++;
    if (a[x+i][y-i]==2 || a[x-j][y+j]==2)
        k4=i+j-1;
 
 
    gotoxy(1,46);
    textcolor(11);
    cprintf("Doc:%d - Ngang%d - \"\\\"%d - \"/\"%d",k1,k2,k3,k4);
 
    if (k1==5||k2==5||k3==5||k4==5) return n;
 
    return -1;
}
 
 
void pos(int &x1,int &y1)   //DOI TOA DO THUC (X,Y) SANG TOA DO MA TRAN (X1,Y1)
{
    x1=(x1-hpos)/2;
    y1=(y1-vpos)/2;
}
 
void whereXY(int &x,int &y) //  TIM TOA DO (X,Y)
{
    x=wherex();
    y=wherey();
}