#include <bits/stdc++.h>
using namespace std;

struct Product
{
    string name;
    double price;
};

struct Discount
{
    string name = "None";
    double amount = 0;
};

const int MAX_PRODUCTS = 3;
const int PACKAGE_CAPACITY = 10;
const double SHIPPING_FEE_PER_PACKAGE = 5.0;
const double GIFT_WRAP_FEE = 1.0;

// Function to calculate the total amount for a product
double calculateProductTotal(int quantity, const Product &product)
{
    return quantity * product.price;
}

// Function to calculate the discount amount based on the discount rule
Discount calculateDiscount(int subtotal, int productQuantity[], const Product product[], int totalQuantity)
{

    Discount discount_applicable;
    double temp = 0, temp_50 = 0;
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        if (totalQuantity > 30)
        {
            if (productQuantity[i] > 15)
            {
                int remaining_quantity = productQuantity[i] - 15;
                temp_50 += remaining_quantity * product[i].price * 0.5;
            }
        }
        if (productQuantity[i] > 10)
        {
            temp += productQuantity[i] * product[i].price * 0.05;
        }
    }
    if (discount_applicable.amount < temp)
    {
        discount_applicable.amount = temp;
        discount_applicable.name = "bulk_5_discount";
        temp = 0;
    }
    if (discount_applicable.amount < temp_50)
    {
        discount_applicable.amount = temp_50;
        discount_applicable.name = "tiered_50_discount";
        temp_50 = 0;
    }
    if (totalQuantity > 20)
    {
        temp = subtotal * 0.1;
        if (discount_applicable.amount < temp)
        {
            discount_applicable.amount = temp;
            discount_applicable.name = "bulk_10_discount";
        }
    }
    if (subtotal > 200)
    {
        if (discount_applicable.amount < 10.0)
        {
            discount_applicable.amount = 10.0;
            discount_applicable.name = "flat_10_discount";
        }
    }
    return discount_applicable;
}

int main()
{
    Product catalog[MAX_PRODUCTS] = {
        {"Product A", 20.0},
        {"Product B", 40.0},
        {"Product C", 50.0}};

    int quantities[MAX_PRODUCTS];
    bool giftWraps[MAX_PRODUCTS];

    double subtotal = 0.0;
    int totalQuantity = 0;

    cout << "*********************************************************************************" << endl
         << "*********************************************************************************" << endl
         << "*********************************************************************************" << endl
         << "                                   Order                                         " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    // Prompt the user for quantity and gift wrap information for each product
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        cout << "Enter the quantity of " << catalog[i].name << " (in integers): ";
        cin >> quantities[i];
        if (quantities[i] > 0)
        {
            cout << "Is " << catalog[i].name << " wrapped as a gift? (1 for yes, 0 for no): ";
            cin >> giftWraps[i];
        }
        else
        {
            giftWraps[i] = false;
        }
        subtotal += calculateProductTotal(quantities[i], catalog[i]);
        totalQuantity += quantities[i];
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    cout << endl
         << "*********************************************************************************" << endl
         << "*********************************************************************************" << endl
         << "*********************************************************************************" << endl;
    // Calculate the discount amount
    Discount productDiscount = calculateDiscount(subtotal, quantities, catalog, totalQuantity);

    // Calculate the shipping fee and gift wrap fee
    int numPackages = (totalQuantity + PACKAGE_CAPACITY - 1) / PACKAGE_CAPACITY;
    double shippingFee = numPackages * SHIPPING_FEE_PER_PACKAGE;
    double giftWrapFee = 0.0;
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        if (giftWraps[i])
        {
            giftWrapFee += quantities[i] * GIFT_WRAP_FEE;
        }
    }

    // Calculate the total amount
    double total = subtotal - productDiscount.amount + shippingFee + giftWrapFee;

    // Display the details
    cout << fixed << setprecision(2);
    cout << "                                     Bill                                        " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        double productTotal = calculateProductTotal(quantities[i], catalog[i]);
        cout << catalog[i].name << ", Quantity: " << quantities[i] << ", Total:                    $" << productTotal << endl;
    }
    cout << endl;

    cout << "Subtotal:                                          $" << subtotal << endl
         << endl;
    ;
    cout << "Discount Applied: " << productDiscount.name << ", Amount:         $" << productDiscount.amount << endl
         << endl;

    cout << "Shipping Fee:                                      $" << shippingFee << endl;
    cout << "Gift Wrap Fee:                                     $" << giftWrapFee << endl
         << endl;
    cout << "Total:                                             $" << total << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
         << endl;
    cout << "*********************************************************************************" << endl
         << "*********************************************************************************" << endl
         << "*********************************************************************************" << endl;
    return 0;
}
