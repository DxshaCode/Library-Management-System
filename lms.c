#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
void addbook();
void viewbooklist();
void removebook();
void issuebook();
void viewissuelist();
void calculatefine();
void returnbook();
int calculatedays(char issue_date[],char return_date[]);
struct books
{
    int id;
    char book_name[20];
    char author_name[20];
    char date[20]; 
}b;
struct student
{
    int id;
    
    char student_name [20];
    char roll_number[20];
    char phone_number [20];
    char course[20];
    char book_name [20];
    char date[20];
    char return_date[20];
}s;
FILE *fp;
FILE *fi;
int main()
{   
    int choice;
    
    while(1){
        system("cls");
    printf("<~~LIBRARY MANAGEMENT SYSTEM~~>\n");
    printf("1.add book.\n");
    printf("2.view book list.\n");
    printf("3.remove book.\n");
    printf("4.issue book\n");
    printf("5.view issued book list.\n");
    printf("6.fine calculation.\n");
    printf("7.return book\n.");
    printf("0.exit\n");
    printf("<~~enter your choice~~>\n");
    scanf("%d",&choice);
    switch(choice)
    {   
        case 0:
        printf("exit.");
        break;

        case 1:
        addbook();
        break;

        case 2:
        viewbooklist();
        break;

        case 3:
        removebook();
        break;

        case 4:
        issuebook();
        break;

        case 5:
        viewissuelist();
        break;

        case 6:
        calculatefine();
        break;

        case 7:
        returnbook();
        break;

        default:
        printf("invalid choice..... \n\n");

    }
    printf("\n\n enter any key to continue........");
    getch();
}
return 0;

}
void addbook()
{
    char mydate[12];
    time_t t=time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(mydate,"%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    strcpy( b.date,mydate);


    fp=fopen("books.txt","ab");
    printf("enter book id:");
    scanf("%d",&b.id);
    printf("enter book name:");
    fflush(stdin);
    scanf("%19s",b.book_name);
    printf("enter author name:");
    fflush(stdin);
    scanf("%19s",b.author_name);
    printf("book added successfull.");
    fwrite(&b,sizeof(b),1,fp);
    fclose(fp);
}

void viewbooklist()
{
    system("cls");
    printf("<~~AVAILAIBLE BOOKS~~>\n\n");
    printf("%-10s %-30s %-20s %s \n\n","book id","book name","author name","date");
    fp=fopen("books.txt","rb");
    while(fread(&b,sizeof(b),1,fp)==1){
     printf("%-10d %-30s %20s %s \n\n",b.id,b.book_name,b.author_name,b.date);
    }
     fclose(fp);
    
}
 void removebook()
{   FILE *ft;
    system("cls");
    printf("<~~REMOVE BOOK~~>");
    int id,f=0;
    printf("\nenter the id of book:");
    scanf("%d",&id);
    fp=fopen("books.txt","rb");
    ft=fopen("temp.txt","wb");
    while(fread(&b,sizeof(b),1,fp)==1)
    {
        if(b.id==id)
        {
            f=1;
        }
        else
        fwrite(&b,sizeof(b),1,ft);
    }   
    if(f==1)
    {
        printf("\n\n book removed successfully.......");
    } 
    else 
    printf("\n\n no book found.......");
    fclose(fp);
    fclose(ft);
    remove("books.txt");
    rename("temp.txt","books.txt");
}

void issuebook()
{  

   
   char mydate[12];
    time_t t=time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(mydate,"%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    strcpy( s.date,mydate);
    int f=0;
    system("cls");
   printf("<~~ISSUE BOOK~~>\n");

   printf("enter book id:");
   scanf("%d",&s.id);
   
   fp=fopen("books.txt","rb");
   while(fread(&b,sizeof(b),1,fp)==1)
   {
    if(b.id==s.id)
    {
        strcpy(s.book_name,b.book_name);
        f=1;
        break;
    }
   }
   if(f==0)
   {
    printf("\n\nbook not found...");
    printf("\n\npls try again....");
    return;
   }
   fp=fopen("issue.txt","ab");
      
   printf("student name:");
   fflush(stdin);
   scanf("%19s",s.student_name);
   printf("enter roll number:");
   fflush(stdin);
   scanf("%19s",s.roll_number);
   printf("enter course:");
   fflush(stdin);
   scanf("%19s",s.course);
   printf("enter phone number:");
   fflush(stdin);
   scanf("%19s",s.phone_number);
   
   printf("\n\n book issued successfully.....");

   fwrite(&s,sizeof(s),1,fp);
   fclose(fp);
}

void viewissuelist()
{
    system("cls");
    printf("%-10s %-20s %-20s %-20s %-20s %-20s  %s\n\n","book id","book name","student name","roll number","course","phone number","issue date");
    fp=fopen("issue.txt","rb");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        printf("%-10d %-20s %-20s %-20s %-20s %-20s   %s\n\n",s.id,s.book_name,s.student_name,s.roll_number,s.course,s.phone_number,s.date);
    }
    fclose(fp);


}
int calculatedays(char issue_date[],char return_date[])
{
    int d1, m1, y1; //for issue date
    int d2,m2,y2; //for return date
    sscanf(issue_date," %d/ %d /%d",&d1,&m1,&y1);
    sscanf(return_date, "%d /%d/ %d",&d2,&m2,&y2);

    struct tm a={0}, b={0}; //a is for issue date and b is for return date
    a.tm_mday=d1;
    a.tm_mon=m1-1;
    a.tm_year=y1-1900;

     b.tm_mday=d2;
    b.tm_mon=m2-1;
    b.tm_year=y2-1900;

    time_t x=mktime(&a); //converts issue date to seconds
    time_t y=mktime(&b); //converts return date to seconds

    double diff =difftime(y,x)/(60*60*24); //converts diffrence in seconds to date
    return (int)diff;

}
void calculatefine()
{
    int id;
    char return_date[20];
    printf("enter book id:");
    scanf("%d",&id);
    printf("enter date of returning(dd/mm/yyyy):");
    scanf("%s",&return_date);

    int found=0;
    fp=fopen("issue.txt","rb");
    
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        if(s.id==id)
        {
            found=1;
            int days=calculatedays(s.date,return_date);
            int free_days=7;
            int fine_per_day=5;
            int fine=0;

            if(days>free_days)
            {
                fine=(days-free_days)*5;
            }
            
            printf("book id:%d",id);
            printf("\nstudent name:%s",s.student_name);
            printf("\nbook name: %s",s.book_name);
            printf("\nissue date:%s",s.date);
            printf("\nreturn date:%s",return_date);
            if(fine>0)
            {
                printf("\ntotal fine :%d",fine);

            }
            else
            printf("\nno fine....");
            break;
        }
        
        
    
       
     }
    if(found==0)
    {
     printf("\n\n book not found....");
    }
    
    fclose(fp);
}
void returnbook()
{   FILE *fr;
    int id;
    int temp=0;
    system("cls");
    printf("<~~RETURN BOOKS~~>\n");
    printf("enter book id:");
    scanf("%d",&id);
    fp=fopen("issue.txt","rb");
    fr=fopen("return.txt","wb");
    while( fread(&s,sizeof(s),1,fp)==1)
    {
        if(s.id==id)
        {
            temp=1;
            

        }
        else
        fwrite(&s,sizeof(s),1,fr);
    }
    if(temp==1)
    {
        printf("\nbook returned succesfully..");
    }
    else{
        printf("\n book not found....");
    }
    fclose(fp);
    fclose(fr);
    remove("issue.txt");
    rename("return.txt","issue.txt");

}
