#include<stdio.h>
#include<iostream>
#include<string>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<ctime>
#include <climits>
#include "sha256.h"
#define max 50
using namespace std;
int num=0;

void setWindowSize(unsigned short int,unsigned short int);
void gotoXY(unsigned short int,unsigned short int);
void cDelay(unsigned short int);
void printLine(unsigned short int, unsigned short int, unsigned short int);
void printBorder(unsigned short int, unsigned short int,unsigned short int, unsigned short int, unsigned short int);
void intro();
void menuAdmin();
void menu();
void getEmployees();
void search();
void insert(unsigned short int);
void write(string);
void validateName(char*);
void validateCode(string);
void validateAge(string);
void validateSalary(string);
void validateInteger(string);

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
Person::Person() { };
Person::Person(unsigned short int _id, unsigned short int _role) { id = _id; role = _role; };
Person::~Person() { };
Person login(unsigned short int);

class Employee{
    public:
        char name[20];
        int code;
        char designation[20];
        int exp;
        int age;
        float salary;
};
Employee emp[max],tempemp[max];

/*files*/
void getEmployees(){
	FILE *fp;
	fp = fopen("employees.txt","r");
	int c = 0;
	if(fp != NULL){
		while(feof(fp) == 0){
			fscanf(fp,"%s\t%d\t%s\t%d\t%d\t%f\n",&emp[c].name,&emp[c].code,&emp[c].designation,&emp[c].exp,&emp[c].age,&emp[c].salary);
			c++;
		}
		num = c;
	}
	fclose(fp);
};

void saveEmployees(){
	if(num==0){
		system("del employees.txt");
	} else {
		FILE *fp;
		fp = fopen("employees.txt","w");
		for(int i=0;i<num;i++){
			fprintf(fp,"%s\t%d\t%s\t%d\t%d\t%f\n",emp[i].name,emp[i].code,emp[i].designation,emp[i].exp,emp[i].age,emp[i].salary);
		}
		fclose(fp);
	}
};

void write(string message) {
    fstream file("logs.txt", ios::app);
    if (!file.is_open()) {
        cout<<"Error while opening the file"<<endl;
    } else {
        file<<message + " : " + to_string(time(0))<<endl;
    }
    file.close();
};
/**/

/*window*/
void setWindowSize(unsigned short width,unsigned short height){ RECT r; };

void gotoXY(unsigned short int X, unsigned short int Y){
    COORD coordinates;
    coordinates.X = X;
    coordinates.Y = Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
};

void cDelay(unsigned short int msec){
    long goal = msec + (clock());
    while (goal > (clock()));
};

void printLine(unsigned short int X, unsigned short int Y, unsigned short int number) {
	gotoXY(X, Y);
    printf("%c", number);
};

void printBorder(unsigned short int xLenS, unsigned short int yLenS, unsigned short int xLenE, unsigned short int yLenE, unsigned short int msec){
    system("cls");
    //Left Corners
    printLine(xLenS, yLenS, 201);
    printLine(xLenS, yLenE, 200);
    //Top and Bottom Border line
    for(int i = xLenS + 1; i <= xLenE - 1; i++){
        cDelay(msec);
        printLine(i, yLenS, 205);
        printLine(i, yLenE, 205);
    }
    //Right Corners
    printLine(xLenE, yLenS, 187);
    printLine(xLenE, yLenE, 188);
    //Left and Right Border Line
    for(int i = yLenS + 1; i <= yLenE - 1; i++){
        cDelay(msec);
        printLine(xLenS, i, 186);
        printLine(xLenE, i, 186);
    }
    printf("\n\n");
};

void intro(){
	gotoXY(45, 12);
    printf("PAYROLL MANAGEMENT SYSTEM");
    gotoXY(42, 14);
    printf("Developed by Pablo Mora Herreros");
    gotoXY(53, 20);
    printf("Loading...");
    gotoXY(48, 22);
    for(int i = 0; i < 20; i++){
        cDelay(200);
        printf("%c",254);
    }
};

void menuAdmin(){
	printBorder(4, 2, 116, 26, 0);
	gotoXY(16, 4);
	printf("*****  Payroll Management System ***** ");
	gotoXY(12, 6);
    cout<<"Press  1 ----> List employees";
	gotoXY(12, 8);
    cout<<"Press  2 ----> Insert a new employee";
	gotoXY(12, 10);
    cout<<"Press  3 ----> Search a employee";
	gotoXY(12, 12);
    cout<<"Press  4 ----> Quit";
	gotoXY(12, 14);
    cout<<"Select Your Option ====> ";
};

