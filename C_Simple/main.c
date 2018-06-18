#include <ctype.h>
#include "global.h"
#include "mybitset.h"
#include <conio.h>

extern int a[10];

struct  ABC {
    bool fill:1;
    unsigned char color : 3;
};
//================================================
int main(void)
{
//    int n;
//    printf("%d", printf("%d\n", scanf("%d", &n)));
//    printf("%d\n", -11 % 3);
//    printf("Hello, world!\n");
//    printf("       *\n");
//    printf("      *\n");
//    printf("     *\n");
//    printf("*   *\n");
//    printf(" * *\n");
//    printf("  *\n");
//
//    printf("球的体积是: %f m^3\n", 3.14159 * (4.0/3.0) * (10 * 10 * 10));
//    printf("%.2f\n", 100.00 * (1 + 0.05));
//    printf("Hello world!\n");
//    goto Label;
//    for (int i = 0; ; i += 7)
//        if (i%2 == 1 && i%3 == 2 && i%5 == 4 && i%7 == 0) {
//            printf("%d", i);
//
//            break;
//
//        }
//        Label:
//    int i = 1;
//    printf("%d\n", sizeof (++i));
//    printf("%d\n", i);


//    printf("%d\n", sizeof(a)/sizeof(*a));
//    for (int i = 0; i < 10; ++i)
//        printf("%d\n", i);
//
//    if (-1LL < 1U)
//        puts("-1 is less than 1U");
//    else
//        puts("-1 is not less than 1U");
//
//    switch (4)
//    {
//int i;
//    case 1:
//        break;
//    case 4:  i= 0;
//        printf("%d",i);
//        break;
//    }
//    char *p = "I am a c";
//    char ar[] = {'I',' ','a','m',' ','a', ' ','c','\0'};
//    //gets(ar);
//    printf("%s\n", ar);
//
//    char *str1 = "this dddd", *str2 = "this aaa";
//    while (*str1 && *str1 - *str2 == 0) // *str2不需要测试
//        ++str1, ++str2;
//    return printf("%d",*str1 - *str2);
//    int ref[] = {8,4,0,2};
//    for (int index = 0, *ptr = ref; index < 4; ++index, ++ptr)
//        printf("%d %d\n", ref[index], *ptr);

//    double vx, vy;
//    printf("输入两个实数(n n):\n");
//    scanf("%lf%lf", &vx, &vy);
//    printf("vx+vy:%f\n", vx+vy);
    //setvbuf(stdin, NULL,_IONBF, 0);
//    const char *str = "12345566";
//    char *str2 = str;
//    printf("stdin buffer size: %d\n", stdin->_bufsiz);
//    int ch;
//    while (EOF != (ch = getchar()))
//    {
//        printf("stdin->_cnt: %d, %c, stdin->_base:%s",
//               stdin->_cnt, ch, stdin->_base);
//    }

//    int ch;
//
//    while ('#' != (ch = getchar())) {
//        if (!isspace(ch)) {
//
//            printf("Step1\n");
//
//            if (ch == 'b')
//                break;
//
//            if (ch != 'c') {
//                switch (ch) {
//                default:
//                    printf("Step2\n");
//
//                case 'h':
//                    printf("Step3\n");
//                    break;
//                } // end switch
//            } // end inner if
//        }// end outer if
//    } // end while
//
//    printf("Done\n");


    //    FILE *pf = fopen("in.txt", "rb+");
    //    char ch;
    //
    //    while (fread(&ch, 1, 1, pf) == 1) {
    //        ch = (char)tolower(ch);
    //        fseek(pf, -1, SEEK_CUR);
    //        fwrite(&ch, 1, 1, pf);
    //        fseek(pf, 0, SEEK_CUR);
    //    }
    //
    //    rewind(pf);
    //    fputs(getbufline(pf, '\n'), stdout);

    //  const char *str = "abcd";
    //  *str = 'e';
    //  printf("\n%s",str);
    //    wint_t ch;
    //    while ((ch = getwc(stdin)) != WEOF)
    //    {
    //        if (ch == L'#')
    //        {
    //            ungetwc(ch, stdin);
    //        }
    //        else
    //            putwchar(ch);
    //    }

    //    fputs(getbufline(stdin,'\n'), stdout);

    //    SList  lst = NULL;
    //    for (int i = 0; i != 20; ++i)
    //        SListPush_front(&lst, i);
    //
    //    SListSort(&lst);
    //    for (Node *p = lst; p != NULL; p = p->next)
    //        printf("%3i", p->value);
    //


    //    int SIZE = 5;
    //    int *ia = sfalloc(int, SIZE + 1);    // + 1 表示为计数位预留空间
    //    ia[0] = 0;       // 计数位
    //    int tmp;
    //    int state;
    //    while (state = scanf("%d%c", &tmp), state != EOF && state != 0)
    //    {
    //        ia[++ia[0]] = tmp;
    //        if (ia[0] == SIZE)     // 已经保存了 ia[0] 个值
    //        {
    //            SIZE <<= 1;
    //            int *newmem = sfalloc(int, SIZE + 1);
    //            memcpy(newmem, ia, ia[0]*sizeof(int));
    //            free(ia);
    //            ia = newmem;
    //        }
    //    }
    //    if (state==0)
    //    {
    //
    //        fprintf(stderr, "Invalid input!\n");
    //        exit(EXIT_FAILURE);
    //    }
    //    for (int i=1; i <= ia[0]; ++i)
    //        printf("%i", ia[i]);
    //


    //    const char *temp = getbufline(stdin, '\n');
    //    char  str[strlen(temp)+1];
    //    strcpy(str, temp);
    //    puts(str);

    //    int a;
    //    while (scanf("%i", &a) != 1 || a <= 0)
    //    {
    //        ignore(stdin, '\n');
    //        fprintf(stderr, "Invalid input! Please input a positive number:\n");
    //    }


    //    char arr[2] = {20, 0};
    //    reset_bit(arr, 4);
    //    printf("%i\n", arr[0]);


    //    printf("%x", reverse_bits(0xf00ff00f));


    //    unsigned  int n = 0xff000000;
    //    int  i = 0xff000000;
    //    n >>= 24;
    //    i >>= 24;
    //    printf("%u , %i ", n, i);

    //    printf("17的平方根为：%f\n", mySqrt(17));
    //    printf("17的平方根为：%f\n", sqrt(17));
    //    char str[80];
    //    copy_n(str, "This is some string!\n", 80);
    //    fputs(str, stdout);

    //    srand(time(NULL));
    //    for (int i=0; i != 1000; )
    //        printf("%d%c", AverageProbability(1000, 10000), ((++i%10 == 0) ? '\n' : '\t'));

    puts("\nOver!");
    return 0;
}
