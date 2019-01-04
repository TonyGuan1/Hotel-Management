//Hotel Mangement System
//Created by Tony Guan

#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>


//void deleteRoom(); //Declare functions
//int mainMenu();
int firstScreen();
int main();
void bookRoom();
void addEmployee();



struct guestInfo //Guest struc
{
	int roomNumber;
	char name[30];
	int stay;
	int persons;
	char guestPhoneNumber[30];
}g;
struct employeeInfo //Employee struc
{
	int id;
	char age[30];
	char name[30];
	char gender[30];
	char occupation[30];

}e;

void mainReturn()
{
	printf("\n\nPress any key to return");
	_getch();
	if (_getch() == 0)
	{
		system("cls");
		firstScreen();
	}
}

int validationString(char x[]) {
	int i;
	boolean c;
	int valid = 0;
	for (i = 0; i < strlen(x); i++) { //Check each letter
		if (isalpha(x[i])) //Check if all alphabet
		{
			c = TRUE;
		}
		else
		{
			c = FALSE;
			printf("Invalid. Input letters only.\n");
		}
	}
	return c; //print out TRUE or FALSE
}

int validationNum(char x[]) {

	boolean c;
	int i, valid = 0;
	for (i = 0; i < strlen(x); i++) {
		if (isdigit(x[i])) //Check if all numbers
		{
			c = TRUE;
		}
		else
		{
			c = FALSE;
			printf("Invalid. Input numbers only.\n");
		}
	}
	return c;
}

void enterDataStrings(char x[30])
{
	FILE *efData;
	int valid = 0;
	fopen_s(&efData, "Employee.txt", "r+");
	while (valid != 1)
	{
		scanf_s("%s", x, 30);
		if (strlen(x) > 0) {
			if (validationString(x) == 1) {
				valid = 1;
			}
		}
		else
		{
			printf("Enter input.\n");
		}

	}  //Loop until correct input is entered
	fclose(efData);

}

void printGuestroominfo() {
	FILE *fp3;
	fopen_s(&fp3, "guestInfo.txt", "r");

	printf("\nCurrent booked rooms\n");
	while (fscanf_s(fp3, "%d %s %d %d %s\n", &g.roomNumber, g.name, 30, &g.stay, &g.persons, g.guestPhoneNumber, 30) != EOF)//While file format is this, it will print out room
	{
		printf("%d ", g.roomNumber);
	}
	fclose(fp3);

}

void deleteRoom(x) //Youtube video used as reference when creating code block https://www.youtube.com/watch?v=IftYEICtkOI
{
	int room;
	int valid = 1;
	FILE *fp, *fp2;
	fopen_s(&fp, "copyguestInfo.txt", "w");//temp file to write into
	fopen_s(&fp2, "guestInfo.txt", "r");//Read from file

	if (fp2 == NULL)//File opening test
	{
		printf(" Error opening file\n");
		exit(1);
	}

	printGuestroominfo();//Print out booked rooms
	printf("\n\nEnter the room number\n");
	scanf_s("%d", &room);

	while (fscanf_s(fp2, "%d %s %d %d %s\n", &g.roomNumber, g.name, 30, &g.stay, &g.persons, g.guestPhoneNumber, 30) != EOF)
	{
		if (room == g.roomNumber)//If present, suspend it
		{
			valid = 0;
		}
		if (room != g.roomNumber)
		{
			valid = 1;
			fprintf(fp, "%d %s %d %d %s\n", g.roomNumber, g.name, g.stay, g.persons, g.guestPhoneNumber); //Write every thing except room entered to new file
		}
	}if (valid == 0)
	{
		printf("Entry deleted.\n");
		fprintf(fp2, "%d %s %d %d %s\n", g.roomNumber, g.name, g.stay, g.persons, g.guestPhoneNumber);
	}
	else
	{
		printf("Entry not deleted.");
	}

	fclose(fp);
	fclose(fp2);
	remove("guestInfo.txt");//Delete info file
	rename("copyguestInfo.txt", "guestInfo.txt");//rename new written file to guestinfo
	mainReturn();
}

void userContinue(x)
{
	char option;
	printf("Continue? Y/N\n");
	getchar();
	option = getchar();//exit
	if (option == 'Y' || option == 'y')
	{
		system("cls");
		bookRoom(x);
	}
	else
	{
		system("cls");
		firstScreen(x);
	}
}

