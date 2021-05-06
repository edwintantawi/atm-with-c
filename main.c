#include <stdio.h>
#include <string.h>

// start | data store
struct Users {
  char id[10];
  char password[10];
  int money;
};
// end | data store

int main(void) {
  // start | initial data store
  struct Users user[2];
  // user1
  strcpy(user[0].id, "12345");
  strcpy(user[0].password, "12345");
  user[0].money = 1000;
  // user2
  strcpy(user[1].id, "54321");
  strcpy(user[1].password, "54321");
  user[1].money = 2500;
  // end | initial data store

  // start | initial value
  int isLogin = -1;
  char inputId[10];
  char inputPass[10];
  // end | initial value

  // start | user input
  printf("ID\t: ");
  gets(inputId);
  printf("Password: ");
  gets(inputPass);
  // end | user input

  // start | check user id and password
  for(int i=0; i<2; i++){
    if(strcmp(user[i].id, inputId) == 0 && strcmp(user[i].password, inputPass) == 0){
      isLogin = i;
    }
  }
  // end | check user id and password

  // start | show status user
  if(isLogin != -1){
      printf("\nBerhasil login\n");
      printf("id\t: %s \n", user[isLogin].id);
      printf("password: %s \n", user[isLogin].password);
      printf("money\t: %d\n\n",user[isLogin].money);
  }else {
    printf("Gagal Login\n\n");
  }
  // end | show status user
  
  return 0;
}