//
//  main.c
//  Library_system
//
//  Created by wvwuu on 2021/3/15.
//


//  book_management
//
//  Created by wvwuu on 2021/3/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"
//comment tets
int main(int argc, const char * argv[]) {

    
    
    User libra = {
        "librarian","123456"
    };

    User jack = {
        "jack","123456"
    };

    User nick = {
        "nick","102688"
    };
    
    nick.borrow = 10;

    BookArray * a = createHead();
    //load_books(a, "/Users/lee/Desktop/test.txt");
    UserArray * u = createLibra();
    createUser(libra);
    add_user(libra,u);
    add_user(jack, u);
    add_user(nick, u);
//NMSMNSMNSMNSMNMNSMNSMN
    Book a3 = {
        "hgg","h",2,2200,2
    };
    Book a1 = {
        "hgg","h",0,2020,0
    };
    Book a2 = {
        "nmsl","hh",1,2020,3
    };
    Book a4 = {
        "will","suck",3,1998,292
    };
    
    
    //another test
    add_book(a1, a);
    add_book(a2, a);
    add_book(a3, a);
    add_book(a4, a);
    main_menu(a,u);
    store_books(a, "/Users/lee/Desktop/book.txt");


}
