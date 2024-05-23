#include<iostream>
#include<string>
#include<fstream>
#include<cstring> // Include this for string comparison using strcmp
#include <conio.h>

using namespace std;

class medical_equipment {
public:
    string name; // Change 'ename' to 'name'
    int eid;
    int qty;

    void display();
    void add();
    bool checkAvailability(const string &equipmentName, int requestedQuantity, int id);
    void updateEquipmentFile(const string &equipmentName, int requestedQuantity);
    void accept();
    
    } m1;

class doctor {
public:
    string name;
    char password[20];
    string eqname; // Consider removing this as 'eqname' is also part of medical_equipment class
    int eid;
    int qty;

    // Functions
    void doctorfn();
    void new_user();
    void validate();
    void display();
    void request(string un);

} d1;

class admin {
public:
    string userid;
    string password;

    void input();
    void show_request();

} a1;

						// start of doctors class fn



void doctor :: doctorfn () {

	int choise ;
	do{ 
        cout << "======================================\n";
        cout << "\tDoctor's menu\n";
        cout << "======================================\n";
		cout << "1. Login\n";
		cout << "2. Sign up\n";
		cout << "3.  Exit\n";
		cout << "   Enter your choise \n";
		cin >> choise;
		switch(choise){
			case 1:
				d1.validate();
				break;
				// login ka validation hoga tab aage badhega

			case 2:
				d1.new_user();
				break;
				// naya user add ho rha h then back to main menu
			case 3:
				cout << "Exiting...\n";
				break;
			default :
				cout << "Invalid choice";
				break;

		}
	}while (choise !=3);
}


void doctor::new_user() {
    int i=0;
    char ch;
    cout << "  Sign Up as a doctor\n";
    cout << "--------------------------------------\n";
    cout << "Enter your User Name \n";
    cin >> name; // Use cin instead of cin.getline for a single word input
    cin.ignore(); // Clear the input buffer
    cout << "Set a password for you\n";
     while ((ch = _getch()) != 13) {
        if (ch == 8 && i >0 ){
            cout << "\b \b";
            i--;
        
        }
        else {
        password[i] = ch;
        i++;
        cout << '*';
    }}

    password[i] = '\0';
    cout << "\n";
    cout << "New Doctor Added\n";
   
    ofstream out("doctor.txt", ios::app);
    out << name << "\t" << password << "\n"; // Changed delimiter from "/t" to "\t"
}

void doctor::validate() {
    int two,i=0;
    char ch;
    string enteredUsername;
    char enteredPassword[20];
    cout << "--------------------------------\n";
    cout << "Login as doctor\n";
    cout << "--------------------------------\n";
    cout << "Enter the user id\n";
    cin >> enteredUsername;
    cout << "Enter the password\n";
     while ((ch = _getch()) != 13) {
        if (ch == 8 && i >0){
            cout << "\b \b";
            i--;
        }
        else {
        enteredPassword[i] = ch;
        i++;
        cout << '*';
    }}

    enteredPassword[i] = '\0';
    cout << "\n";

    ifstream in("doctor.txt");
    string un, pw;
    bool loginSuccessful = false;

    while (in >> un >> pw) { // Read username and password separately from each line
        if (un == enteredUsername && pw == enteredPassword) {
            loginSuccessful = true;
            cout << "\nLogin successful..\n\n";
            do {
                cout << "   Doctor's Menu\n";
                cout << "----------------------\n";
                cout << "1. Request an equipment\n";
                cout << "2. Display list of equipments \n";
                cout << "3.Exit\n";
                cout << "Enter your choice: ";
                cin >> two;
                cout << "\n";

                switch (two) {
                    case 1:
                        request(un);
                        break;
                    case 2:
                        display(); // Function call of another class in the same class
                        break;
                    case 3:
                        cout << "Exiting\n";
                        break;
                    default:
                        cout << "Invalid input\n";
                        break;
                }
            } while (two != 3);
            break;
        }
    }

    if (!loginSuccessful) {
        cout << "\nWrong info\n";
    }
}



void doctor :: request(string un){

	cout << "You can now raise a request for the equipment\n ";
	cout << "--------------------------------------------------\n";
	cout << "Equipment id\n";
	cin >> eid;// kia hme iske lea ek alag fie banani chahiye jisme hm sari requests save kareinge
	cout << "Name of the equipment\n";
	cin >> eqname;
	cout << "Enter the Quantity\n";
	cin >> qty;
    

	ofstream out("request.txt",ios::app);
	out << un << "\t ";
	out << eid << "\t ";
	out << eqname << "\t ";
	out << qty << endl;
    cout << "Request send to admin\n";

}

