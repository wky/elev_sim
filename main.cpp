#include <stdio.h>
#include "storage.h"
#include "defs.h"
#include "level_info.h"
#include "poisson.h"

int main()
{
    /*
	int a=0;
    int b = 1;
    printf("yeah, it works!\n%d\n", a+b);
    
    StorageManager * m = new StorageManager(5);
    Passenger* ptr = m->get_new();
    printf("m:0x%x, ptr:0x%x\n", m, ptr);
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    m->push_arrived(ptr);
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    m->push_arrived(ptr);
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    m->push_arrived(ptr);
    
    delete m;
    */
    ElevatorParameters e;
    e.arrival_rate = 0.8;
    poisson p(&e);
    cout << p.get_next() << endl;
        cout << p.get_next() << endl;
        cout << p.get_next() << endl;
        cout << p.get_next() << endl;
        cout << p.get_next() << endl;
        cout << p.get_next() << endl;
        cout << p.get_next() << endl;
        cout << p.get_next() << endl;
    
        cout << p.get_next() << endl;
        cout << p.get_next() << endl;
    return 0;

}


// sob: Weikun "William" Yang wkyjyy@gmail.com

