#include <stdio.h>
#include <string.h>
#include "book.h"

void registerNewBook() {
    struct Book book;
    printf("Enter Book ID: ");
    scanf("%d", &book.bookId);
    printf("Enter Book Title: ");
    scanf(" %[^\n]s", book.title);
    printf("Enter Book Author: ");
    scanf(" %[^\n]s", book.author);
    book.isBorrowed = 0;

    FILE *file = fopen("book.txt", "ab");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }
    fwrite(&book, sizeof(struct Book), 1, file);
    fclose(file);
    printf("New book registered successfully!\n");
}



void deleteBook() {
    int bookIdToDelete;
    printf("Enter Book ID to delete: ");
    scanf("%d", &bookIdToDelete);

    FILE *file = fopen("book.txt", "r+");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

    struct Book book;
    int found = 0;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (book.bookId == bookIdToDelete) {
            found = 1;
            break;
        }
    }

    if (found) {
        fseek(file, -sizeof(struct Book), SEEK_CUR);
        memset(&book, 0, sizeof(struct Book)); // clear the book data
        fwrite(&book, sizeof(struct Book), 1, file);
        printf("Book with ID %d deleted successfully!\n", bookIdToDelete);
    } else {
        printf("Book with ID %d not found.\n", bookIdToDelete);
    }

    fclose(file);
}


void checkAvailableBooks() {
    FILE *file = fopen("book.txt", "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

    struct Book book;
    int availableBooks = 0;
    printf("Available Books:\n");
    printf("-------------------------------\n");
    printf("Book ID\tTitle\t\tAuthor\n");
    printf("-------------------------------\n");
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (!book.isBorrowed) {
            printf("%d\t\t%s\t\t%s\n", book.bookId, book.title, book.author);
            availableBooks++;
        }
    }

    if (availableBooks == 0) {
        printf("No available books.\n");
    }

    fclose(file);
}

void borrowBook() {
    int bookIdToBorrow;
    printf("Enter Book ID to borrow: ");
    scanf("%d", &bookIdToBorrow);
    getchar(); // consume newline character

    FILE *file = fopen("book.txt", "r+");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

    struct Book book;
    int found = 0;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (book.bookId == bookIdToBorrow) {
            found = 1;
            break;
        }
    }

    if (found) {
        if (book.isBorrowed) {
            printf("Book with ID %d is already borrowed.\n", bookIdToBorrow);
        } else {
            fseek(file, -sizeof(struct Book), SEEK_CUR);
            book.isBorrowed = 1;
            printf("Enter Student ID: ");
            scanf("%s", book.studentId);
            getchar(); // consume newline character
            fwrite(&book, sizeof(struct Book), 1, file);

            // Collect student information
            struct Student student;
            printf("Enter Student Name: ");
            scanf(" %[^\n]s", student.name);

            // Append student information to a separate file
            FILE *studentFile = fopen("students.txt", "ab");
            if (studentFile == NULL) {
                printf("Failed to open student file\n");
                return;
            }
            fwrite(&student, sizeof(struct Student), 1, studentFile);
            fclose(studentFile);

            printf("Book with ID %d borrowed successfully!\n", bookIdToBorrow);
        }
    } else {
        printf("Book with ID %d not found.\n", bookIdToBorrow);
    }

    fclose(file);
}



void returnBook() {
    int bookIdToReturn;
    printf("Enter Book ID to return: ");
    scanf("%d", &bookIdToReturn);
    getchar(); // consume newline character

    FILE *file = fopen("book.txt", "r+");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

    struct Book book;
    int found = 0;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (book.bookId == bookIdToReturn) {
            found = 1;
            break;
        }
    }

    if (found) {
        if (!book.isBorrowed) {
            printf("Book with ID %d is not currently borrowed.\n", bookIdToReturn);
        } else {
            fseek(file, -sizeof(struct Book), SEEK_CUR);
            book.isBorrowed = 0;
            fwrite(&book, sizeof(struct Book), 1, file);

            // Remove student information from the separate student file
            FILE *studentFile = fopen("students.txt", "r+");
            if (studentFile == NULL) {
                printf("Failed to open student file\n");
                return;
            }
            struct Student student;
            int foundStudent = 0;
            while (fread(&student, sizeof(struct Student), 1, studentFile)) {
                if(strcmp(student.studentId, book.studentId) == 0) {
    // studentId and book.studentId are now both pointers to char (strings)
    // rest of the code
}
 {
                    foundStudent = 1;
                    break;
                }
            }
            if (foundStudent) {
                fseek(studentFile, -sizeof(struct Student), SEEK_CUR);
                struct Student emptyStudent = {0}; // Fill with 0 values
                fwrite(&emptyStudent, sizeof(struct Student), 1, studentFile);
            }
            fclose(studentFile);

            printf("Book with ID %d returned successfully!\n", bookIdToReturn);
        }
    } else {
        printf("Book with ID %d not found.\n", bookIdToReturn);
    }

    fclose(file);
}

void checkBorrowedBooks() {
    FILE *bookFile = fopen("book.txt", "rb");
    if (bookFile == NULL) {
        printf("Failed to open book file\n");
        return;
    }

    printf("List of Borrowed Books:\n");
    printf("Student ID        Book ID    Book Title\n");
    printf("-------------------------------\n");

    struct Book book;
    while (fread(&book, sizeof(struct Book), 1, bookFile)) {
        if (book.isBorrowed == 1) {
            printf("%s               %d       %s\n", book.studentId, book.bookId, book.title);
        }
    }

    fclose(bookFile);
}
