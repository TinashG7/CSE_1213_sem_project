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

void loadAdmin(vector<Admin>& admin){
  ifstream file("admin.txt");

  if (!file){
    cout <<"Error: Admin database could not open." <<endl;
  }

  Admin temp;
  while (file >>temp.adminUsername >>temp.adminPword){
      admin.push_back(temp); // add data to the admin vector
      //break;
  }

  file.close();
}

// Load meters function
void loadMeters(vector<Meter>& meter){
  ifstream file("metersDB.txt");

  if (!file){
    cout <<"Error: Metersdatabase could not open." <<endl;
    return;
  }

  Meter temp;
  while (file >>temp.meterNo >>temp.meterPword >>temp.balance){
      meter.push_back(temp); // add data to the meter vector
      //break;
  }

  file.close();
}

// Register new consumer
void registerConsumer(vector<Meter>& meter){
  /*
  - Meter number
  - Password for new metre/consumer
  */
 //loadMeters(meter);
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
  file <<newMeterNo <<" " <<newMeterPword <<" " <<balance <<endl;
  
  file.close();
}

// Save meters
void saveMeters(vector<Meter>& meter){
    ofstream file("metersDB.txt");
    if (!file){
        cout << "Error: Could not open meters database." << endl;
        return;
    }
    for (int i = 0; i < meter.size(); i++){
        file << meter[i].meterNo << " " << meter[i].meterPword << " " << meter[i].balance << endl;
    }
    file.close();
}

//Top-up Energy (Deposit)
void topUpEnergy(vector<Meter>& meter){
  /**
  - Admin to input top up units
  - metersdb.txt to update balance
  */
  
  float topUpUnits;
  string meterNo;
  //int index = -1;

  cout <<"Enter the meter number you would like to top up to:" <<endl;
  cin >>meterNo;

  // Ensure the entered meter number actually exists
  bool found=false;
  int meterIndex=-1;

  for (int i = 0; i < meter.size(); i++){
    if (meter[i].meterNo==meterNo){
      found=true;
      meterIndex=i;
      break;
    }
  }

  if (!found){
    cout <<"Meter number does not exist. Try again." <<endl;
    return;
  }

  cout <<"Enter the number of units to top up:" <<endl;
  cin >>topUpUnits;

  // Add units to balance
meter[meterIndex].balance += topUpUnits;
saveMeters(meter);
  // fstream file("metersDB.txt");
  //       file <<meter[meterIndex].meterNo <<" " <<meter[meterIndex].meterPword <<" " <<meter[meterIndex].balance <<endl;

  cout << "Top-up successful. New balance: " << meter[meterIndex].balance << " kWh" << endl;
}

// Function to view all meters
void viewMeters(vector<Meter>& meter){
  // load all the meters from the meters DB
  //loadMeters(meter);

  // display all the meters
  cout <<"These are all the meters that are registered, their passwords and their balance" <<endl;
  for (int i = 0; i < meter.size(); i++){
    cout <<meter[i].meterNo <<" " <<meter[i].meterPword <<" " <<meter[i].balance <<endl;
  }
} 

// Function to change admin pword
void changeAdminPword(vector<Admin>& admin, string loggedInUsername){
  string oldPword, newPword, currentPword;

  // Load the logged-in username from the DB to the vector 
  int adminIndex=-1;
  for (int i = 0; i < admin.size(); i++){
    if (admin[i].adminUsername == loggedInUsername){
      adminIndex=i;
      break;
    }
  }

  // Enter the new Pword
  do {
    do {
      cout <<"Enter your old password: ";
      cin >>currentPword;
      if (currentPword != admin[adminIndex].adminPword){
        cout <<"Invalid password. Try again." <<endl;
      }
    } while (currentPword != admin[adminIndex].adminPword);

    do {
    cout <<"Enter the new password (6-20 characters): ";
    cin >>newPword;  
    if (newPword.size()<6 || newPword.size()>20){
      cout <<"Invalid password, Must be between 6 and 20 characters." <<endl;
    }
    } while (newPword.size()<6 || newPword.size()>20); 
  
    // Prevent reusing the same password
    if (newPword == currentPword){
    cout <<"New password must be different from the current password." <<endl;
    }
  } while (newPword == admin[adminIndex].adminPword);

  // Store it in the vector
  admin[adminIndex].adminPword = newPword;
  
  // Store in file
  ofstream file("admin.txt");
if (!file){
    cout << "Error: Could not open admin database." << endl;
    return;
}
for (int i = 0; i < admin.size(); i++){
    file << admin[i].adminUsername << " " << admin[i].adminPword << endl;
}
file.close();

cout << "Password changed successfully." << endl;
}

