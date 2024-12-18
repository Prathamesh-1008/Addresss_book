#ifndef ADDRESS_BOOK_H
#define  ADDRESS_BOOK_H
struct Address_book
{
  char name[20];
  char mobile_no[12];
  char gmail[25];
  char loction[20];
}info;

int count;
char search_by[30];
void add();
void copy(FILE *,FILE *);
void print();
void search();
void edit();
void delete();
void mo_no();
void gmail();
char * choice();
int ascend(char *, char *);
int descend(char *, char *);
#endif