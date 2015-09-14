//Methods of class
#ifndef class_cpp
#define class_cpp

int GetDays(int date)
{
    struct std::tm tmp;
    tmp.tm_sec = 0;
    tmp.tm_min = 0;
    tmp.tm_hour = 0;
    tmp.tm_mday = date % 100;
    tmp.tm_mon = (date / 100) % 100;
    tmp.tm_year = (date / 10000);

    return (std::mktime(&tmp) / 3600 / 24);
}

//Bank::public:
Bank::Bank ()
{
    this -> Total = 0;
    this -> Last = 0;
    std::cout << "START" << std::endl;
    Bank::interface interface(*this);
}
Bank::~Bank ()
{
}

int Bank::Append ()
{
    int Number = this -> GetNumber();
    Account tmp(Number);
    std::swap(Data.back(), tmp);
    ++(this -> Total);
    std::cout <<"CREATED" << std::endl;
    return Number;
}
int Bank::Delete (int number)
{
    Data.at(this -> GetIndex(number)).Pop();
    this -> DelNumber (number);
    --(this -> Total);
    return 0;
}
Account Bank::Query (int number)
{
    return Data.at(this -> GetIndex(number));
}
Account & Bank::Set (int number)
{
    return Data.at(this -> GetIndex(number));
}
int Bank::Legal (int number)
{
    if (Number.size() <= number)
        return 0;
    return 1;
}
//Bank::private:
int Bank::GetNumber ()
{
    int Number = 0;
    if (this -> Last >= this -> Number.size())
    {
        Number = this -> Data.size();
        this -> Number.push_back(Number);
        this -> Data.push_back(Account());
    }
    else
    {
        Number = this -> Number.at(this -> Last);
    }
    ++(this -> Last);

    return Number;
}
int Bank::GetIndex (int number)
{
    if (Number.size() <= number)
    {
        std::cerr << "Inlegal index!" << std::endl;
        return -1;
    }
    return (this -> Number.at(number));
}
int Bank::DelNumber (int number)
{
    this -> Number.push_back(-1);
    std::swap(this -> Number.at(number), Number.back());

    return 0;
}

//Account::public:
Account::Account ()
{
    this -> Type = 0;
    this -> Number = -1;
    this -> Name = "";
}
Account::Account (const int number)
{
    this -> Type = 0;
    this -> Number = number;
    this -> Name = "";
} 
Account::Account (const Account & Mother)
{
    this -> Type = Mother.Type;
    this -> Number = Mother.Number;
    this -> Name = Mother.Name;
    this -> Fixed.clone(Mother.Fixed);
    this -> Current.clone(Mother.Current);
}
Account::Account (const int number, const std::string & name)
{
    this -> Number = number;
    this -> Name = name;
}
Account::~Account ()
{
}

std::string Account::GetName ()
{
    return this -> Name;
}
std::string Account::Rename (const std::string & name)
{
    std::string tmp = name;
    swap(this -> Name, tmp);

    return tmp;
}
int Account::SetType (const std::string & type)
{
    if (type == ACCOUNT_TYPE_CURRENT)
        this -> SetType(ACCOUNT_TYPE_CURRENT_CODE);
    if (type == ACCOUNT_TYPE_FIXED)
        this -> SetType(ACCOUNT_TYPE_FIXED_CODE);
    if (type == ACCOUNT_TYPE_BOTH)
        this -> SetType(ACCOUNT_TYPE_BOTH_CODE);
    return 0;
}
int Account::SetType (int type)
{
    this -> Type = type;
    if (!(type & ACCOUNT_TYPE_CURRENT_CODE))
        this -> Current.Clear();
    if (!(type & ACCOUNT_TYPE_FIXED_CODE))
        this -> Fixed.Clear();
    return 0;
}
std::string Account::GetType ()
{
    int code = GetTypeCode();
    std::string type;
    if (code == ACCOUNT_TYPE_BOTH_CODE)
        type = ACCOUNT_TYPE_BOTH;
    if (code == ACCOUNT_TYPE_CURRENT_CODE)
        type = ACCOUNT_TYPE_CURRENT;
    if (code == ACCOUNT_TYPE_FIXED_CODE)
        type = ACCOUNT_TYPE_FIXED;

    return type;
}
int Account::GetTypeCode ()
{
    return this -> Type;
}
int Account::Push (double balance)
{
    int type = this -> GetTypeCode();
    if (type == ACCOUNT_TYPE_BOTH_CODE)
    {
        std::cerr << "Ambiguity" << std::endl;
        return -1;
    }
    if (type | ACCOUNT_TYPE_CURRENT_CODE)
        this -> Current.Push(balance);
    if (type | ACCOUNT_TYPE_FIXED_CODE)
        this -> Fixed.Push(balance);

    return 0;
}
int Account::Push (double balance, int type)
{
    if (type == ACCOUNT_TYPE_BOTH_CODE)
    {
        std::cerr << "Ambiguity" << std::endl;
        return -1;
    }
    if (type | ACCOUNT_TYPE_CURRENT_CODE)
        this -> Current.Push(balance);
    if (type | ACCOUNT_TYPE_FIXED_CODE)
        this -> Fixed.Push(balance);

    return 0;
}
int Account::Pop ()
{
    int number = this -> Number;
    this -> Type = -1 & 0x03;
    this -> Number = -1;
    Name.clear();
    Fixed.Clear();
    Current.Clear();

    return Number;
}
int Account::Print ()
{
    std::cout << "Account Number:\n" << this -> Number << std::endl;
    std::cout << "Name:\n" << this -> GetName() << std::endl;
    std::cout << "Deposit Account Type:\n" << this -> GetType() << std::endl;
    std::cout << "Fixed Deposit Account Information:\n" << std::endl;
    if (this -> GetTypeCode() & ACCOUNT_TYPE_FIXED_CODE)
        this -> Fixed.Print();
    else
        std::cout << "Not Available" << std::endl;
    std::cout << "Current Deposit Account Information:\n" << std::endl;
    if (this -> GetTypeCode() & ACCOUNT_TYPE_FIXED_CODE)
        this -> Current.Print();
    else
        std::cout << "Not Available" << std::endl;

    return 0;
}

