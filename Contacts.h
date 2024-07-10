#ifndef CONTACTS_H
#define CONTACTS_H

#include <iostream>

using namespace std;

class Contacts {

   private:
      string name, email, address, phone;

   public:
      Contacts() {}
      Contacts(string);

      string getName() { return name; }
      string getEmail() { return email; }
      string getAddress() { return address; }
      string getPhone() { return formatPhoneNumber(phone); }

      void setName(string contactName) { name = contactName; }
      void setEmail(string contactEmail) { email = contactEmail; }
      void setAddress(string contactAddress) { address = contactAddress; }
      void setPhone(string contactPhone) { phone = contactPhone; }

      string formatPhoneNumber(string& phoneNumber);
};

string Contacts::formatPhoneNumber(string& phoneNumber) {
    // Check if the input phone number is valid (you may want to add more validation)
    if (phoneNumber.size() != 10) {
        return phoneNumber;
    }

    // Format the phone number as (XXX)XXX-XXXX
    return "(" + phoneNumber.substr(0, 3) + ")" + phoneNumber.substr(3, 3) + "-" + phoneNumber.substr(6);
}


Contacts::Contacts(string contactName) {
   name = contactName;
}

#endif