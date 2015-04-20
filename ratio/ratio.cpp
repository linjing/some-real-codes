#include <ratio>
#include <stdio.h>
#include <chrono>
#include <iostream>

int main () 
{
    using namespace std;
    using jiffies = chrono::duration<int, ratio<1, 100>>;
    
    cout << chrono::duration_cast<jiffies>(jiffies::max ()).count () << endl;


    chrono::seconds sec(10);
    chrono::minutes min(10);
    cout << chrono::duration_cast<jiffies>(sec).count ()
        << " jiffies\n";

    cout << chrono::duration_cast<jiffies>(min).count ()
        << " jiffies\n";

    ratio<1, 100> a;
    printf ("%d, %d\n", a.num, a.den);
    return 0;
}
