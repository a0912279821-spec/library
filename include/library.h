#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>

#define max 100

typedef struct
{
    int id;//图书编号
    char name[30];//图书名称
    char author[30];//作者
    char publisher[30];//出版社
    double price;//价格
    int total;//总数量
    int stock;//当前库存
    int recommend;
}Book;

/* main.c 需要调用的函数声明 */
int inputInt(const char *prompt, int *value);
void addBook(void);
void listBook(void);
void searchBook(void);
void deleteBook(void);
void updateBook(void);
void borrowBook(void);
void returnBook(void);
void budgetRecommend(void);
void saveBooksToFile(void);
void loadBooksFromFile(void);

#endif
