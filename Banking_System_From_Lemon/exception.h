//Exceptions
#ifndef exception_h
#define exception_h

class Exception
{
    public:
        Exception();
        Exception(const Exception& Mother);
        ~Exception();
};
class NumberException : public Exception
{

};

#endif
