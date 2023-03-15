#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <iomanip>
#include<conio.h>
using namespace std;
struct User
{
	string username;
	string password;
};
struct Car
{
	string brand;
	string plate;
	string color;
	int hours;
	double cost;
	string status;
};
string getPass(string prompt)
{
	cout << prompt;
	string password;
	char ch;
	while ((ch = _getch()) != 13)
	{
		if (ch == 8)
		{
			if (password.length() > 0)
			{
				cout << "\b \b";
				password.resize(password.length() - 1);
			}
		}
		else
		{
			password += ch;
			cout << "*";
		}

	}
	cout << "\n";
	return password;
}
void read_file_user_line(fstream& fuser, User& user)
{
	if (fuser.get() == EOF) return;
	fuser.seekg(-1, ios::cur);
	getline(fuser, user.username, ',');
	
	fuser.seekg(1, 1);
	getline(fuser, user.password);

}
void read_file_user(vector<User>& list)
{
	fstream fuser;
	fuser.open("user.txt", ios::in);
	while (fuser.eof() == 0)
	{
		User user;
		read_file_user_line(fuser,user);
		list.push_back(user);
	}
	fuser.close();
}
void signup( vector<User>& list)
{
	fstream fuser;
	fuser.open("user.txt", ios::in);
	read_file_user( list);
	User user;
	cout << "\n\n======================SIGN UP======================\n\n";
	
	do
	{
		printf("ENTER USERNAME: ");
		cin.ignore();
		getline(cin, user.username);
		user.password = getPass("ENTER PASSWORD: ");
		bool check = 1;
		for (int i = 0; i < list.size(); i++)
		{
			if (user.username == list[i].username)
			{
				cout << "This account is taken. Try again.\n";
				check = 0;
				break;
			}
			for (int j = 0; j < user.username.length(); j++)
			{
				if (user.username[j] == ' ')
				{
					cout << "This account is invalid. Try again.\n";
					check = 0;
					break;
				}
				if (check == 0) break;
			}
		}
		if (check) break;
	} while (1);
	list.insert(list.begin(), user);
	fuser.close();
	fuser.open("user.txt", ios::app);
	fuser << user.username << ", " << user.password<<"\n";
	fuser.close();
	cout << "======================================================";
}
void login( vector<User>& list, bool& check)
{
	fstream fuser;
	fuser.open("user.txt", ios::in);
	User user;
	read_file_user(list);
	int count = 0;
	check = 0;
	
	do {
		cout << "\n\n======================LOGIN======================\n\n";
		cout << "ENTER USERNAME: ";
		cin >> user.username;
		user.password = getPass("ENTER PASSWORD: ");
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].password == user.password && list[i].username == user.username)
			{
				cout << "Login Accepted!!\n";
				check = 1;
				break;
			}
		}
		if (check) break;
		else
		{
			cout << "Wrongg!!\n";
			system("pause");
			count++;
			system("cls");
		}
		if (count >= 3)
		{
			check = 0;
			
			return;
		}
	} while (1);
	fuser.close();
	cout << "======================================================";
}
void read_list_car_line(fstream& fcar, Car& car)
{
	fcar >> car.plate;
	fcar >> car.brand;
	fcar >> car.color;
	fcar >> car.hours;
	fcar >> car.cost;
	fcar >> car.status;
}
void read_list_car( vector<Car>& list_car)
{
	fstream fcar;
	fcar.open("car.txt", ios::in);
	while ((fcar.eof()) == 0)
	{
		Car car;
		read_list_car_line(fcar,car);
		list_car.push_back(car);
	}
	fcar.close();
}
void AddCar(vector<Car> &list_car)
{
	list_car.clear();
	fstream fcar;
	fcar.open("car.txt", ios::in);
	read_list_car( list_car);
	Car car;
	bool check = 1;
	int count = 0;
	do {
		cout << "\n\n======================ADDCAR======================\n\n";
		check = 1;
		cout << "Plate Number: ";
		cin >> car.plate;
		for (int i = 0; i < list_car.size(); i++)
		{
			if (car.plate == list_car[i].plate)
			{
				cout << "\nThis car exists. Try again\n";
				cout << "--------------------------------------------\n\n";
				system("pause");
				system("cls");
				check = 0;
				count++;
				break;
			}
		}
		if (count >= 3) return;
	} while (check == 0);

	cout << "Brand: ";
	cin >> car.brand;
	cout << "Color: ";
	cin >> car.color;
	string ch;
	int check1 = 0;
	while (1)
	{
		cout << "Cost: ";
		cin >> ch;
		int count = 0;
		int count1 = 0;
		for (int i = 0; i < ch.size(); i++)
		{
			if (ch[i] == 46)
			{
				count1++;
				count++;
			}
			if (ch[i] >= 48 && ch[i] <= 57) count++;
		}
		if (count1 != 1 && count1 != 0)
		{
			cout << "Cost must be a double number. Input again!\n\n";
			continue;
		}
		if (count == ch.size())
		{
			car.cost = stod(ch);
			break;
		}
		else
			check1++;
		if (check1 >= 3)
			return;
		else cout << "Cost must be a double number. Input again!\n\n";
	}
	car.hours = 0;
	car.status = "Available";
	fcar.close();
	fcar.open("car.txt", ios::app);
	fcar << car.plate << "\n" << car.brand << "\n" << car.color << "\n"<<car.hours <<"\n" <<car.cost << "\n"<<car.status<< "\n";
	fcar.close();
	cout << "\n\nADD CAR SUCCESSFULL\n\n";
	cout << "\nPRESS ANY KEY TO COMBACK MENU.\n\n\n\n\n";
}
void ViewCar( vector<Car>& list_car)
{
	list_car.clear();
	cout << "\n\n===================================VIEWCAR===================================\n\n";
	fstream fcar;
	fcar.open("car.txt", ios::in);
	if (fcar.fail())
		std::cout << "Failed to open this file!" << std::endl;
	read_list_car(list_car);
	cout<< setw(20) << left << "Plate Number"<< setw(15) << left << "Brand"<<setw(10) << left << "Color"<<setw(5) << right<<"Hours" << setw(15) << right<< "Cost" << setw(20) << right<<"Status\n";

	for (int i = 0; i < list_car.size(); i++)
	{
		if (list_car[i].plate == "") break;
		cout << setw(20) << left << list_car[i].plate << setw(15) << left << list_car[i].brand << setw(10) << left << list_car[i].color << setw(5) << right << list_car[i].hours << setw(15) << right << list_car[i].cost << setw(20) << right << list_car[i].status << "\n";
	}
	cout << "\nPRESS ANY KEY TO COMBACK MENU.\n\n\n\n\n";
	fcar.close();
}
void writefromvectortofile(vector<Car>& list_car)
{
	fstream fcar;
	fcar.open("car.txt", ios::out);
	for (int i = 0; i < list_car.size(); i++)
	{
		if (list_car[i].plate == "") break;
		fcar << list_car[i].plate;
		fcar << endl;
		fcar << list_car[i].brand;
		fcar << endl;
		fcar << list_car[i].color;
		fcar << endl;
		fcar << list_car[i].hours;
		fcar << endl;
		fcar << list_car[i].cost;
		fcar << endl;
		fcar << list_car[i].status;
		fcar << endl;
	}
	fcar.close();
}
void DeleteCar( vector<Car>& list_car)
{
	list_car.clear();
	string plate;
	fstream fcar;
	fcar.open("car.txt", ios::in || ios::out);
	read_list_car( list_car);
	cout << setw(20) << left << "Plate Number" << setw(15) << left << "Brand" << setw(10) << left << "Color" << setw(5) << right << "Hours" << setw(15) << right << "Cost" << setw(20) << right << "Status\n";

	for (int i = 0; i < list_car.size(); i++)
	{
		if (list_car[i].plate == "") break;
		if (list_car[i].status == "Rented") continue;
		cout << setw(20) << left << list_car[i].plate << setw(15) << left << list_car[i].brand << setw(10) << left << list_car[i].color << setw(5) << right << list_car[i].hours << setw(15) << right << list_car[i].cost << setw(20) << right << list_car[i].status << "\n";
	}


	cout << "                                       DELETE CAR                                       \n\n";
	bool check = 0;
	bool check1 = 0;
	int count = 0;
	do {
		cout << "Which Plate Car do you want to delete?\n";
		cout << "Your Answer: ";
		cin >> plate;
		for (int i = 0; i < list_car.size(); i++)
		{
			if (plate == list_car[i].plate) check = 1;
			if (plate == list_car[i].plate && list_car[i].status == "Available")
			{
				list_car.erase(list_car.begin() + i);
				break;
			}
			if (plate == list_car[i].plate && list_car[i].status == "Rented")
			{
				check1 = 1;
				break;
			}
		}
		if (check != 1)
		{
			cout << "The car doesn't exist.\nPlease input your answer again!\n";
			count++;
		}
		if (check1 == 1)
		{
			cout << "\nSorry. This car rented.\nPlease input your answer again!\n";
			count++;
		}
		if(count >= 3 ) return;
	} while (check != 1 || check1 == 1);
	writefromvectortofile(list_car);
	fcar.close();
	cout << "\nPRESS ANY KEY TO COMBACK MENU.\n\n\n\n\n";
}
void Rental( vector<Car>& list_car)
{
	list_car.clear();
	string plate;
	fstream fcar;
	fcar.open("car.txt", ios::in);
	read_list_car( list_car);
	cout << setw(20) << left << "Plate Number" << setw(15) << left << "Brand" << setw(10) << left << "Color" << setw(5) << right << "Hours" << setw(15) << right << "Cost" << setw(20) << right << "Status\n";

	for (int i = 0; i < list_car.size(); i++)
	{
		if (list_car[i].plate == "") break;
		if (list_car[i].status == "Rented") continue;
		cout << setw(20) << left << list_car[i].plate << setw(15) << left << list_car[i].brand << setw(10) << left << list_car[i].color << setw(5) << right << list_car[i].hours << setw(15) << right << list_car[i].cost << setw(20) << right << list_car[i].status << "\n";
	}
	char check = 0;
	bool check1 = 0;
	int count = 0;
	cout << "\n\n                                       RENTAL\n\n";
	do {
		cout << "Which Plate Car do you want to rent?\n";
		cout << "Your Answer: ";
		cin >> plate;
		for (int i = 0; i < list_car.size(); i++)
		{
			if (plate == list_car[i].plate && list_car[i].status == "Available")
			{
				int hrs;
				char check;
				string strhours;
				int check1 = 0;
				while (1)
				{
					cout << "How many hours do you want to rent?\n";
					cin >> strhours;
					int count = 0;
					for (int i = 0; i < strhours.size(); i++)
					{
						if (strhours[i] >= 48 && strhours[i] <= 57) count++;
					}
					if (count == strhours.size())
					{
						hrs = stoi(strhours);
						break;
					}
					else
						check1++;
					if (check1 >= 3)
						return;
					else cout << "Hours must be a integer number. Input again!\n\n";
				}
				cout << "\nYour bill: " << hrs * list_car[i].cost;
				cout << "\nDo you want to rent? \n";
				cout << "Your answer (Input 0 if you don't want to rent): ";
				cin >> check;
				if (check != '0')
				{
					list_car[i].hours = hrs;
					list_car[i].status = "Rented";
					cout << "\n RENTED SUCCESSFULL\n\n";
				}
				else break;
			}
			if (plate == list_car[i].plate)
			{
				check = 1;
			}
			if (plate == list_car[i].plate && list_car[i].status == "Rented")
			{
				check1 = 1;
				break;
			}
		}
		if (count >= 3) return;
		if (check != 1)
		{
			cout << "\nThe car doesn't exist.\nPlease input your answer again!\n";
			count++;
		}
		if (check1 == 1)
		{
			cout << "\nSorry. This car rented.\nPlease input your answer again!\n";
			count++;
		}
	} while (check != 1 || check1 == 1);
	writefromvectortofile(list_car);
	fcar.close();
	cout << "\nPRESS ANY KEY TO COMBACK MENU.\n\n\n\n\n";
}
void ReturnCar(vector<Car>& list_car)
{
	list_car.clear();
	string plate;
	fstream fcar;
	fcar.open("car.txt", ios::in);
	cout << setw(20) << left << "Plate Number" << setw(15) << left << "Brand" << setw(10) << left << "Color" << setw(5) << right << "Hours" << setw(15) << right << "Cost" << setw(20) << right << "Status\n";

	for (int i = 0; i < list_car.size(); i++)
	{
		if (list_car[i].plate == "") break;
		if (list_car[i].status == "Available") continue;
		cout << setw(20) << left << list_car[i].plate << setw(15) << left << list_car[i].brand << setw(10) << left << list_car[i].color << setw(5) << right << list_car[i].hours << setw(15) << right << list_car[i].cost << setw(20) << right << list_car[i].status << "\n";
	}
	cout << "\n\n======================RETURN CAR======================\n\n";
	bool check=0;
	int count = 0;
	do {
		cout << "Which Plate Car do you return?\n";
		cout << "Your Answer: ";
		cin >> plate;

		for (int i = 0; i < list_car.size(); i++)
		{
			if (plate == list_car[i].plate && list_car[i].status == "Rented")
			{
				check = 1;
				list_car[i].status = "Available";
				list_car[i].hours = 0;
				break;
			}
		}
		if (check != 1)
		{
			cout << "The car doesn't exsit.\nPlease input your answer again!\n";
			count++;
		}
		if (count >= 3) return;
	} while (check != 1 );
	writefromvectortofile( list_car);
	cout << "\nPRESS ANY KEY TO COMBACK MENU.\n\n\n\n\n";
}
void menulogin()
{
	cout << "\n======================MENU======================\n";
	cout << "\n\t1. Login.\n";
	cout << "\t2. Register.\n";
	cout << "\t0. Exit.\n\n";
	cout << "-------------------------------------------\n";
}
void menumain()
{
	system("cls");
	cout << "\n\n======================MAINMENU======================\n";
	cout << "\n\t1. AddCar.";
	cout << "\n\t2. ViewCar.";
	cout << "\n\t3. DeleteCar.";
	cout << "\n\t4. Rental.";
	cout << "\n\t5. ReturnCar.";
	cout << "\n\t0. Sign out.";
	cout << "\n\n----------------------------------------------------------\n";
}
void program()
{
	vector<Car> list_car;
	string choose;
	while (1)
	{
		menumain();
		cout << "\nWhat is your choice?\n";
		cout << "Your answer: ";
		cin >> choose;
		if (choose == "1")
		{
			system("cls");
			AddCar(list_car);
			cout << "\n";
			system("pause");
		}
		else if (choose == "2")
		{
			system("cls");
			ViewCar(list_car);
			system("pause");
			cout << "\n";
		}
		else if (choose == "3")
		{
			system("cls");
			DeleteCar(list_car);
			cout << "\n";
			system("pause");
		}
		else if (choose == "4")
		{
			system("cls");
			Rental(list_car);
			cout << "\n";
			system("pause");
		}
		else if (choose == "5")
		{
			system("cls");
			ReturnCar(list_car);
			cout << "\n";
			system("pause");
		}
		else if (choose == "0")
		{
			return;
		}
		else
		{
			cout << "The choice is invalid.\n";
			system("pause");
			cout << "\n";
		}
	}
}
void loginprogram()
{
	vector<User> list;
	vector<Car> list_car;
	string choose;
	bool checkregister = 0;
	do
	{
		menulogin();
		cout << "\nWhat is your choice?\n";
		cout << "Your answer: ";
		cin >> choose;
		if (choose=="1")
		{
			system("cls");
			login(list,checkregister);
			cout << "\n";
			
			if (checkregister == 0)
			{
				system("cls");
				cout << "Do you want to register?\nIf you want, press 2.\n";
			}
			else system("pause");
		}
		else if(choose=="2")
		{
			system("cls");
			signup(list);
			cout << "\n";
			system("pause");
			
		}
		else if (choose == "0")
		{
			exit(0);
		}
		else
		{
			cout << "The choice is invalid.\n";
			system("pause");
			system("cls");
		}
		if (choose == "2" || checkregister == 1)
		{
			program();
			system("cls");
		}
	} while (1);
}
int main()
{
	loginprogram();
	return 0;
}