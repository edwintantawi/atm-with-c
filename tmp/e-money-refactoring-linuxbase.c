#include<stdio.h>
#include<stdbool.h>
#include<string.h>


struct Users {
    char id[10];
    char password[20];
    long int saldo;
};

struct TransactionHistory {
  char from[10];
  char to[10];
  long int nominal;
};

// Global Variable
int activeUser = -1, numOfUser = 2, numOfTransactionHistory = 32, minimumTransaction = 1000, transactionHistoryLabel = 0;

bool Login(struct Users user[numOfUser], char inputID[10], char inputPassword[20]);
bool Transfer(struct Users user[numOfUser], char idPenerima[10], long int nominal, struct TransactionHistory history[numOfTransactionHistory]);
void viewLogin(struct Users user[numOfUser], struct TransactionHistory history[numOfTransactionHistory]);
void viewDashboard(struct Users user[numOfUser], struct TransactionHistory history[numOfTransactionHistory]);
void viewTransfer(struct Users user[numOfUser], struct TransactionHistory history[numOfTransactionHistory]);
void viewHistory(struct Users user[numOfUser], struct TransactionHistory history[numOfTransactionHistory]);
void viewBalance(struct Users user[numOfUser], struct TransactionHistory history[numOfTransactionHistory]);
void viewAfterLogOut(struct Users user[numOfUser], struct TransactionHistory history[numOfTransactionHistory]);

int main()
{

    struct Users allUser[2] = {
        {"12345","testes",1500000},
        {"54321","testing",2000000}
    };

    struct TransactionHistory allHistory[numOfTransactionHistory];

    viewLogin(allUser, allHistory);


    return 0;
}

bool Login(struct Users user[numOfUser], char inputID[10], char inputPassword[20]) {
    for(int i=0; i < numOfUser; i++){
        int validateUsername = strcmp(user[i].id, inputID);
        int validatePassword = strcmp(user[i].password, inputPassword);

        if(validateUsername == 0 && validatePassword == 0){
            activeUser = i;
            break;
        } else {
            continue;
        }
    }

    if (activeUser != -1) {
        return true;
    } else {
        return false;
    }
}

bool Transfer(struct Users user[numOfUser], char idPenerima[10],long int nominal, struct TransactionHistory history[numOfTransactionHistory]) {
    int transferTo = -1;
    if (nominal >= minimumTransaction && nominal <= user[activeUser].saldo) {
        for (int i = 0; i < numOfUser; i++) {
            if (strcmp(user[i].id, idPenerima) == 0 && strcmp(user[activeUser].id, user[i].id) != 0) {
                transferTo = i;
                break;
            } else {
                continue;
            }
        }
    }

    if (transferTo != -1) {
        user[activeUser].saldo -= nominal;
        user[transferTo].saldo += nominal;
        // add to history
        strcpy(history[transactionHistoryLabel].from, user[activeUser].id);
        strcpy(history[transactionHistoryLabel].to, user[transferTo].id);
        history[transactionHistoryLabel].nominal = nominal;
        transactionHistoryLabel++;
        return true;
    } else {
        return false;
    }
}

void viewLogin(struct Users user[numOfUser],struct TransactionHistory history[numOfTransactionHistory]) {
    char userId[10], passwordUser[20];
    bool loopConditional;


    do {
        printf("\t\t\tE-Money Machine (LOGIN)\n");
        printf("\n");

        printf("\tEnter ID\t\t: ");
        scanf("%s", &userId);

        printf("\n");
        printf("\tEnter Password\t\t: ");
        scanf("%s", &passwordUser);

        bool result = Login(user,userId,passwordUser);

        if (result == true) {
            system("clear");

            loopConditional = false;
            viewDashboard(user,history);
        } else {
            system("clear");
            printf("\t\t\tALERT( Login Failed )\n\n");
            printf("\n");
            loopConditional = true;
        }

    } while (loopConditional);

}

void viewDashboard(struct Users user[numOfUser],struct TransactionHistory history[numOfTransactionHistory]) {
    bool loopConditional;
    int inputMenu;


    do {
        printf("\t\t\tE-Money Machine (DASHBOARD)\n");
        printf("\n");

        printf("\tID\t: %s\n", user[activeUser].id);

        printf("\n");
        printf("\n");
        printf("\t\t\t==========MENU===========\n");
        printf("\n");

        printf("\t1. Balance check\n");
        printf("\t2. Transfer\n");
        printf("\t3. Transaction history\n");
        printf("\t0. Logout\n\n");
        printf("\tSelection (1 or 2 or 3 or 0) : ");
        scanf("%d", &inputMenu);

        switch (inputMenu) {
            case 1 :
                system("clear");
                viewBalance(user, history);
                loopConditional = false;
                break;
            case 2 :
                system("clear");
                viewTransfer(user,history);
                loopConditional = false;
                break;
            case 3 :
                system("clear");
                viewHistory(user,history);
                loopConditional = false;
                break;
            case 0 :
                system("clear");
                activeUser = -1;
                viewAfterLogOut(user,history);
                loopConditional = false;
        }


    } while (loopConditional);
}

