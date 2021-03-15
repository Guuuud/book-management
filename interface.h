//
//  interface.h
//  book_management
//
//  Created by wvwuu on 2021/3/8.
//

#ifndef interface_h
#define interface_h

#include <stdio.h>
#include "book.h"
#include "user.h"
#endif /* interface_h */


char * password;
char * user_name;

char * case_title;
char * case_author;

unsigned int case_year;

void main_menu(BookArray * headnode, UserArray * usernode);
char * ask_question(const char *question);

