#include <stdio.h>
#include "book.h"
#include<string.h>
#include <stdlib.h>

int main(){
    int choice;
    do{
        printf("Choose one of the following: \n");
        printf("1. Register new book\n");
        printf("2. Delete book\n");
        printf("3. Check available books\n");
        printf("4. Borrow book\n");
        printf("5. Return a book\n");
        printf("6. Check Borowed  Books\n");
        printf("7. Exit the system\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                registerNewBook();
                break;

            case 2:
                deleteBook();
                break;

            case 3:
                checkAvailableBooks();
                break;

            case 4:
                borrowBook();
                break;

            case 5:
                returnBook();
                break;
            case 6:
                checkBorrowedBooks(); 
                break;   

            case 7:
                printf("Thank you for using the library management system! Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    } while(choice != 7); // Terminate loop when choice is 6

    return 0;
}


    

