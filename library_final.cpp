//LIBRARY MANAGEMENT SYSTEM

//Including Header Files
#include<fstream>
#include"conio.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iomanip>
#include<iostream>
using namespace std;
string usn;

//Creating a Class for Book
class book
{
	char bno[50];
	char bname[50];
	char aname[50];
public:
	void create_book()//function to create a new book
	{
		cout << "\nNEW BOOK ENTRY\n";
		cout << "\nEnter The book number : ";
		cin >> bno;
		cout << "\n\nEnter The Name of The Book : ";
		cin >> bname;
		cout << "\n\nEnter The Author's Name : ";
		cin >> aname;
		cout << "\n\n\nBook is Created";
	}
	void show_book()//function to display book
	{
		cout << "\nBook number : ";
		cout << bno;
		cout << "\nBook Name : ";
		puts(bname);
		cout << "Author Name : ";
		puts(aname);
	}
	void modify_book()// function to modify bbok
	{
		cout << "\nBook number : " << bno;
		cout << "\nModify Book Name : ";
		cin >> bname;
		cout << "\nModify Author's Name of Book : ";
		cin >> aname;
	}
	char *retbno()//return book number
	{
		return bno;
	}
	void report()//prinits about book name and author name
	{
		cout << bno << setw(30) << bname << setw(30) << aname << endl;
	}
};

//Creating a Class for Student
class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
public:
	void create_student()//function to create a student
	{
		cout << "\nNEW STUDENT ENTRY\n";
		cout << "\nEnter The admission number : ";
		cin >> admno;
		cout << "\n\nEnter The Name of the student : ";
		cin >> name;
		token = 0;
		stbno[0] = '\0';
		cout << "\n\nStudent Record Created";
	}
	void show_student()//function to display the student
	{
		cout << "\nAdmission number : ";
		cout << admno;
		cout << "\nStudent Name : ";
		puts(name);
		cout << "\nNumber of Books issued : " << token;
		if (token == 1)
		{
			cout << "\nBook Number : " << stbno;
		}
	}
	void modify_student()//function to modify the student
	{
		cout << "\nAdmission number : " << admno;
		cout << "\nModify Student Name : ";
		cin >> name;
	}
	char *retadmno()//returns admission no
	{
		return admno;
	}
	char *retstbno()//returns book number
	{
		return stbno;
	}
	int rettoken()//return token
	{
		return token;
	}
	void addbook()//updates token value when book is issued
	{
		token = 1;
	}
	void retbook()//updates token value when book is returned
	{
		token = 0;
	}
	void getstbno(char t[])
	{
		strcpy(stbno, t);
	}
	void report()//prints students details
	{
		cout << "\t" << admno << setw(20) << name << setw(10);
		cout << token << endl;
	}
};

fstream fp, fp1; // decalring objects globally
book bk;
student st;

//Creates a New Book
void write_book()
{
    string x;
    fp.open("book.txt",ios::out | ios::app);//opens file named book in append mode or to write
    while(1)
    {
        bk.create_book();//calling create book fn in class book using that class object
        fp.write((char *)&bk, sizeof(book));
		cout << "\n\nDo you want to add more record(y/n)?"<<endl;
		cin>>x;//to enter another book
		if(x=="y"||x=="Y")
		{
			continue;
		} 
		else if(x=="n"||x=="N")
			break;
		else
			cout<<"Enter either y or n "<<endl;
	} 
	fp.close();//closing file
}

//Displays all Books in the Library
void display_allbooks()
{
	fp.open("book.txt", ios::in);//opening file named book
	if (!fp)
	{
		cout << "ERROR!!! FILE COULD NOT BE OPEN ";
		cin.get();
		return;
	}
	cout << "\n\n\t\tBook LIST\n\n";
	cout << "BookNumber" << setw(20) << "BookName" << setw(25)<< "Author\n";
	while (fp.read((char *)&bk, sizeof(book)))//reading data from book file
	{
		bk.report();
	}
	fp.close();
	cin.get();
}

