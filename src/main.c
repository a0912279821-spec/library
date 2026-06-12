#include "library.h"

int main()
{
    int choice;
    loadBooksFromFile();
    while (1)
    {
        printf("==== 图书管理系统 ====\n");
        printf("1.添加图书\n");
        printf("2.显示全部图书\n");
        printf("3.查询图书\n");
        printf("4.删除图书\n");
        printf("5.修改图书\n");
        printf("6.借书\n");
        printf("7.还书\n");
        printf("8.预算购书推荐\n");
        printf("0.退出系统\n");
        inputInt("请输入你的选择:", &choice);
        if (choice == 1)
        {
            addBook();
        }
        else if (choice == 2)
        {
            listBook();
        }
        else if (choice == 3)
        {
            searchBook();
        }
        else if (choice == 4)
        {
            deleteBook();
        }
        else if (choice == 5)
        {
            updateBook();
        }
        else if (choice == 6)
        {
            borrowBook();
        }
        else if (choice == 7)
        {
            returnBook();
        }
        else if (choice == 8)
        {
            budgetRecommend();
        }
        else if (choice == 0)
        {
            saveBooksToFile();
            printf("程序已退出。\n");
            break;
        }
        else
        {
            printf("输入错误，请重新输入。\n");
        }
    }
    return 0;
}
