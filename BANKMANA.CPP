#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<process.h>
#include<fstream.h>
#include<ctype.h>
#include<dos.h>


//  CLASS USED:

class account
{
  long acno;
  char name[50];
  double deposit,withdraw;
  char type;
 public:
  account()
  {
   acno=0;
  }
  int u[4];
  void create_account()
  {
   cout<<"\n\nEnter The Name of The Account Holder (min. 13 char.):";
   gets(name);
   cout<<"\n\nEnter Type of The Account (C/S) :";
   cin>>type;
   type=toupper(type);
   cout<<"\n\nEnter The Initial Amount(>=500 for Saving and >=1000 for current ):";
   cin>>deposit;
   assignac();
   cout<<"YOUR ACCOUNT NO.: "<<acno;
   cout<<"\n\n\nAccount Created..";
  }
  void sep(char x=NULL,int n=0)
  {
   int b,d,c,r=0;
   if(n==0)
    b=x;
   if(x==NULL)
    b=n;
   for(int i=0;b>0;i++)
   {
    c=(b/10);
    u[i]=b%10;
    b=c;r=i;
   }
   for(i=r+1;i<4;i++)
   {
    u[i]=-1;
   }
  }
  void assignac() //FOR ASSIGNING ACCOUNT NO.
  {
   int a[9],i,j=0,count,c;
   count=check(); //CHECKING NO. OF RECORDS IN ACC
   if(count==0)
   {
    a[8]=1;c=7;
   }
   else
   {
    count++;
    sep(count);
    for(i=8;u[j]>-1;i--)
    {
     a[i]=u[j];
     j++;
    }
    c=i;
   }
   for(i=c;i>-1;i--)
   {
    if(i<8 && i>2)
    {
     randomize();
     a[i]=random(10);
    }
    if(i==2)
    {
     sep(name[0]);
     a[i]=u[0];
    }
    if(i==1)
    {
     sep(type);
     a[i]=u[0];
    }
    if(i==0)
    {
     a[0]=7;
    }
   }
   j=8;acno=0;
   for( i=0;i<9;i++)
   {
    acno=acno+a[i]*pow(10,j);j--;  //MAKING ARRAY a[] TO LONG acno
   }
  }
  void show_account()
  {
   cout<<"\n\nAccount No. : "<<acno;
   cout<<"\n\nAccount Holder Name : ";
   puts(name);
   cout<<"\n\nType of Account : "<<type;
   cout<<"\n\nBalance amount : "<<deposit;
  }

  void modify_account()
  {
   cout<<"\n\nAccount No. : "<<acno;
   cout<<"\n\nModify Account Holder Name : ";
   gets(name);
  }
  void dep(int x)
  { deposit+=x; }
  void draw(int x)
  { deposit-=x; }
  void report()
  { cout<<"\n\t   "<<acno<<"\t    "<<name<<"\t"<<type<<"\t\t "<<deposit; }
  int  retacno()
  { return acno; }
  float retdeposit()
  { return deposit; }
  char rettype()
  { return type; }

};         //class ends



//Global declaration for stream object, object:
fstream fp;
account ac;

//Function to write in file:
void write_account()
{
 fp.open("acc.dat",ios::out|ios::app);
 ac.create_account();
 fp.write((char*)&ac,sizeof(account));
 fp.close();
}
int check()
{
 ifstream f;account a;
 int c=0;
 f.open("acc.dat",ios::in);
 f.read((char*)&a,sizeof(a));
 while(!f.eof())
 {
  c++;
  f.read((char*)&a,sizeof(a));
 }
 return c;
}
//Function to read specific record from file:
void display_sp(int n)
{
    clrscr();
    cout<<"\nBALANCE DETAILS\n";
    int flag=0;
    fp.open("acc.dat",ios::in);
    while(fp.read((char*)&ac,sizeof(account)))
	{
	 if(ac.retacno()==n)
		{
		 ac.show_account();
		 flag=1;
		}
	}
    fp.close();
    if(flag==0)
    cout<<"\n\nAccount number does not exist!!!";
    getch();
}

