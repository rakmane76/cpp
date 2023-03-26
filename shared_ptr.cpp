#include<memory>
#include<iostream>

using namespace std;

class A{
    public:
        A() { cout << "In A \n"; }
        ~A() { cout << "In ~A \n"; }
};

void check_weak_ptr(){
    std::shared_ptr<int> sptr; // empty definition

    sptr.reset( new int ); // takes ownership of pointer
    *sptr = 10;

    // get pointer to data without taking ownership
    std::weak_ptr<int> weak1 = sptr;

    // deletes managed object, acquires new pointer
    sptr.reset( new int );
    *sptr = 5;

    // get pointer to new data without taking ownership
    std::weak_ptr<int> weak2 = sptr;

    // weak1 is expired!
    if ( auto tmp = weak1.lock() ){
        std::cout << *tmp << '\n';
    }
    else{
        std::cout << "weak1 is expired\n";
    }

    // weak2 points to new data (5)
    if ( auto tmp = weak2.lock() ){
        std::cout << *tmp << '\n';
    }
    else{
        std::cout << "weak2 is expired\n";
    }
    
}

int main(){
    auto pa= make_shared<A>();
    pa.reset(new A());
    check_weak_ptr();
    return 0;
}
