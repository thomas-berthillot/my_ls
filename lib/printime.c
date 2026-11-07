#include "lib.h"
#include <stdlib.h>
#include <time.h>

static void printrecent(int month, int day, int hours, int minutes)
{
    char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    my_putstr(months[month]);
    my_putchar(' ');
    if (day < 10)
        my_putchar(' ');
    my_putnbr(day);
    my_putchar(' ');
    if (hours < 10)
        my_putchar('0');
    my_putnbr(hours);
    my_putchar(':');
    if (minutes < 10)
        my_putchar('0');
    my_putnbr(minutes);
    my_putchar(' ');
}

static void printold(int month, int day, int year)
{
    char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    my_putstr(months[month]);
    my_putchar(' ');
    if (day < 10)
        my_putchar(' ');
    my_putnbr(day);
    my_putstr("  ");
    my_putnbr(year);
    my_putchar(' ');
}

static int get_month(char *str)
{
    char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    for (int i = 0; i < 12; i++) {
        if (str[0] == months[i][0] && str[1] == months[i][1]
            && str[2] == months[i][2])
            return i;
    }
    return 0;
}

static void parse_date(char *s, int *m, int *d)
{
    *m = get_month(&s[4]);
    if (s[8] == ' ')
        *d = s[9] - '0';
    else
        *d = (s[8] - '0') * 10 + (s[9] - '0');
}

static void parse_time_values(char *s, int *h, int *min, int *y)
{
    *h = (s[11] - '0') * 10 + (s[12] - '0');
    *min = (s[14] - '0') * 10 + (s[15] - '0');
    *y = (s[20] - '0') * 1000 + (s[21] - '0') * 100
        + (s[22] - '0') * 10 + (s[23] - '0');
}

void printime(time_t mtime)
{
    char *t_str = ctime(&mtime);
    time_t cur;
    int m;
    int d;
    int h;
    int min;
    int y;

    if (t_str == NULL)
        return;
    parse_date(t_str, &m, &d);
    parse_time_values(t_str, &h, &min, &y);
    time(&cur);
    if (cur - mtime < 180L * 24 * 3600 && cur - mtime >= 0)
        printrecent(m, d, h, min);
    else
        printold(m, d, y);
}
