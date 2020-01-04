//Definations of Classes
#ifndef defination_h
#define defination_h

class Bank;
class Account;
class Deposit;
class FixedDeposit;
class CurrentDeposit;

class Bank
{
    public:
        Bank ();
        ~Bank ();

        class interface
        {
            public:
                interface (Bank & bank);
                ~interface ();
            private:
                int Status;
                int menu ();
                int GetInput (std::string & input);
                template <typename T>
                int GetInput (T & input);
                int confirm (std::string prompt);
                int GetNumber(Bank & bank);
                int creation (Bank & bank);
                int query (Bank & bank);
                int edit (Bank & bank, int & value);
                int editCurrent (CurrentDeposit & deposit);
                int editFixed (FixedDeposit & deposit);
                int Delete (Bank & bank);
                int Pause ();
                int Error ();
        };
        int Append ();
//        int Append (Account account);
        int Delete (int number);
        Account Query (int number);
        Account & Set (int number);
        int Legal (int number);
    private:
        int Total;
        int Last;
        int GetNumber ();
        int GetIndex (int number);
        int DelNumber (int number);
        std::vector <int> Number;
        std::vector <Account> Data;
};

class DetailStruct
{
    public:
        int Date;
        int Term;
        double Balance;
        double InterestRate;
        bool Terminated;
        int Terminate (int date, double interestCRate);
};
class Deposit
{
    public:
        Deposit ();
        Deposit (const Deposit & Mother);
        ~Deposit ();
        virtual int clone (const Deposit & Mother);

        double GetBalance ();
        double GetBalance (int date);
//        double SetBalance (double balance);
        int GetDate ();
        int SetDate (int date);
        double GetInterestRate ();
        int SetInterestRate (double interestRate);
        int Update (int date);
//        virtual int Print ();
        virtual int Clear ();
        int Size();
    protected:
        typedef std::vector<DetailStruct>::iterator iter;
        int Date;
        double Balance;
        int UpdateDate;
        double InterestRate;
        virtual int CalculateInterest (int date);
        std::vector <DetailStruct> Detail;
};

class FixedDeposit : public Deposit
{
    public:
        int clone (const FixedDeposit & Mother);

        int GetTerm ();
        int SetTerm (int term);
        int GetStatus (int number);
        double SetCurrentInterestRate (double interestRate);
        double GetCurrentInterestRate ();
        int Push (double balance);
        int Push (double balance, int term);
        int Transfer (int number, int date, int term);
        double Pop(int number, int date);
        int Print ();
        int Clear ();
    private:
        int Term;
        double CurrentInterestRate;
        int CalculateInterest (int date);
};

class CurrentDeposit : public Deposit
{
    public:
        int Push (double balance);
        int Print();
        int Print (int date);
};

class Account
{
    public:
        Account ();
        explicit Account (const int number);
        Account (const Account & Mother);
        Account (const int number, const std::string & name);
        ~Account ();

        std::string GetName ();
        std::string Rename (const std::string & name);
        int PrintProfile ();
        int SetType (const std::string & type);
        int SetType (int type);
        std::string GetType ();
        int GetTypeCode ();
        int Push (double balance);
        int Push (double balance, int type);
//        int Push (double balance, const std::string & type);
        int Pop ();
        int Print();
        FixedDeposit Fixed;
        CurrentDeposit Current;

    private:
        int Type;
        int Number;
        std::string Name;
};

#endif
