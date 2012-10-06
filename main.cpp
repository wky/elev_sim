#include <stdio.h>
#include "storage.h"
#include "defs.h"
int main()
{
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
    return 0;

}


// sob: Weikun "William" Yang wkyjyy@gmail.com