//Function to add a feature to ask if u want to add more students or not
void write_student()
{
	char ch;
	fp.open("student.txt", ios::out | ios::app);//openning file named student.txt
	do
	{
		st.create_student();//calling function in class student
		fp.write((char *)&st, sizeof(student));//writing data into file
		cout << "\n\ndo you want to add more record(y/n)?";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fp.close();
}

//Displays the List of all Registered Students
void display_allstudents()
{
	fp.open("student.txt", ios::in);//opening file named student.txt
	if (!fp)
	{
		cout << "ERROR!!! FILE COULD NOT BE OPEN ";
		cin.get();
		return;
	}
	cout << "\n\n\t\tSTUDENT LIST\n\n";
	cout << "\tAdmissionNo."<< setw(10) << "Name" << setw(20) << "Book Issued\n";
	while (fp.read((char *)&st, sizeof(student)))//reading data from file
	{
		st.report();//calling fn in class student
	}
	fp.close();
	cin.get();
}

//Displays Specific Book
void display_spb(char n[])
{
	cout << "\nBOOK DETAILS\n";
	int flag = 0;
	fp.open("book.txt", ios::in);//opening file named book.txt
	while (fp.read((char *)&bk, sizeof(book)))//reading data from file
	{
		if (strcmp(bk.retbno(), n) == 0)//comparing the data read from file and input from user
		{
			bk.show_book();//printing the specified book if found 
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)
	{
		cout << "\n\nBook does not exist";
	}
	cin.get();
}

//Function to display Specific student record
void display_sps(char n[])
{
	cout << "\nSTUDENT DETAILS\n";
	int flag = 0;
	fp.open("student.txt", ios::in);//opening file named student.txt
	while (fp.read((char *)&st, sizeof(student)))//reading data from file
	{
		if ((strcmp(st.retadmno(), n) == 0)) //comparing the admission no from data and user data
		{
			st.show_student();//calling show_student function from class student
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)
	{
		cout << "\n\nStudent does not exist";
	}
	cin.get();
}

//Function to Modify Book Details
void modifybook()
{
	char n[10];
	int found = 0;
    long  long int pos;
	cout << "\n\n\tMODIFY BOOK REOCORD ";
	cout << "\n\n\tEnter The book number of The book";
	cin>>n;
	fp.open("book.txt", ios::in | ios::out);// opening file named "book
	while (fp.read((char *)&bk, sizeof(book)) && found == 0)//reading data from file
	{
		if (strcmp(bk.retbno(), n) == 0)//comparing the data and user data
		{
			bk.show_book();//printing the present details of the book
			cout << "\nEnter The New Details of book : ";
			cout << endl;
			bk.modify_book();//calling modify_book
			cout<<sizeof(bk);
			pos = -1 * sizeof(bk);
			fp.seekp(pos, ios::cur);//setting the cursor position at pos value
			fp.write((char *)&bk, sizeof(book));//writing the new data of the book at the cursor position
			cout << "\n\n\t Record Updated";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
	{
		cout << "\n\n Record Not Found ";
	}
	cin.get();
}

//Function to Modify Student Details
void modifystudent()
{
	char n[10];
    long int pos;
	int found = 0;
	cout << "\n\n\tMODIFY STUDENT RECORD";
	cout << "\n\n\tEnter The Admission number of The student : ";
	cin >> n;
	fp.open("student.txt", ios::in | ios::out);
	while (fp.read((char *)&st, sizeof(student)) && found == 0)
	{
		if (strcmp(st.retadmno(), n) == 0)
		{
			st.show_student();
			cout << "\nEnter The New Details of the student : ";
			cout << endl;
			st.modify_student();
			pos = -1 * sizeof(st);
			fp.seekp(pos, ios::cur);
			fp.write((char *)&st, sizeof(student));
			cout << "\n\n\t Record Updated";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
	{
		cout << "\n\n Record Not Found ";
	}
	cin.get();
}

//Function to Delete Student Record
void delete_student()
{
	char n[6];
	int flag = 0;
	cout << "\n\n\n\tDELETE STUDENT";
	cout << "\n\nEnter The Admission number of the Student you want To Delete : ";
	cin >> n;
	fp.open("student.txt", ios::in | ios::out);
	fstream fp2;
	fp2.open("Temp.txt", ios::out);//opening a temporary file
	fp.seekg(0, ios::beg); //the file pointer is at the beginning 
	while (fp.read((char *)&st, sizeof(student)))//reading data from file
	{
		if (strcmp(st.retadmno(), n) != 0)//comparing with the file data and user data
		{
			fp2.write((char *)&st, sizeof(student));//entering the data into the temporary file except the n value
		}
		else
		{
			flag = 1;
		}
	}
	fp2.close();
	fp.close();
	remove("student.txt");//deleting the student file
	rename("Temp.txt", "student.txt");//renaming the temp.txt file to student.txt
	if (flag == 1)
	{
		cout << "\n\n\tRecord is been Deleted ";
	}
	else
	{
		cout << "\n\nRecord not found";
	}
	cin.get();
}

//Function to Delete a Book
void delete_book()
{
	char n[6];
	cout << "\n\n\n\tDELETE BOOK";
	cout << "\n\nEnter The Book number of the Book You Want To Delete : ";
	cin >> n;
	fp.open("book.txt", ios::in | ios::out);
	fstream fp2;
	fp2.open("Temp.txt", ios::out);//creating a temporary file
	fp.seekg(0, ios::beg);
	while (fp.read((char *)&bk, sizeof(book)))//reading data from file
	{
		if (strcmp(bk.retbno(), n) != 0)
		{
			fp2.write((char *)&bk, sizeof(book));//entering the data into the temporary file except the n value
		}
	}
	fp2.close();
	fp.close();
	remove("book.txt");//deleting the student file
	rename("Temp.txt", "book.txt");//renaming the temp.txt file to student.txt
	cout << "\n\n\tRecord is been Deleted ";
	cin.get();
}

//Function to Issue a Book
void book_issue()
{	book bk;
	student st;
	char bn[6],sn[6];
	int i=0;
    unsigned long long int pos;
	int found = 0, flag = 0;
	//sys(clear);
	cout<< "\n\nBOOK ISSUE";
	cout << "\n\n\tEnter The student's admission number : ";
	cin >> sn;
	fp.open("student.txt", ios::in | ios::out);//opening file  named student.txt
	fp1.open("book.txt", ios::in | ios::out);//opening file named book.txt
	while (fp.read((char *)&st, sizeof(student)) && found == 0)//reading data from file 
	{
		if (strcmp(st.retadmno(), sn) == 0)//finding the student  no
		{
			found+=1;
			if (st.rettoken() == 0 || st.rettoken() == 1)//checking token to issue a book
			{
				cout << "\n\n\tEnter the book numer : ";
				cin >> bn;
				while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)//reading data from book.txt
				{
					if (strcmp(bk.retbno(), bn) == 0)
					{
						bk.show_book();
						flag = 1;
						st.addbook();
						st.getstbno(bk.retbno());
						pos = -1 * sizeof(st);
						fp.seekp(pos, ios::cur);
						fp.write((char *)&st, sizeof(student));
						cout << "\n\n\t Book issued successfully";
						cout << "\n\nPlease Note: Write current date backside of book and submit within 15 days\n.";
						cout << "Fine of Rs.1 for each day will be taken after 15 days period";
					}
				}
				if(flag == 0)
				{
					cout << "Book no. does not exist";
				}
			}
			else
			{ 	cout << "The maximum book borrow limit is reached\n";
				cout << "You have not returned the last book \n";
				cout << "Book can be issued only after returning the previous one \n";
			}
		}
	}
		if(found==0)
		{
			cout << "Student record does not exist";
		}
		cin.get();
	fp.close();
	fp1.close();
}

//Function to Deposit a Book
void book_deposit()
{	book bk;
	student st;
	char sn[6], bn[6],rbno[6];
    unsigned long long int pos;
	int found = 0, flag = 0, day, fine;
	cout << "\n\nBOOK DEPOSIT";
	cout << "\n\n\tEnter The student's admission number : ";
	cin >> sn;
	fp.open("student.txt", ios::in | ios::out);
	fp1.open("book.txt", ios::in | ios::out);
	while (fp.read((char *)&st, sizeof(student)) && found == 0)
	{
		if (strcmp(st.retadmno(), sn) == 0)
		{
			found = 1;
			if (st.rettoken() == 1 || st.rettoken() ==2)
			{	cout<<"Enter the book number : "<<endl;
				cin>>rbno;
				while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)
				{
					if (strcmp(bk.retbno(),rbno) == 0)
					{
						bk.show_book();
						flag += 1;
						cout << "\n\nBook is deposited in how many number of days ? ";
						cin >> day;
						if (day > 15)
						{
							fine = (day - 15) * 1;
							cout << "\n\nFine has to deposited of Rs";
							cout << fine;
						}
						st.retbook();
						pos = -1 * sizeof(st);
						fp.seekp(pos, ios::cur);
						fp.write((char *)&st, sizeof(student));
						cout << "\n\n\t Book deposited successfully";
					}
				}
				if(flag==0)
				{
					cout << "inconsistent data" << endl;
				}
			}
		}
	}
	if (found == 0)
		cout << "Student record does not exist";
	cin.get();
	fp.close();
	fp1.close();
}

//Function for Admin Menu
void admin_menu()
{
	int ch2;
	char num[10];
	do{
	cout << "\n\n\n\tADMINISTRATOR MENU";
	cout << "\n\n\t1.CREATE STUDENT RECORD";
	cout << "\n\n\t2.DISPLAY ALL STUDENTS RECORD";
	cout << "\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
	cout << "\n\n\t4.MODIFY STUDENT RECORD";
	cout << "\n\n\t5.DELETE STUDENT RECORD";
	cout << "\n\n\t6.CREATE BOOK ";
	cout << "\n\n\t7.DISPLAY ALL BOOKS ";
	cout << "\n\n\t8.DISPLAY SPECIFIC BOOK ";
	cout << "\n\n\t9.MODIFY BOOK ";
	cout << "\n\n\t10.DELETE BOOK ";
	cout << "\n\n\t11.BACK TO MAIN MENU";
	cout << "\n\n\tPlease Enter Your Choice (1-11): ";
	cin >> ch2;
	switch (ch2)
	{
	case 1: 
	system("cls");
		write_student();
		break;
	case 2:
	system("cls");
		display_allstudents();
		break;
	case 3:
	system("cls");
		cout << "\n\n\tPlease Enter The Admission Number : ";
		cin >> num;
		display_sps(num);
		break;
	case 4:
		modifystudent();
		break;
	case 5:
		delete_student();
		break;
	case 6: 
		write_book();
		break;
	case 7:
	system("cls");
		display_allbooks();
		break;
	case 8:
		cout << "\n\n\tPlease Enter The book Number : ";
		cin >> num;
		display_spb(num);
		break;
	case 9:
		modifybook();
		break;
	case 10:
		delete_book();
		break;
	case 11:
		return;
	default:
		cout << "\n\tENTER A VALID CHOICE";
	}
}while(ch2!=11);
}

//Function for Signup Feature
void valid(string str,int tm)
{
    string dir,user;
    ifstream file;
    dir = str+".txt";
    file.open(dir.c_str());
    if(!file.is_open() && file.fail())
    {
        //file.close();
        return;
    }
    else
    {
        tm++;
        if(tm==3)
        {
            cout<<"\nThis username already exists\nPlease try Again";
            //file.close();
            return;
        }
        cout<<"\nThis username already exists!! \nCreate a username : ";
        cin>>usn;
        //file.close();
        valid(usn,tm);
    }
}

/*login system code*/
int login()
{
	int choice,i,exit=0,tm;
    string ans,psd,name,fname,bio,usern,pw,line,nusn;
    ofstream fileo;
    ifstream filei;
     //intro();
    while(exit==0)
    {
        cout<<"\nChoose one option : \n1.LogIn\n2.SignUp\n\n Enter your choice : ";
        cin>>choice;
        if(choice==1)
        {
            cout<<"Enter your username : ";
            cin>>usn;
            cout<<"\nEnter your password : ";
            cin>>psd;
            fname=usn+".txt";
            filei.open(fname.c_str());
            if(!filei.is_open() && filei.fail())
            {
                cout<<"\nYou are not registered, please register before logging in \n";
                filei.close();
                break;
            }
            getline(filei,usern);
            getline(filei,line);
            getline(filei,pw);
            if(usn==usern && psd==pw)
            {
                cout<<"\nYou are successfully logged in :)";
                filei.close();
                return 1;
            }
            else
            {
                cout<<"\nWrong username or password!! \nPlease try Again\n";
                return -1;
            }
            cout<<endl;
        }
        else if(choice==2)
        {
            cout<<"\nEnter your name : ";
            cin.ignore();
            getline(cin,name);
            cout<<"\nCreate a username : ";
            cin>>usn;
            tm=0;
            valid(usn,tm);
            if(tm>=3)
            {
                continue;
            }
            cout<<"\nCreate a password : ";
            cin>>psd;
            fname=usn+".txt";
            //cout<<fname;
            fileo.open(fname.c_str());
            fileo<<usn<<endl<<name<<endl<<psd<<endl;
            cout<<"\nYou are successfully registered :) ";
            fileo.close();
        }
        else
        {
            exit=1;
            break;
        }
    }
}

//Main Function
int main()
{
    int ch;
	int check;
	cout << "\tLIBRARY MANAGEMENT SYSTEM";
	cout << "\n\n\tMADE BY : GROUP - 2";
	cout << "\n\n\tCollege : SRM UNIVERSITY AP \n\n";
    do{
	check = login();
    while(check==1)
	{
		cout << "\n\n\n\t MAIN MENU";
		cout << "\n\n\t1. ADMINISTRATOR MENU";
		cout << "\n\n\t2. BOOK ISSUE";
		cout << "\n\n\t3. BOOK DEPOSIT";
		cout << "\n\n\t4. EXIT";
		cout << "\n\n\tPlease Select Your Option (1-4): ";
		cin >> ch;
		switch (ch)
		{
		case 1: 
			admin_menu();
			break;
		case 2:
			book_issue();
			break;
		case 3:
			book_deposit();
			break;
		case 4:
			return 0;
		default:
			cout << "\n\tENTER A VALID CHOICE";
		}
	} }while (ch !=4);
}

//End of Program