//Function to modify record of file:
void modify_account()
{
 int no,found=0;
 clrscr();
 cout<<"\n\n\tTO MODIFY RECORD ";
 cout<<"\n\nEnter The account No. of the account to be modified: ";
 cin>>no;
 fp.open("acc.dat",ios::in|ios::out);
 while(fp.read((char*)&ac,sizeof(account)) && found==0)
 {
  if(ac.retacno()==no)
  {
   ac.show_account();
   cout<<"\nEnter The New Details of account:-"<<endl;
   ac.modify_account();
   int pos=-1*sizeof(ac);
   fp.seekp(pos,ios::cur);
   fp.write((char*)&ac,sizeof(account));
   cout<<"\n\n\t Record Updated";
   found=1;
  }
 }
 fp.close();
 if(found==0)
  cout<<"\n\n Record Not Found ";
 getch();
}
//Function to delete record of file:
void delete_account()
{
 int no;int found=0;char ch='y';int flag=1;int go=0;
 clrscr();
 cout<<"\n\n\n\tTO DELETE RECORD";
 cout<<"\n\nEnter The account no. of the account to be Deleted:";
 cin>>no;
 fp.open("acc.dat",ios::in|ios::out);
 fstream fp2;
 fp2.open("Temp.dat",ios::out);
 fp.seekg(0,ios::beg);
 while(fp.read((char*)&ac,sizeof(account))|| go==1)
 {
  if(ac.retacno()!=no || go==1)
  {
   if(go==1)
   {  fp.seekp(-sizeof(ac),ios::beg);
   }
   fp2.write((char*)&ac,sizeof(account));flag=2;go=2;
  }
  if(ac.retacno()==no && flag==1)
  {
   ac.show_account();
   cout<<"\n Are you sure to delete the account(y/n)?";
   cin>>ch;
   ch=tolower(ch);
   if(ch=='y')
    found=1;
   if(ch=='n')
   {	found=2;go=1; }
  }
 }
 fp2.close();
 fp.close();
 remove("acc.dat");
 rename("Temp.dat","acc.dat");
 if(found==1)
  cout<<"\n\n\tRecord Deleted ..";
 if(found==0)
  cout<<"\nRecord Not Found";
 if(found==2)
  cout<<"\nRecord not deleted";
 getch();
}
//Function to display all accounts deposit list:
void display_all()
{
 clrscr();
 ifstream fp;
 account ac;
 fp.open("acc.dat",ios::in);
 if(!fp)
 {
  cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
  getch();
  return;
 }
 else
 {
  cout<<"\n\n\t\t\t    ACCOUNT HOLDER LIST\n\n";
  cout<<"\t   ==============================================================\n";
  cout<<"\t     Sno.                NAME\t      Type\t\tBalance\n";
  cout<<"\t   ==============================================================\n";

  while(fp.read((char*)&ac,sizeof(account)))
  {
   ac.report();
  }
 }
 fp.close();
}

