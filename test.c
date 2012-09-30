//
//  test.c
//  
//
//  Created by tomato on 12-9-24.
//
//

#include <stdio.h>
#include <iostream>
using namespace std;
int divpwr2(int x, int n)
{
    return x >> n;
}
int main()
{
    cout << divpwr2(-33,4) << endl;
    return 0;
}