//DetailStruct::public:
int DetailStruct::Terminate (int date, double interestCRate)
{
    if (this -> Terminated)
        return 1;
    int Days = GetDays(date) - GetDays(this -> Date);
    if (Days < Term)
        this -> Balance *= std::pow(interestCRate/365 + 1, Days);
    else
        this -> Balance *= std::pow(this -> InterestRate/365 + 1, Days);
    this -> Terminated = 1;
    return 0;
}
//Deposit::public:
Deposit::Deposit ()
{
    this -> Date = -1;
    this -> Balance = 0;
    this -> UpdateDate = 0;
    this -> InterestRate = 0;
    this -> Detail.clear();
    std::cerr << "DEPOSIT INITIALIZE" << std::endl;
}
Deposit::Deposit (const Deposit & Mother)
{
    this -> clone (Mother);
}
Deposit::~Deposit ()
{
}
int Deposit::clone (const Deposit & Mother)
{
    this -> Date = Mother.Date;
    this -> Balance = Mother.Balance;
    this -> UpdateDate = Mother.UpdateDate;
    this -> InterestRate = Mother.InterestRate;
    this -> Detail.assign(Mother.Detail.begin(), Mother.Detail.end());
    return 0;
}

double Deposit::GetBalance ()
{
    return this -> Balance;
}
double Deposit::GetBalance (int date)
{
    this -> Update(date);
    return this -> Balance;
}
int Deposit::GetDate ()
{
    return this -> Date;
}
int Deposit::SetDate (int date)
{
    if (this -> Date == -1)
        this -> Date = date;
    this -> UpdateDate = date;
    return 0;
}
double Deposit::GetInterestRate ()
{
    return this -> InterestRate;
}
int Deposit::SetInterestRate (double interestRate)
{
    this ->InterestRate = interestRate;
    return 0;
}
int Deposit::Update (int date)
{
    this -> CalculateInterest(date);
    this -> SetDate(date);
    return 0;
}/*
int Deposit::Print ()
{
    std::cout << "Open Date:\n" << this -> GetDate() << std::endl;
    std::cout << "Balance:\n" << this -> GetBalance() << std::endl;
    std::cout << "Interest Rate:\n" << this -> GetInterestRate() << std::endl;
    try
    {
        std::cout << "Interest Rate of Current Deposit: (for fixed deposit only)\n" << this -> GetCurrentInterestRate() << std::endl;
    }
    catch (Exception_Function_Not_Exist)
    {
    }
    std::cout << "Update date:\n" << this -> UpdateDate << std::endl;

    return 0;
}*/
int Deposit::Clear()
{
    this -> Date = -1;
    this -> Balance = 0;
    this -> UpdateDate = -1;
    this -> InterestRate = 0;
    this -> Detail.clear();
    std::cerr << "DEPOSIT CLEAR" << std::endl;
    return 0;
}
int Deposit::Size()
{
    return Detail.size();
}
//Deposit::private:
int Deposit::CalculateInterest (int date)
{
    int days = GetDays(date) - GetDays(this -> UpdateDate);
    Balance *= std::pow((1 + this -> InterestRate/100), days);
    return 0;
}