// Function for consumer to check their balance
void checkBalance(vector<Meter>& meter, int meterIndex){
    cout << "Your current balance is: " << meter[meterIndex].balance << " kWh" << endl;
}


// Function for consumer to simulate load
void simulateLoad(vector<Meter>& meter, int index){

    float V, I, hours;

    cout << "\n--- Simulate Load ---\n";

    // Get electrical parameters
    cout << "Enter Voltage (V): ";
    cin >> V;

    cout << "Enter Current (A): ";
    cin >> I;

    cout << "Enter Duration (Hours): ";
    cin >> hours;

    // Apply Physics Formula
    // Energy (kWh) = (V × I × Hours) / 1000
    float energy = (V * I * hours) / 1000;

    cout << "Energy Consumed: "
         << energy << " kWh\n";

    // Check if balance is sufficient
    if (meter[index].balance >= energy){

        // Deduct energy from balance
        meter[index].balance -= energy;

        // Immediately update file
        //fstream file("metersDB.txt");
        //file <<meter[index].meterNo <<" " <<meter[index].meterPword <<" " <<meter[index].balance <<endl;
        saveMeters(meter);

        cout << "Load Successful.\n";
        cout << "New Balance: "
             << meter[index].balance << " kWh\n";

    } else {

        // If insufficient balance
        cout << "Low Balance. Please Top-up.\n";
    }
}

//Function for admin to log in
void adminLogin(vector<Admin>& admin, vector<Meter>& meter){
  /* TO DO
  - Enter their username - done
  - Enter their password - done
  - verify that the username matches the pword - done
  - verify that the username and the pword match what is in the txt file
  */

  string admin_Username, admin_Password;
  string loggedInUsername = "";
  int adminIndex;

  // cout <<"Enter your username:" <<endl;
  // cin >>admin_Username;
  // cout <<"Enter your password:" <<endl;
  // cin >>admin_Password;

  bool found=false;

  while (!found) {

        // Step 1: ask for meter number
        cout << "Enter your username: " << endl;
        cin >> admin_Username;

        // Check if admin exists
        adminIndex = -1;
        for (int i = 0; i < admin.size(); i++){
            if (admin[i].adminUsername == admin_Username){
                adminIndex = i;
                break;
            }
        }
        if (adminIndex == -1){
                      cout << "Admin does not exist. Try again." << endl;
                      continue; // go back to start of while loop
                  }
        while (!found){
            

          // Step 2: ask for password
          cout << "Enter your password: " << endl;
          cin >> admin_Password;

          if (admin[adminIndex].adminPword == admin_Password){
              cout << "Login successful." << endl;
              loggedInUsername = admin_Username;
              found = true; // exit the loop
          } else {
              cout << "Incorrect password. Try again." << endl;
              // loop continues automatically
          }  
        }
        
    }


  // for (int i = 0; i < admin.size(); i++){
  //     if (admin[i].adminUsername == admin_Username && admin[i].adminPword == admin_Password){
  //       found=true;
  //       loggedInUsername = admin_Username; 
  //       cout <<"Login successful." <<endl;
  //       break;
  // //     } else{
  // //       cout <<"Incorrect username or password. Try again." <<endl;
  // //     }
  //  }
  // }

  // if(!found){
  //   cout <<"Incorrect username or password. Try again." <<endl;
  //   return;
  // }

  // Admin menu
  int choice;
  bool stayLoggedIn = true;

  while (stayLoggedIn){
    cout << "\n--- Admin Menu ---" << endl;
    cout << "1. Register a new user" << endl;
    cout << "2. Top-up energy (deposit)" << endl;
    cout << "3. View all meters" <<endl;
    cout << "4. Change Password" << endl;
    cout << "5. Logout" << endl;
    cout << "Enter your choice: " << endl;
    cin >> choice;

    switch (choice){
      case 1:
        registerConsumer(meter);
        break;
      case 2:
        topUpEnergy(meter);
        break;
      case 3:
        viewMeters(meter);
        break;
      case 4:
        changeAdminPword(admin, loggedInUsername);
        break;
      case 5:
        cout << "Logging out..." << endl;
        stayLoggedIn = false;
        break;
      default:
        cout << "Invalid option. Try again." << endl;
    }
  }

}

