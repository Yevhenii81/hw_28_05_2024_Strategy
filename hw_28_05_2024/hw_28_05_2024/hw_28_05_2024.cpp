#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum TimeOfDay { Breakfast, Lunch, Dinner };
enum Product { Bread, Mayonnaise, Dumplings, Cheese, Ham, Egg, Tomato };

class Refrigerator
{
private:
    vector<Product> products;
public:
    void AddProduct(Product product) {
        products.push_back(product);
    }

    bool HasProduct(Product product) const {
        for (const auto& p : products) {
            if (p == product) {
                return true;
            }
        }
        return false;
    }
};

class CookingStrategy
{
public:
    virtual void cook(const Refrigerator& refrigerator) const = 0;
    virtual ~CookingStrategy() = default;
};

class BreakfastStrategy : public CookingStrategy {
public:
    void cook(const Refrigerator& refrigerator) const override {
        if (refrigerator.HasProduct(Product::Bread) && refrigerator.HasProduct(Product::Cheese) && refrigerator.HasProduct(Product::Ham)) {
            cout << "Making a ham and cheese sandwich for breakfast\n";
        }
        else if (refrigerator.HasProduct(Product::Egg)) {
            cout << "Making scrambled eggs for breakfast\n";
        }
        else {
            cout << "No ingredients for breakfast\n";
        }
    }
};

class LunchStrategy : public CookingStrategy {
public:
    void cook(const Refrigerator& refrigerator) const override {
        if (refrigerator.HasProduct(Product::Dumplings)) {
            cout << "Cooking dumplings for lunch\n";
        }
        else if (refrigerator.HasProduct(Product::Tomato) && refrigerator.HasProduct(Product::Cheese)) {
            cout << "Making a tomato and cheese salad for lunch\n";
        }
        else {
            cout << "No ingredients for lunch\n";
        }
    }
};

class DinnerStrategy : public CookingStrategy {
public:
    void cook(const Refrigerator& refrigerator) const override {
        if (refrigerator.HasProduct(Product::Bread) && refrigerator.HasProduct(Product::Mayonnaise) && refrigerator.HasProduct(Product::Ham)) {
            cout << "Making a ham sandwich for dinner\n";
        }
        else if (refrigerator.HasProduct(Product::Dumplings)) {
            cout << "Cooking dumplings for dinner\n";
        }
        else {
            cout << "No ingredients for dinner\n";
        }
    }
};

class CookingContext {
private:
    CookingStrategy* plan = nullptr;
public:
    void SetPlan(CookingStrategy* plan) {
        this->plan = plan;
    }

    void cook(const Refrigerator& refrigerator) const {
        if (plan) {
            plan->cook(refrigerator);
        }
        else {
            cout << "No cooking strategy set\n";
        }
    }
};

int main()
{
    Refrigerator refrigerator;
    refrigerator.AddProduct(Product::Bread);
    refrigerator.AddProduct(Product::Mayonnaise);
    refrigerator.AddProduct(Product::Ham);

    CookingContext context;
    TimeOfDay timeOfDay = TimeOfDay::Dinner;

    context.SetPlan(new DinnerStrategy());
    context.cook(refrigerator);
}
