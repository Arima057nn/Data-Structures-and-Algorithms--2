#include <stdio.h>
#include "phonebook.h"

int main() {
  PhoneBook pb = createPhoneBook();

  
  addPhoneNumber("Duc", 12345, &pb);
  addPhoneNumber("Minh", 54321, &pb);
  addPhoneNumber("Huong", 88888, &pb);

  if ( getPhoneNumber( "Huong",pb) != NULL)
    printf("Phone number of Huong is:%ld\n", pb.entries->number);
  else
    printf("Can\'t find phone number of Huong\n");

  return 0;  
}
