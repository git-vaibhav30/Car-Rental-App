#include<stdio.h>
#include"conio2.h"
#include<string.h>
#include"car.h"
#include<time.h>

void addAdmin()
{
 FILE*fp=fopen("Admin.bin","r");
 if(fp==NULL)
 {
  fp=fopen("Admin.bin","wb");
  User u[2]= {{"Admin","test","Ravi"},{"super", "demo", "Anil"}};
  fwrite(u,sizeof(u),1,fp);

 }
 fclose(fp);

}
User*getInput()
{
 int i;
 clrscr();
 textcolor(YELLOW);
 gotoxy(32,1);
 printf("CAR RENTAL SYSTEM\n");
 for(i=1;i<=80;i++)
    printf("%c",247);

    gotoxy(32,5);
 printf("LOGIN PANEL\n");
 gotoxy(1,7);
 textcolor(LIGHTCYAN);
 for(i=1;i<=80;i++)
    printf("%c",247);

    gotoxy(1,15);
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(16,8);
    textcolor(WHITE);
    printf("Press 0 to exit");
    textcolor(LIGHTCYAN);
    gotoxy(25,10);
    printf("Enter userid:");
    textcolor(WHITE);
    static User u;
    fflush(stdin);
    fgets(u.userid,20,stdin);
    char *pos;
    pos=strchr(u.userid,'\n');
    if(pos!=NULL)
    {
       *pos='\0';
    }
    if(strcmp(u.userid,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(30,17);
        printf("Login Cancelled");
        getch();
        textcolor(YELLOW);
        return NULL;

    }
    textcolor(LIGHTCYAN);
    gotoxy(25,11);
    printf("Enter password:");
    fflush(stdin);
    i=0;
    textcolor(WHITE);
    for(;;)
    {
        u.pwd[i]=getch();
        if(u.pwd[i]==13)
        {
            break;
        }
        printf("*");
        i++;
    }
    u.pwd[i]='\0';
     if(strcmp(u.pwd,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(30,17);
        printf("Login Cancelled");
        getch();
        textcolor(YELLOW);
        return NULL;

    }
    getch();
    return &u;
}
int checkUserExist(User u,char*usertype)
{
    if(strlen(u.userid)==0||strlen(u.pwd)==0)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Both fields are mandatory. Try again");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t\t");
        return 0;
    }
    FILE*fp;
    if(strcmp(usertype,"admin")==0)
    {
     fp=fopen("admin.bin","rb");
    }
    else
    {
       fp=fopen("emp.bin","rb");
    }
    if(fp==NULL)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Sorry! Cannot open the file");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t\t");
        return -1;
    }
    int found=0;
    User user;
    while(fread(&user,sizeof(user),1,fp)==1)
    {
        if(strcmp(u.userid,user.userid)==0&&strcmp(u.pwd,user.pwd)==0)
        {
            found=1;
            break;
        }
    }
    if(found==0)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Invalid userid/Password. Try again");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t\t");
    }
    else
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Login successfull");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t\t");
    }
    fclose(fp);
    return found;
}
int adminMenu()
{
    int i,choice;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("ADMIN MENU\n");
    for(i=1;i<=80;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1. Add Employee");
     gotoxy(32,9);
    printf("2. Add Car Details");
     gotoxy(32,10);
    printf("3. Show Employee");
     gotoxy(32,11);
    printf("4. Show Car Details");
     gotoxy(32,12);
    printf("5. Delete Employee");
     gotoxy(32,13);
    printf("6. Delete Car Details");
     gotoxy(32,14);
     printf("7. Exit");
      gotoxy(32,16);
      printf("Enter choice:");
      scanf("%d",&choice);
      return choice;

}
void addEmployee()
{
  char empid[10]={"EMP-"};
  char temp[10];
  char choice;
  User u;
  FILE*fp=fopen("emp.bin","ab+");
  fseek(fp,0,SEEK_END);
  long total_rec=ftell(fp)/sizeof(User);


  total_rec++;
  sprintf(temp,"%d",total_rec);
  strcat(empid,temp);
  strcpy(u.userid,empid);
  do
  {
      clrscr();
      gotoxy(32,2);
  textcolor(LIGHTRED);
  printf("CAR RENTAL APP");
  textcolor(LIGHTGREEN);
  int i;
  gotoxy(1,3);
  for(i=1;i<=80;i++)
  printf("~");
  textcolor(WHITE);
  gotoxy(25,5);
  printf("*****ADD EMPLOYEE DETAILS*****");
  gotoxy(1,8);
  textcolor(YELLOW);
  printf("Enter Employee Name:");
  fflush(stdin);
  textcolor(WHITE);
  fgets(u.name,20,stdin);
  char*pos;
  pos=strchr(u.name,'\n');
  if(pos!=NULL)
  {
      *pos='\n';
  }
  textcolor(YELLOW);
  printf("Enter Employee Pwd:");
  fflush(stdin);
  textcolor(WHITE);
  fgets(u.pwd,20,stdin);
  pos=strchr(u.pwd,'\n');
  if(pos!=NULL)
  {
      *pos='\0';
  }
  fwrite(&u,sizeof(u),1,fp);
  gotoxy(30,15);
  textcolor(LIGHTGREEN);
  printf("EMPLOYEE ADDEDS SUCCESSFULLY");
  printf("\nEMPLOYEE ID IS: %s",u.userid);
  getch();
  gotoxy(1,20);
  textcolor(LIGHTRED);
  printf("Do you want to add more employee(Y/N)?");
  textcolor(WHITE);
  fflush(stdin);
  scanf("%c",&choice);
  if(choice=='N')
    break;
  total_rec++;
  sprintf(u.userid,"EMP-%d",total_rec);
  }while(1);
  fclose(fp);


}
void viewEmployee()
{
    FILE*fp=fopen("emp.bin","rb");
    User usr;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(31,5);
    printf("EMPLOYEE DETAILS");
    gotoxy(8,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    if(fp==NULL)
    {
        gotoxy(31,9);
        textcolor(LIGHTRED);
        printf("Sorry! No employee added yet");
        getch();
        return;
    }
    gotoxy(1,8);
    printf(" Employee ID\t\t\tName\t\t\tPassword");
    gotoxy(1,9);
        for(i=1;i<=80;i++)
        printf("%c",247);
        int row=10;
        textcolor(YELLOW);
        while(fread(&usr,sizeof(usr),1,fp)==1)
        {
         gotoxy(2,row);
         printf("%s",usr.userid);
         gotoxy(33,row);
         printf("%s",usr.name);
         gotoxy(57,row);
         printf("%s",usr.pwd);
         row++;

        }
        fclose(fp);
        getch();
}
int deleteEmp()
{
    FILE*fp1=fopen("emp.bin","rb");
    char empid[10];
    int i,result;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=80;i++)
    {
        printf("%c",247);
    }
    gotoxy(29,5);
    printf("DELETE EMPLOYEE RECORD");
    gotoxy(1,12);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
    {
        printf("%c",247);
    }
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        gotoxy(32,10);
        printf("No employee added yet!");
        return 1;
    }
    FILE*fp2=fopen("temp.bin","wb");
     if(fp2==NULL)
    {
        textcolor(LIGHTRED);
        gotoxy(32,10);
        printf("Sorry!Cannot create temp file");
        return -1;
    }
    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter employee id to delete the record");
    textcolor(WHITE);
    scanf("%s",empid);
    User u;
    int found=0;
    while(fread(&u,sizeof(u),1,fp1)!=0)
    {
        if(strcmp(u.userid,empid)!=0)
            fwrite(&u,sizeof(u),1,fp2);
        else
            found=1;
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
     remove("temp.bin");
    }
    else
    {
        result=remove("emp.bin");
        if(result!=1)
            return 2;
        result=rename("temp.bin","emp.bin");
        if(result!=0)
            return 2;
    }
    return found;
}
int empMenu()
{
    int choice,i;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i=0;i<=80;i++);
    printf("*");
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1. Rent A Car");
    gotoxy(32,9);
    printf("2. Booking Details");
    gotoxy(32,10);
    printf("3. Available Car Details");
    gotoxy(32,11);
    printf("4. Show All Car Details");
    gotoxy(32,12);
    printf("5. Exit");
    gotoxy(32,15);
    printf("Enter choicr");
    scanf("%d",&choice);
    return choice;
}
int selectCarModel()
{
FILE*fp=fopen("car.bin","rb");
int flag;
int choice,rowno=9;
Car C;
gotoxy(34,rowno);
int carcount=0;
while(fread(&C,sizeof(C),1,fp)==1)
{
    if(C.car_count>0)
    {
        printf("%d. %s",C.car_count,car_name);
        gotoxy(34,++rowno);
        ++carcount;
    }
}
if(carcount==0)
{
    fclose(fp);
    return -2;
}
gotoxy(34,rowno+2);
printf("Enter your choice(0 to quit):");
while(1)
{
    flag=0;
    scanf("%d",&choice);
    if(choice==0)
    {
    fclose(fp);
    return 0;
    }
    rewind(fp);
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_id==choice&&C.car_count>0)
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        fclose(fp);
        return flag;
    }
    gotoxy(37,rowno+4);
    textcolor(LIGHTRED);
    printf("Wrong Input");
    getch();
    gotoxy(35,rowno+4);
    printf("\t\t\t");
    gotoxy(52,rowno+2);
    printf("\t\t\t");
    gotoxt(52,rowno+2);
    textcolor(WHITE);
}
}
int isValidDate(struct tm dt)
{
    if(dt.tm_year>=2021&&dt.tm_year<=2022)
    {
      if(dt.tm_mon>=1&&dt.tm_mon<=12)
      {
          if((dt.tm_mday>=1&&dt.tm_mday<=31)&&(dt.tm_mon==1||dt.tm_mon==3||dt.tm_mon==5||dt.tm_mon==7||dt.tm_mon==8||dt.tm_mon==10||dt.tm_mon==12))
            return 1;
          else if((dt.tm_mday>=1&&dt.tm_mday<=30)&&(dt.tm_mon==4||dt.tm_mon==6||dt.tm_mon==9||dt.tm_mon==11))
            return 1;
          else if((dt.tm_mday>=1&&dt.tm_mday<=28)&&dt.tm_mon==2)
            return 1;
          else if((dt.tm_mday>=1&&dt.tm_mday<=229)&&dt.tm_mon==2&&(dt.tm_year%400==0||(dt.tm_year%4==0&&dt.tm_year%100!=0)))
          return 1;
      }

    }
    return 0;
}
void updateCarCount(int c)
{
    FILE*fp=fopen("car.bin","rb+");
    if(fp==NULL)
    {
        printf("Sorry! File cannot be open!");
        getch();
        return;
    }
    Car C;
    while(fread(&C,sizeof(Car),1,fp)==1)
    {
        if(C.car_id==c_id)
        {
          int x=C.car_count;
          x--;
          fseek(fp,-8,SEEK_CUR);
          fwrite(&x,sizeof(int),1,fp);
          break;
        }
    }
    fclose(fp);
}
void bookedCarDetails()
{
    clrscr();
    FILE*fp=fopen("customer.bin","rb");
    Customer_Car_Details CC;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM");
    for(i=1;i<=80;i++);
    printf("%c",247);
    gotoxy(31,5);
    printf("*BOOKED CAR DETAILS*");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++);
    printf("%c",247);
    gotoxy(1,8);
    printf("Model\t    Cust Name\t   Pick Up\t   Drop\t\t  S_Date\t   E_Date");
    gotoxy(1,9);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++);
    printf("%c",247);
    int row;
    textcolor(YELLOW);
    while(fread(&CC,sizeof(Customer_Car_Details),1,fp)==1)
    {
        gotoxy(1,row);
        printf("%s",getCarName(CC.car_id));

        gotoxy(13,row);
        printf("%s",CC.cust_name);

        gotoxy(27,row);
        printf("%s",CC.pickup);

        gotoxy(44,row);
        printf("%s",CC.drop);

        gotoxy(58,row);
        printf("%d-%d-%d",CC.sd.tm_mday,CC.sd.tm_mon,CC.sd.tm_year);

        gotoxy(70,row);
        printf("%d-%d-%d",CC.ed.tm_mday,CC.ed.tm_mon,CC.ed.tm_year);

        row++;
    }
    fclose(fp);
    getch();
}
char* getCarName(int c_id)
{
    FILE*fp=fopen("car.bin","rb");
    if(fp==NULL)
    {
        printf("Sorry! File cannot be created");
        return NULL;
    }
    static Car C;
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_id==c_id)
        {
            break;
        }
    }
    fclose(fp);
    return C.car_name;
}
int rentCar()
{
    Customer_Car_Details CC;
    int c,i;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i=0;i<=80;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(32,8);
    c=selectCarModel();
    if(c==0||c==-2)
        return c;
    CC.car_id=c;
    clrscr();

    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i=0;i<=80;i++)
        printf("*");
    gotoxy(1,17);
    for(i=0;i<=80;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(27,9);
    printf("Enter Customer Name");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.cust_name,30,stdin);
    char *pos;
    pos=strchr(CC.cust_name,'\n');
    *pos='\0';
    textcolor(YELLOW);
    gotoxy(27,10);
    printf("Enter pickup point:");
    textcolor(WHITE);
    fflush(stdin);
    fgets(CC.pickup,30,stdin);
    pos=strchr(CC.pickup,'\n');
    *pos='\0';
    textcolor(YELLOW);
    gotoxy(27,11);
    printf("Enter drop point:");
    textcolor(WHITE);
    fflush(stdin);
    fgets(CC.drop,30,stdin);
    pos=strchr(CC.drop,'\n');
    *pos='\0';
    gotoxy(27,12);
    textcolor(YELLOW);
    printf("Enter start date(dd/mm/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d %d %d",&CC.sd.tm_mday,&CC.sd.tm_mon,&CC.sd.tm_year);
        int datevalid=isValidDate;(CC.sd);
        if(datevalid==1)
            break;
        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("Wrong Date!");
        getch();
        gotoxy(27,18);
        printf("\t\t\t");
        gotoxy(56,12);
        printf("\t\t\t");
        gotoxy(56,12);
        textcolor(WHITE);
    }while(1)
    gotoxy(27,12);
    textcolor(YELLOW);
    printf("Enter end date(dd/mm/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d %d %d",&CC.ed.tm_mday,&CC.ed.tm_mon,&CC.ed.tm_year);
        int datevalid=isValidDate;(CC.ed);
        if(datevalid==1)
            break;
        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("Wrong Date!");
        getch();
        gotoxy(27,18);
        printf("\t\t\t");
        gotoxy(54,13);
        printf("\t\t\t");
        gotoxy(54,13);
        textcolor(WHITE);
    }while(1);
    //Now validate the dates against current date as well as against each other.  complete yourself
    FILE*fp;
    fp=fopen("customer.bin","ab");
    if(fp==NULL)
    {
        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened")
        return -1;
    }
    fwrite(&CC,sizeof(Customer_Car_Car_Details),1,fp);
    gotoxy(27,18);
    textcolor(WHITE);
    printf("Booking done for car %d",CC.car_id);
    printf("\nPress any key to continue");
    getch();
    fclose(fp);
    updateCarCount();
    bookedCarDetails();
    return 1;

}
void availCarDetails()
{
    FILE*fp=fopen("car.bin","rb");
    Car C;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(32,5);
    textcolor(YELLOW);
    printf("AVAILABLE CAR DETAILS");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    if(fp==NULL)
    {
        gotoxy(32,8);
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be created");
        getch();
        return;
    }
    gotoxy(1,8);
    printf("Car ID\t   Model\t\t   Capacity\tAvailable\tPrice/Day");
    gotoxy(1,9);
    for(i=1;i<=80;i++)
        printf("%c",247);
    int row=10;
    textcolor(YELLOW);
    while(fread(&C,sizeof(C),1,fp)==1)
    {
      if(C.car_count>0)
      {
          gotoxy(2,row);
          printf("%d",C.car_id);
          gotoxy(13,row);
          printf("%s",C.car_name);
          gotoxy(35,row);
          printf("%d",C.capacity);
          gotoxy(50,row);
          printf("%d",C.car_count);
          gotoxy(68,row);
          printf("%d",C.price);
          row++;
      }
    }
    fclose(fp);
}
void showCarDetails()
{
    FILE*fp=fopen("car.bin","rb");
    Car C;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(32,5);
    textcolor(YELLOW);
    printf("ALL CAR DETAILS");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    if(fp==NULL)
    {
        gotoxy(32,8);
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be created");
        getch();
        return;
    }
    gotoxy(1,8);
    printf("Car ID\t   Model\t\t   Capacity\tAvailable\tPrice/Day");
    gotoxy(1,9);
    for(i=1;i<=80;i++)
        printf("%c",247);
    int row=10;
    textcolor(YELLOW);
    while(fread(&C,sizeof(C),1,fp)==1)
    {

    }
    fclose(fp);
}
