//
//  user.c
//  book_management
//
//  Created by wvwuu on 2021/3/8.
//

#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int user_number = 0;
struct User * all_users = 0;
int user_memory = 0;

//用于创建user的头节点
UserArray * createLibra(){
    UserArray * head = (UserArray*)malloc(sizeof(UserArray));
    head -> next = NULL;
    return head;
}

//用于创建user的节点
UserArray * createUser(User user){
    
    UserArray * newNode = (UserArray*)malloc(sizeof(UserArray));
    newNode -> user = user;
    newNode -> next = NULL;
    return newNode;
}

//遍历来发现名字是否已被注册
//以及判断数据库中有没有这个名字，以用于登陆
//但是只能用于图书管理员
int name_available(UserArray * u,char * name){
    
    UserArray * pMove = u->next;
    if(pMove == NULL){
        printf("空的啊阿啊撒啊啊！\n");
    }
    //返回0无，返回1有
    while (pMove) {
        if (strcmp(name, pMove->user.name) == 0) {
            return 1;
        }else{
            pMove = pMove->next;
        }
        
    }
    return 3;
}

UserArray * user_available(UserArray * u, char * name){
    UserArray * pMove = u->next;
    if(pMove == NULL){
        printf("空的啊阿啊撒啊啊！\n");
    }
    //返回0无，返回1有
    while (pMove) {
        if (strcmp(name, pMove->user.name) == 0) {
            return pMove;
        }else{
            pMove = pMove->next;
        }
        
    }
    return NULL;
}


User borrow_book(User u,BookArray * book){
    if (book ->book.copies > 0) {
        u.book[10-u.borrow] = (book->book);
        u.book[10-u.borrow].title = book->book.title;
        //printf("能借的书是%d\n",u.borrow);
        //printf("%d",u.book[10-u.borrow].id);
        //printf("%s",u.book[10-u.borrow].title);
        u.borrow -= 1;
        book->book.copies-=1;
        //printf("能借的书是%d\n",u.borrow);
        printf("\nborrowed success!\n");
       
        display_borrow(u);
    }else{
        printf("Sorry, the book \"%s\" were all borrowed.\n",book->book.title);
    }
    return u;
}

int if_repeat(User u,char * tiltle){
    for (int i = 0; i < 10-u.borrow; i++) {
        if (strcmp(u.book[i].title, tiltle) == 0) {
            
            return 1;
        }
    }
    return 0;
}


void display_borrow(User u){
    printf("Here is your borrow list\n");
    printf("ID\tTitle\t\t\t\t\tAuthor\t\t\tyear\n");
    for (int i = 0; i < 10-u.borrow; i++) {
        if (u.book[i].year==20000) {
            continue;
        }
        printf("%d\t",u.book[i].id);
        
        printf("%s",u.book[i].title);
        title_length(u.book[i].title);
        printf("%s",u.book[i].authors);
        author_length(u.book[i].title);
        printf("%d\t\n",u.book[i].year);
        //printf("LLLLDLDLDLDLDLLD");
    }
    //printf("%d]]]]]]",u.borrow);
}

//int return_book(char * title){
//    
//}
int password_right(UserArray * u,char * password,char * name){
    UserArray * pMove = u->next;
    while (pMove) {
        if (strcmp(pMove->user.password, password) == 0 && strcmp(name, pMove->user.name) == 0) {
            
            return 1;
        }else{
            pMove = pMove->next;
        }
    }
    
    return 0;
}
//添加用户
void add_user(User user,UserArray * headnode){
    
    UserArray * add_book = createUser(user);
    add_book -> next = headnode -> next;
    headnode -> next = add_book;
    
}


//用于创建图书管理员






