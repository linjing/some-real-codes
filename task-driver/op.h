#ifndef __OP_H__
#define __OP_H__

class driver;
class op {
    public:
        virtual ~ op () {}
        virtual void operator () () = 0;
};

class op_a : public op {
    public:
        op_a (driver *d) : d_ (d) {}
        void operator () ();
    private:
        driver *d_;
};
class op_b : public op {
    public:
        op_b (driver *d) : d_ (d) {}
        virtual void operator () ();
    private:
        driver *d_;
};
class op_c : public op {
    public:
        op_c (driver *d) : d_ (d) {}
        virtual void operator () ();
    private:
        driver *d_;
};
class op_d : public op {
    public:
        op_d (driver *d) : d_ (d) {}
        virtual void operator () ();
    private:
        driver *d_;
};
class op_e : public op {
    public:
        op_e (driver *d) : d_ (d) {}
        virtual void operator () ();
    private:
        driver *d_;
};

class op_f : public op {
    public:
        op_f (driver *d) : d_ (d) {}
        virtual void operator () ();
    private:
        driver *d_;
};
#endif // #ifndef __OP_H__
