#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//array sizes
const int DOC_NUM = 10;
const int PATIENT_NUM=10;
const int DATE_NUM = 10;
const int APPOINT_NUM = 10;


//structure types
struct date {
	int day;
	int month;
	int year;
}dates[DATE_NUM];
struct patient {
	string id;
	string username;
	string password;
	string name;
	int age;
} infoPatients[PATIENT_NUM];
struct doc {
	string id;
	string username;
	string password;
	string name;
} infoDocs[DOC_NUM];
struct appoint {
	patient appointPatient;
	doc appointDoc;
	date appointDate;
	string timeSlot;
}infoAppoints[APPOINT_NUM];

//global variables
int lastPatient = 1;
int lastDoc = 1;
int lastAppoint = 1;
string timeSlots[5] = { "09:00 - 10:00","10:00 - 11:00","11:00 - 12:00","12:00 - 01:00","01:00 - 02:00" };


//gen functions 
void chooseDate(appoint infoAppoints[], int i);
void display(appoint appointment);
void display(date someDate);

//patient functions
int patientLogin();
void patientReg();
void editPatientInfo(patient infoPatients[], int patientIndex);
void displayPatientMenu(int i);
void makeAppoint(appoint infoAppoints[], doc infoDocs[], int patientIndex);
void patientViewAppoints(appoint infoAppoints[], patient infoPatients[], int patientIndex);
void editAppoint(appoint infoAppoints[], int patientIndex);
void cancelAppoint(appoint infoAppoints[], int patientIndex);

//doctor functions
int docLogin();
void docReg();
void displayDocMenu(int docIndex);
void editDocInfo(doc infoDocs[], int docIndex);
void docViewAppoints(appoint infoAppoints[], doc infoDocs[], int docIndex);
void addTime();
void removeTime();

int main() //start of main
{
	menu1:
	cout << "\n**************************************************\n\n"
		<< "************** Welcome to E7gezly **************\n"
		<< "\n**************************************************\n\n";

	int status;

	menu2: //main menu
do {

	cout << "Are you a patient or doctor?\n\n"
		<< "1 \t Patient \n"
		<< "2 \t Doctor\n\n"
		<< "Selection: ";

	int userMode;
	cin >> userMode;
	int selection;


	switch (userMode)
	{
	case 1: //patient
		cout
			<< "\n"
			<< "1 \t Login \n"
			<< "2 \t Register\n"
			<< "3 \t Previous menu\n\n"//incomplete 
			<< "Selection: ";

		cin >> selection;

		switch (selection)
		{
		case 1: //login
			int patientIndex;
			patientIndex = patientLogin();
			if (patientIndex != -1)
			{
				displayPatientMenu(patientIndex);
				goto menu1;
			}
			else
				goto menu2;
			break;
		case 2: //register
			patientReg();
			break;
		case 3:
			goto menu2;
			break;
		default:
			break;
		}
		break;

	case 2: //doctor
		cout
			<< "\n"
			<< "1 \t Login \n"
			<< "2 \t Register\n"
			<< "3 \t Previos menu\n\n"//incomplete 
			<< "Selection: ";

		cin >> selection;

		switch (selection)
		{
		case 1: //doc login

			int docIndex;
			docIndex = docLogin();
			if (docIndex != -1)
			{
				displayDocMenu(docIndex);
			}
			else
				goto menu2;
			break;
		case 2:
			docReg();
			break;
		case 3:
			goto menu2;
		default:
			break;
		}
		break;

	default:
		cout << "Please enter a valid choice!";
	}
	//exit login menu
	cout << "\n**************************************************\n\n"
		<< "1 \t Main menu \n"
		<< "2 \t Exit \n\n"
		<< "Selection: ";

	cin >> status;

} while (status != 2);
//exit main menu
cout << "\n******** Thank you for using E7gezly! ********\n";

return 0;
} // end of main

//gen function declarations
// 
void chooseDate(appoint infoAppoints[], int i)
{
cout << "Please enter date: \n"
	 <<"Day: ";
cin >> infoAppoints[i].appointDate.day;
cout << "Month: ";
cin >> infoAppoints[i].appointDate.month;
cout << "Year: ";
cin >> infoAppoints[i].appointDate.year;
}
void chooseTimeSLot(appoint infoAppoints[], int i)
{
	cout << "Select time: \n";
	for (int i = 0; i < 5; i++) 
		cout << i + 1 << "\t" << timeSlots[i] << "\n";
	cout << "Selection: ";
}

void display(date someDate)
{
	cout << someDate.day << "/" << someDate.month << "/" << someDate.year << "\n";

}
void display(appoint appointment)
{
	cout << "Patient:" << appointment.appointPatient.name <<"\n";
	cout << "Doctor:" << appointment.appointDoc.name << "\n";
	cout << "Date:";
	display(appointment.appointDate);
	cout << "Time: " << appointment.timeSlot <<"\n";
}