void enterRoomnum()
{
	int valid = 0;
	int roomNumber;
	FILE *fp12;


	fopen_s(&fp12, "guestInfo.txt", "r+");
	if (fp12 == NULL)
	{
		printf("Error opening file");
		exit(1);
	}

	do {
		valid = 1;
		scanf_s("%d", &roomNumber);
		if (roomNumber > 0 && roomNumber <= 30)
		{
			while (fscanf_s(fp12, "%d %s %d %d %s\n", &g.roomNumber, g.name, 30, &g.stay, &g.persons, g.guestPhoneNumber, 30) != EOF)
			{

				if (roomNumber == g.roomNumber) //If it is equal to what is printed in file,print out booked
				{
					printf("Booked\n");
					valid = 0;

				}
				g.roomNumber = roomNumber;//set room number
			}
		}
		else
		{
			printf("Not in range");
			valid = 0;
		}
	} while (valid != 1);

	fclose(fp12);
}

void enterGuestname() {
	FILE *fpName;
	int valid = 1;
	fopen_s(&fpName, "guestInfo.txt", "r+");
	printf("Enter Name\n");
	do
	{
		scanf_s("%s", g.name, 30);
		if (strlen(g.name) < 0)
		{
			printf("Invalid. Try again");
			valid = 0;
		}
		else
		{
			if (validationString(g.name) == 1)
			{
				valid = 1;
			}
		}
	} while (valid != 1); //Loop until correct input is entered
	fclose(fpName);
}

void viewGuestroomPrint() {
	printf("\t----------------------------------------------------------------------------------------------------------");
	printf("\n\tROOM NUMBER ");
	printf("\t  NAME ");
	printf("\t\tPERIOD OF STAY");
	printf("\t\tNUMBER OF PEOPLE ");
	printf("\t\tPHONE NUMBER");
	printf("\n\t----------------------------------------------------------------------------------------------------------");

}

void viewGuestroom(int room, char name[30], int stay, int persons, char guestPhoneNumber[30])
{
	FILE *fp;

	fopen_s(&fp, "guestInfo.txt", "r");
	if (fp == 0)
	{
		printf("Error opening file.");
		exit(1);
	}

	while (fscanf_s(fp, "%d %s %d %d %s\n", &room, name, 30, &stay, &persons, guestPhoneNumber, 30) == 5)
	{
		printf("\n\t%6d", room);
		printf("\t\t %5s", name, 30);
		printf("\t\t\t%d", stay);
		printf("\t\t\t%d", persons);
		printf("\t\t\t%s", guestPhoneNumber, 30);
		printf("\n\t----------------------------------------------------------------------------------------------------------");
	}
	fclose(fp);
	mainReturn();
}

void enterGuestnights() {
	int valid = 1;

	FILE *fpNights;
	fopen_s(&fpNights, "guestInfo.txt", "r+");
	do {//Repeat if input is not within range
		printf("Enter number of nights (1-14)\n");
		scanf_s("%d", &g.stay);
		if (g.stay > 0 && g.stay <= 14) {//Nights condition
			valid = 1;
		}
		else
		{
			printf("Not valid\n");
		}
	} while (valid != 1);
	fclose(fpNights);
}

void enterGuestpersons() {
	int valid = 1;
	FILE *fpGuestpersons;

	fopen_s(&fpGuestpersons, "guestInfo.txt", "r+");
	do {//Repeat if input is not within range
		printf("Amount of persons (1-4)\n");
		scanf_s("%d", &g.persons);
		if (g.persons > 0 && g.persons <= 4) {//Condition
			valid = 1;
		}
		else
		{
			printf("Not valid\n");
			valid = 0;
		}
	} while (valid != 1);
	fclose(fpGuestpersons);
}

void enterGuestphone() {
	FILE *fpGuestphone;
	int valid = 1;
	fopen_s(&fpGuestphone, "guestInfo.txt", "r+");

	printf("Enter phone number (7-15 digits)\n");
	do
	{
		scanf_s("%s", &g.guestPhoneNumber, 30);

		if ((strlen(g.guestPhoneNumber)) > 6 && (strlen(g.guestPhoneNumber)) <= 15)
		{
			if (validationNum(g.guestPhoneNumber) == 1) {//Check if validation is true
				valid = 1;
				break;
			}

		}
		else
		{
			printf("Enter at least 7 to 15 digits \n");
			valid = 0;
		}

	} while (valid != 1);//Loop until valid is 1
	fclose(fpGuestphone);
}

