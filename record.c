/*****************************************************************************************/
/*                                                                                       */
/*        THIS PROJECT IS CREATED BY YASH SHARMA AS A PART OF DSA ASSESSMENT             */
/*                              DURING SEMESTER 3                                        */
/*                                                                                       */
/*                                                                                       */
/*****************************************************************************************/
/* INCLUDING ALL REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
/* DECLARING HEAD OF LINKED LIST*/
struct record *head = NULL;
/* DECLARATION OF LINKED LIST TO STORE DATA */
struct record
{
    long long int Roll;
    char Name[20];
    char Gender;
    int Age;
    struct record *next;
};
/* ALLOCATING EXISTING RECORDS REQUIRED MEMORY */
void allocate_storage()
{
    FILE *fp = fopen("Records.txt", "r");
    if (fp == NULL)
        fp = fopen("Records.txt", "w");
    struct record r1, *loc, *new;
    int no = 0;
    while (fread(&r1, sizeof(struct record), 1, fp)) //CREATING NODES
        FOR EXISTING RECORD
        {
            new = (struct record *)malloc(sizeof(struct record));
            new->Roll = r1.Roll;
            strcpy(new->Name, r1.Name);
            new->Gender = r1.Gender;
            new->Age = r1.Age;
            new->next = NULL;
            if (no == 0) //HEADER NODE
            {
                head = new;
                loc = new;
                no = 1;
            }
            else //OTHER NODES
            {
                loc->next = new;
                loc = new;
            }
        }
    fclose(fp);
}
/* FUNCTION TO DISPLAY ALL RECORDS */
void show()
{
    struct record *r1 = head;
    if (r1 == NULL)
        printf("\nNo Record found.\n");
    else
 printf("\nRecord File contains : \n%-11s %-20s %-6s
%-3s\n","Roll No.","Name","Gender","Age");
 while (r1 != NULL)
 {
            printf("%11lld %-20s %c %-3d\n", r1->Roll, r1->Name, r1 - > Gender, r1->Age);
            r1 = r1->next;
 }
}
/* ADDING DATA TO EXTERNAL TEXT FILE */
void add(struct record *r1)
{
    FILE *fp1 = fopen("Records.txt", "w");
    struct record *loc = head, *p, q;
    if (loc == NULL)
    {
        head = r1;
        printf("\nRecord added Successfully.\n");
    }
    else if (loc->Roll > r1->Roll)
    {
        r1->next = head;
        head = r1;
        printf("\nRecord added Successfully.\n");
    }
    else
        while (loc != NULL)
        {
            if (loc->Roll == r1->Roll)
            {
                free(r1);
 printf("\nRecord already exists with same Roll
No.\n");
 break;
            }
            else if (loc->Roll > r1->Roll)
            {
                r1->next = loc;
                p->next = r1;
                printf("\nRecord added Successfully.\n");
                break;
            }
            else if (loc->next == NULL)
            {
                loc->next = r1;
                printf("\nRecord added Successfully.\n");
                break;
            }
            else
            {
                p = loc;
                loc = loc->next;
            }
        }
    /* REWRITING MODIFIED RECORDS*/
    p = head;
    while (p != NULL)
    {
        fwrite(p, sizeof(struct record), 1, fp1);
        p = p->next;
    }
    fclose(fp1);
}
/* CREATING NEW NODE AND CALLING ADD FUNCTION */
void insert()
{
    long long roll = 0, age = 0;
    char gender = 'M', name[20] = {};
    struct record *new = (struct record *)malloc(sizeof(struct record));
    printf("Enter Roll : ");
    scanf("%lld", &roll);
    printf("Enter Age : ");
    scanf("%d", &age);
    printf("Enter Name : ");
    scanf(" %[^\n]", name);
    printf("Enter Gender (M/F) : ");
    gender = getch();
    putch(gender);
    new->Age = age;
    strcpy(new->Name, name);
    new->Gender = gender;
    new->Roll = roll;
    new->next = NULL;
    add(new);
}
/* FUNCTION TO DELETE A PARTICULAR NODE */
void del()
{
    struct record r1, *loc, *p;
    long long roll;
    printf("Enter the Roll No whose record you want to delete : ");
    scanf("%11lld", &roll);
    FILE *fp1 = fopen("Records.txt", "w");
    int res = 0;
    loc = head;
    while (loc != NULL)
        if (loc->Roll == roll && loc == head)
        {
            head = head->next;
            res++;
            free(loc);
            break;
        }
        else if (loc->Roll == roll)
        {
            p->next = loc->next;
            res++;
            free(loc);
            break;
        }
        else
        {
            p = loc;
            loc = loc->next;
        }
    /* REWRITING MODIFIED RECORDS*/
    loc = head;
    while (loc != NULL)
    {
        fwrite(loc, sizeof(struct record), 1, fp1);
        loc = loc->next;
    }
    fclose(fp1);
    if (res == 0)
        printf("Record not found.\n");
    else
        printf("Record deleted successfully.\n");
}
/* FUNCTION TO SEARCH RECORD BY ROLL NO */
void search()
{
    long long roll;
    printf("Enter Roll No whose record you want to search : ");
    scanf("%11lld", &roll);
    struct record *loc = head;
    int res = 0;
    while (loc != NULL)
    {
        if (loc->Roll == roll)
        {
            printf("Record found as follows : \n");
            printf("Roll No. : %11lld\n", loc->Roll);
            printf("Name : %s\n", loc->Name);
            printf("Gender : %c\n", loc->Gender);
            printf("Age : %d\n", loc->Age);
            res++;
            break;
        }
        loc = loc->next;
    }
    if (res == 0)
        printf("\nRecord not found\n");
}
/* MAIN DRIVING CODE */
int main()
{
    int choice = -1;
    struct record *head2 = head;
    allocate_storage();
    printf("\n\n**********************************************************************************************************************\n");
    printf("\t\t\t\tWelcome to students record center\n");
    while (choice != 0)
    {
        printf("\nEnter choice from following.\n");
        printf("1 to enter new record\n");
        printf("2 to delete a record\n");
        printf("3 to search a record\n");
        printf("4 to display all record\n");
        printf("0 to exit\n");
        printf("Press choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            insert();
            break;
        case 2:
            del();
            break;
        case 3:
            search();
            break;
        case 4:
            show();
            break;
        case 0:;
            break;
        default:
            printf("Enter valid choice.");
            break;
        }
    }
    return 0;
}