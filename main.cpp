#include<iostream>
#include<fstream>
#include<cstdio>
#include "SinglyLinkedList.h"

using namespace std;

void CreateNewContact(SinglyLinkedList& list);
bool deleteStringFromFile(const string& target);
void RemoveContact(SinglyLinkedList& list, int num);
void PrintContactInfo(SinglyLinkedList &list, int num);
void EditContact(SinglyLinkedList &list, int num);
void UpdateFileInfo(int num, Contacts contact, SinglyLinkedList &list);

int main() {
   SinglyLinkedList list;
   ifstream fileInput, inf;
   ofstream of;
   fileInput.open("Contacts.txt");
   if (!fileInput.is_open()) {
      cerr << "Error opeining file. Restart application.";
      of.open("Contacts.txt");
      of.close();
      exit(0);
   }
   string info;
   while (getline(fileInput, info)) {
      Contacts *contactSave = new Contacts(info);
      inf.open(info + ".txt");
      if (!inf.is_open()) {
         cerr << "Error opeining file. Restart application.";
         of.open("Contacts.txt");
         of.close();
         exit(0);
      }
      string line = "";
      int i = 0;
      while (getline(inf, line)) {
         switch(i) {
            case 0:
               break;

            case 1:
               contactSave->setPhone(line);
               break;
            
            case 2:
               contactSave->setEmail(line);
               break;

            case 3:
               contactSave->setAddress(line);
               break;

            default:
               break;
         }
         
         i++;
      }
      inf.close();
      list.insertContact(*contactSave);
   }

   fileInput.close();

   cout << "--------------------------------------------------------------------------------\n"
        << "                                Contact Manager                                 \n"
        << "Contacts:\n";
   list.printList();

   int input;
   cout << endl;

   cout << "================================================================================\n"
        << "Options:\n"
        << "1. Show contacts list\n"
        << "2. Add new contact\n"
        << "3. Remove a contact\n"
        << "4. View a contact's information\n"
        << "5. Edit a contact's information\n"
        << "6. Quit Program\n"
        << "================================================================================\n";
   cout << "Option: ";
   cin >> input;

   int num;
   while (input != 6) {
      switch(input){
         case 1:
            cout << "Contacts:\n";
            list.printList();
            system("pause");
            break;

         case 2:
            CreateNewContact(list);
            break;

         case 3:
            list.printList();
            if (!list.isListEmpty()) {
               cout << "Choose which contact to remove: ";
               cin >> num;
               RemoveContact(list, num);
               cout << "Contact deletion complete." << endl;
            }
            break;

         case 4:
         list.printList();
         if (!list.isListEmpty()) {
            cout << "Choose which contact to view their information: ";
            cin >> num;
            cout << endl;
            PrintContactInfo(list, num);
            system("pause");
         }
            break;

         case 5:
            list.printList();
            if (!list.isListEmpty()) {
               cout << "Choose which contact to edit their information: ";
               cin >> num;
               cout << endl;
               PrintContactInfo(list, num);
               EditContact(list, num);
            }
            break;

         case 6:
            exit(0);

         default:
            cerr << "invalid Input\n";
      }

      cout << endl;
      cout << "================================================================================\n"
           << "Options:\n"
           << "1. Show contacts list\n"
           << "2. Add new contact\n"
           << "3. Remove a contact\n"
           << "4. View a contact's information\n"
           << "5. Edit a contact's information\n"
           << "6. Quit Program\n"
           << "================================================================================\n";
      cout << "Option: ";
      cin >> input;
      
   }
}

void CreateNewContact(SinglyLinkedList& list) {
   ofstream of, newFile;
   of.open("Contacts.txt", ios_base::app);
   if (!of.is_open()) {
      cerr << "Error opeining file";
      exit(0);
   }
   string info;
   Contacts *contact = new Contacts();
   cout << "Enter the name of the new contact: ";
   cin.ignore();
   getline(cin, info);
   of << info << endl;
   newFile.open(info + ".txt");
   if (!newFile.is_open()) {
      cerr << "Error opeining file";
      exit(0);
   }
   newFile << info << endl;;
   contact->setName(info);
   cout << "Enter contact's phone number: ";
   getline(cin, info);
   newFile << info << endl;
   contact->setPhone(info);
   cout << "Enter contact's email: ";
   getline(cin, info);
   newFile << info << endl;
   contact->setEmail(info);
   cout << "Enter contact's address: ";
   getline(cin, info);
   newFile << info << endl;
   contact->setAddress(info);
   list.insertContact(*contact);

   cout << "Contact Info Saved!\n";

   of.close();
   newFile.close();
}

