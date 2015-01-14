#include "op.h"
#include "driver.h"

void op_a::operator () () {
            task_record &task = d_->get_task ();
            task.info += "op_a\n";
            d_->op_a_ed ();
        }
void op_b::operator () () {
            task_record &task = d_->get_task ();
            task.info += "op_b\n";
            d_->op_b_ed ();
        }
void op_c::operator () () {
            task_record &task = d_->get_task ();
            task.info += "op_c\n";
            d_->op_c_ed ();
        }
void op_d::operator () () {
            task_record &task = d_->get_task ();
            task.info += "op_d\n";
            d_->op_d_ed ();
        }
void op_e::operator () () {
            task_record &task = d_->get_task ();
            task.info += "op_e\n";
            d_->op_e_ed ();
        }
void op_f::operator () () {
            task_record &task = d_->get_task ();
            task.info += "op_f\n";
            d_->op_f_ed ();
        }
