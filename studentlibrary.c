#include <stdio.h>
#include <string.h>
struct Book {
    char title[50];
    char author[50];
    int id;
    int borrowed;
};
void borrowBook(struct Book books[], int id) {
    int i;
    for (i = 0; i < 100; i++) {
        if (books[i].id == id) {
            if (books[i].borrowed == 0) {
                books[i].borrowed = 1;
                printf("Book borrowed successfully!\n");
            } else {
                printf("Sorry, this book is already borrowed.\n");
            }
            return;
        }
    }
    printf("Sorry, book not found.\n");
}
void checkAvailability(struct Book books[], int id) {
    int i;
    for (i = 0; i < 100; i++) {
        if (books[i].id == id) {
            if (books[i].borrowed == 0) {
                printf("This book is available for borrowing.\n");
            } else {
                printf("Sorry, this book is currently borrowed.\n");
            }
            return;
        }
    }
    printf("Sorry, book not found.\n");
}
void returnBook(struct Book books[], int id) {
    int i;
    for (i = 0; i < 100; i++) {
        if (books[i].id == id) {
            if (books[i].borrowed == 1) {
                books[i].borrowed = 0;
                printf("Book returned successfully!\n");
            } else {
                printf("Sorry, this book is not currently borrowed.\n");
            }
            return;
        }
    }
    printf("Sorry, book not found.\n");
}
int main() {
    struct Book books[100];
    int i;
    printf("--------------------------------------STUDENTS LIBRARY MANAGEMENT SYSTEM--------------------------------------------------\n");
    printf("Register New Books\n\n");
    for (i = 0; i < 100; i++) {
        printf("Enter book title: ");
        scanf("%s", books[i].title);
        printf("Enter book author: ");
        scanf("%s", books[i].author);
        printf("Enter book ID: ");
        scanf("%d", &books[i].id);

        books[i].borrowed = 0;
    }
    int choice, bookID;
    do {
        printf("\nLibrary Management System\n");
        printf("1. Borrow a book\n");
        printf("2. Check availability of a book\n");
        printf("3. Return a book\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter book ID to borrow: ");
                scanf("%d", &bookID);
                borrowBook(books, bookID);
                break;
            case 2:
                printf("Enter book ID to check availability: ");
                scanf("%d", &bookID);
                checkAvailability(books, bookID);
                break;
            case 3:
                printf("Enter book ID to return: ");
                scanf("%d", &bookID);
                returnBook(books, bookID);
                break;
            case 4:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);
    return 0;
}