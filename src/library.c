#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"

/* library.c 内部使用的函数声明（不对外暴露） */
int findBookid(int id);
void clearInputBuffer(FILE *stream);
int readLine(FILE *stream, char str[], int size);
int inputDouble(const char *prompt, double *value);
void inputString(const char *prompt, char str[], int size);
void dfsBuyBook(int index, double sum, int bookCount);

Book books[max];
int count=0;//书的数量
double budget;
int chosen[max];
int bestChosen[max];
double bestSum=0;
int bestBookCount=0;
int hasBestPlan=0;

void clearInputBuffer(FILE *stream)
{
    int ch;
    while ((ch = fgetc(stream)) != '\n' && ch != EOF)
    {
    }
}

/* 读取一行：成功返回 1；遇到输入结束(EOF)返回 0 */
int readLine(FILE *stream, char str[], int size)
{
    if (fgets(str, size, stream) != NULL)
    {
        str[strcspn(str, "\n")] = '\0';
        return 1;
    }
    str[0] = '\0';
    return 0;
}

int inputInt(const char *prompt, int *value)
{
    char line[100];
    char extra;

    while (1)
    {
        printf("%s", prompt);
        if (readLine(stdin, line, sizeof(line)) == 0)
        {
            printf("\n检测到输入结束，程序退出。\n");
            exit(0);
        }
        if (strlen(line) == 0)
        {
            printf("输入不能为空，请重新输入。\n");
            continue;
        }
        if (sscanf(line, "%d %c", value, &extra) == 1)
        {
            return 1;
        }
        printf("输入错误，请重新输入。\n");
    }
}

int inputDouble(const char *prompt, double *value)
{
    char line[100];
    char extra;

    while (1)
    {
        printf("%s", prompt);
        if (readLine(stdin, line, sizeof(line)) == 0)
        {
            printf("\n检测到输入结束，程序退出。\n");
            exit(0);
        }
        if (strlen(line) == 0)
        {
            printf("输入不能为空，请重新输入。\n");
            continue;
        }
        if (sscanf(line, "%lf %c", value, &extra) == 1)
        {
            return 1;
        }
        printf("输入错误，请重新输入。\n");
    }
}

void inputString(const char *prompt, char str[], int size)
{
    while (1)
    {
        printf("%s", prompt);
        if (readLine(stdin, str, size) == 0)
        {
            printf("\n检测到输入结束，程序退出。\n");
            exit(0);
        }
        if (strlen(str) == 0)
        {
            printf("输入不能为空，请重新输入。\n");
            continue;
        }
        return;
    }
}

void addBook(void)
{
    if (count >= max)
    {
        printf("图书数量已满，无法继续添加\n");
        return;
    }

    while (1)
    {
        inputInt("请输入图书编号:", &books[count].id);
        if (findBookid(books[count].id) != -1)
        {
            printf("该图书编号已存在，无法重复添加\n");
        }
        else
        {
            break;
        }
    }

    inputString("请输入图书名称:", books[count].name, sizeof(books[count].name));
    inputString("请输入作者名称:", books[count].author, sizeof(books[count].author));
    inputString("请输入出版社:", books[count].publisher, sizeof(books[count].publisher));
    inputDouble("请输入价格:", &books[count].price);
    inputInt("请输入图书总量:", &books[count].total);
    inputInt("是否推荐(1.是 0.否): ", &books[count].recommend);
    books[count].stock = books[count].total;
    count++;
    saveBooksToFile();
    printf("图书添加成功\n");
}

