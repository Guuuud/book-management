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

char upper;

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
        fprintf(fp, "%u\t%s\t%s\t%d\t%d\n",book ->book.id,book ->book.title,book ->book.authors,book ->book.year,book->book.copies);
        book = book -> next;
    }
    fclose(fp);
    
    return 0;
}

int load_books(BookArray * array, char * filename){
    
    FILE * fp = fopen(filename, "r");
    Book book;
//    book.title = (char*)malloc(sizeof(char));
//    book.authors = (char*)malloc(sizeof(char));
//    int i = 0;
//    while (i < 4) {
//        //printf("KKKKKK");
//        i++;
//        fscanf(fp, "%u\t%s\t%s\t%d\t%d\n",&book.id,book.title,book.authors,&book.year,&book.copies);
//        book.title = (char*)malloc(sizeof(char));
//        book.authors = (char*)malloc(sizeof(char));
//        add_book(book, array);
//    }
//
    BookArray * hode = array;
    
    while (!feof(fp)) {
        BookArray * node = malloc(sizeof(BookArray));
        
        
        node->book.title = (char*)malloc(40* sizeof(char));
        node->book.authors = (char*)malloc(40* sizeof(char));
        
        memset(node->book.title, 0, 40* sizeof(char));
        memset(node->book.authors, 0, 40* sizeof(char));
        
//        fscanf(fp,"%s %s %d %d %u", book.title,book.authors,&book.id,&book.year,&book.copies);
        
        fread(node->book.title, 40 * sizeof(char), 1, fp);
        fread(node->book.authors, 40 * sizeof(char), 1, fp);
        fread(&node->book.id, sizeof(int), 1, fp);
        fread(&node->book.year, sizeof(int), 1, fp);
        fread(&node->book.copies, sizeof(int), 1, fp);
        
        node -> next = array ->next;
        node = array -> next;
        printf("KKKLKLKLKL\n");
        //printf("%s",node->book.title);
        
        //node -> next = NULL;
        
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
    //???headnode?????????????????????id
    
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
            printf("Sorry, there's no books named \"%s\" were found in the library\n\n",title);
            return NULL;
        }
        if((strcmp(findnode ->book.title,title) == 0)){
            return findnode;
        }
    }
    if((strcmp(findnode ->book.title,title) == 0)){
        return findnode;
    }
    printf("?????????????????????\n");
    return NULL;
}


BookArray * find_book_by_author (BookArray * headNode,const char *title){
    
    BookArray * findnode = headNode->next;
    if (findnode == NULL) {
        printf("Sorry, there's no books in the library\n");
        return NULL;
    }
    while (strcmp(findnode ->book.authors,title) != 0) {
        findnode = findnode->next;
        if (findnode->next == NULL) {
            printf("Sorry, there's no auhtor named \"%s\" were found in the library\n\n",title);
            return NULL;
        }
        if((strcmp(findnode ->book.authors,title) == 0)){
            return findnode;
        }
    }
    if((strcmp(findnode ->book.authors,title) == 0)){
        return findnode;
    }
    printf("?????????????????????\n");
    return NULL;
    
    
}

BookArray * find_book_by_id(BookArray * headNode,int id){

    BookArray * findnode = headNode->next;
    if (findnode == NULL) {
        printf("Sorry, there's no books in the library\n");
        return NULL;
    }
    if(findnode->book.id == id){
        return findnode;
    }
    
    while (findnode->book.id != id) {
        findnode = findnode->next;
        if (findnode->next == NULL) {
            printf("Sorry, there's no books with the id of \"%d\" were found in the library\n",id);
            return NULL;
        }
        if(findnode->book.id == id){
            //printf("????????????");
            return findnode;
        }
    }
    if(findnode->book.id == id){
        //printf("????????????2");
        return findnode;
    }
    printf("?????????????????????\n");
    return NULL;
}

BookArray * find_book_by_year (BookArray * headNode,unsigned int year){
    
    BookArray * findnode = headNode->next;
    if (findnode == NULL) {
        printf("Sorry, there's no books in the library\n");
        return NULL;
    }
    if(findnode->book.year == year){
        return findnode;
    }
    
    while (findnode->book.year != year) {
        findnode = findnode->next;
        if (findnode->next == NULL) {
            printf("Sorry, there's no books with the id of \"%d\" were found in the library\n",year);
            return NULL;
        }
        if(findnode->book.year == year){
            //printf("????????????");
            return findnode;
        }
    }
    if(findnode->book.year == year){
        //printf("????????????2");
        return findnode;
    }
    printf("?????????????????????\n");
    return NULL;
}




//????????????
//????????????id
void Id_arrange(BookArray * node){
    BookArray * pMove = node ->next;
    for (int i = 0; i < node->length; i++) {
        pMove->book.id = node->length - i - 1;
        pMove = pMove->next;
    }
}
//??????????????????
BookArray * createNode(Book bookk){
    
    BookArray * newNode = (BookArray*)malloc(sizeof(BookArray));
    newNode -> book = bookk;
    newNode -> next = NULL;
    return newNode;
    
    
}

