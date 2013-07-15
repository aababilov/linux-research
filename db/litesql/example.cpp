// include LiteSQL's header file and generated header file
#include <iostream>
#include <litesql.hpp>
#include "exampledatabase.hpp"
// provide implementation for Person::sayHello
void example::Person::sayHello() {
    std::cout << "Hi! My name is " << name 
        << " and I am " << age << " years old." << std::endl;
}

void example::user::sayHello() {
    std::cout << "Hi! My name is " << name << std::endl;
}

// no name collisions expected
using namespace litesql;
using namespace example;

int main(int argc, char **argv) {

    try {
        // using SQLite3 as backend
        ExampleDatabase db("mysql",
			   "database=ex_db;password=1;user=root");
        // create tables, sequences and indexes
        db.verbose = true;
        if (db.needsUpgrade())
        {
          db.upgrade();
        }
    } catch (Except e) {
        cerr << e << endl;
        return -1;
    }
    return 0;
}
