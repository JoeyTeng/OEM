//Interface
#ifndef interface_cpp
#define interface_cpp
Bank::interface::interface(Bank & bank)
{
    std::cout << std::fixed;
    std::cout.precision(2);
    int option = 0;
    int Value = -1;
    this -> Status = MENU;
    std::system(CLEAN);
    std::cout << "Welcome to the Banking system!" << std::endl;
    std::cout << "Press Enter/Return to continue..." << std::endl;
    std::cin.get();
    while (this -> Status)
        switch (this -> Status)
        {
            case MENU: this -> menu(); break;
            case CREATION: Value = this -> creation(bank); break;
            case QUERY: this -> query(bank); break;
            case EDIT: this -> edit(bank, Value); break;
            case DELETE: this -> Delete(bank); break;
            default: this -> Error();
        }
}
Bank::interface::~interface()
{
}
int Bank::interface::menu()
{
    std::system(CLEAN);
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Create New Account" << std::endl;
    std::cout << "2. Query via Number" << std::endl;
    std::cout << "3. Edit an Account" << std::endl;
    std::cout << "4. Delete an Account via Number" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Please input an integer in [1,4] to choose" << std::endl;
    int option = 0;
    this -> GetInput(option);
    switch(option)
    {
        case 1: this -> Status = CREATION; break;
        case 2: this -> Status = QUERY; break;
        case 3: this -> Status = EDIT; break;
        case 4: this -> Status = DELETE; break;
        case 0: this -> Status = 0; break;
        default: this -> Status |= INVALID_OPERATION; break;
    }

    return 0;
}
template <typename T>
int Bank::interface::GetInput(T & input)
{
    T tmp;
    while ((std::cin >> tmp).fail()) 
    {
        std::cerr << "Please type in an legal input!" << std::endl;
        std::cin.clear();
        std::cin.get();
    }
    input = tmp;
    return 0;
}
int Bank::interface::confirm(std::string prompt)
{
    std::string tmp;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, tmp);
        std::cout << std::endl;
        if (tmp == "Y" || tmp == "y")
            return 1;
        if (tmp == "N" || tmp == "n")
            return 0;
    }
    return -1;
}
int Bank::interface::GetNumber(Bank & bank)
{
    int Number = 0;
    std::string prompt(" is it your account number?(Y/N) ");
    std::stringstream transfer;
    while (true)
    {
        std::cout << "Please input your account number: ";
        this -> GetInput(Number);
        transfer << Number;
        std::string tmp;
        transfer >> tmp;
        prompt = tmp + prompt;
        std::cin.get();
        if (this -> confirm(prompt) == 1)
        {
            if (bank.Legal(Number))
                break;
            else
                std::cout << "Non-exist Account Number" << std::endl;
            std::cin.clear();
            std::cin.get();
        }
    }
    return Number;
}
int Bank::interface::creation(Bank & bank)
{
    std::system(CLEAN);
    int Number = 0;
    std::cin.get();
    if (this -> confirm("Do you really want to create a new account?(Y/N) ") != 1)
    {
        this -> Status = MENU;
        return -1;
    }
    Number = bank.Append();
    std::system(CLEAN);
    std::cout << "New Account Created! Your Account Number is: " << Number << ", Please memerise carefully." << std::endl;
    if (this -> confirm("Do you want to edit this account now?(Y/N) ") != 1)
    {
        std::cout << "OK! Now return to Menu..." << std::endl;
        this -> Status = MENU;
        return 0;
    }
    this -> Status = EDIT;
    return Number;
}
int Bank::interface::query(Bank & bank)
{
    std::system(CLEAN);
    int Number = this -> GetNumber(bank);
    while (true)
    {
        std::system(CLEAN);
        std::cout << "What do you want to know?" << std::endl
                  << "1. Name" << std::endl
                  << "2. Account Type" << std::endl
                  << "3. All Information" << std::endl
                  << "4. Change the Account" << std::endl
                  << "0. Return to Main Menu (will change the Account)" << std::endl;

        int option = 0;
        this -> GetInput(option);
        std::system(CLEAN);
        switch (option)
        {
            case 1: std::cout << "Name:\n" << bank.Query(Number).GetName() << std::endl; break;
            case 2: std::cout << "Account Type:\n" << bank.Query(Number).GetType() << std::endl; break;
            case 3: bank.Query(Number).Print(); break;
            case 4:
            case 0: this -> Status = MENU; return -1;
            default: this -> Status |= INVALID_OPERATION; return -1;
        }
        std::cin.get();
        std::cin.get();
        std::system(CLEAN);
    }
    return 0;
}

