#ifndef _YOS_STRING_
#define _YOS_STRING_ 1

#include <x86.h>

#define COLUMNS                 80
#define LINES                   24
#define ATTRIBUTE               7
#define pos(x, y) ((x + y * COLUMNS) * 2)
#define char_attr(c, a) ((a << 8) | (c & 0xff))

#endif

static int x;
static int y;

static void newline() {
	x = 0;
	y++;
	if (y >= LINES)
		y = 0;
}

static void putchar(int c) {
	if (c == '\n' || c == '\r')
	{
		newline();
		return;
	}
	_putc(pos(x, y), char_attr(c, ATTRIBUTE));

	x++;
	if (x >= COLUMNS) {
		newline();
		return;
	}
}

void cls() {
	int i;
	for (i = 0; i < COLUMNS * LINES * 2; i += 2)
		_putc(i, 0);
	x = 0;
	y = 0;
}

static void itoa (char *buf, int base, int d)
{
	char *p = buf;
	char *p1, *p2;
	unsigned long ud = d;
	int divisor = 10;

	/* 如果指定了 %d 并且 D 是负数，在开始添上负号。 */
	if (base == 'd' && d < 0)
	{
		*p++ = '-';
		buf++;
		ud = -d;
	}
	else if (base == 'x')
		divisor = 16;

	/* 用 DIVISOR 去除 UD 直到 UD == 0。 */
	do
	{
		int remainder = ud % divisor;

		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
	}
	while (ud /= divisor);

	/* 在字符串尾添上终结符。 */
	*p = 0;

	/* 反转 BUF。 */
	p1 = buf;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}

void printf (const char *format, ...)
{
	char **arg = (char **) &format;
	int c;
	char buf[20];

	arg++;

	while ((c = *format++) != 0)
	{
		if (c != '%')
			putchar (c);
		else
		{
			char *p;

			c = *format++;
			switch (c)
			{
			case 'd':
			case 'u':
			case 'x':
				itoa (buf, c, *((int *) arg++));
				p = buf;
				goto string;
				break;

			case 's':
				p = *arg++;
				if (! p)
					p = "(null)";

string:
				while (*p)
					putchar (*p++);
				break;

			default:
				putchar (*((int *) arg++));
				break;
			}
		}
	}
}