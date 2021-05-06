#include <stdio.h>
#include <string.h>

// start | data store
struct Users {
  char idCard[10];
  char password[10];
  int balance;
};

// history transaction
struct TransactionHistory {
  char from[10];
  char to[10];
  int nominal;
};
// end | data store

void main()
{
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

  // create instance from TransactionHistory
  struct TransactionHistory transactionHistory[64];
  int transactionHistoryLabel = 0;
  // end | initial data store

  // start | initial value
  int activeUser = -1;
  int inputMenu;
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
      int menu = 1;
      while (menu == 1){
        system("clear");
        printf("ID Card\t: %s \n", user[activeUser].idCard);

        // menu
        printf("Menu (select by number) :\n");
        printf("1. Balance check\n");
        printf("2. Transfer\n");
        printf("3. Transaction history\n\n");
        printf("Selection (1 or 2 or 3) : ");
        scanf("%d", &inputMenu);

        switch (inputMenu){
          case 1:
            system("clear");
            printf("ID Card\t: %s \n", user[activeUser].idCard);
            printf("Balance\t: $%d \n\n", user[activeUser].balance);
            printf("1. Back\n");
            printf("0. Close & logout\n");
            printf("Selection (1 or 0) : ");
            scanf("%d", &inputMenu);

            switch (inputMenu){
              case 1:
                menu = 1;
                break;
              case 0:
                menu = 0;
                system("clear");
                break;
              default:
                printf("Invalid Input!");
                break;
            }
            break;
          case 2:
            // transfer
            system("clear");
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
            printf("0. Close & logout\n");
            printf("9. Transaction confirmation\n");
            printf("Selection (1 or 0 or 9) : ");
            scanf("%d", &inputMenu);

            switch (inputMenu){
              case 1:
                menu = 1;
                break;
              case 0:
                menu = 0;
                system("clear");
                break;
              case 9:
                if(transferNominal >= 100 && transferNominal <= user[activeUser].balance){
                  system("clear");

                  // TODO process transaction
                  // added transaction
                  strcpy(transactionHistory[transactionHistoryLabel].from, user[activeUser].idCard);
                  strcpy(transactionHistory[transactionHistoryLabel].to, transferTo);

                  int transferToId = -1;
                  for (int i = 0; i < 2; i++){
                    if(strcmp(user[i].idCard, transferTo) == 0){
                      transferToId = i;
                    }
                  }

                  if(transferToId != -1){
                    transactionHistory[transactionHistoryLabel].nominal = transferNominal;
                    user[activeUser].balance -= transferNominal;
                    user[transferToId].balance += transferNominal;
                    transactionHistoryLabel++;
                    printf("Transfer Success\n\n");
                  } else {
                    printf("Transfer Failed, Invalid Target Card Id\n\n");
                  }

                  printf("1. Back\n");
                  printf("0. Close & logout\n");
                  scanf("%d", &inputMenu);
                  switch (inputMenu){
                    case 1:
                      menu = 1;
                      break;
                    case 0:
                      menu = 0;
                      system("clear");
                      break;
                    default:
                      printf("Invalid Input!");
                      break;
                  }
                } else {
                  system("clear");
                  printf("Transfer failed, insufficient balance\n\n");
                  printf("1. Back\n");
                  printf("0. Close & logout\n");
                  scanf("%d", &inputMenu);
                  switch (inputMenu){
                    case 1:
                      menu = 1;
                      break;
                    case 0:
                      menu = 0;
                      system("clear");
                      break;
                    default:
                      printf("Invalid Input!");
                      break;
                  }
                }
                break;
              default:
                printf("Invalid Input transaction!");
                break;
            }
            break;
          case 3:
            // print transaction by user
            system("clear");
            printf("ID Card\t: %s \n", user[activeUser].idCard);
            printf("Balance\t: $%d \n\n", user[activeUser].balance);
            int hasTransaction = 0;
            for (int i = 0; i < 64; i++)
            {
              if( strcmp(transactionHistory[i].from, user[activeUser].idCard) == 0 || strcmp(transactionHistory[i].to, user[activeUser].idCard) == 0 ){
                printf("\nTransaction\n");
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
            printf("0. Close & logout\n");
            printf("Selection (1 or 0) : ");
            scanf("%d", &inputMenu);

            switch (inputMenu){
              case 1:
                menu = 1;
                break;
              case 0:
                menu = 0;
                system("clear");
                break;
              default:
                printf("Invalid Input!");
                break;
            }
            break;
          default:
            break;
        }
      }
  }
  else
  {
    printf("\nLogin Failed\n\n");
  }
  // end | show status user
}