#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define numOfUsers 2
#define transactionHistoryLength 32
#define minTransferBalanceAmount 100

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

int activeUser = -1, transactionLabels = 0;

void LoginView(struct Users users[numOfUsers]);
bool LoginController(struct Users users[numOfUsers], char inputIdCard[10], char inputPassword[10]);
void DashboardView(struct Users users[numOfUsers], struct TransactionHistory transactionHistory[transactionHistoryLength]);
void BalanceView(struct Users users[numOfUsers]);
void TransferView(struct Users users[numOfUsers], struct TransactionHistory transactionHistory[transactionHistoryLength]);
int TransferController(struct Users user[numOfUsers], struct TransactionHistory transactionHistory[transactionHistoryLength], char inputTransferTo[10], long int inputBalanceAmount);
void TransactionView(struct Users users[numOfUsers], struct TransactionHistory transactionHistory[transactionHistoryLength]);

void main(){
  bool isRunning = true;
  struct Users users[numOfUsers] = {
      {"12345", "12345", 1000},
      {"54321", "54321", 2000}
  };
  struct TransactionHistory transactionHistory[transactionHistoryLength];

  do{
    LoginView(users);
    DashboardView(users, transactionHistory);
  } while (isRunning);
}

void LoginView(struct Users users[numOfUsers]){
  char inputIdCard[10];
  char inputPassword[10];
  bool reView = true;

  do{
    printf("E-Money Machine ( Login )\n\n");
    printf("Enter IDCard\t: ");
    scanf("%s", &inputIdCard);
    printf("Enter Password\t: ");
    scanf("%s", &inputPassword);

    int isLoggedIn = LoginController(users, inputIdCard, inputPassword);
    system("cls");
    if(isLoggedIn){
      printf("Login Success!\n\n");
      break;
    }
    printf("Login Failed!\n\n");
  } while (reView);
}

bool LoginController(struct Users users[numOfUsers], char inputIdCard[10], char inputPassword[10] ){
  for (int indexOfUser = 0; indexOfUser < numOfUsers; indexOfUser++){
    int isValidIdCard = strcmp(users[indexOfUser].idCard, inputIdCard);
    int isValidPassword = strcmp(users[indexOfUser].password, inputPassword);
    if( isValidIdCard == 0 && isValidPassword == 0 ){
      activeUser = indexOfUser;
      return true;
    }
  }
  return false;
}

void DashboardView(struct Users users[numOfUsers], struct TransactionHistory transactionHistory[transactionLabels]){
  int inputMenu;
  bool reView = true;
  do
  {
    system("cls");
    printf("E-Money Machine ( DASHBOARD )\n\n");
    printf("==============MENU==============\n");
    printf("1. Balance check\n");
    printf("2. Transfer\n");
    printf("3. Transaction history\n");
    printf("0. Logout\n");
    printf("\nSelection (1 or 2 or 3 or 0) : ");
    scanf("%d", &inputMenu);

    switch (inputMenu){
    case 1:
      BalanceView(users);
      break;
    case 2:
      TransferView(users, transactionHistory);
      // TransferView
      break;
    case 3:
      TransactionView(users, transactionHistory);
      // TransactionView
      break;
    case 0:
      system("cls");
      reView = false;
      break;
    default:
      break;
    }
  } while (reView);
}

void BalanceView(struct Users users[numOfUsers]){
  int inputMenu;
  do{
    system("cls");
    printf("E-Money Machine ( BALANCE )\n\n");
    printf("IDCard\t: %s\n", users[activeUser].idCard);
    printf("Balance amount\t: %d\n\n", users[activeUser].balance);
    printf("==============MENU==============\n");
    printf("1. Back\n");
    printf("\nSelection (1) : ");
    scanf("%d", &inputMenu);
  } while (inputMenu != 1);
}

