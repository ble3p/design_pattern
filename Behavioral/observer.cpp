#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

class Subject;

class AbsObserver
{
public:
    virtual void update(string content) = 0;
    
};

class Subject
{
public:
    Subject() = default;
    Subject(const string &str):title(str) {}
    Subject(Subject *s) : title(s -> title)
    {
        vec.assign(s -> vec.begin(), s -> vec.end());
    }
    void attach(AbsObserver *obs)
    {
        vec.push_back(obs);
    }
    void detach(AbsObserver *obs)
    {
        auto it = find(vec.begin(), vec.end(), obs);
        if (it != vec.end())
            vec.erase(it);
    }
    void notify(const string &str)
    {
        for (auto &e :vec)
            e -> update(str);
    }
    string getTitle()
    {
        return title;
    }
private:
    string title;
    vector<AbsObserver*> vec;
    
};

class Observer :public AbsObserver
{
public:
    Observer(Subject *s, string n) :sub(s), name(n) {}
    void update(string content) override
    {
        cout << "[" << sub -> getTitle() <<  "]: " << content << "----------" << name << endl;
    }
private:
    string name;
    Subject *sub;
    
};

int main()
{
    string first_name = "observer ";
    vector<Observer> vec;
    Subject s("美食channel");
    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(Observer(&s, first_name + to_string(i + 1)));
    }
    for (int i = 0; i < vec.size(); ++i)
    {
        s.attach(&vec[i]);
    }
    s.notify("今日菜谱: Omlet");
}