//Function to deposit and withdraw amounts:
void deposit_withdraw(int option)
{
 int no,found=0,amt;
 clrscr();
 cout<<"\n\n\t Enter The account No. : ";
 cin>>no;
 fp.open("acc.dat",ios::in|ios::out);
 while(fp.read((char*)&ac,sizeof(account)) && found==0)
 {
  if(ac.retacno()==no)
  {
   ac.show_account();
   if(option==1)
   {
    cout<<"\n\n\n\n\t TO DEPOSITE AMOUNT ";
    cout<<"\n\n Enter the amount to be deposited : ";
    cin>>amt;
    ac.dep(amt);
   }
   if(option==2)
   {
    cout<<"\n\n\n\n\t TO WITHDRAW AMOUNT ";
    cout<<"\n\n Enter the amount to be withdrawn : ";
    cin>>amt;
    int bal=ac.retdeposit()-amt;
    if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
     cout<<"Insufficience balance";
    else
     ac.draw(amt);
   }
   int pos=-1*sizeof(ac);
   fp.seekp(pos,ios::cur);
   fp.write((char*)&ac,sizeof(account));
   cout<<"\n\n\t Record Updated";
   found=1;
  }
 }
 fp.close();
 if(found==0)
  cout<<"\n\n Record Not Found ";
 getch();
}
//INTRODUCTION FUNCTION:
void intro()
{
 clrscr();
 char ch,choice;
 int action;
 cout<<"\n     w       w   e e e e   l          c c c    o o o    m       m   e e e e"
     <<"\n     w       w   e         l         c        o     o   m m   m m   e      "
     <<"\n     w   w   w   e e e     l         c        o     o   m   m   m   e e e  "
     <<"\n     w w   w w   e         l         c        o     o   m       m   e      "
     <<"\n     w       w   e e e e   lllllll    c c c    o o o    m       m   e e e e" ;
 cout<<"\n"
     <<" \n\t\t\t        t t t t t   o o o  "
     <<" \n\t\t\t            t      o     o "
     <<" \n\t\t\t            t      o     o "
     <<" \n\t\t\t            t      o     o "
     <<" \n\t\t\t            t       o o o  ";
 cout<<"\n    b b b         a       n       n   k   k   i   n       n     g g g   "
     <<"\n    b     b      a a      n n     n   k k     i   n n     n   g         "
     <<"\n    b b b       a   a     n   n   n   k       i   n   n   n   g         "
     <<"\n    b     b    a  a  a    n     n n   k k     i   n     n n   g   g g   "
     <<"\n    b b b     a       a   n       n   k   k   i   n       n     g g g   "
     <<"\n"
     <<"\n\t      s s s   y       y    s s s   t t t t t   e e e e   m       m   "
     <<"\n\t     s          y   y     s            t       e         m m   m m   "
     <<"\n\t      s s s       y        s s s       t       e e e     m   m   m   "
     <<"\n\t           s      y             s      t       e         m       m   "
     <<"\n\t      s s s       y        s s s       t       e e e e   m       m   ";

 getch();
}
int menu()
{
 cout<<"\n";
 cout<<"\t\t\t  ";
 for( int i=0;i<33;i++)
 {cout<<"-";}
 cout<<"\n\t\t\t  +\t01. NEW ACCOUNT \t  +\n";
 for(i=0;i<2;i++)
 {cout<<"\t\t\t  +\t\t\t\t  +\n";}
 cout<<"\t\t\t  +\t02. DEPOSIT AMOUNT \t  +\n";
 for(i=0;i<2;i++)
 {cout<<"\t\t\t  +\t\t\t\t  +\n";}
 cout<<"\t\t\t  +\t03. WITHDRAW AMOUNT \t  +\n";
 for(i=0;i<2;i++)
 {cout<<"\t\t\t  +\t\t\t\t  +\n";}
 cout<<"\t\t\t  +\t04. BALANCE ENQUIRY  \t  +\n";
 for(i=0;i<2;i++)
 {cout<<"\t\t\t  +\t\t\t\t  +\n";}
 cout<<"\t\t\t  +\t05. ACCOUNT HOLDER LIST\t  +\n";
 for(i=0;i<2;i++)
 {cout<<"\t\t\t  +\t\t\t\t  +\n";}
 cout<<"\t\t\t  +\t06. CLOSE AN ACCOUNT\t  +\n";
 for(i=0;i<2;i++)
 {cout<<"\t\t\t  +\t\t\t\t  +\n";}
 cout<<"\t\t\t  +\t07. MODIFY AN ACCOUNT\t  +\n";
 for(i=0;i<2;i++)
 {cout<<"\t\t\t  +\t\t\t\t  +\n";}
 cout<<"\t\t\t  +\t08. EXIT\t\t  +";
 cout<<"\n";
 cout<<"\t\t\t  ";
 for(i=0;i<33;i++)
 {cout<<"-";}
 cout<<"\n\t\t\tSelect Your Option (1-8) : ";
 int a;
 a=getche();
 return a;
}
//THE MAIN FUNCTION OF PROGRAM:
void main()
{
 clrscr();
 remove ("acc.dat");
 int main(int);
 char ch;
 intro();
 clrscr();
 cout<<"\n\n\n\n\n\n\n\n\n";
 cout<<"\t\t\t\t INSTRUCTION \n\n\n\n\t";
 cout<<"PLEASE ENSURE THAT YOU DON'T ENTER ALREADY EXISTING ACCOUNT NUMBER";
 cout<<"\n\n\n IF THE NAME DOSE NOT CONTAIN 13 CHARACTERS EXTEND IT BY ENTERING EMPTY SPACES";
 delay(4000);
 do
 {
  clrscr();
  cout<<"\n\n\n\n\t\t\t\t     MAIN MENU";
  ch=menu();
  switch(ch)
  {
   case '1':
    clrscr();
    write_account();
    getch();
    break;
   case '2':
    clrscr();
    deposit_withdraw(1);
    break;
   case '3':
    clrscr();
    deposit_withdraw(2);
    getch();
    break;
   case '4':
    int num;
    clrscr();
    cout<<"\n\n\tEnter The account No. ";
    cin>>num;
    display_sp(num);
    break;
   case '5':
    clrscr();
    display_all();
    getch();
    break;
   case '6':
    delete_account();
    break;
   case '7':
    clrscr();
    modify_account();
    getch();
    break;
   case '8':
    clrscr();
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout<<"\t\t\t\t";
    cout<<"THANK YOU \n\n\t\t\t\t   VISIT AGAIN.....";
    delay(1000);
    exit(0);
   default :
   cout<<"\a\a";
  }
 }while(ch!='8');
}

//END OF PROJECT