void TransferView(struct Users users[numOfUsers], struct TransactionHistory transactionHistory[transactionHistoryLength]){
  int inputMenu;
  bool reView = true;
  char inputTransferTo[10];
  int inputBalanceAmount;
  int transferStatus;
  int sectionInputMenu;

  do {
    system("cls");
    printf("E-Money Machine ( TRANSFER )\n\n");
    printf("IDCard\t: %s\n", users[activeUser].idCard);
    printf("Balance amount\t: %d\n\n", users[activeUser].balance);

    printf("Transfer to (IDCard)\t: ");
    scanf("%s", &inputTransferTo);
    printf("Transfer nominal ($)\t: ");
    scanf("%d", &inputBalanceAmount);
    printf("\n==============MENU==============\n");
    printf("1. Cancel and Back\n");
    printf("2. Retype again\n");
    printf("9. Accept and Transfer\n");
    printf("\nSelection (1, 2, 9) : ");
    scanf("%d", &inputMenu);

    switch (inputMenu){
    case 1:
      reView = false;
      break;
    case 9:
      transferStatus = TransferController(users, transactionHistory, inputTransferTo, inputBalanceAmount);
      system("cls");
      switch (transferStatus){
      case 1:
        printf("Transfer Success\n\n");
        break;
      case -1:
        printf("Transfer Failed, IDCard Not Found\n\n");
        break;
      case -2:
        printf("Transfer Failed, Invalid Balance Amount\n\n");
        break;
      default:
        printf("Transfer Failed, Unknow Error\n\n");
        break;
      }
      do{
        printf("==============MENU==============\n");
        printf("1. Back\n");
        printf("2. Transfer again\n");
        printf("\nSelection (1, 2) : ");
        scanf("%d", &sectionInputMenu);
        switch (sectionInputMenu){
          case 1:
            reView = false;
            break;
          case 2:
            break;
          default:
            break;
        }
      } while (sectionInputMenu != 1 && sectionInputMenu != 2);
      break;
    case 2:
    default:
      break;
    }

  } while (reView);
}

int TransferController(struct Users users[numOfUsers], struct TransactionHistory transactionHistory[transactionHistoryLength], char inputTransferTo[10], long int inputBalanceAmount){
  int indexOfTransferToUser = -1;
  for (int indexOfUser = 0; indexOfUser < numOfUsers; indexOfUser++) {
    int isValidIdCard = strcmp(users[indexOfUser].idCard, inputTransferTo);
    int isNotMine = strcmp(users[activeUser].idCard, inputTransferTo);
    if (isValidIdCard == 0 && isNotMine != 0){
      indexOfTransferToUser = indexOfUser;
      break;
    }
  }

  if(indexOfTransferToUser == -1){
    return -1;
  }

  if (inputBalanceAmount >= minTransferBalanceAmount && inputBalanceAmount <= users[activeUser].balance){
    users[activeUser].balance -= inputBalanceAmount;
    users[indexOfTransferToUser].balance += inputBalanceAmount;
    strcpy(transactionHistory[transactionLabels].from, users[activeUser].idCard);
    strcpy(transactionHistory[transactionLabels].to, users[indexOfTransferToUser].idCard);
    transactionHistory[transactionLabels].nominal = inputBalanceAmount;
    transactionLabels++;
    return 1;
  }

  return -2;
}

void TransactionView(struct Users users[numOfUsers], struct TransactionHistory transactionHistory[transactionHistoryLength]){
  int inputMenu;
  bool hasTransaction = false;
  do{
    system("cls");
    printf("E-Money Machine ( TRANSACTION HISTORY )\n\n");
    for (int transactionLabel = 0; transactionLabel < transactionLabels; transactionLabel++)
    {
      int isYouTransactionFrom = strcmp(transactionHistory[transactionLabel].from, users[activeUser].idCard);
      int isYouTransactionTo = strcmp(transactionHistory[transactionLabel].to, users[activeUser].idCard);
      if (isYouTransactionFrom == 0){
        printf("--------------------------------\n");
        printf("From\t: %s (you)\n", transactionHistory[transactionLabel].from);
        printf("To\t: %s\n", transactionHistory[transactionLabel].to);
        printf("Nominal\t: %d\n", transactionHistory[transactionLabel].nominal);
        printf("--------------------------------\n");
        hasTransaction = true;
      }
      else if (isYouTransactionTo == 0){
        printf("--------------------------------\n");
        printf("From\t: %s\n", transactionHistory[transactionLabel].from);
        printf("To\t: %s (you)\n", transactionHistory[transactionLabel].to);
        printf("Nominal\t: %d\n", transactionHistory[transactionLabel].nominal);
        printf("--------------------------------\n");
        hasTransaction = true;
      }
    }
    if(!hasTransaction){
      printf("--------------------------------\n");
      printf("--You not have any Transaction--\n");
      printf("--------------------------------\n");
    }

      printf("\n==============MENU==============\n");
    printf("1. Back\n");
    printf("\nSelection (1) : ");
    scanf("%d", &inputMenu);
  } while (inputMenu != 1);
}
