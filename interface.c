//
//  interface.c
//  book_management
//
//  Created by wvwuu on 2021/3/8.
//

#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * password;
char * user_name;

char * case_title;
char * case_author;
unsigned int case_year;

//一个变量用于remove books
char * dele_title;

//一个变量用于借书
BookArray * borrow_books;

int borrow_id;

//这个是复制餐馆的，需要注意修改
char *ask_question(const char *question) {

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

//1.register






//main menu
void main_menu(BookArray * headnode, UserArray * usernode){
    
    int choice = 5;
    int lib_choice = 5;
    int user_choice = 5;
    int search_choice = 4;
    do{
        char * answer = ask_question("Please choose an option\n1) Register an account\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n");
        choice = atoi(answer);
        free(answer);
        printf("\n");
        switch (choice) {
            //注册账户
            //Registrate an account
            case 1:
                printf("----REGISTRATION----\n");
                User user;
                user.name = ask_question("Please enter the name:");
                if (name_available(usernode,user.name) == 1) {
                    //If name named already used,the registration will fail
                    printf("Sorry, named already used, Please chosse another name!\n\n");
                    break;
                }
                user.password = ask_question("please enter the password:");
                user.borrow = 10;
                add_user(user, usernode);
                printf("Registration successfully!\n\n");
                break;
            //Login
                
            case 2:
                //如果是管理员那么
                //Login as librarian
                printf("----LOGIN-----\n");
                user_name = ask_question("Please enter your name:\n");
                password = ask_question("Please enter your password:\n");
                if(name_available(usernode, user_name) == 1)
                //通过判断库中是否有这个名字来进入
                //If the name already existed, it will enter the librarian surface
                {
                    //管理员
                    if(strcmp(user_name,"librarian")==0 && password_right(usernode, password,user_name) == 1){
                        printf("Login successfully!\n\n");
                        
                        do{
                            printf("(Logged in as %s)\n",user_name);
                            answer = ask_question("Please choose an option\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) Log out\n");
                            lib_choice = atoi(answer);
                            free(answer);
                            if (lib_choice == 1) {
                                Book book;
                                book.title = ask_question("Enter the title of the book:");
                                book.authors = ask_question("Enter the name of the author:");
                                book.year = atoi(ask_question("Enter the year of the book:"));
                                
                                book.copies = atoi(ask_question("Enter the copies of the book:"));
                                if(is_number(book.authors) == 0){
                                    printf("Invalid author name! please try again.\n\n");
                                    continue;
                                }
                                if (book.year == 0) {
                                    printf("Invalid year! please try again.\n");
                                    continue;
                                }
                                if (book.copies == 0) {
                                    printf("Invalid copies! please try again.\n");
                                    continue;
                                }
                                
                                book.id = headnode->length;
                                printf("Add Successfully!\n");
                                add_book(book, headnode);
                                display_books(headnode);
                                
                            }
                            else if (lib_choice == 2){
                                display_books(headnode);
                                dele_title = ask_question("Enter the tilte of the book you want to delete:\n");
                                //找不到
                                if(find_book_by_title(headnode, dele_title)==NULL){
                                    printf("找不到！\n");
                                //找得到
                                }else{
                                    Book book = find_book_by_title(headnode, dele_title)->book;
                                    remove_book(book, headnode);
                                    Id_arrange(headnode);
                                    printf("Ok了家人们，删成了\n");
                                }
                                
                                
                                
                            }else if(lib_choice == 4){
                                display_books(headnode);
                            }else if(lib_choice == 3){
                                
                                answer = ask_question("Please choose an option:\n1)Find book by title\n2)Find book by author\n3)Find book by year\n4)Return to previous menu\nOption:");
                                search_choice = atoi(answer);
                                do{
                                    
                                    switch (search_choice) {
                                        case 1:
                                            case_title = ask_question("Please enter the title:");
                                            display_books(find_book_by_title(headnode, case_title));

                                            break;
                                        case 2:
                                            case_author = ask_question("Please enter the author:");
                                            break;
                                        case 3:
                                            printf("Pleasr enter the year:");
                                            scanf("%d",&case_year);
                                            printf("\n");
                                            display_books(find_book_by_year(headnode, case_year));
                //                            answer = ask_question("Please choose an option:\n1)Find book by title\n2)Find book by author\n3)Find book by year\n4)Return to previous menu\nOption:");
                //                            search_choice = atoi(answer);
                                            break;
                                        case 4:
                                            break;
                                            
                                    }
                                    printf("|||||||||||\n");
                                    getchar();
                                    answer = ask_question("Please choose an option:\n1)Find book by title\n2)Find book by author\n3)Find book by year\n4)Return to previous menu\nOption:");
                                    search_choice = atoi(answer);
                                    
                                }while (search_choice != 4);
                            }
                            
                        }while (lib_choice != 5);
                        
                    }
                    else if(password_right(usernode, password,user_name) != 1){
                        printf("Wrong password! Please try again\n\n");
                    }
                    //如果不是图书管理员
                    else if(password_right(usernode, password,user_name) == 1){
                        printf("Login successfully!\n\n");
                        printf("(Logged in as %s)\n",user_name);
                        answer = ask_question("Please choose an option\n1) Borrow a book\n2) Return a book\n3) Search for books\n4) Display all books\n5) Log out\n");
                        user_choice = atoi(answer);
                        User u = user_available(usernode,user_name)->user;
                        do{
                           
                            switch (user_choice) {
                                case 1:
                                    answer = ask_question("Please enter the id of the book you want to borrow: ");
                                    if (find_book_by_id(headnode, atoi(answer)) !=NULL) {
                                        borrow_id = atoi(answer);
                                        borrow_books = find_book_by_id(headnode, borrow_id);
                                        if (if_repeat(u, borrow_books->book.title)==0) {
                                            //bug的错误在于你这个函数返回的u是一个全新的u，而不是nick
                                            u = borrow_book(u,borrow_books);
                                            user_available(usernode,user_name)->user = u;
                                        }else{
                                            printf("Sorry, you've already borrow this book\n");
                                        }
                                        
                                    }
                                    
                                    break;
                                case 2:
                                    display_borrow(u);
                                    
                                        answer = ask_question("\nEnter the name of the book you want to return:");
                                        borrow_books = find_book_by_title(headnode, answer);
                                    if (borrow_books != NULL && if_repeat(u, borrow_books->book.title)==1) {
                                        borrow_books->book.copies += 1;
                                    printf("Return successfully!\n");
                                        for (int i = 0; i < 10- u.borrow; i++) {
                                            if (strcmp(u.book[i].title,answer)==0) {
                                                u.book[i].year = 20000;
                                                u.book[i].title = "fudiouifauhfd";
                                            }
                                        }
                                    }else{
                                        printf("There is no such book called \"%s\" in you borrow list.\n",answer);
                                    }
                                        
                                        
                                    break;
                                case 3:
                                    answer = ask_question("Please choose an option:\n1)Find book by title\n2)Find book by author\n3)Find book by year\n4)Return to previous menu\nOption:");
                                    search_choice = atoi(answer);
                                    do{
                                        
                                        switch (search_choice) {
                                            case 1:
                                                case_title = ask_question("Please enter the title:");
                                                display_books(find_book_by_title(headnode, case_title));

                                                break;
                                            case 2:
                                                case_author = ask_question("Please enter the author:");
                                                break;
                                            case 3:
                                                printf("Pleasr enter the year:");
                                                scanf("%d",&case_year);
                                                printf("\n");
                                                display_books(find_book_by_year(headnode, case_year));
                    //                            answer = ask_question("Please choose an option:\n1)Find book by title\n2)Find book by author\n3)Find book by year\n4)Return to previous menu\nOption:");
                    //                            search_choice = atoi(answer);
                                                break;
                                            case 4:
                                                break;
                                                
                                        }
                                        //printf("|||||||||||\n");
                                        getchar();
                                        answer = ask_question("Please choose an option:\n1)Find book by title\n2)Find book by author\n3)Find book by year\n4)Return to previous menu\nOption:");
                                        search_choice = atoi(answer);
                                        
                                    }while (search_choice != 4);
                                    break;
                                case 4:
                                    //printf("NMSL\n");
                                    display_books(headnode);
                                    break;
                                default:
                                    printf("sorry, that doesn't seem to be an option, please choose between 1 - 5\n");
                            }
                            printf("\n(Logged in as %s)\n",user_name);
                            answer = ask_question("Please choose an option\n1) Borrow a book\n2) Return a book\n3) Search for books\n4) Display all books\n5) Log out\n");
                            user_choice = atoi(answer);
                        }while (user_choice != 5);

                    }
                }else{
                    printf("Sorry, there is no users named “%s”\n\n",user_name);
                    break;
                }
                
                
                break;
            case 3:
//                printf("在这里！！！");
                answer = ask_question("Please choose an option:\n1)Find book by title\n2)Find book by author\n3)Find book by year\n4)Return to previous menu\nOption:");
                search_choice = atoi(answer);
                do{
                    
                    switch (search_choice) {
                        case 1:
                            case_title = ask_question("Please enter the title:");
                            display_books_by_title(find_book_by_title(headnode, case_title));

                            break;
                        case 2:
                            case_author = ask_question("Please enter the author:");
                            break;
                        case 3:
                            printf("Pleasr enter the year:");
                            scanf("%d",&case_year);
                            printf("\n");
                            display_books(find_book_by_year(headnode, case_year));
//                            answer = ask_question("Please choose an option:\n1)Find book by title\n2)Find book by author\n3)Find book by year\n4)Return to previous menu\nOption:");
//                            search_choice = atoi(answer);
                            break;
                        case 4:
                            break;
                            
                    }
                    //printf("|||||||||||\n");
                    getchar();
                    answer = ask_question("Please choose an option:\n1)Find book by title\n2)Find book by author\n3)Find book by year\n4)Return to previous menu\nOption:");
                    search_choice = atoi(answer);
                    
                }while (search_choice != 4);
                break;
            case 4:
                display_books(headnode);
                break;
            case 5:
                printf("goodbye\n");
                break;
            default:
                printf("sorry, that doesn't seem to be an option, please choose between 1 - 5\n");
               
        }
    }while (choice != 5 );
    
    return;
    
    
}