void CreateNewContact(SinglyLinkedList& list, Contacts newContact) {
   ofstream of, newFile;
   of.open("Contacts.txt", ios_base::app);
   if (!of.is_open()) {
      cerr << "Error opeining file";
      exit(0);
   }
   string info;
   Contacts *contact = new Contacts();
   of << newContact.getName() << endl;
   newFile.open(newContact.getName() + ".txt");
   if (!newFile.is_open()) {
      cerr << "Error opeining file";
      exit(0);
   }
   newFile << newContact.getName() << endl;;
   contact->setName(newContact.getName());
   newFile << newContact.getPhone() << endl;
   contact->setPhone(newContact.getPhone());
   newFile << newContact.getEmail() << endl;
   contact->setEmail(newContact.getEmail());
   newFile << newContact.getAddress() << endl;
   contact->setAddress(newContact.getAddress());
   list.insertContact(*contact);

   of.close();
   newFile.close();
}

void RemoveContact(SinglyLinkedList& list, int num) {
   Contacts contact = list.removeContact(num - 1);
   string fileName = contact.getName() + ".txt";

   if (remove(fileName.c_str()) != 0) { 
      cerr << "Error deleting file\n";
   }

   if(deleteStringFromFile(contact.getName())) {
      return;
   }
   else {
      cerr << "Error.";
   }
}

bool deleteStringFromFile(const string& target) {
   string filename = "Contacts.txt";
   ifstream inputFile(filename);
   if (!inputFile.is_open()) {
      cerr << "Error opening input file." << endl;
      return false;
   }

   string tempFilename = "temp.txt"; // Temporary file to store modified content
   ofstream tempFile(tempFilename);
   if (!tempFile) {
      cerr << "Error creating temporary file." << endl;
      inputFile.close();
      return false;
   }

   string line;
   bool found = false, outputLine = true; // Indicates whether the target string was found in the file

   while (getline(inputFile, line)) {
      size_t foundPos = line.find(target);
      if (foundPos != string::npos) {
         found = true;
         outputLine = false;
      }
      if (outputLine) {
         tempFile << line << '\n'; // Write the modified or original line to the temporary file
      }
      outputLine = true;
   }

   inputFile.close();
   tempFile.close();

   if (!found) {
      // The target string was not found in the file
      remove(tempFilename.c_str()); // Delete the temporary file
      cout << "Target string not found in the file." << endl;
      return false;
   }

   if (remove(filename.c_str()) != 0) {
      cerr << "Error deleting original file." << endl;
      return false;
   }

   if (rename(tempFilename.c_str(), filename.c_str()) != 0) {
      cerr << "Error renaming temporary file." << endl;
      return false;
   }

   return true;
}

void PrintContactInfo(SinglyLinkedList &list, int num) {
   Contacts contact = list.getContact(num - 1);

   cout << "Name: " << contact.getName() << endl;
   cout << "Phone Number: " << contact.getPhone() << endl;
   cout << "Email: " << contact.getEmail() << endl;
   cout << "Address: " << contact.getAddress() << endl << endl;
}

void EditContact(SinglyLinkedList &list, int num) {
   Contacts contact = list.getContact(num - 1);
   Contacts oldContact = contact;
   int option = 0;
   string edit = "";

   cout << "What would you life to edit?\n"
        << "1. Name\n"
        << "2. Phone Number\n"
        << "3. Email\n"
        << "4. Address\n"
        << "5. Go Back\n";
   cout << "Option: ";
   cin >> option;

   while (option != 5) {
      switch (option) {
         case 1:
            cout << "Old Name: " << contact.getName() << endl;
            cout << "New Name: ";
            cin.ignore();
            getline(cin, edit);
            contact.setName(edit);
            cout << "Success!\n";
            break;

         case 2:
            cout << "Old Phone Number: " << contact.getPhone() << endl;
            cout << "New Phone Number: ";
            cin.ignore();
            getline(cin, edit);
            contact.setPhone(edit);
            cout << "Success!\n";
            break;

         case 3:
            cout << "Old Email: " << contact.getEmail() << endl;
            cout << "New Email: ";
            cin.ignore();
            getline(cin, edit);
            contact.setEmail(edit);
            cout << "Success!\n";
            break;

         case 4:
            cout << "Old Address: " << contact.getAddress() << endl;
            cout << "New Address: ";
            cin.ignore();
            getline(cin, edit);
            contact.setAddress(edit);
            cout << "Success!\n";
            break;

         default:
            cerr << "invalid Input\n";

      }

      cout << "\nWhat else would you life to edit?\n"
           << "1. Name\n"
           << "2. Phone Number\n"
           << "3. Email\n"
           << "4. Address\n"
           << "5. Done editing\n";
      cout << "Option: ";
      cin >> option;
   }


   list.replaceContact(oldContact, contact);
   UpdateFileInfo(num, contact, list);
}

void UpdateFileInfo(int num, Contacts contact, SinglyLinkedList &list) {
   RemoveContact(list, num);
   CreateNewContact(list, contact);
}