//
//  user.h
//  book_management
//
//  Created by wvwuu on 2021/3/8.
//

#ifndef user_h
#define user_h

#include <stdio.h>
#include "book.h"
#endif /* user_h */



typedef struct _User{
    char * name;
    char * password;
    Book book[9];
    int borrow;
}User;



typedef struct _UserArray{
    
    struct _UserArray * next;
    User user;
    
}UserArray;


UserArray * createLibra();

//login有关判断
int name_available(UserArray * u,char * name);
int password_right(UserArray * u,char * password,char * name);
UserArray * user_available(UserArray * u, char * name);

//借书
User borrow_book(User u,BookArray * book);
//展示借的书
void display_borrow(User u);
UserArray * createUser(User user);
void add_user(User user,UserArray * headnode);
//const struct User * users_add(struct User a);
//void exist_or_not();

int if_repeat(User u,char * tiltle);

struct User users_add(struct User a);