// Function for consumer to change pword
void changeConsumerPword(vector<Meter>& meter, string loggedInUsername){
  string oldPword, newPword, currentPword;

  // Load the logged-in username from the DB to the vector 
  int meterIndex=-1;
  for (int i = 0; i < meter.size(); i++){
    if (meter[i].meterNo == loggedInUsername){
      meterIndex=i;
      break;
    }
  }

  // Enter the new Pword
  do {
    do {
      cout <<"Enter your old password: ";
      cin >>currentPword;
      if (currentPword != meter[meterIndex].meterPword){
        cout <<"Invalid password. Try again." <<endl;
      }
    } while (currentPword != meter[meterIndex].meterPword);

    do {
    cout <<"Enter the new password (6-20 characters): ";
    cin >>newPword;  
    if (newPword.size()<6 || newPword.size()>20){
      cout <<"Invalid password, Must be between 6 and 20 characters." <<endl;
    }
    } while (newPword.size()<6 || newPword.size()>20); 
  
    // Prevent reusing the same password
    if (newPword == currentPword){
    cout <<"New password must be different from the current password." <<endl;
    }
  } while (newPword == meter[meterIndex].meterPword);

  // Store it in the vector
  meter[meterIndex].meterPword = newPword;
  
  // Store in file
  ofstream file("metersDB.txt");
if (!file){
    cout << "Error: Could not open admin database." << endl;
    return;
}
for (int i = 0; i < meter.size(); i++){
    file << meter[i].meterNo << " " << meter[i].meterPword <<" " <<meter[i].balance << endl;
}
file.close();

cout << "Password changed successfully." << endl;
}

// Function for consumer to log in
void consumerLogin(vector<Meter>& meter){
  /* TO DO
  - Enter their username - done
  - Enter their password - done
  - verify that the username matches the pword - done
  - verify that the username and the pword match what is in the txt file
  */

  string meter_No, meter_Pword;
  string loggedInUsername = "";
  int meterIndex;

  bool loggedIn = false; // flag to control the loop

    while (!loggedIn) {

        // Step 1: ask for meter number
        cout << "Enter your meter number: " << endl;
        cin >> meter_No;

        // Check if meter exists
        meterIndex = -1;
        for (int i = 0; i < meter.size(); i++){
            if (meter[i].meterNo == meter_No){
                meterIndex = i;
                break;
            }
        }
        if (meterIndex == -1){
                      cout << "Meter number does not exist. Try again." << endl;
                      continue; // go back to start of while loop
                  }
        while (!loggedIn){
            

          // Step 2: ask for password
          cout << "Enter your password: " << endl;
          cin >> meter_Pword;

          if (meter[meterIndex].meterPword == meter_Pword){
              cout << "Login successful." << endl;
              loggedInUsername = meter_No;
              loggedIn = true; // exit the loop
          } else {
              cout << "Incorrect password. Try again." << endl;
              // loop continues automatically
          }  
        }
        
    }

     // Consumer menu
  int choice;
  bool stayLoggedIn = true;

  while (stayLoggedIn){
    cout << "\n--- Consumer Menu ---" << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Simulate Load" << endl;
    cout << "3. Change Password" << endl;
    cout << "4. Logout" << endl;
    cout << "Enter your choice: " << endl;
    cin >> choice;

    switch (choice){
      case 1:
        checkBalance(meter, meterIndex);
        break;
      case 2:
        simulateLoad(meter, meterIndex);
        break;
      case 3:
        changeConsumerPword(meter, loggedInUsername);
        break;
      case 4:
        cout << "Logging out..." << endl;
        stayLoggedIn = false;
        break;
      default:
        cout << "Invalid option. Try again." << endl;
    }
  }
}


int main() {
  vector<Admin> admin;
  vector<Meter> meter;
  loadAdmin(admin);
  loadMeters(meter);

  
  int choice;
  cout <<"Welcome! Login as:" <<endl;
  cout <<"1. Admin" <<endl;
  cout <<"2. Consumer" <<endl;
  cout <<"3. Exit" <<endl;
  cin >>choice;

  switch (choice){
      case 1:
        adminLogin(admin, meter);
        break;
      case 2:
        consumerLogin(meter);
        break;
      case 3:
          return 0;
      default:
        cout <<"Invalid option. Try again!" <<endl;
          break;
  }
  

  return 0;
}