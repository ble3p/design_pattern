#include <cstdlib>
#include <iostream>

using namespace std;

class Discount
{
public:
    virtual float getRate() = 0;
    
};

class CommonDiscount :public Discount
{
public:   
    float getRate() override
    {
        return 1.0f;
    }
};

class StudentDiscount :public Discount
{
public:   
    float getRate() override
    {
        return 0.8f;
    }
};


class ElderDiscount :public Discount
{
public:   
    float getRate() override
    {
        return 0.0f;
    }
};

class Ticket
{
public:
    Ticket() = default;
    Ticket(Discount *discount, float price) : dis_(discount), price(price) {}
    float getPrice()
    {
        return price * dis_ -> getRate();
    }
private:
    Discount *dis_;
    float price;
};

class Conductor
{
public:
    void saleTickets(Ticket* ticket, int num)
    {
        cout << "待支付: " << ticket -> getPrice() * num << "元" << endl;
    }
};

class TravelStrategy
{
public:
    virtual void travel() = 0;
    virtual ~TravelStrategy() = default;
    
};

class WalkStrategy :public TravelStrategy
{
public:
    void travel() override
    {
        cout << "步行出行..........." << endl;
    }
    
};

class CarStrategy :public TravelStrategy
{
public:
    void travel() override
    {
        cout << "开车出行..........." << endl;
    }
    
};

class TrainStrategy :public TravelStrategy
{
public:
    void travel() override
    {
        cout << "火车出行..........." << endl;
    }
    
};


class FlightStrategy :public TravelStrategy
{
public:
    void travel() override
    {
        cout << "飞机出行..........." << endl;
    }
    
};

class Travel
{
public:
    void setStrategy(TravelStrategy *ts) { ts_ = ts; }
    void travel()
    {
        ts_ -> travel();
    }
private:
    TravelStrategy *ts_;
};
int main()
{
    
    Travel t;
    TravelStrategy *ts = new FlightStrategy;
    t.setStrategy(ts);
    t.travel();
    delete ts;
    return 0;
}