// yaha changes h 

void doctor::display() {
    ifstream in("equipment.txt");
    string line;
    while (getline(in, line)) { // Read line by line from the file
        cout << line << endl;
    }
    cout << "---------------------------------------\n\n";
    in.close();
}






			// End of doctor class
 


			// start of medical equipmemnt class


void medical_equipment::display() {
    ifstream in("equipment.txt");
    string str1, str2, str3;
    cout << "\n\n-----------------------------------------------\n";
    cout << "    Displaying Equipment list\n";
    cout << "-------------------------------------------------\n";
    cout << "ID    Name        Qty\n";
    while (in >> str1 >> str2 >> str3) {
        cout << "\n";
        cout << str1 << " ";
        cout << str2 << " ";
        cout << str3 << " \n";
    }
    in.close();
}

void medical_equipment::add() {
    cout << "\n  Enter the details of equipment\n ";
    cout << "--------------------------------------------\n";
    cout << "Enter equipment id" << endl;
    cin >> eid;
    cin.ignore(); // Clear the input buffer
    cout << "Enter equipment name" << endl;
    getline(cin, name);
    cout << "Enter the quantity" << endl;
    cin >> qty;

    ifstream in("equipment.txt");
    ofstream out("equipment_temp.txt", ios::app); // Temporary file to store modified data

    bool itemExists = false;
     int existingID;
        string existingName;
        int existingQty;
    
    while (in >> existingID >> existingName >> existingQty) {
       
            if (existingID == eid && existingName == name) {
                // Item with the same ID and name exists, increase the quantity
                existingQty += qty;
                out << existingID << "\t" << existingName << "\t" << existingQty << endl;
                itemExists = true;
            } else {
                // Copy the existing item to the temporary file
                out << existingID << "\t" << existingName << "\t" << existingQty << endl;
            }
       
    }

    in.close();
    out.close();

    // Replace the original file with the temporary file
    remove("equipment.txt");
    rename("equipment_temp.txt", "equipment.txt");

    if (!itemExists) {
        // If the item doesn't exist, add it to the end of the file
        ofstream appendOut("equipment.txt", ios::app);
        appendOut << eid << "\t" << name << "\t" << qty << endl;
    }

    cout << "\nEquipment Added Successfully...\n";
    cout << "----------------------------------------------\n";
}

bool medical_equipment:: checkAvailability(const string& equipmentName, int requestedQuantity, int id ) {
    ifstream equipmentFile("equipment.txt");

    int existingID;
    string existingName;
    int existingQty;


    while (equipmentFile >> existingID >> existingName >> existingQty) {
        if ( existingID == id, existingName == equipmentName && existingQty >= requestedQuantity) {
            equipmentFile.close();
            return true; // Equipment is available in sufficient quantity
        }
    }

    equipmentFile.close();
    return false; // Equipment not available or quantity is insufficient
}

