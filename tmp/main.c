#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// start | data store
struct Users {
  char idCard[10];
  char password[10];
  long int balance;
};

// history transaction
struct TransactionHistory {
  char from[10];
  char to[10];
  long int nominal;
};
// end | data store

void main()
{
  // start | initial value
  int activeUser = -1, numOfUsers = 2, numOfTransactionHistory = 32, minimumTransaction = 100 ,inputMenu;
  char inputIdCard[10];
  char inputPassword[10];
  bool isLogout = false;
  // end | initial value

  // start | initial data store
  //create instance from User to user 
  struct Users user[numOfUsers];
  // user1
  strcpy(user[0].idCard, "12345");
  strcpy(user[0].password, "12345");
  user[0].balance = 1000;
  // user2
  strcpy(user[1].idCard, "54321");
  strcpy(user[1].password, "54321");
  user[1].balance = 2500;

  // create instance from TransactionHistory
  struct TransactionHistory transactionHistory[numOfTransactionHistory];
  int transactionHistoryLabel = 0;
  // end | initial data store

  do{
    printf("E-money Machine (Login)\n\n");
    // start | user input
    printf("idCard\t: ");
    scanf("%s", &inputIdCard);
    printf("Password: ");
    scanf("%s", &inputPassword);
    // end | user input

    // start | check user idCard and password
    for(int i=0; i < numOfUsers; i++){
      if(strcmp(user[i].idCard, inputIdCard) == 0 && strcmp(user[i].password, inputPassword) == 0){
        activeUser = i;
      }
    }
    // end | check user idCard and password

    // start | show status user
    if(activeUser != -1){
        bool menu = true;
        while (menu){
          system("clear");
          printf("E-money Machine (Dashboard)\n\n");
          printf("ID Card\t: %s \n\n", user[activeUser].idCard);

          // menu
          printf("Menu (select by number) :\n");
          printf("1. Balance check\n");
          printf("2. Transfer\n");
          printf("3. Transaction history\n");
          printf("0. Logout\n\n");
          printf("Selection (1 or 2 or 3 or 0) : ");
          scanf("%d", &inputMenu);

          switch (inputMenu){
            case 1:
              system("clear");
              printf("E-money Machine (Balance)\n\n");
              printf("ID Card\t: %s \n", user[activeUser].idCard);
              printf("Balance\t: $%d \n\n", user[activeUser].balance);
              printf("1. Back\n");
              printf("Selection (1) : ");
              scanf("%d", &inputMenu);

              switch (inputMenu){
                case 1:
                  menu = true;
                  break;
                default:
                  printf("Invalid Input!\n");
                  break;
              }
              break;
            case 2:
              // transfer
              system("clear");
              printf("E-money Machine (Transfer)\n\n");
              printf("ID Card\t: %s \n", user[activeUser].idCard);
              printf("Balance\t: $%d \n\n", user[activeUser].balance);

              char transferTo[5];
              int transferNominal;
              printf("Transfer To (ID Card) : ");
              scanf("%s", &transferTo);
              printf("Nominal ($100 - $%d) : ", user[activeUser].balance);
              scanf("%d", &transferNominal);
              puts("");
              printf("1. Back\n");
              printf("9. Transaction confirmation\n");
              printf("Selection (1 or 9) : ");
              scanf("%d", &inputMenu);

              switch (inputMenu){
                case 1:
                  menu = true;
                  break;
                case 9:
                  if(transferNominal >= minimumTransaction && transferNominal <= user[activeUser].balance){
                    system("clear");
                    // added transaction
                    int transferToId = -1;
                    for (int i = 0; i < numOfUsers; i++){
                      if(strcmp(user[i].idCard, transferTo) == 0 && strcmp(user[i].idCard, user[activeUser].idCard) != 0 ){
                        transferToId = i;
                      }
                    }
                    if(transferToId != -1){
                      strcpy(transactionHistory[transactionHistoryLabel].from, user[activeUser].idCard);
                      strcpy(transactionHistory[transactionHistoryLabel].to, transferTo);
                      transactionHistory[transactionHistoryLabel].nominal = transferNominal;
                      user[activeUser].balance -= transferNominal;
                      user[transferToId].balance += transferNominal;
                      transactionHistoryLabel++;
                      printf("ALERT( Transfer Success )\n\n");
                    } else {
                      printf("ALERT( Transfer Failed, Invalid Target Card Id )\n\n");
                    }

                    printf("1. Back\n");
                    printf("Selection (1) : ");
                    scanf("%d", &inputMenu);
                    switch (inputMenu){
                      case 1:
                        menu = true;
                        break;
                      default:
                        printf("Invalid Input!\n");
                        break;
                    }
                  } else {
                    system("clear");
                    printf("ALERT( Transfer failed, insufficient balance )\n\n");
                    printf("1. Back\n");
                    printf("Selection (1) : ");
                    scanf("%d", &inputMenu);
                    switch (inputMenu){
                      case 1:
                        menu = true;
                        break;
                      default:
                        printf("Invalid Input!\n");
                        break;
                    }
                  }
                  break;
                default:
                  printf("ALERT( Invalid Input transaction! )\n\n");
                  break;
              }
              break;
            case 3:
              // print transaction by user
              system("clear");
              printf("E-money Machine (Transaction History)\n\n");
              printf("ID Card\t: %s \n", user[activeUser].idCard);
              printf("Balance\t: $%d \n\n", user[activeUser].balance);
              int hasTransaction = 0;
              for (int i = 0; i < numOfTransactionHistory; i++)
              {
                if( strcmp(transactionHistory[i].from, user[activeUser].idCard) == 0 || strcmp(transactionHistory[i].to, user[activeUser].idCard) == 0 ){
                  printf("Transaction\n");
                  printf("from\t: %s \n", transactionHistory[i].from);
                  printf("to\t: %s \n", transactionHistory[i].to);
                  printf("nominal\t: $%d\n", transactionHistory[i].nominal);
                  hasTransaction = 1;
                }
              }

              if(hasTransaction == 0){
                printf("You don't have a transaction history...\n");
              }
              puts("");
              printf("1. Back\n");
              printf("Selection (1) : ");
              scanf("%d", &inputMenu);

              switch (inputMenu){
                case 1:
                  menu = true;
                  break;
                default:
                  printf("Invalid Input!\n");
                  break;
              }
              break;

            case 0:
              menu = false;
              isLogout = true;
              activeUser = -1;
              system("clear");
              break;
            default:
              printf("Invalid Input!\n");
              break;
          }
        }
    }
    else{
      system("clear");
      printf("\nALERT( Login Failed )\n\n");
      isLogout = true;
    }
    // end | show status user
  } while (isLogout);
}