#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/*
  TO DO:
  - Create a function for logging in for the admin
*/

struct Admin{
  string adminUsername;
  string adminPword;
};

struct Meter{
  string meterNo;
  string meterPword;
  float balance;
};

void adminLogin(vector<Admin>& admin){
  /* TO DO
  - Enter their username
  - Enter their password
  - verify that the username matches the pword
  - verify that the username and the pword match what is in the txt file
  */

  string admin_Username, admin_Password;

  cout <<"Enter your username:" <<endl;
  cin >>admin_Username;
  cout <<"Enter your password:" <<endl;
  cin >>admin_Password;

  bool found=false;
  for (int i = 0; i < admin.size(); i++){
      if (admin[i].adminUsername == admin_Username && admin[i].adminPword == admin_Password){
        found=true;
        cout <<"Login successful." <<endl;
        break;
      } else{
        cout <<"Incorrect username or password. Try again." <<endl;
      }
  }

  // if(!found){
  //   cout <<"Incorrect username or password. Try again." <<endl;
  // }

}

void loadAdmin(vector<Admin>& admin){
  ifstream file("admin.txt");

  if (!file){
    cout <<"Error: admin.txt could not open." <<endl;
  }

  Admin temp;
  while (file >>temp.adminUsername >>temp.adminPword){
      admin.push_back(temp); // add data to the admin vector
      break;
  }

  file.close();
}

void consumerLogin(){

}

// Register new consumer
void registerConsumer(vector<Meter>& meter){
  /*
  - Meter number
  - Password for new metre/consumer
  */
  string newMeterNo, newMeterPword;
  float balance=50.0;
  cout <<"Enter the meter number for the new consumer: " <<endl;
  cin >>newMeterNo;
  cout <<"Enter the password for the new consumer: " <<endl;
  cin >>newMeterPword;
  
  ofstream file("metersDB.txt");
  if(!file){
    cout <<"Error: The meters database did not open" <<endl;
  }

  Meter temp;
  temp.meterNo = newMeterNo;
  temp.meterPword = newMeterPword;
  meter.push_back(temp);
  file <<newMeterNo <<" " <<newMeterPword;
  
  file.close();
}

int main() {
  vector<Admin> admin;
  vector<Meter> meter;
  loadAdmin(admin);

  registerConsumer(meter);
  
  /*
  int choice;
  cout <<"Welcome! Login as:" <<endl;
  cout <<"1. Admin" <<endl;
  cout <<"2. Consumer" <<endl;
  cout <<"3. Exit" <<endl;
  cin >>choice;

  switch (choice){
      case 1:
        adminLogin(admin);
        break;
      case 2:
        //consumerLogin(consumer);
        break;
      case 3:
          return 0;
      default:
        cout <<"Invalid option. Try again!" <<endl;
          break;
  }
          */

  return 0;
}