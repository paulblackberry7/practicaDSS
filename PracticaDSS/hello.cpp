#include<stdio.h>
#include<iostream>
#include<string>
#include<windows.h>//Para RECT
#include<time.h>//Para clock
#include<conio.h>//Para getch
#include<string.h>
#include<fstream>//Para manejar archivos de texto
#include "sha256.h"
#define max 50
using namespace std;//Para no poner a cada rato std

int num=0;
void setWindowSize(unsigned short int,unsigned short int);
void gotoXY(unsigned short int,unsigned short int);
void Cdelay(unsigned short int);
void printLine(unsigned short int, unsigned short int, unsigned short int);
void printBorder(unsigned short int, unsigned short int,unsigned short int, unsigned short int, unsigned short int);
void intro();
void menuAdmin();
void menu();
void getRecords();
//bool isFilePresent();
void search();

class Person{
    private:
        unsigned short int id;
        unsigned short int role;
    public:
        Person();
        Person(unsigned short int _id, unsigned short int _role);
        ~Person();
        unsigned short int getId() { return id; };
        unsigned short int getRole() { return role; };
};
Person::Person() { }
Person::Person(unsigned short int _id, unsigned short int _role) { id = _id; role = _role; }
Person::~Person() { }
Person login();

class Employee{
    public:
        char name[20];
        int code;
        char designation[20];
        int exp;
        int age;
        int salary;
};
Employee emp[max],tempemp[max];

void getRecords(){
	FILE *fp;
	fp = fopen("registros.txt","r");
	int c=0;
	if(fp!=NULL){
		while(feof(fp)==0){
			fscanf(fp,"%s\t%d\t%s\t%d\t%d\t%d\n",&emp[c].name,&emp[c].code,&emp[c].designation,&emp[c].exp,&emp[c].age,&emp[c].salary);
			c++;
		}
		num=c;
	}
	fclose(fp);
};

void setWindowSize(unsigned short width,unsigned short height){
	RECT r;
}

