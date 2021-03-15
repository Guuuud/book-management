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

    BookArray * a = createHead();
    UserArray * u = createLibra();
    createUser(libra);
    add_user(libra,u);
    add_user(jack, u);
    add_user(nick, u);

    Book a3 = {
        "h","h",0,220,2
    };
    Book a1 = {
        "h","h",0,2020,2
    };
    Book a2 = {
        "nmsl","hh",0,2020,3
    };
    Book a4 = {
        "h","h",0,243090,2
    };
    add_book(a1, a);
    add_book(a2, a);
    main_menu(a,u);
    //store_books(a, "/Users/lee/Desktop/book.txt");


}
