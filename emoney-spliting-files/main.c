#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "view.h"


void main(){
  bool isRunning = true;
  struct Users users[2] = {
      {"12345", "12345", 1000},
      {"54321", "54321", 2000}
  };
  struct TransactionHistory transactionHistory[transactionHistoryLength];

  do{
    LoginView(users);
    DashboardView(users, transactionHistory);
  } while (isRunning);
}