void bookRoom(x) //Calls all function for guests
{
	int valid = 1;
	FILE *fp;

	printGuestroominfo();//call each function
	printf("\nEnter room number (1-30)\n");
	enterRoomnum();
	printf("Enter Name\n");
	enterDataStrings(g.name);
	enterGuestnights();
	enterGuestpersons();
	enterGuestphone();
	fopen_s(&fp, "guestInfo.txt", "a+");//a+ to prevent rewriting over lines


	fprintf(fp, "%d %s %d %d %s\n", g.roomNumber, (g.name), g.stay, g.persons, g.guestPhoneNumber); //Write to file in this format
	fclose(fp);//close file and save
	userContinue();//Ask user if they want to repeat
}

void employeeContinue(x)
{
	char option;
	printf("Continue? Y/N\n");
	getchar();
	option = getchar();//exit
	if (option == 'Y' || option == 'y')
	{
		system("cls");
		addEmployee(x);
	}
	else
	{
		system("cls");
		firstScreen(x);
	}
}

void printEmployeeInfo() {

	FILE *fp3;
	fopen_s(&fp3, "Employee.txt", "r");

	printf("\nCurrent IDs inuse\n");
	while (fscanf_s(fp3, "%d %s %s %s %s\n", &e.id, e.name, 30, e.occupation, 30, e.gender, 30, e.age, 30) != EOF)//While file format is this, it will print out room
	{
		printf("%d ", e.id);
	}
	fclose(fp3);

}
void enterEmployeeDataAge(char x[30])
{
	FILE *efData;
	int valid = 1;
	fopen_s(&efData, "Employee.txt", "r+");
	do
	{
		scanf_s("%s", x, 30);
		if (x < 0) //Input must be greater than 0
		{
			printf("Invalid age. Must be greater than 0.");
			valid = 0;
		}
		else
		{
			if (validationNum(x) == 1) {
				valid = 1;
			}

		}
	} while (valid != 1); //Loop until correct input is entered
	fclose(efData);
}
void deleteEmployee(x) { //Youtube video used as reference when creating code block https://www.youtube.com/watch?v=IftYEICtkOI
	int number;
	int valid = 1;
	FILE *fp, *fp2;

	fopen_s(&fp, "tempEmployee.txt", "w");//temp file to write into
	fopen_s(&fp2, "Employee.txt", "r");//Read from file

	if (fp2 == NULL)//File opening test
	{
		printf("Error opening file!\n");
	}
	printEmployeeInfo();//Print out IDs
	printf("\n\nEnter the ID\n");
	scanf_s("%d", &number);

	while (fscanf_s(fp2, "%d %s %s %s %s\n", &e.id, e.name, 30, e.occupation, 30, e.gender, 30, e.age, 30) != EOF)//Reads entire file
	{
		if (number == e.id)//Copys all content EXCEPT the input
		{
			valid = 0; //Valid is 0 when ID is found

		}
		if (number != e.id)//Copys all content of the file when ID is not present
		{

			valid = 1;
			fprintf(fp, "%d %s %s %s %s\n", e.id, e.name, e.occupation, e.gender, e.age);

		}
	}
	if (valid == 0)
	{
		printf("\nEntry has been deleted\n"); //
		fprintf(fp2, "%d %s %s %s %s\n", e.id, e.name, e.occupation, e.gender, e.age);//Prints out content except the removed ID
	}
	else
	{
		printf("Entry not found\n");
	}
	fclose(fp);
	fclose(fp2);
	remove("Employee.txt");//Delete  file
	rename("tempEmployee.txt", "Employee.txt");//rename new written file
	mainReturn();
} //Youtube video used as reference when creating code block https://www.youtube.com/watch?v=IftYEICtkOI

void enterEmployeeID()
{
	FILE *eFID;
	int input;
	int valid = 1;

	fopen_s(&eFID, "Employee.txt", "a");//open file to read/write
	if (eFID == 0)// If the file cannnot be opened
	{
		printf("Error opening file");
		exit(1);
	}
	do {
		printf("\n\nEnter ID\n");
		valid = 1;
		scanf_s("%d", &input);
		if (input >= 0)
		{
			while ((fscanf_s(eFID, "%d %s %s %s %s\n", &e.id, e.name, 30, e.occupation, 30, e.gender, 30, e.age, 30) != EOF))//Scan entire file
			{

				if (input == e.id) //If they equal, it is already in use. set valid to 0 and continue loop
				{
					printf("ID is already in use\n");
					valid = 0;
				}
				else
				{
					valid = 1; //Break out of loop
				}
			}
			e.id = input;//set the input to print value
		}
		else
		{
			printf("Enter a value greater than 0"); //Input must be greater than 0
		}
	} while (valid != 1);
	fclose(eFID);
}