void menu(){
	printBorder(4, 2, 116, 26, 0);
	gotoXY(16, 4);
	printf("*****  Payroll Management System ***** ");
	gotoXY(12, 6);
    cout<<"Press  1 ----> List employees";
	gotoXY(12, 8);
    cout<<"Press  2 ----> Quit";
	gotoXY(12, 10);
    cout<<"Select Your Option ====> ";
};
/**/

/*actions*/
void list(){
	printBorder(4, 2, 116, 26, 0);
	gotoXY(20, 4);
	printf("       ******** List of the Employees ********");
	gotoXY(6, 6);
	cout<<"Name\tCode\tDesignation\tYears(EXP)\tAge\tSalary "<<endl;
	gotoXY(6, 7);
	cout<<"------------------------------------------------------------------"<<endl;
	for(int i = 0, j = 8; i <= num - 1; i++, j++){
		gotoXY(6, j);
		cout<<emp[i].name;
		gotoXY(19, j);
		cout<<emp[i].code;
		gotoXY(26, j);
		cout<<emp[i].designation;
		gotoXY(47, j);
		cout<<emp[i].exp;
		gotoXY(58, j);
		cout<<emp[i].age;
		gotoXY(66, j);
		cout<<emp[i].salary;
	}
	getch();
};

void insert(unsigned short int id) {
    printBorder(4, 2, 116, 26, 0);
	int i = num;
	num += 1;
    int height = 4;
    try {
        gotoXY(28, height);
        height += 2;
        printf("Insert a new employee");
        //name
        gotoXY(10, height);
        height += 2;
        cout<<"Name (max 19 characters): ";
        cin>>emp[i].name;
        validateName(emp[i].name);
        //code
        gotoXY(10, height);
        height += 2;
        cout<<"Code (max 1000): ";
        string code;
        cin>>code;
        validateCode(code);
        emp[i].code = stoi(code);
        //designation
        gotoXY(10, height);
        height += 2;
        cout<<"Designation (max 19 characters): ";
        cin>>emp[i].designation;
        validateName(emp[i].designation);
        //experience
        gotoXY(10, height);
        height += 2;
        cout<<"Years of Experience (min 0 - max 150): ";
        string exp;
        cin>>exp;
        validateInteger(exp);
        emp[i].exp = stoi(exp);
        //age
        gotoXY(10, height);
        height += 2;
        cout<<"Age (min 16 - max 150): ";
        string age;
        cin>>age;
        validateAge(age);
        emp[i].age = stoi(age);
        //salary
        gotoXY(10, height);
        height += 2;
        cout<<"Salary (max 1000000000): ";
        string salary;
        cin>>salary;
        validateSalary(salary);
        emp[i].salary = stof(salary);

        gotoXY(14, 22);
        saveEmployees();
        cout<<"Recorded succesfully...!!!";
        write("User " + to_string(id) + " has inserted employee " + to_string(emp[i].code));
    } catch(char c) {
        gotoXY(10, height);
        printf("Letters are not valid");
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        num -= 1;
    } catch (const char* length) {
        gotoXY(10, height);
        printf("Invalid length");
        num -= 1;
    } catch(int i) {
        gotoXY(10, height);
        printf("Digits are not valid");
        num -= 1;
    } catch( ... ) {
        gotoXY(10, height);
        system("Error, try again");
        num -= 1;
    }
	getch();
};

void search(){
    printBorder(2, 2, 96, 24, 0);
	int jobcode;
	bool found = false;
	gotoXY(10, 4);
	cout<<"You can search only through the code of an employee";
	gotoXY(10, 6);
	cout<<"Enter code of the employee : ";
	cin>>jobcode;
	for(int i = 0; i <= num - 1; i++){
		if(emp[i].code == jobcode){
			gotoXY(6, 8);
			cout<<"Name\tCode\tDesignation\tYears(EXP)\tAge\tSalary "<<endl;
			gotoXY(6, 9);
			cout<<"------------------------------------------------------------------"<<endl;
			gotoXY(6, 11);
			cout<<emp[i].name;
			gotoXY(19, 11);
			cout<<emp[i].code;
			gotoXY(26, 11);
			cout<<emp[i].designation;
			gotoXY(47, 11);
			cout<<emp[i].exp;
			gotoXY(58, 11);
			cout<<emp[i].age;
			gotoXY(66, 11);
			cout<<emp[i].salary;
			found = true;
		}
	}
	if(!found){
		gotoXY(26, 11);
		cout<<"No employee found...!!!\a";
        cin.clear();
        cin.ignore(INT_MAX,'\n');
	}
	getch();
};
/**/

