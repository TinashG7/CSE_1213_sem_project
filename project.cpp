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
    cout <<"Error: Admin database could not open." <<endl;
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

// Load meters function
void loadMeters(vector<Meter>& meter){
  ifstream file("metersDB.txt");

  if (!file){
    cout <<"Error: Metersdatabase could not open." <<endl;
  }

  Meter temp;
  while (file >>temp.meterNo >>temp.meterPword){
      meter.push_back(temp); // add data to the admin vector
      break;
  }

  file.close();
}

// Register new consumer
void registerConsumer(vector<Meter>& meter){
  /*
  - Meter number
  - Password for new metre/consumer
  */
 loadMeters(meter);
  string newMeterNo, newMeterPword;
  float balance=50.0;
  bool isUnique=false;

  while (!isUnique){
    cout <<"Enter the meter number for the new consumer: " <<endl;
    cin >>newMeterNo;

    isUnique=true;

    for (int i = 0; i < meter.size(); i++){
      if (meter[i].meterNo == newMeterNo){
        isUnique=false;
        cout <<"Meter number already exists. Try again." <<endl;
        break;
      }
    }

  }

  // do {
  //   cout <<"Enter the meter number for the new consumer: " <<endl;
  //   cin >>newMeterNo;

  //   if (meter){
      
  //   }

  // } while (condition);

  // cout <<"Enter the meter number for the new consumer: " <<endl;
  // cin >>newMeterNo;

  do {
    cout <<"Enter the password for the new consumer: " <<endl;
    cin >>newMeterPword;
    if (newMeterPword.size()<6 || newMeterPword.size()>20){
    cout <<"Invalid password. Password should be between 6 and 20 characters long." <<endl;
    }
  } while (newMeterPword.size()<6 || newMeterPword.size()>20);
  
  ofstream file("metersDB.txt", ios::app);
  if(!file){
    cout <<"Error: The meters database did not open" <<endl;
  }

  Meter temp;
  temp.meterNo = newMeterNo;
  temp.meterPword = newMeterPword;
  meter.push_back(temp);
  file <<newMeterNo <<" " <<newMeterPword <<endl;
  
  file.close();
}

//Top-up Energy (Deposit)


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