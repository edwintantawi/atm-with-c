#include <stdio.h>
#include <string.h>

// start | data store
struct Users {
  char idCard[10];
  char password[10];
  int balance;
};
// end | data store

void main() {
  // start | initial data store
  //create instance from User to user 
  struct Users user[2];
  // user1
  strcpy(user[0].idCard, "12345");
  strcpy(user[0].password, "12345");
  user[0].balance = 1000;
  // user2
  strcpy(user[1].idCard, "54321");
  strcpy(user[1].password, "54321");
  user[1].balance = 2500;
  // end | initial data store

  // start | initial value
  int activeUser = -1;
  char inputIdCard[10];
  char inputPassword[10];
  // end | initial value

  // start | user input
  printf("idCard\t: ");
  gets(inputIdCard);
  printf("Password: ");
  gets(inputPassword);
  // end | user input

  // start | check user idCard and password
  for(int i=0; i<2; i++){
    if(strcmp(user[i].idCard, inputIdCard) == 0 && strcmp(user[i].password, inputPassword) == 0){
      activeUser = i;
    }
  }
  // end | check user idCard and password

  // start | show status user
  if(activeUser != -1){
      printf("\nLogin Successfully\n");
      printf("ID Card\t: %s \n", user[activeUser].idCard);
      printf("Password: %s \n", user[activeUser].password);
      printf("Balance\t: $%d\n\n",user[activeUser].balance);
  }else {
    printf("\nLogin Failed\n\n");
  }
  // end | show status user
}