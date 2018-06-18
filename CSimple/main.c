#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "mystdafx.h"

#define  CUBIC_INCHES_PER_POUND   166
#define  VOLUME_TO_WEIGHT(n)   (((n) + CUBIC_INCHES_PER_POUND - 1) / \
                                CUBIC_INCHES_PER_POUND)
struct abc
{
    int a;
    int b;
    int c;
};
struct abc s = {1,2,1};
int main(void/*int argc, char *argv[]*/)
{
    printf("%d\n", -22%7);
#if 0
    char buf[81];
    const time_t t = time(NULL);
    strftime(buf, 81, "%Z", localtime(&t));
    printf(buf);
    printf("\n");
    strftime(buf, 81, "%Z", gmtime(&t));
    printf(buf);

    int hour, minute;
    const char *ptime;
    printf("Enter a 24-hour time(hh:mm):");
    scanf("%d:%d", &hour, &minute);

    assert(hour >= 0 && hour < 24 && minute >=0 && minute < 60);

    if (hour >= 0 && hour < 12) {
        if (hour == 0)
            hour = 12;
        ptime = "AM";
    }
    else {
        if (hour != 12)
            hour -= 12;
        ptime = "PM";
    }

    printf("Equivalent 12-hour time: %2d:%.2d %s", hour, minute, ptime);

    int area_code;
    printf("input area code:\n");
    scanf("%d", &area_code);
    const char *pCityname;
    switch ( area_code)
    {
    case 229:
        pCityname = "Albany";
        break;
    case 404:
    case 470:
    case 678:
    case 770:
        pCityname = "Atlanta";
        break;
    case 478:
        pCityname = "Macon";
        break;
    case 706:
    case 762:
        pCityname = "Columbus";
        break;
    case 912:
        pCityname = "Savannah";
        break;
    default:
        pCityname = "Area code not recognized!";
        break;
    }
    printf(pCityname);


    int i = 1;
    switch ( i % 3 )
    {
        case 0: printf("zero");
        case 1: printf("one");
        case 2: printf("two");
    }

    int age;
    bool teenager;
    printf("输入年龄：\n");
    scanf("%d", &age);

    teenager = (age < 13 || age > 19) ? false : true;
    printf( teenager ? "true" : "false");

    int i, j, k;
    i = 3, j = 2;
    //printf("%d", i<j ? -1 : i==j ? 0 : 1);

    i = -15;
    printf("%d\n", i >= 0 ? i : -i);


    // 5.3
    i = 3; j = 4; k = 5;
    printf("%d\n", i < j || ++j < k);  // 1
    printf("%d %d %d\n", i, j, k);  // 3 4 5

    i = 7; j = 8; k = 9;
    printf("%d\n", i - 7 && j++ < k); // 0
    printf("%d %d %d\n", i, j, k);   // 7 8 9

    i = 7; j = 8; k = 9;
    printf("%d\n", (i = j) || (j = k)); // 1
    printf("%d %d %d\n", i, j, k);   // 8 8 9

    i = 1; j = 1; k = 1;
    printf("%d\n", ++i || (++j && ++k));   // 1
    printf("%d %d %d\n", i, j, k);   // 2 1 1

    // 5.2
    i = 10; j = 5;
    printf("%d\n", !i < j);  // 1

    i = 2; j = 1;
    printf("%d\n", !!i + !j);  // 1

    i = 5; j = 0; k = -5;
    printf("%d\n", (i && j) || k);  // 1

    i = 1; j = 2; k = 3;
    printf("%d\n", i < j || k);  // 1

    // 5.1

    i = 2, j = 3;
    k = i * j == 6;
    printf("%d\n", k);  // 1

    i = 5; j = 10; k = 1;
    printf("%d\n", k > i < j);  // 1

    i = 3; j = 2; k = 1;
    printf("%d\n", (i < j) == (j < k)); // 1

    i = 3; j = 4; k = 5;
    printf("%d\n", i % j + i < k);  // 0

    printf(" -1 / 2 : %d\n", -1 / 2);
    printf(" -1 % 2 : %d\n", -1 % 2);
    printf(" 1 / -2 : %d\n", 1 / -2);
    printf(" 1 % -2 : %d\n", 1 % -2);


    //练习3.2
    int itemNum = 0;
    printf("Enter item number:");
    scanf("%d", &itemNum);

    float unitPrice = 0.f;
    printf("Enter unit price:");
    scanf("%f",&unitPrice);

    int year = 0;
    int month = 0;
    int day = 0;
    printf("输入购买日期，格式为 mm/dd/yyyy:");
    scanf("%d/%d/%d", &month, &day, &year);

    // 格式化输出
    printf("Item\t\tUnit Price\t\tPurchase Date\n");
    printf("%d\t\t%10.2f\t\t%02d/%02d/%d",
           itemNum, unitPrice, month, day, year);


    // 练习3.1
    int year = 0;
    int month = 0;
    int day = 0;
    printf("输入一个日期，格式为 mm/dd/yyyy:");
    scanf("%d/%d/%d", &month, &day, &year);
    printf("你输入的日期是:%d-%d-%d\n", year, month, day);

    char  a[20];
    const char *str = "0123456789";
    memcpy(a, str, 11);
    printf("%s\n", a);
    memcpy(a+5, a, 11);     // 测试 memcpy
    printf("%s\n", a);


    printf("To C, or not to C , that is a question!\n\n");
    size_t sz;
    unsigned int* p = &sz;

    square(4.0);
    square(11.0);
    boo(3);


    int N = 10, M = 20;
#define N  (N+M)
#define M  (N+M)
    printf("%d\n", N);

    for (color =red; color <= blue; color++)
        printf("%d\n", color);

    FILE *fp = fopen(argv[1], "r+");
    char str[10];
    while (fgets(str, 10, fp))
    {
        fputs(str, stdout);
    }

    int ch;
    while (EOF != (ch = getc(fp)))
    {
        if (ch == '$')
        {
            ungetc('#', fp);
        }
        else if (ch == '#')
        {
            fpos_t  pos;
            fgetpos(fp, &pos);
            fseek(fp, -1, SEEK_CUR);
            if (EOF ==  putc(ch, fp))
            {
                perror("putc(ch, fp) error!\n");
            }
            fsetpos(fp, &pos);
        }
    }
    rewind(fp);
    while (EOF != (ch = getc(fp)))
    {
        putchar(ch);
    }
    fclose(fp);




    float f = 3 / 2 / 1.0;
    int  i = 0x80000000;
    int  j = i + 1;
    char ch = 255;
    printf("i = %u, j = %d, f = %e, &g_num = %p\n", i, j, f, &g_num);
    printf("ch = %i\n", ch);


    bool f;
    printf("%zd\n", sizeof('b'));

    printf("%zu", sizeof(STRING));
    unsigned  int n = -1;
    int64_t  m = n;
    printf("\n%lld", m);

    printf("*\n%d", printf("%-16.2g", 0.00000253));

    int height, length, width;
    printf("输入箱子的规格：\nLength:");
    scanf("%d", &length);
    printf("Width:");
    scanf("%d", &width);
    printf("Height:");
    scanf("%d", &height);
    printf("您输入的是：Length = %d, Width = %d, Height = %d\n",
           length, width, height);

    int volume = length * width * height;
    int weightByVolume = VOLUME_TO_WEIGHT(volume);

    printf("Demenisions(in inch): %d x %d x %d\n", length, width, height);
    printf("Volumes(cubic inches): %d\n", volume);
    printf("Demenisional weight(pounds): %d\n", weightByVolume);
#endif
    return 0;
}