//patient fucntion declarations
void patientReg()
{
	cout << "Enter name: ";
	cin >> infoPatients[lastPatient].name;
	cout << "Enter age: ";
	cin >> infoPatients[lastPatient].age;
	cout << "Enter username: \n";
	cin >> infoPatients[lastPatient].username;
	cout << "Enter password: ";
	cin >> infoPatients[lastPatient].password;


	lastPatient++;
}
int patientLogin()
{
	string username, password;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	for (int i = 1; i < PATIENT_NUM; i++)
	{
		if (username == infoPatients[i].username)
		{
			if (password == infoPatients[i].password)
			{
				cout << "Hello, " << infoPatients[i].name << "! \n\n";
				return i;
			}
		}

	}
	cout << "\n Incorrect username or password! Please try again. \n\n";
	return -1;



}
void displayPatientMenu(int patientIndex)
{
	char choice = 'n';
	do
	{
		cout << "\n**************************************************\n\n";
		cout << "What would you like to do?\n\n"
			<< "1 \t Make an appointment \n"
			<< "2 \t View my appointments \n"
			<< "3 \t Edit an appointment\n"
			<< "4 \t Cancel an appointment\n"
			<< "5 \t Edit personal info\n\n"
			<< "6 \t Logout\n\n"
			<< "Selection: ";
		int selection;
		cin >> selection;
		switch (selection)
		{
		case 1: //make an appointment
			makeAppoint(infoAppoints, infoDocs, patientIndex);
			break;
		case 2: //view  my appointments
			patientViewAppoints(infoAppoints, infoPatients, patientIndex);
			break;
		case 3: //edit  an appointment
			editAppoint(infoAppoints, patientIndex);
			break;
		case 4: // cancel an appointment
			cancelAppoint(infoAppoints, patientIndex);
			break;
		case 5: // edit personal info
			editPatientInfo(infoPatients, patientIndex);
			break;
		case 6: // logout
			cout << "Are you sure you want to log out? (y/n)";
			cin >> choice;
			break;
		default:
			break;
		}

	} while (choice != 'y' &&  choice != 'Y');
}
void editPatientInfo(patient infoPatients[], int patientIndex) // F1
{
	void editAppoint(appoint infoAppoints[], int patientIndex)
{
	int selection;
	display(infoAppoints[patientIndex]); // dispalay before editing
	cout << "Edit: \n"
		<< "1. Doctor \n"
		<< "2. Date \n"
		<< "3. Time \n";
	cin >> selection;
	switch (selection) {
	case 1:
		cout << "Select doctor: \n";
		for (int i = 1; i < lastDoc; i++)
		{
			cout << i << "\t" << infoDocs[i].name << "\n";
		}
		infoAppoints[patientIndex].appointPatient = infoPatients[patientIndex];
		infoAppoints[patientIndex].appointDoc = infoDocs[selection - 1];
		break;

	case 2:
		// working on it
		break;
	case 3:
		cout << "Select time: \n";
		for (int i = 0; i < 5; i++)
		{
			cout << i + 1 << "\t" << timeSlots[i] << "\n";
		}
		cout << "Selection: ";
		cin >> selection;
		selection--; // array things

		infoAppoints[patientIndex].timeSlot = timeSlots[selection];
		break;

		display(infoAppoints[patientIndex]); //display after editing
	}
}
}
void makeAppoint(appoint infoAppoints[], doc infoDocs[], int patientIndex)
{
	int selection;
	cout << "Select doctor: \n";
	for (int i = 1; i < lastDoc; i++)
	{
		cout << i << "\t" << infoDocs[i].name << "\n";
	}

	cout << "\nSelection: ";
	cin >> selection;

	int i = lastAppoint;
	infoAppoints[i].appointPatient = infoPatients[patientIndex];
	infoAppoints[i].appointDoc = infoDocs[selection - 1];
	chooseDate(infoAppoints, i);

	cout << "Select time: \n";
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << "\t" << timeSlots[i] << "\n";
	}
	cout << "Selection: ";
	cin >> selection;
	selection--;

	infoAppoints[i].timeSlot = timeSlots[selection];
	lastAppoint++;

}
void patientViewAppoints(appoint infoAppoints[], patient infoPatients[], int patientIndex)
{
	for(int i=1; i<=lastAppoint; i++)
	{ 
		if (infoAppoints[i].appointPatient.id == infoPatients[patientIndex].id)
		{
			cout << "#" << i << "\n";
			display(infoAppoints[i]);
			cout << "\n";
		}
	}
}
void editAppoint(appoint infoAppoints[], int patientIndex) //F4
{

} 

void cancelAppoint(appoint infoAppoints[], int patientIndex) //F5
{
}


//doc function declarations
void docReg()
{

	cout << "Enter name: ";
	cin >> infoDocs[lastDoc].name;

	cout << "Enter username: \n";
	cin >> infoDocs[lastDoc].username;

	cout << "Enter password: ";
	cin >> infoDocs[lastDoc].password;

	lastDoc++;
}
int docLogin()
{
	string username, password;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	for (int i=0; i<DOC_NUM; i++)
	{
		if (username == infoDocs[i].username)
		{
			if (password == infoDocs[i].password)
				cout << "Hello, " << infoDocs[i].name <<"! \n\n";
				return i;
		}

	}
	cout << "\n Incorrect username or password! Please try again. \n\n";
	return -1;
}
void displayDocMenu(int docIndex)
{
	char choice = 'n';
	do
	{
		cout << "\n**************************************************\n\n";
		cout << "What would you like to do?\n\n"
			<< "1 \t Add available time \n"
			<< "2 \t Remove available time \n"
			<< "3 \t View patients with appointments\n"
			<< "4 \t Edit personal info\n"
			<< "5 \t Logout\n\n"
			<< "Selection: ";
		int selection;
		cin >> selection;
		switch (selection)
		{
		case 1: //Add available time
			addTime();
			break;
		case 2: //Remove available time
			removeTime();
			break;
		case 3: //View patients with appointments
			docViewAppoints(infoAppoints, infoDocs, docIndex);
			break;
		case 4: // Edit personal info
			editDocInfo(infoDocs, docIndex);
			break;
		case 5: // logout
			cout << "Are you sure you want to log out? (y/n)";
			cin >> choice;
			break;
		default:
			break;
		}

	} while (choice != 'y' && choice != 'Y');
}

void editDocInfo(doc infoDocs[], int docIndex) //F2
{

}

void docViewAppoints(appoint infoAppoints[], doc infoDocs[], int docIndex) //F3
{

}
void addTime() //F6
{

}
void removeTime() //F7
{

}