//?????????????????????
BookArray * createHead(){
    BookArray * head = (BookArray*)malloc(sizeof(BookArray));
    head -> next = NULL;
    head -> length = 0;
    head ->book.title = NULL;
    return head;
}


//???????????????????????????
//Book *create_book_added(){
//    Book *book = malloc(sizeof(Book));
//    printf("What's the name of the book?\n");
//    scanf("%s",book->title);
//    printf("What's the name of the author?\n");
//    scanf("%s",book->authors);
//    return book;
//
//}

//????????????


void display_books(BookArray * a){
    
    //BookArray * pMove = a->next;
    if (a == NULL) {
        return;
    }
    printf("LIBRARY LIST ^^ LIBRARY LIST ^^ LIBRARY LIST ^^ \n");
    printf("-------------------------------------------------------------\n");
    printf("ID\tTitle\t\t\t\t\tAuthor\t\t\t\tyear\tcopies\n");
    
    BookArray * pMove = a;
    if (pMove ->book.title == NULL) {
        pMove = a->next;
    }
    
    while (pMove) {
        printf("%d\t",pMove ->book.id);
        printf("%s",pMove ->book.title);
        title_length(pMove ->book.title);
        printf("%s",pMove ->book.authors);
        author_length(pMove ->book.authors);
        printf("%d\t",pMove ->book.year);
        printf("%d\t\n",pMove ->book.copies);
        pMove = pMove->next;
    }
    printf("-------------------------------------------------------------\n");
}

void display_books_by_title(BookArray * pMove){
    
    //BookArray * pMove = a->next;
//    if (a == NULL) {
//        return;
//    }
    if (pMove == NULL) {
        return;
    }
    printf("LIBRARY LIST ^^ LIBRARY LIST ^^ LIBRARY LIST ^^ \n");
    printf("-------------------------------------------------------------\n");
    printf("ID\tTitle\t\t\t\t\tAuthor\t\t\t\tyear\tcopies\n");
    
//    BookArray * pMove = a;
//    if (pMove ->book.title == NULL) {
//        pMove = a->next;
//    }
    
//    while (pMove) {
        printf("%d\t",pMove ->book.id);
        printf("%s",pMove ->book.title);
        title_length(pMove ->book.title);
        printf("%s",pMove ->book.authors);
        author_length(pMove ->book.authors);
        printf("%d\t",pMove ->book.year);
        printf("%d\t\n",pMove ->book.copies);
//        pMove = pMove->next;
//    }
    printf("-------------------------------------------------------------\n");
}

void display_books_by_author(char * author,BookArray * pMove){
    

    if (pMove == NULL) {
        return;
    }
    printf("LIBRARY LIST ^^ LIBRARY LIST ^^ LIBRARY LIST ^^ \n");
    printf("-------------------------------------------------------------\n");
    printf("ID\tTitle\t\t\t\t\tAuthor\t\t\t\tyear\tcopies\n");

    while (pMove) {
        if (strcmp(author, pMove->book.authors) == 0) {
            printf("%d\t",pMove ->book.id);
            printf("%s",pMove ->book.title);
            title_length(pMove ->book.title);
            printf("%s",pMove ->book.authors);
            author_length(pMove ->book.authors);
            printf("%d\t",pMove ->book.year);
            printf("%d\t\n",pMove ->book.copies);
        }
       pMove = pMove->next;
        //printf("sdds\n");
    }
    printf("-------------------------------------------------------------\n");
}


int is_number(char * obj){
    
    int i = 0;
    while (obj[i]) {
        if ((obj[i] >= 'a' && obj[i] <= 'z') || (obj[i] >= 'A' && obj[i] <= 'Z')) {
            i++;
        }else{
            return 0;//??????0???????????????
        }
    }
    return 1;//??????1?????????????????????
}

//char all_upper(char obj){
//    int i = 0;
//    while (obj[i]) {
//        if ((obj[i] >= 'a' && obj[i] <= 'z')) {
//            obj[i] += 26;
//            i++;
//        }else{
//            i++;
//        }
//    }
//    return obj;
//}

void title_length(char * word){
    if (strlen(word) < 4) {
        printf("\t\t\t\t\t\t");
    }else if(strlen(word) < 8){
        printf("\t\t\t\t\t");
    }else if(strlen(word) < 12){
        printf("\t\t\t\t");
    }else if (strlen(word) < 16){
        printf("\t\t\t");
    }else{
        printf("\t\t");
    }
}

void author_length(char * word){
    if(strlen(word) < 4){
        printf("\t\t\t\t\t");
    }else if (strlen(word) < 8){
        printf("\t\t\t\t");
    }else if(strlen(word) < 12){
        printf("\t\t\t");
    }else if(strlen(word) < 16){
        printf("\t\t");
    }else{
        printf("\t");
    }
}

//
//BookArray * create_head(){
//    
//}
