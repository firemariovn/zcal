/*
[October 2024]
Su Mo Tu We Th Fr Sa
       1  2  3  4< 5
 6  7  8  9 10 11 12
13 14 15 16 17 18 19
20 21 22 23 24 25 26
27 28 29 30 31
*/

#include <stdio.h>
#include <time.h>

int doZellerCongruence(int _q, int _m, int year) {
  int result = -1;

  if (_m >= 3 || _m <= 12) {
    // _m = _m;
  } else {
    return -1; // FIXME: January and February
  }

  int _k = year % 100;
  int _j = year / 100;

  // printf("[DEBUG] q = %d \n", _q);
  // printf("[DEBUG] m = %d \n", _m);
  // printf("[DEBUG] K = %d \n", _k);
  // printf("[DEBUG] J = %d \n", _j);
  result = (_q + ((13 * (_m + 1)) / 5) + _k + _k / 4 + _j / 4 - 2 * _j) % 7;

  result = ((result + 6) % 7) + 1; // ISO week date thing...

  return result;
}

int getDayOfWeek(int day, int month, int year) {
  return doZellerCongruence(day, month, year);
}

char *getMonth(int month) {
  if (month < 1 || month > 12)
    return "UNKNOWN";
  char *szMonths[] = {
      "January",   // 1
      "February",  // 2
      "March",     // 3
      "April",     // 4
      "May",       // 5
      "June",      // 6
      "July",      // 7
      "August",    // 8
      "September", // 9
      "October",   // 10
      "November",  // 11
      "December"   // 12
  };

  return szMonths[month - 1];
}

int daysInMonth(int month, int year) {
  if (month < 1 || month > 12)
    return -1;

  int daysInMonths[] = {
      31, // 1
      28, // 2
      31, // 3
      30, // 4
      31, // 5
      30, // 6
      31, // 7
      31, // 8
      30, // 9
      31, // 10
      30, // 11
      31  // 12
  };

  if (month == 2) {
    if (year % 4 == 0)
      return 29;
  }

  return daysInMonths[month - 1];
}

int main() {
  time_t now;
  time(&now);
  struct tm *local = localtime(&now);

  int currentDay = local->tm_mday;
  int currentMonth = local->tm_mon + 1;
  int currentYear = local->tm_year + 1900;

  // printf("day: ");
  // printf("%d\n", currentDay);

  // printf("month: ");
  // printf("%d\n", currentMonth);

  // printf("year: ");
  // printf("%d\n", currentYear);

  // printf("day of month:\n");
  // printf("%02d\n", daysInMonth(currentMonth, currentYear));

  // printf("month string:\n");
  // printf("%s\n", getMonth(currentMonth));

  // printf("Zeller day :\n"); // 1 = Su .. 7 = Sa
  // printf("%d\n", getDayOfWeek(currentDay, currentMonth, currentYear));

  // printf("----------\n");
  printf("[%s %04d]\n", getMonth(currentMonth), currentYear);
  printf("Su Mo Tu We Th Fr Sa\n");
  size_t nZellerDay = getDayOfWeek(currentDay, currentMonth, currentYear);
  size_t nLoop = daysInMonth(currentMonth, currentYear);
  for (int i = 1; i <= nLoop; ++i) {
    if (nZellerDay == i) {
      printf("%02d ", currentDay);
    } else {
      printf("[] ");
      if (i % 7 == 0)
        printf("\n");
    }
  }

  return 0;
}
