#include <iostream>
    #include <complex>
    using namespace std;

    class Base {
    public:
        virtual void f( int ) {
            cout << "Base::f(int)" << endl;
        }

        virtual void f( double ) {
            cout << "Base::f(double)" << endl;
        }

        virtual void g( int i = 10 ) {
            cout << i << endl;
        }
    };

    class Derived: public Base {
    public:
        void f( complex<double> ) { // this just hide base::f
            cout << "Derived::f(complex)" << endl;
        }

        void g( int i = 20 ) { // default takes on base, but content takes from derived, oops
            cout << "Derived::g() " << i << endl;
        }
    };

    int main() {
        Base    b;
        Derived d;
        Base*   pb = new Derived;

        b.f(1.0);
        d.f(1.0);
        pb->f(1.0);

        b.g();
        d.g();
        pb->g();

        delete pb; // partial destructor, ~base not virtual
        
        
        // CONST playing
        int a = 0;
        int* const pa = &a; 
        *pa = 7;
        // cannot pa = NULL;
        const int u = 0;
        const int* pu = &u; 
        pu = NULL;
        //cannot *pu = 9;
    
        const int* const puu = &u; 
        // cannot puu = NULL;
        // cannot *puu = 9;
    }
    
    
    /*
[ptson@mps1a boost]$ ./a.out 
Base::f(double)
Derived::f(complex)
Base::f(double)
10
Derived::g() 20
Derived::g() 10

    */