void listBook(void)
{
    if(count == 0)
    {
        printf("当前没有图书信息。\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        printf("编号:%d\n", books[i].id);
        printf("书名:%s\n", books[i].name);
        printf("作者:%s\n", books[i].author);
        printf("出版社:%s\n", books[i].publisher);
        printf("价格:%.2lf\n", books[i].price);
        printf("总数量:%d\n", books[i].total);
        printf("库存:%d\n", books[i].stock);
        if (books[i].recommend == 1)
        printf("推荐状态:推荐\n");
        else
        printf("推荐状态:普通\n");
        printf("-------------------\n");
    }
}

int findBookid(int id)
{
    for(int i=0;i<count;i++)
    {
        if(books[i].id==id)
        {
            return i;
        }
    }
    return -1;
}

void searchBook(void)
{
    int id;
    int index;
    inputInt("请输入要查询的图书编号: ", &id);
    index = findBookid(id);
    if(index == -1)
    printf("未找到图书信息\n");
    else
    {
        printf("编号:%d\n",books[index].id);
        printf("书名:%s\n", books[index].name);
        printf("作者:%s\n", books[index].author);
        printf("出版社:%s\n", books[index].publisher);
        printf("价格:%.2lf\n", books[index].price);
        printf("总数量:%d\n", books[index].total);
        printf("库存:%d\n", books[index].stock);
        if (books[index].recommend == 1)
        printf("推荐状态:推荐\n");
        else
        printf("推荐状态:普通\n");
    }
}

void deleteBook(void)
{
    int id;
    int index;
    inputInt("请输入想要删除的图书:", &id);
    index = findBookid(id);
    if(index==-1)
    {
        printf("未找到图书信息\n");
        return;
    }
    else
    {
        for(int i=index;i<count-1;i++)
        {
            books[i]=books[i+1];
        }
        count--;
        saveBooksToFile();
        printf("图书删除成功\n");
    }
}

void updateBook(void)
{
    int id;
    int index;
    inputInt("请输入要修改的图书:", &id);
    index = findBookid(id);
    if(index==-1)
    {
        printf("未找到图书信息\n");
        return;
    }
    else
    {
        int borrowed = books[index].total - books[index].stock;
        int newTotal;
        inputString("请输入新的图书名称: ", books[index].name, sizeof(books[index].name));
        inputString("请输入新的作者名称: ", books[index].author, sizeof(books[index].author));
        inputString("请输入新的出版社: ", books[index].publisher, sizeof(books[index].publisher));
        inputDouble("请输入新的价格: ", &books[index].price);
        while (1)
        {
            inputInt("请输入新的图书总量: ", &newTotal);
            if (newTotal < borrowed)
            {
                printf("新的总量(%d)不能小于已借出数量(%d)，请重新输入。\n", newTotal, borrowed);
                continue;
            }
            break;
        }
        books[index].total = newTotal;
        inputInt("是否推荐(1.是 0.否): ", &books[index].recommend);
        books[index].stock = books[index].total - borrowed;
        saveBooksToFile();
        printf("图书信息修改成功\n");
    }
}

void borrowBook(void)
{
    int id;
    int index;
    inputInt("请输入要借阅的图书编号: ", &id);
    index = findBookid(id);
    if (index == -1)
    {
        printf("未找到图书信息\n");
        return;
    }
    if (books[index].stock <= 0)
    {
        printf("库存不足，无法借阅\n");
        return;
    }
    books[index].stock--;
    saveBooksToFile();
    printf("借书成功，当前库存:%d\n", books[index].stock);
}

void returnBook(void)
{
    int id;
    int index;
    inputInt("请输入要归还的图书编号: ", &id);
    index = findBookid(id);
    if (index == -1)
    {
        printf("未找到图书信息\n");
        return;
    }

    if (books[index].stock >= books[index].total)
    {
        printf("该图书库存已满，无需归还\n");
        return;
    }
    books[index].stock++;
    saveBooksToFile();
    printf("还书成功，当前库存:%d\n", books[index].stock);
}

void saveBooksToFile(void)
{
    FILE *fp = fopen("books.txt", "w");
    if (fp == NULL)
    {
        printf("文件打开失败，无法保存数据\n");
        return;
    }

    fprintf(fp, "%d\n", count);

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d\n%s\n%s\n%s\n%.2lf %d %d %d\n",
                books[i].id,
                books[i].name,
                books[i].author,
                books[i].publisher,
                books[i].price,
                books[i].total,
                books[i].stock,
                books[i].recommend);
    }

    fclose(fp);
}

void loadBooksFromFile(void)
{
    FILE *fp = fopen("books.txt", "r");
    int result;
    int n;
    if (fp == NULL)
    {
        return;//文件不存在：首次运行，正常启动，没有图书数据
    }

    //读取图书数量，必须是合法整数且在 0~max 范围内
    if (fscanf(fp, "%d", &n) != 1 || n < 0 || n > max)
    {
        printf("books.txt 格式不正确，已忽略文件内容\n");
        count = 0;
        fclose(fp);
        return;
    }
    clearInputBuffer(fp);

    for (int i = 0; i < n; i++)
    {
        if (fscanf(fp, "%d", &books[i].id) != 1)
        {
            printf("books.txt 数据不完整，已忽略文件内容\n");
            count = 0;
            fclose(fp);
            return;
        }
        clearInputBuffer(fp);
        readLine(fp, books[i].name, sizeof(books[i].name));
        readLine(fp, books[i].author, sizeof(books[i].author));
        readLine(fp, books[i].publisher, sizeof(books[i].publisher));
        result = fscanf(fp, "%lf %d %d %d",
               &books[i].price,
               &books[i].total,
               &books[i].stock,
               &books[i].recommend);
        if (result == 3)
        {
            books[i].recommend = 0;//兼容没有 recommend 字段的旧格式
        }
        else if (result != 4)
        {
            printf("books.txt 数据不完整，已忽略文件内容\n");
            count = 0;
            fclose(fp);
            return;
        }
        clearInputBuffer(fp);
    }

    count = n;//全部记录都读取成功后，才提交图书数量
    fclose(fp);
}

void dfsBuyBook(int index, double sum, int bookCount)
{
    if(sum>budget)
    return;
    if(index==count)
    {
        if(bookCount==0)
        {
            return;
        }
        if(hasBestPlan==0 || sum>bestSum || (sum==bestSum && bookCount>bestBookCount))
        {
            hasBestPlan = 1;
            bestSum = sum;
            bestBookCount = bookCount;
            for(int i=0;i<count;i++)
            {
                bestChosen[i] = chosen[i];
            }
        }
        return;
    }
    chosen[index]=0;
    dfsBuyBook(index+1,sum,bookCount);
    chosen[index]=1;
    dfsBuyBook(index+1,sum+books[index].price,bookCount+1);
    chosen[index]=0;
}

void budgetRecommend(void)
{
    inputDouble("请输入预算: ", &budget);

    for (int i = 0; i < count; i++)
    {
        chosen[i] = 0;
        bestChosen[i] = 0;
    }

    bestSum = 0;
    bestBookCount = 0;
    hasBestPlan = 0;

    dfsBuyBook(0, 0, 0);

    if (hasBestPlan == 0)
    {
        printf("当前预算下没有合适方案\n");
        return;
    }

    printf("最优方案如下:\n");
    for(int i=0;i<count;i++)
    {
        if(bestChosen[i]==1)
        {
            printf("%s\n",books[i].name);
        }
    }
    printf("最优方案书的数量:%d\n", bestBookCount);
    printf("总价:%.2lf\n",bestSum);
}
