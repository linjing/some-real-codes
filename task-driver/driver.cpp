#include "driver.h"
#include "op.h"

using namespace std;

int main () {
    task_record task_a;
    driver driver_a (task_a);
    driver_a.driver_generated ();

    return 0;
}