int Bank::interface::edit(Bank & bank, int & value)
{
Index_Exception:
    system(CLEAN);
    int Number = value;
    if (value == -1)
        Number = this -> GetNumber(bank);
    else
        value = -1;
    Account * accountPointer = NULL;
    try
    {
        accountPointer = &bank.Set(Number);
    }
    catch (std::out_of_range)
    {
        value = -1;
        std::cin.get();
        goto Index_Exception;
    }
    Account & account = *accountPointer;
    std::string tmp;

    while (true)
    {
        std::system(CLEAN);
        std::cout << "Which Deposit Account do you want to edit?" << std::endl;
        std::cout << "1. Current Deposit" << ((account.GetTypeCode() & ACCOUNT_TYPE_CURRENT_CODE) ? ("(Available)") : ("(Unavailable)")) << std::endl
                  << "2. Fixed Deposit" << ((account.GetTypeCode() & ACCOUNT_TYPE_FIXED_CODE) ? ("(Available)") : ("(Unavailable)")) << std::endl
                  << "3. Profile Information" << std::endl
                  << "4. Change Deposit Type" << std::endl
                  << "5. Change the Account" << std::endl
                  << "0. Return to Main Menu (will change the Account)" << std::endl;
        int option = 0;
        int Option = 0;
        this -> GetInput(option);
        system(CLEAN);
        std::cin.get();
        switch (option)
        {
            case 1:
                if (!(account.GetTypeCode() & ACCOUNT_TYPE_CURRENT_CODE))
                {
                    this -> Status |= INVALID_OPERATION;
                    return -1;
                }
                else
                {
                    this -> editCurrent(account.Current);
                    if (this -> Status == MENU)
                        return -1;
                }
                break;
            case 2:
                if (!(account.GetTypeCode() & ACCOUNT_TYPE_FIXED_CODE))
                {
                    this -> Status |= INVALID_OPERATION;
                    return -1;
                }
                else
                {
                    this -> editFixed(account.Fixed);
                    if (this -> Status == MENU)
                        return -1;
                }
                break;
            case 3:
                std::cout << "What is your name again?" << std::endl;
                this -> GetInput(tmp);
                account.Rename(tmp);
                break;
           case 4:
                std::system(CLEAN);
                std::cout << "Which Type of Account do you want?" << std::endl
                          << "1. Current Deposit only" << std::endl
                          << "2. Fixed Deposit only" << std::endl
                          << "3. Both Current & Fixed Deposit" << std::endl
                          << "0. Cancel this operation" << std::endl;
                this -> GetInput(Option);
                switch(Option)
                {
                    case 1: account.SetType(ACCOUNT_TYPE_CURRENT); break;
                    case 2: account.SetType(ACCOUNT_TYPE_FIXED); break;
                    case 3: account.SetType(ACCOUNT_TYPE_BOTH); break;
                    case 0: break;
                }
                
                break;
            case 5:
                return -1;
            case 0:
                this -> Status = MENU;
                return -1;
            default:
                this -> Status |= INVALID_OPERATION;
                return -1;
        }
    }
}
int Bank::interface::editCurrent(CurrentDeposit & current)
{
    while (true)
    {
        std::system(CLEAN);
        std::cout << "what to you want to do?" << std::endl
                  << "1. Deposit money" << std::endl
                  << "2. Withdraw money" << std::endl
                  << "3. Show my Balacne" << std::endl
                  << "4. Change Interest Rate" << std::endl
                  << "0. Return to last menu" << std::endl;
        int option = 0;
        double Amount = 0;
        int date = 0;
        double InterestRate = 0.0;
        this -> GetInput(option);
        switch (option)
        {
            case 1:
                std::cout << "Amount: " << std::endl;
                this -> GetInput(Amount);
                std::cout << "Date (yyyymmdd): " << std::endl;
                this -> GetInput(date);
                current.Update(date);
                current.Push(Amount);
                current.Update(date);
                std::cout << "Balance: " << current.GetBalance(date) << std::endl;
                break;

            case 2:
                std::cout << "Date (yyyymmdd): " << std::endl;
                this -> GetInput(date);
                std::cout << "Amount: " << std::endl;
                while (true)
                {
                    this -> GetInput(Amount);
                    if (Amount > current.GetBalance(date))
                    {
                        std::cerr << "Inlegal input: over withdraw!" << std::endl;
                    }
                    else
                    {
                        current.Push(-Amount);
                        std::cout << "Withdraw Success!" << std::endl;
                        std::cout << "New Balance: ";
                        current.Print(date);
                        std::cout << std::endl;
                        break;
                    }
                }
                break;
            case 3:
                std::cout << "Date (yyyymmdd): " << std::endl;
                this -> GetInput(date);
                std::cout << "Balance: " << std::endl;
                current.Print(date);
                std::cout << std::endl;
                break;
            case 4:
                std::cout << "Date (yyyymmdd): " << std::endl;
                this -> GetInput(date);
                std::cout << "Please input new interest rate: (eg. prefer 0.04 but not 4%)" << std::endl;
                this -> GetInput(InterestRate);
                current.Update(date);
                current.SetInterestRate(InterestRate);
            case 0:
                return 0;

            default:
                break;
        }
    }
}
int Bank::interface::editFixed(FixedDeposit & fixed)
{
    int number = 0;
    
    while (true)
    {
        std::system(CLEAN);
        std::cout << "what to you want to do?" << std::endl
                  << "1. Deposit money" << std::endl
                  << "2. Withdraw money" << std::endl
                  << "3. Prolong saving term" << std::endl
                  << "4. List my Account" << std::endl
                  << "5. Change Interest Rate" << std::endl
                  << "0. Return to last menu" << std::endl;
        int option = 0;
        int date = 0;
        double Amount = 0;
        double InterestRate = 0;
        double CurrentInterestRate = 0;
        int term = 0;
        this -> GetInput(option);
        switch (option)
        {
            case 1:
                std::cout << "Amount: " << std::endl;
                this -> GetInput(Amount);
                std::cout << "Date (yyyymmdd): " << std::endl;
                this -> GetInput(date);
                std::cout << "Term:(in days) " << std::endl;
                this -> GetInput(term);
                fixed.Update(date);
                fixed.Push(Amount, term);
                fixed.Update(date);
                break;

            case 2:
                std::cout << "Please choose an record to continue:" << std::endl;
                fixed.Print();
                this -> GetInput(number);
                if (!(number > -1 && number < fixed.Size()))
                {
                    std::cout << "Non-exist record!" << std::endl;
                    break;
                }
                if (fixed.GetStatus(number))
                {
                    std::cout << "Unavailable record!" << std::endl;
                    break;
                }
                std::cout << "Date (yyyymmdd): " << std::endl;
                this -> GetInput(date);
                std::cout << "Withdraw Success!" << std::endl;
                std::cout << "Money your get: " << fixed.Pop(number, date) << std::endl;
                break;
            case 3:
                std::cout << "Please choose an record to continue:" << std::endl;
                fixed.Print();
                if (!(number > -1 && number < fixed.Size()))
                {
                    std::cout << "Non-exist record!" << std::endl;
                    break;
                }
                std::cout << "Date (yyyymmdd): " << std::endl;
                this -> GetInput(date);
                std::cout << "Term: " << std::endl;
                this -> GetInput(term);
                fixed.Transfer(number, date, term);
            case 4:
                fixed.Print();
                std::cout << std::endl;
                break;
            case 5:
                std::cout << "Date (yyyymmdd): " << std::endl;
                this -> GetInput(date);
                std::cout << "Please input new interest rate of fixed deposit: (eg. prefer 0.04 but not 4%)" << std::endl;
                this -> GetInput(InterestRate);
                std::cout << "Please input new interest rate of current depoist: (same eg as above)" << std::endl;
                this -> GetInput(CurrentInterestRate);
                fixed.Update(date);
                fixed.SetInterestRate(InterestRate);
                fixed.SetCurrentInterestRate(CurrentInterestRate);
            case 0:
                return 0;

            default:
                break;
        }
    }
}
int Bank::interface::Delete(Bank & bank)
{
    int Number = this -> GetNumber(bank);
    bank.Delete(Number);
    this -> Status = MENU;
    return 0;
}
int Bank::interface::Error()
{
    std::cout << "Error Raised" << std::endl;
    std::cerr << "Interface Error: " << this -> Status << std::endl;
    this -> Status &= ~INVALID_OPERATION;
    return 0;
}

#endif
