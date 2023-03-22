#include <bits/stdc++.h>
#include "Calculator.h"


int main()
{
    IPCalculator::IP IPAddress(5,5,5,5,5);

    IPCalculator::Conversions* Converter = new IPCalculator::Conversions();

    Converter->IPToBinaryArray(&IPAddress);

    return 0;
}

std::vector<std::vector<int>> IPCalculator::Conversions::IPToBinaryArray(IP *IPToConvert)
{
    std::vector<std::vector<int>> ReturningArray (4, std::vector<int>(8, 0));

    std::vector<int> CurrentBinaryResult;



}
