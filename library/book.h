#ifndef BOOK_H
#define BOOK_H

struct Book {
    int bookId;
    char title[100];
    char author[100];
    int isBorrowed;
    char studentId[14];
    int borrowedByStudentId;
    

    };

struct Student {
    char studentId[14];
    char name[100];
    
};

void borrowBook();
void registerNewBook();
void checkBorrowedBooks();
void borrowBook();
void checkAvailableBooks();
void deleteBook();
void returnBook();


#endif