void viewEmployeePrint() //Employeee Table Format
{
	printf("\n\t----------------------------------------------------------------------------------------------------------");
	printf("\t\tID ");
	printf("\t\tNAME ");
	printf("\t\tOCCUPATION");
	printf("\t\tGENDER ");
	printf("\t\t\tAGE");
	printf("\n\t----------------------------------------------------------------------------------------------------------");
}
void viewEmployee(int id, char name[30], char occupation[30], char gender[30], char age[30])
{
	FILE *eF;
	fopen_s(&eF, "Employee.txt", "r");
	if (eF == 0)
	{
		fopen_s(&eF, "Employee.txt", "w");
		fclose(eF);

		//printf("Error opening file.");
		//exit(1);
	}
	else
	{
		while (fscanf_s(eF, "%d %s %s %s %s\n", &id, name, 30, occupation, 30, gender, 30, age, 30) != EOF)
		{
			printf("\n\t%d", id);
			printf("\t\t%s", name, 30);
			printf("\t\t %s", occupation, 30);
			printf("\t\t\t%s", gender, 30);
			printf("\t\t\t%s", age, 30);
			printf("\n\t----------------------------------------------------------------------------------------------------------");
		}
		fclose(eF);
		mainReturn();
	}
}

void addEmployee()
{
	FILE *eF;
	printEmployeeInfo();
	enterEmployeeID();
	printf("Enter Name\n");
	enterDataStrings(e.name);
	printf("Enter Occupation\n");
	enterDataStrings(e.occupation);
	printf("Enter Gender\n");
	enterDataStrings((e.gender));
	printf("Enter Age\n");
	enterEmployeeDataAge(e.age);
	fopen_s(&eF, "Employee.txt", "a+");//Creates file and prevent being overwritten
	fprintf(eF, "%d %s %s %s %s\n", e.id, e.name, e.occupation, e.gender, e.age); //Write in this format
	fclose(eF);
	employeeContinue();//Ask if want to repeat
}

int firstScreen() //Selecton Screen
{
	int input;
	mainMenu();
	scanf_s("\n%d", &input); //User input for selection screen
	switch (input) {
	case 1:
		system("cls");//Clears the screen
		printf("You've chosen to book a room");
		bookRoom(input);
		break;
	case 2:
		system("cls");
		puts("You've chosen to delete a booking");
		deleteRoom(input);
		break;
	case 3:
		system("cls");
		printf("You've chosen to view bookings\n");
		viewGuestroomPrint();//Print table format
		viewGuestroom(g.roomNumber, g.name, g.stay, g.persons, g.guestPhoneNumber);
		break;
	case 4:
		system("cls");
		printf("You've chosen to add an employee");
		addEmployee();
		break;
	case 5:
		system("cls");
		printf("You've chosen to view employees");
		viewEmployeePrint();
		viewEmployee(e.id, e.name, e.occupation, e.gender, e.age);
		break;
	case 6:
		system("cls");
		printf("You've chosen to delete an employee entry");
		deleteEmployee(input);
	case 7:
		system("Cls");
		puts("You've chosen to exit.");
		printf("Good Bye.\n");
		exit(0);
	default:
		system("cls");
		printf("That is not a valid option. Try again\n");
		main(input);
	}
	return 0;
}

int mainMenu(i)
{
	printf("Welcome to the Hotel Mangement System...");
	printf("\nPick an option:\n");
	printf(" \nEnter 1 ----> Book a room");
	printf(" \nEnter 2 ----> Delete a room");
	printf(" \nEnter 3 ----> View booked rooms");
	printf(" \nEnter 4 ----> Add an employee");
	printf(" \nEnter 5 ----> View employees");
	printf(" \nEnter 6 ----> Delete an employee entry");
	printf(" \nEnter 7 ----> Exit \n");
	return 0;
}

int main()
{
	FILE *fp, *fp2;
	fopen_s(&fp, "guestInfo.txt", "a+");//Creates the file if it does not exist. Using a+ to not overwrite if they do exist.
	fclose(fp); //Close file
	fopen_s(&fp2, "Employee.txt", "a+");
	fclose(fp2);
	firstScreen(); //Calls the option screen

	return 0;
}
