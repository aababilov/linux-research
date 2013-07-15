#include <unistd.h>
#include <stdio.h>
unsigned char buf[1024];

int main()
{
	unsigned char *p = buf;
	unsigned c;
	int num = 0, ans = 0;
	unsigned char oper = '+'; //0+ 1- 2* 3/
	read(0, buf, sizeof(buf) - 1);
	while (1) {
		c = *p++;
		if ('0' <= c && c <= '9') {
			num = num * 10 + (c - '0');
		} else {			
			if (oper == '+')
				ans += num;
			else if (oper == '-')
				ans -= num;
			else if (oper == '*')
				ans *= num;
			else if (oper == '/') 
				if (num != 0)
					ans /= num;
				else
					printf("division by zero!\n");		
			else {
				printf("bad operator %c (0x%hhx)!\n", oper, oper);
			}			
			if (c == '\0' || c == '\n')
				break;
			num = 0;
			oper = c;			
		}
	}
//	p = buf + sizeof(buf) - 1;
	*p = 0;
	if (ans < 0) {
		c = 1;
		ans *= -1;
	} else {
		c = 0;
	}
	do {
		--p;
		*p = '0' + ans % 10;
		ans /= 10;
	} while (ans);
	if (c)
		*--p = '-';
				
	printf("%s\n", p);
	_exit(0);
}
