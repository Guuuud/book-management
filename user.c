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


void borrow_book(UserArray * u, char * name,int id,BookArray * book){
    UserArray * pMove = u ->next;
    while (pMove) {
        if (strcmp(name, pMove->user.name) == 0) {
            //pMove->user.book = book;
            BookArray * borrow_book = find_book_by_id(book, id);
            pMove ->user.book[10 - pMove ->user.borrow] = borrow_book->book;
            pMove ->user.borrow -= 1;
        }else{
            pMove = pMove->next;
        }
        
    }
}

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