void gotoXY(unsigned short int X, unsigned short int Y){
    COORD coordinates;
    coordinates.X = X;
    coordinates.Y = Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void Cdelay(unsigned short int msec){
    long goal = msec + (clock());
    while (goal > (clock()));
}

void printLine(unsigned short int X, unsigned short int Y, unsigned short int number) {
	gotoXY(X, Y);
    printf("%c", number);
}

void printBorder(unsigned short int xLenS, unsigned short int yLenS, unsigned short int xLenE, unsigned short int yLenE, unsigned short int msec){
    system("cls");
    //Left Corners
    printLine(xLenS,yLenS, 201);
    printLine(xLenS,yLenE, 200);
    //Top and Bottom Border line
    for(int i = xLenS + 1; i <= xLenE - 1; i++){
        Cdelay(msec);
        printLine(i,yLenS, 205);
        printLine(i,yLenE, 205);
    }
    //Right Corners
    printLine(xLenE,yLenS, 187);
    printLine(xLenE,yLenE, 188);
    //Left and Right Border Line
    for(int i = yLenS + 1; i <= yLenE - 1; i++){
        Cdelay(msec);
        printLine(xLenS, i, 186);
        printLine(xLenE, i, 186);
    }
    printf("\n\n");
}

void intro(){
	gotoXY(45,12);
    printf("PAYROLL MANAGEMENT SYSTEM");
    gotoXY(42,14);
    printf("Developed by Pablo Mora Herreros");
    gotoXY(53,20);
    printf("Loading...");
    gotoXY(48,22);
    for(int i = 0; i < 20; i++){
        Cdelay(200);
        printf("%c",254);
    }
}

Person login(){
    Person person(0, 0);
    ifstream lectura;
    unsigned short int id, role;
    char username[51], auxUsername[51], password[65], auxPassword[10], ch;
    int i = 0;
    lectura.open("usuarios.txt", ios::in);
    if (lectura.is_open()){
        fflush(stdin);
        gotoXY(20,10);
        cout<<"Enter Username : ";
        cin.getline(auxUsername, 51);
        gotoXY(20,12);
        cout<<"Enter Password : ";
        while(1){
    	    ch = getch();
    	    if(ch==13) break;
    	    if(ch==32||ch==9) continue;
    	    else {
			    cout<<"*";
			    auxPassword[i]=ch;
			    i++;
    	    }
	    }
	    auxPassword[i] = '\0';
        lectura>>id>>username;
        while(!lectura.eof() && person.getId() == 0) {
            if (strcmp(auxUsername, username) == 0) {
                lectura>>password>>role;
                string nuevo = SHA256::cifrar(auxPassword);
                char cifrado[65];
                strcpy(cifrado, nuevo.c_str());
                if (strcmp(cifrado, password) == 0) {
                    person = Person(id, role);
                } else {
                    lectura>>id>>username;
                }
            } else {
                lectura>>password>>role>>id>>username;
            }
        }
    } else {
        printf("Error");
    }
    lectura.close();
    return person;
}

void menuAdmin(){
	printBorder(4, 2, 116, 26, 0);
	gotoXY(16,4);
	printf("*****  Payroll Management System ***** ");
	gotoXY(12,6);
    cout<<"Press  1 ----> List employees";
	//gotoXY(12,8);
	//cout<<"Press  e ----> Edit a Record.";
	//gotoXY(12,10);
	//cout<<"Press  d ----> Delete a Record.";
	//gotoXY(12,12);
    //cout<<"Press  i ----> Insert New Record.";
	//gotoXY(12,14);
	//cout<<"Press  l ----> Search a employee";
	//gotoXY(12,16);
	//cout<<"Press  p ----> Print Employee PaySlip.";
	gotoXY(12,18);
	cout<<"Press  7 ----> Quit Program.";
	gotoXY(16,22);
	cout<<"Select Your Option ====> ";
}

void menu(){
	printBorder(4, 2, 116, 26, 0);
	gotoXY(16,4);
	printf("*****  Payroll Management System ***** ");
	gotoXY(12,6);
    cout<<"Press  1 ----> List employees";
	//gotoXY(12,8);
	//cout<<"Press  e ----> Edit a Record.";
	//gotoXY(12,10);
	//cout<<"Press  d ----> Delete a Record.";
	//gotoXY(12,12);
    //cout<<"Press  i ----> Insert New Record.";
	//gotoXY(12,14);
	//cout<<"Press  l ----> Search a employee";
	//gotoXY(12,16);
	//cout<<"Press  p ----> Print Employee PaySlip.";
	gotoXY(12,18);
	cout<<"Press  7 ----> Quit Program.";
    gotoXY(16,22);
	cout<<"Select Your Option ====> ";
}

void  list(){
	printBorder(2, 2, 96, 24, 0);
	gotoXY(20,4);
	printf("       ******** List of the Employees ********");
	gotoXY(6,6);
	cout<<"Name\tCode\tDesignation\tYears(EXP)\tAge\tSalary "<<endl;
	gotoXY(6,7);
	cout<<"------------------------------------------------------------------"<<endl;
	for(int i=0,j=8;i<=num-1;i++,j++){
		gotoXY(6,j);
		cout<<emp[i].name;
		gotoXY(19,j);
		cout<<emp[i].code;
		gotoXY(26,j);
		cout<<emp[i].designation;
		gotoXY(47,j);
		cout<<emp[i].exp;
		gotoXY(58,j);
		cout<<emp[i].age;
		gotoXY(66,j);
		cout<<emp[i].salary;
	}
	getch();
}

void search(){
    printBorder(2, 2, 96, 24, 0);
	int jobcode;
	bool found = false;
	gotoXY(10,4);
	cout<<"You can search only through the code of an employee";
	gotoXY(10,6);
	cout<<"Enter code of the employee : ";
	cin>>jobcode;
	for(int i=0;i<=num-1;i++){
		if(emp[i].code==jobcode){
			gotoXY(6,8);
			cout<<"Name\tCode\tDesignation\tYears(EXP)\tAge\tSalary "<<endl;
			gotoXY(6,9);
			cout<<"------------------------------------------------------------------"<<endl;
			gotoXY(6,11);
			cout<<emp[i].name;
			gotoXY(19,11);
			cout<<emp[i].code;
			gotoXY(26,11);
			cout<<emp[i].designation;
			gotoXY(47,11);
			cout<<emp[i].exp;
			gotoXY(58,11);
			cout<<emp[i].age;
			gotoXY(66,11);
			cout<<emp[i].salary;
			found = true;
		}
	}
	if(!found){
		gotoXY(26,11);
		cout<<"No records found...!!!\a";
	}
	getch();
}

/*bool isFilePresent(){
	FILE *fp;
	fp = fopen("registros.txt","r");
	if(fp==NULL) return false;
	else return true;
}*/

int main(){
    setWindowSize(1080, 720);
    printBorder(4, 2, 116, 26, 10);
    intro();
    printBorder(18, 8, 75, 15, 10);
    bool found = false;
    Person person;
    while (found == false) {
        person = login();
        if (person.getId() != 0) {
            found = true;
            system("cls");
            printBorder(18, 8, 55, 15, 10);
            gotoXY(27,10);
            cout<<"Login Success!!!";
            gotoXY(21,12);
            cout<<"Will be redirected in 3 Seconds...";
            cout<<person.getRole();
            gotoXY(56,12);
            Cdelay(1000);
            gotoXY(44,12);
            cout<<"\b \b2";
            gotoXY(56,12);
            Cdelay(1000);
            gotoXY(44,12);
            cout<<"\b \b1";
            gotoXY(56,12);
            Cdelay(1000);
        }
        else {
            system("cls");
            printBorder(18, 8, 55, 15, 10);
            gotoXY(27,10);
            printf("Access Denied!!!\a");
            gotoXY(21,12);
            cout<<"Will be redirected in 3 Seconds...";
            gotoXY(56,12);
            Cdelay(1000);
            gotoXY(44,12);
            cout<<"\b \b2";
            gotoXY(56,12);
            Cdelay(1000);
            gotoXY(44,12);
            cout<<"\b \b1";
            gotoXY(56,12);
            Cdelay(1000);
            system("cls");
            printBorder(18, 8, 55, 15, 10);
        }
    }
    getRecords();
    int option;
    //if(emp[0].code==0 && isFilePresent()) num--;
    if (person.getRole() == 1) {
        menuAdmin:
        system("cls");
        menuAdmin();
        while(1){
            cin>>option;
            switch(option){
                case 1:
                    list();
                    goto menuAdmin;
                    break;
                case 'i':
                    //insert();
                    break;
                case 'd':
                    //deletes();
                    break;
                case 'e':
                    //edit();
                    break;
                case 2:
                    search();
                    break;
                case 'p':
                    //displayPayslip();
                    break;
                case 7:
                    exit(0);
                default:
                    goto menuAdmin;
                    break;
            }
	    }
    } else if (person.getRole() == 2) {
        menu:
        system("cls");
        menu();
        while(1){
            cin>>option;
            switch(option){
                case 1:
                    list();
                    goto menu;
                    break;
                case 7:
                    exit(0);
                default:
                    goto menu;
                    break;
            }
	    }
    } else {
        cout<<"Sorry, you don't have a role";
        system("pause");
    }
    return 0;
}