void viewTransfer(struct Users user[numOfUser], struct TransactionHistory history[numOfTransactionHistory]) {
    bool loopConditional;
    int inputMenu;
    char idPenerima[10];
    int nominal;
    bool result;



    do {
        printf("\t\t\tE-Money Machine (transfer)\n");
        printf("\n");

        printf("\tID\t\t: %s\n", user[activeUser].id);
        printf("\tBalance\t\t: %d\n", user[activeUser].saldo);

        printf("\n");

        printf("\tTransfer To\t: ");
        scanf("%s", &idPenerima);

        printf("\tNominal\t\t: ");
        scanf("%d", &nominal);

        printf("\n");
        printf("\n");
        printf("\t\t\t==========MENU===========\n");
        printf("\n");

        printf("\t1. Transfer Now\n");
        printf("\t9. Cancel\n");
        printf("\tSelection (1 or 9) : ");
        scanf("%d", &inputMenu);

        switch (inputMenu) {
            case 1 :
                result = Transfer(user,idPenerima,nominal,history);
                system("clear");
                if (result) {
                    printf("\t\t\tALERT( Transfer Success )\n\n");
                } else {
                    printf("\t\t\tALERT( Transfer Failed )\n\n");
                }
                viewDashboard(user,history);
                break;
            case 9 :
                system("clear");
                viewDashboard(user,history);
                break;
            default :
                printf("Invalid Input!\n");
                loopConditional = true;
                break;
        }

    } while (loopConditional);

}

void viewHistory(struct Users user[numOfUser], struct TransactionHistory history[numOfTransactionHistory]) {
    bool loopConditional;
    int inputMenu;
    bool result;


    int hasTransaction = 0;
    do {
        printf("\t\t\tE-Money Machine (History)\n");
        printf("\n");

        printf("\tID\t\t: %s\n", user[activeUser].id);
        printf("\tBalance\t\t: %d\n", user[activeUser].saldo);

        printf("\n");

        printf("\t\t\t=======HISTORY=========\n");
        printf("\n");
        for (int i = 0; i < transactionHistoryLabel; i++) {
            if( strcmp(history[i].from, user[activeUser].id) == 0 || strcmp(history[i].to, user[activeUser].id) == 0 ){
                  printf("\tFrom\t: %s \n", history[i].from);
                  printf("\tTo\t: %s \n", history[i].to);
                  printf("\tNominal\t: %d\n", history[i].nominal);
                  if(transactionHistoryLabel > 1) {
                    printf("\t-------------------\n");
                  }
                  hasTransaction = 1;
            }
        }

        if (hasTransaction == 0) {
            system("clear");
            printf("\t\t\tYou don't have a transaction history...\n");
            printf("\n");
            viewDashboard(user,history);
        }


        printf("\n");
        printf("\n");
        printf("\t\t\t==========MENU===========\n");
        printf("\n");

        printf("\t1. Back");
        printf("\tSelection (1) : ");
        scanf("%d", &inputMenu);

        switch (inputMenu) {
            case 1 :
                system("clear");
                viewDashboard(user,history);
                break;
            default :
                printf("Invalid Input!\n");
                loopConditional = true;
                break;
        }

    } while (loopConditional);

}

void viewBalance(struct Users user[numOfUser],struct TransactionHistory history[numOfTransactionHistory]) {
    bool loopConditional;
    int inputMenu;


    do {
        printf("\t\t\tE-Money Machine (BALANCE)\n");
        printf("\n");

        printf("\tID\t\t: %s\n", user[activeUser].id);

        printf("\n");

        printf("\tBalance\t\t: %d\n", user[activeUser].saldo);

        printf("\n");
        printf("\n");
        printf("\t\t\t==========MENU===========\n");
        printf("\n");

        printf("\t1. Back\n");
        printf("\n");
        printf("\n");
        printf("\tSelection (1) : ");
        scanf("%d", &inputMenu);

        switch (inputMenu) {
            case 1 :
                system("clear");
                loopConditional = false;
                viewDashboard(user,history);
                break;
            default :
                printf("Invalid Input!\n");
                loopConditional = true;
                break;
        }


    } while (loopConditional);
}

void viewAfterLogOut(struct Users user[numOfUser], struct TransactionHistory history[numOfTransactionHistory]) {
    int inputMenu;
    bool loopCondition;
    do {
        printf("\t\t\tTHANK YOU & SEE YOU AGAIN\n");
        printf("\n");

        printf("\n");
        printf("\n");
        printf("\t\t\t==========MENU===========\n");
        printf("\n");

        printf("\t1. LOGIN\n");
        printf("\t9. CLOSE\n");
        printf("\n");
        printf("\tSelection (1) : ");
        scanf("%d", &inputMenu);

        switch(inputMenu) {
            case 1:
                system("clear");
                viewLogin(user,history);
                break;
            case 9:
                system("clear");
                exit(0);
                break;
            default:
                printf("\n\n\t\t\t!!!!!!Invalid Input!!!!!!\n");
                printf("\n");
                loopCondition = true;
                break;
        }


    } while (loopCondition);
}
