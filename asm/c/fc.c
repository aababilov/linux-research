#include <unistd.h>
#include <stdio.h>
char buf[167] = "www";
    char b[12];
    int f ;

int main()
{
/*    char buuu[234];
    int a, b;
    unsigned int c, d;
    a = 10;
    b = -10;
    a = a * b;
    
    c = 5;
    d = -10;
    c = d * c;
    printf("%d %ud", a, c);
    scanf("%s", buuu);
    write(1, "hello world\n", 13);*/
    f = buf[1];
    write(1, buf, 12);
    return 0;
}
