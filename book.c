//
//  book.c
//  book_management
//
//  Created by wvwuu on 2021/3/8.
//

#include "book.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char *as_question(const char *question) {

    printf("%s",question);

    const int size_step = 2;
    char *answer = malloc(size_step);
    answer[0] = 0;
    
    
    char *next_chunk = answer;
    int iteration = 0;
    do {
        answer = realloc(answer, size_step + iteration*size_step);
        next_chunk = answer + strlen(answer); //answer may have moved.
        fgets(next_chunk, size_step, stdin);

        next_chunk = answer + strlen(answer); //take the new read into account
        ++iteration;
    } while (* (next_chunk-1) != '\n');

    *(next_chunk-1) = 0; //truncate the string eliminating the new line.

    return answer;
}

int store_books(BookArray * array,char * filename){
    
    FILE * fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("NO FILE!\n");
    }
    BookArray * book = array -> next;
    while (book) {
        fprintf(fp, "%u\t%s\t\t\t\t\t%s\t\t\t\t\t%d\t%d\n",book ->book.id,book ->book.title,book ->book.authors,book ->book.year,book->book.copies);
        book = book -> next;
    }
    fclose(fp);
    
    return 0;
}

int load_books(BookArray * array, char * filename){
    
    FILE * fp = fopen(filename, "r");
    Book book;
//    while (fscanf(fp, "%u\t%s\t\t\t\t\t%s\t\t\t\t\t%d\t%d\n",&book.id,book.title,book.authors,&book.year,&book.copies) != EOF) {
//        add_book(book, array);
//    }
    while (fscanf(fp, "%u\t\%s\n",&book.id,book.title) != EOF) {
        
        add_book(book, array);
    }
    fclose(fp);
    /*
     
     */
    return 0;
}



int add_book(Book book,BookArray * headnode){
    
    BookArray * add_book = createNode(book);
    add_book -> next = headnode -> next;
    headnode -> next = add_book;
    headnode -> length +=1;
    //将headnode的长度赋给书的id
    
    return 0;
    
}

int remove_book(Book book,BookArray * headnode){
    
    BookArray * find_node = headnode -> next;
    BookArray * front_node = headnode;
    
    if (headnode == NULL) {
        printf("There's no book in the library.\n");
        return 0;
    }
    
    while (find_node -> book.id != book.id || find_node ->book.authors != book.authors || find_node ->book.title != book.title) {
        front_node = find_node;
        find_node = front_node -> next;
        
    }
    
    front_node -> next = find_node ->next;
    headnode -> length -= 1;
    free(find_node);
    return 0;
    
    
}

BookArray * find_book_by_title (BookArray * headNode,const char *title){
    
    BookArray * findnode = headNode->next;
    if (findnode == NULL) {
        printf("Sorry, there's no books in the library\n");
        return NULL;
    }
    while (strcmp(findnode ->book.title,title) != 0) {
        findnode = findnode->next;
        if (findnode->next == NULL) {
            printf("Sorry, there's no books named \"%s\" were found in the library\n",title);
            return NULL;
        }
        if((strcmp(findnode ->book.title,title) == 0)){
            return findnode;
        }
    }
    if((strcmp(findnode ->book.title,title) == 0)){
        return findnode;
    }
    printf("是这里出错辣！\n");
    return NULL;
}

BookArray * find_book_by_id(BookArray * headNode,int id){
    
    BookArray * findnode = headNode->next;
    for (int i = 0; i < headNode -> length; i++) {
        if (findnode ->book.id == id) {
            return findnode;
        }else{
            findnode = findnode->next;
        }
    }
    return NULL;
}

BookArray * find_book_by_year (BookArray * headNode,unsigned int year){
    
//    BookArray * findnode = headNode->next;
//    if (findnode == NULL) {
//        printf("Sorry, there's no books in the library\n");
//        return NULL;
//    }
//
//    while (findnode ->book.year != year && findnode != NULL) {
//        findnode = findnode->next;
//    }
//    printf("Sorry, there's no books in the library");
//    return findnode;
    BookArray * findnode = headNode->next;
    for (int i = 0; i < headNode -> length; i++) {
        if (findnode ->book.year == year) {
            return findnode;
        }else{
            findnode = findnode->next;
        }
    }
    return NULL;
}




//我的函数
//重新排列id
void Id_arrange(BookArray * node){
    BookArray * pMove = node ->next;
    for (int i = 0; i < node->length; i++) {
        pMove->book.id = node->length - i - 1;
        pMove = pMove->next;
    }
}
//用于创立节点
BookArray * createNode(Book bookk){
    
    BookArray * newNode = (BookArray*)malloc(sizeof(BookArray));
    newNode -> book = bookk;
    newNode -> next = NULL;
    return newNode;
    
    
}

//用于创立头节点
BookArray * createHead(){
    BookArray * head = (BookArray*)malloc(sizeof(BookArray));
    head -> next = NULL;
    head -> length = 0;
    head ->book.title = NULL;
    return head;
}


//创建书问的那些问题
//Book *create_book_added(){
//    Book *book = malloc(sizeof(Book));
//    printf("What's the name of the book?\n");
//    scanf("%s",book->title);
//    printf("What's the name of the author?\n");
//    scanf("%s",book->authors);
//    return book;
//
//}

//打印测试


void display_books(BookArray * a){
    
    //BookArray * pMove = a->next;
    if (a == NULL) {
        return;
    }
    printf("ID\tTitle\t\t\t\t\tAuthor\t\t\t\t\tyear\tcopies\n");
    
    BookArray * pMove = a;
    if (pMove ->book.title == NULL) {
        pMove = a->next;
    }
    
    while (pMove) {
        printf("%d\t",pMove ->book.id);
        printf("%s\t\t\t\t\t",pMove ->book.title);
        printf("%s\t\t\t\t\t",pMove ->book.authors);
        printf("%d\t",pMove ->book.year);
        printf("%d\t\n",pMove ->book.copies);
        pMove = pMove->next;
    }
}


int is_number(char * obj){
    
    int i = 0;
    while (obj[i]) {
        if ((obj[i] >= 'a' && obj[i] <= 'z') || (obj[i] >= 'A' && obj[i] <= 'Z')) {
            i++;
        }else{
            return 0;//返回0表示有数字
        }
    }
    return 1;//返回1表示全部是字母
}

//
//BookArray * create_head(){
//    
//}