void medical_equipment::updateEquipmentFile(const string& equipmentName, int requestedQuantity) {
    ifstream inFile("equipment.txt");
    ofstream outFile("equipment_temp.txt", ios::app);

    int existingID;
    string existingName;
    int existingQty;

    while (inFile >> existingID >> existingName >> existingQty) {
        if (existingName == equipmentName) {
            // Reduce the quantity in the equipment file
            existingQty -= requestedQuantity;
        }

        // Copy the existing item to the temporary file
        outFile << existingID << "\t" << existingName << "\t" << existingQty << endl;
    }

    inFile.close();
    outFile.close();

    // Replace the original file with the temporary file
    remove("equipment.txt");
    rename("equipment_temp.txt", "equipment.txt");
}
void medical_equipment::accept() {
    //a1.show_request();
    
    string dname,rname,id,name;
    int qty;
    cout << "\n\nEnter the Doctor's Name : " ;
    cin >> dname;

    cout << "\n\n------------------------------------------------\n";
    cout << "Showing requests received by Doctor  " << dname << endl;
    cout << "-------------------------------------------------\n";

    ifstream in("request.txt");

    cout << "ID     Name      Qty\n";

    // Read and display each character from the file
    while (in >> rname >> id >> name >> qty) {
        if (rname == dname){
            cout << id  << "\t" << name << "\t" << qty << endl;
        }
    }

    in.close();
	
    int eid;
    cout << "\n\n------------------------------------------------\n";
    cout << "Accepting Requests\n";
    cout << "-------------------------------------------------\n";
    cout << "Enter the Equipment id to Accept\n";
    cin >> eid;

    // Read the requests from the file
    ifstream requestFile("request.txt");
    ofstream assignedFile("assigned_requests.txt", ios::app);

    int requestID;
    string doctorName;
    string equipmentName;
    int quantity;

    while (requestFile >> doctorName >> requestID >> equipmentName >> quantity) {
        // Display the request details
        if (doctorName==dname && requestID == eid){
        cout << "Request ID: " << requestID << "\n";
        cout << "Doctor Name: " << doctorName << "\n";
        cout << "Equipment Name: " << equipmentName << "\n";
        cout << "Requested Quantity: " << quantity << "\n";

        // Assume you have a function to check if the equipment is available in sufficient quantity
        // For example, checkAvailability(equipmentName, quantity)
        // If available, update the equipment file and mark the request as assigned
        if (checkAvailability( equipmentName, quantity, requestID)) {
            // Reduce the quantity in the equipment file
            updateEquipmentFile(equipmentName, quantity);



            cout << "Request Accepted\n";

            // yaha hm chahte h ki jo jo req full fill ho jae wo delet ho jae 
        } else {
        
            cout << " Request not accepted.\n";
        }

        cout << "-------------------------------------------------\n";
    }
    else {
        assignedFile << doctorName << "\t" << requestID << "\t" << equipmentName << "\t" << quantity << endl;

    }
    }
    requestFile.close();
    assignedFile.close();
    remove("request.txt");
    rename("assigned_requests.txt", "request.txt");
    // Close the files

}

			// End of medical_equipment class



			// start of admin class

void admin :: input(){

	int choice,i = 0;
    char ch;
    cout << "----------------------------\n";
    cout << "Admin login\n";
    cout << "----------------------------\n";
	cout << "Enter user id \n";
	cin >> userid;// how to get input of string in character array
	cin.sync();
	cout << "Enter the password\n" ;
     while ((ch = _getch()) != 13) {
        if (ch == 8 && i >0){
            cout << "\b \b";
            i--;
        }
        else{
        password[i] = ch;
        i++;
        cout << '*';
    }
}

    password[i] = '\0';

	//cin >> password;
	if (strcmp(userid.c_str(),"shubham")==0 && strcmp(password.c_str(),"agrawal")==0) {
		cout << "\nlogin sucessfull..\n";
		do{ 
            cout << "\n-----------------------------\n";
			cout << " Admin menu \n";
            cout << "-----------------------------\n";
			cout << " 1. Add equipment\n ";
			cout << "2. Display list\n ";
			cout << "3. Show Request\n" ;
			cout << " 4. Exit\n";
			cout << "Enter your choice : ";
			cin >> choice;

			switch (choice){
			case 1:
				m1.add();
				// add fn call hoga
				break;

			case 2:
				m1.display();
				// display fn call hoga
				break ;
			case 3:
				m1.accept();
				// show req fn call hoga
				break ;
			case 4:
				cout << "Exiting...\n\n";
				break;
			default :
				cout << "Invalid input\n";
			}
		}while(choice!=4);
	}
	else {
		cout << "\nwrong password\n";
    }

}


void admin :: show_request(){
	
	
    string dname,rname,id,name;
    int qty;
    cout << "\n\nEnter the Doctor's Name : " ;
    cin >> dname;

    cout << "\n\n------------------------------------------------\n";
    cout << "Showing requests received by Doctor Mrs." << dname << endl;
    cout << "-------------------------------------------------\n";

    ifstream in("request.txt");

    cout << "ID     Name      Qty\n";

    // Read and display each character from the file
    while (in >> rname >> id >> name >> qty) {
        if (rname == dname){
            cout << id  << "\t" << name << "\t" << qty << endl;
        }
    }

    in.close();
	
}



		// end of admin class




int main (){
	int one;

	
	do{ 
        cout << "========================================\n";
        cout << "Main Menu\n";
        cout << "========================================\n";
		cout << "\n\n1. Admin " << endl;
		cout << "2. Doctor" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choise: ";
		cin >> one;


		switch (one){
			case 1:
				a1.input();
				break;	// yaha admin ke functions call honge

			case 2:
				d1.doctorfn();
				break;
				// yaha doctor ke functions
			case 3:
				cout << "Exiting... \n";
				break;
			default :
				cout << "wrong input" << endl;
				break;
		}
	}while (one != 3);
	return 0;
}