/*login*/
Person login(unsigned short int tries){
    Person person(0, 0);
    ifstream lectura;
    unsigned short int id, role;
    char username[51], auxUsername[51], password[65], auxPassword[10], ch;
    int i = 0;
    lectura.open("users.txt", ios::in);
    if (lectura.is_open()){
        fflush(stdin);
        if (tries < 3) {
            gotoXY(20, 14);
            cout<<"You only have "<<tries<<" attemps";
        }
        gotoXY(20, 10);
        cout<<"Enter Username : ";
        cin.getline(auxUsername, 51);
        gotoXY(20,12);
        cout<<"Enter Password : ";
        while(1){
    	    ch = getch();
    	    if(ch == 13) break;
            if (ch != 8) {
                if(ch == 32 || ch == 9) continue;
    	        else {
                    cout<<"*";
                    auxPassword[i] = ch;
                    i++;
    	        }
            } else {
                if (i > 0) {
                    cout<<"\b \b";
                    i--;
                }
            }
	    }
	    auxPassword[i] = '\0';
        lectura>>id>>username;
        while(!lectura.eof() && person.getId() == 0) {
            if (strcmp(auxUsername, username) == 0) {
                lectura>>password>>role;
                string nuevo = SHA256::cifrar(auxPassword);
                char encryption[65];
                strcpy(encryption, nuevo.c_str());
                if (strcmp(encryption, password) == 0) {
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
};
/**/

/*Validators*/
void validateName(char* text) {
    for (int i = 0; i < strlen(text); i++) {
        if (isdigit(text[i])) throw i;
    };
    if (strlen(text) == 0 || strlen(text) >= 20) throw "length";
};

void validateCode(string code) {
    for (int i = 0; i < code.length(); i++) {
        if (!isdigit(code[i])) throw 'x';
    };
    if (stoi(code) <= 0 || stoi(code) > 1000) throw "length";
};

void validateAge(string age) {
    for (int i = 0; i < age.length(); i++) {
        if (!isdigit(age[i])) throw 'x';
    };
    if (stoi(age) <= 15 || stoi(age) > 150) throw "length";
};

void validateInteger(string number) {
    for (int i = 0; i < number.length(); i++) {
        if (!isdigit(number[i])) throw 'x';
    };
    if (stoi(number) < 0 || stoi(number) > 150) throw "length";
};

void validateSalary(string salary){
    for (int i = 0; i < salary.length(); i++) {
        if (!(isdigit(salary[i]) || salary[i] == 46)) throw 'x';
    };
    if (stof(salary) < 0 || stof(salary) > 1000000000) throw "length";
};
/*End validators*/

int main(){
    setWindowSize(1080, 720);
    printBorder(4, 2, 116, 26, 10);
    intro();
    printBorder(18, 8, 70, 15, 10);
    bool found = false;
    unsigned short int tries = 3;
    Person person;
    while (found == false && tries > 0) {
        person = login(tries);
        if (person.getId() != 0) {
            found = true;
            system("cls");
            printBorder(18, 8, 70, 15, 10);
            gotoXY(27, 10);
            cout<<"Login Success!!!";
            write("User " + to_string(person.getId()) + " has entered");
            gotoXY(21, 12);
            cout<<"Will be redirected in 3 seconds...";
            gotoXY(56, 12);
            cDelay(1000);
            gotoXY(44, 12);
            cout<<"\b \b2";
            gotoXY(56, 12);
            cDelay(1000);
            gotoXY(44, 12);
            cout<<"\b \b1";
            gotoXY(56, 12);
            cDelay(1000);
        } else {
            system("cls");
            printBorder(18, 8, 70, 15, 10);
            gotoXY(27, 10);
            printf("Access Denied!!!\a");
            gotoXY(21, 12);
            if (tries > 1) cout<<"Will be redirected in 3 seconds...";
            else cout<<" System will close in 3 seconds...";
            gotoXY(56, 12);
            cDelay(1000);
            gotoXY(44, 12);
            cout<<"\b \b2";
            gotoXY(56, 12);
            cDelay(1000);
            gotoXY(44, 12);
            cout<<"\b \b1";
            gotoXY(56, 12);
            cDelay(1000);
            system("cls");
            printBorder(18, 8, 70, 15, 10);
            tries--;
        }
    }
    if (tries > 0) {
        getEmployees();
        int option;
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
                    case 2:
                        insert(person.getId());
                        goto menuAdmin;
                        break;
                    case 3:
                        search();
                        goto menuAdmin;
                        break;
                    case 4:
                        exit(0);
                        break;
                    default:
                        cin.clear();
                        cin.ignore(INT_MAX,'\n');
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
                    case 2:
                        exit(0);
                        break;
                    default:
                        cin.clear();
                        cin.ignore(INT_MAX,'\n');
                        goto menu;
                        break;
                }
            }
        } else {
            cout<<"Sorry, you don't have a role";
            system("pause");
        }
    }
    return 0;
};