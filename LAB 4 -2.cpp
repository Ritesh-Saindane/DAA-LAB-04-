#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string add(string x, string y)
{
    string result = "";
    int carry = 0, sum = 0;

    while (x.size() < y.size())
        x = "0" + x;
    while (y.size() < x.size())
        y = "0" + y;

    for (int i = x.size() - 1; i >= 0; --i)
    {
        sum = (x[i] - '0') + (y[i] - '0') + carry;
        carry = sum / 10;
        result = char(sum % 10 + '0') + result;
    }

    if (carry)
        result = '1' + result;

    return result;
}

string subtract(string x, string y)
{
    string result = "";
    int borrow = 0;

    while (x.size() < y.size())
        x = "0" + x;
    while (y.size() < x.size())
        y = "0" + y;

    for (int i = x.size() - 1; i >= 0; --i)
    {
        int sub = (x[i] - '0') - (y[i] - '0') - borrow;
        if (sub < 0)
        {
            sub += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result = char(sub + '0') + result;
    }

    while (result[0] == '0' && result.size() > 1)
        result.erase(0, 1);

    return result;
}

string karatsuba(string x, string y)
{
    if (x.size() < 2 || y.size() < 2)
    {
        return to_string(stoi(x) * stoi(y));
    }

    int n = max(x.size(), y.size());
    int half = n / 2;

    string a = x.substr(0, x.size() - half);
    string b = x.substr(x.size() - half);
    string c = y.substr(0, y.size() - half);
    string d = y.substr(y.size() - half);

    string ac = karatsuba(a, c);
    string bd = karatsuba(b, d);
    string ad_plus_bc = add(karatsuba(a, d), karatsuba(b, c));

    for (int i = 0; i < 2 * (n - half); ++i)
        ac += '0';
    for (int i = 0; i < n - half; ++i)
        ad_plus_bc += '0';

    return add(add(ac, ad_plus_bc), bd);
}

string parseScientific(const string &input)
{
    size_t ePos = input.find('e');
    if (ePos == string::npos)
        return input;

    string base = input.substr(0, ePos);
    int exponent = stoi(input.substr(ePos + 1));

    string integerPart = base;
    while (base.find('.') != string::npos)
    {
        integerPart.erase(integerPart.find('.'), 1);
    }

    int decimalPosition = base.find('.');
    if (decimalPosition != string::npos)
    {
        exponent += decimalPosition - (integerPart.size() - 1);
    }

    return integerPart + string(exponent, '0');
}

int main()
{
    string num1 = "123456789";
    string num2 = "987654321";
    string product = karatsuba(num1, num2);
    cout << "Product: " << product << endl;

    string scientific = "2.34e5";
    string parsed = parseScientific(scientific);
    cout << "Parsed scientific: " << parsed << endl;

    return 0;
}
