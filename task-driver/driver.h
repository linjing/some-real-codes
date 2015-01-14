#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <string>
#include <iostream>

#include "op.h"

struct task_record {
    std::string info;
    int op_d_cnt;
    int op_d_finished;

    bool op_d_done () {
        return op_d_cnt == op_d_finished;
    }
};

class driver
{
    public:
        driver (task_record &task) : task_ (task) {}
        task_record &get_task () { return task_; }
        virtual void driver_generated () {
            op_a next(this);
            next ();
        }
    public:
        virtual void op_a_ed () {
            op_b next(this);
            next ();
        }
        virtual void op_b_ed () {
            task_.op_d_finished = 0;
            task_.op_d_cnt = 2;
            op_d d1 (this);
            op_d d2 (this);
            d1 (); d2 ();
        }
        virtual void op_c_ed () {
            // I can send next operator object to bg thread
            op_f next(this);
            next ();
        }
        virtual void op_d_ed () {
            task_.op_d_finished += 1;
            if (task_.op_d_done ()) {
                op_f next (this);
                next ();
            }
        }
        virtual void op_e_ed () {}
        virtual void op_f_ed () {
            std::cout << task_.info << std::endl;
            std::cout << "task done" << std::endl;
        }
    protected:

        task_record &task_;
};

#endif // #ifndef __DRIVER_H__
