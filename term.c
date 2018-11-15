#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TITLE_LENGTH 30
#define MAX_CONTENT_LENGTH 100

#define MAX_MONTH 12
#define MAX_DATE 31

typedef struct
{
   char title[MAX_TITLE_LENGTH];
   char content[MAX_TITLE_LENGTH];
} _PLAN;

typedef struct
{
   int year;
   int month;
   int day;

   _PLAN *plan;

   struct _DAY *tomorrow;
   struct _DAY *yesterday;
} _DAY;

int isLeapYear(int year); //윤년인지 아닌지를 판단하는 함수
int getDayoftheWeek(int year, int month, int day); // 년, 월, 일을 넘기면 요일을 반환하는 함수
_DAY initTargetDay(int month_day[]); // 오늘 날짜를 받아와서 기준일을 생성하는 함수

int main()
{
   int month_day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   char dayoftheWeek[7][4] = { "SUN\0", "MON\0", "TUE\0", "WED\0", "THU\0", "FRI\0", "SAT\0" };

   _DAY targetDay = initTargetDay(month_day);

   printf("%d-%d-%d\n", targetDay.year, targetDay.month, targetDay.day);

   int answer = getDayoftheWeek(targetDay.year, targetDay.month, targetDay.day);

}

int isLeapYear(int year)
{
   if( !(year % 4) && (year % 100) || !(year % 400) ) return 1;
   else return 0;
}

int getDayoftheWeek(int year, int month, int day)
{
   int month_day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   // 1900년 1월 1일은 월요일
   // 일월화수목금토 0 ~ 6

   int i;

   int date = (year-1900)*365;

   for( i = 1; i < month; i++ )
   {
      if( i == 2 && isLeapYear(year) )
         ++date;

      date+=month_day[i];
   }

   date+=day;

   return date&7;

}

_DAY initTargetDay(int month_day[])
{
   _DAY targetDay;

   int day;

   while(1)
   {
      printf("년 월 일을 입력하세요. 입력 형태 : 20181105\n> ");
      scanf("%d", &day);

      targetDay.year = day/10000;
      targetDay.month = (day/100)%100;
      if( targetDay.month < 1 || targetDay.month > 12 )
      {
         printf("[error]올바른 월을 입력하세요.\n");
         continue;
      }
      targetDay.day = day%100;
      if( targetDay.day < 1 || targetDay.day > month_day[targetDay.month] )
      {
         printf("[error]올바른 일을 입력하세요.\n");
         continue;
      }

      break;
   }

   return targetDay;
}