//FixedDeposit::public:
int FixedDeposit::clone (const FixedDeposit & Mother)
{
    this -> Date = Mother.Date;
    this -> Balance = Mother.Balance;
    this -> UpdateDate = Mother.UpdateDate;
    this -> InterestRate = Mother.InterestRate;
    this -> Detail.assign(Mother.Detail.begin(), Mother.Detail.end());
    this -> Term = Mother.Term;
    return 0;
}
int FixedDeposit::GetTerm ()
{
    return this -> Term;
}
int FixedDeposit::SetTerm (int term)
{
    std::swap(term, this -> Term);
    return term;
}
int FixedDeposit::GetStatus (int number)
{
    return this -> Detail.at(number).Terminated;
}
double FixedDeposit::SetCurrentInterestRate (double interestRate)
{
    double tmp = interestRate;
    std::swap(this -> CurrentInterestRate, tmp);
    return tmp;
}
double FixedDeposit::GetCurrentInterestRate ()
{
    return this -> CurrentInterestRate;
}
int FixedDeposit::Push (double balance)
{
    DetailStruct tmp;
    tmp.Date = this -> UpdateDate;
    tmp.Term = this -> Term;
    tmp.Balance = balance;
    tmp.InterestRate = this -> InterestRate;
    tmp.Terminated = 0;
    this -> Detail.push_back(tmp);
    return 0;
}
int FixedDeposit::Push (double balance, int term)
{
    std::swap(this -> Term, term);
    this -> Push(balance);
    std::swap(this -> Term, term);
    return 0;
}
int FixedDeposit::Transfer (int number, int date, int term)
{
    Detail.at(number).Terminate(date, this -> GetCurrentInterestRate());
    Detail.at(number).Date = date;
    Detail.at(number).Term = term;
    Detail.at(number).Terminated = false;
    return 0;
}
double FixedDeposit::Pop(int number, int date)
{
    Detail.at(number).Terminate(date, this -> GetCurrentInterestRate());
    return Detail.at(number).Balance;
}
int FixedDeposit::Print ()
{
    std::cout << "Open Date:\n" << this -> GetDate() << std::endl;
    std::cout << "Interest Rate:\n" << this -> GetInterestRate() << std::endl;
    std::cout << "Interest Rate for early withdraw:\n" << this -> GetCurrentInterestRate() << std::endl;
    std::cout << "Update date:\n" << this -> UpdateDate << std::endl;

    int i = 0;
    for (iter it = this -> Detail.begin(); it != this -> Detail.end(); ++it)
    {
        std::cout << i++ << ". ";
        std::cout << "Date: " << it -> Date << "\tTerm: " << it -> Term << "\tBalance: " << it -> Balance 
                  << "\tInterest Rate: " << it -> InterestRate
                  << "\tStatus: " << ((it -> Terminated) ? "Terminated" : "In Progress") << std::endl;
    }
    return 0;
}
int FixedDeposit::Clear ()
{
    this -> Date = -1;
    this -> Balance = 0;
    this -> UpdateDate = 0;
    this -> InterestRate = 0;
    this -> Detail.clear();

    this -> Term = 0;
    std::cerr << "FIXED CLEAR" << std::endl;
    return 0;
}
//FixedDeposit::private:
int FixedDeposit::CalculateInterest (int date)
{
    double balance = 0;
    for (iter it = this -> Detail.begin(); it != this -> Detail.end(); ++it)
    {
        int tmp;
        tmp = it -> Terminate(date, this -> GetCurrentInterestRate());
        balance += it -> Balance;
        it -> Terminated = tmp;
    }
    this -> Balance = balance;
    return 0;
}

//CurrentDeposit::public:
int CurrentDeposit::Push (double balance)
{
    DetailStruct tmp;
    tmp.Date = this -> UpdateDate;
    tmp.Term = INT_MAX;
    tmp.Balance = balance;
    tmp.InterestRate = this -> InterestRate;
    tmp.Terminated = 0;
    Detail.push_back(tmp);
    this -> Balance += balance;
    return 0;
}
int CurrentDeposit::Print ()
{
    std::cout << "Balance: " << this -> Balance << std::endl;
    std::cout << "Interest Rate: " << this -> InterestRate << std::endl;
    std::cout << "Update Date: " << this -> UpdateDate<< std::endl;
    return 0;
}
int CurrentDeposit::Print (int date)
{
    std::cout << this -> GetBalance(date) << std::endl;
    return 0;
}

#endif
