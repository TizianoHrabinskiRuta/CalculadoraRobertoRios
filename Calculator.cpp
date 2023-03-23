#include <bits/stdc++.h>
#include <cmath>
#include "Calculator.h"


int main()
{
    int hola3 = 0;

    IPCalculator::IP IPAddress(140, 10, 245, 100);

    IPCalculator::Calculations* Converter = new IPCalculator::Calculations();

    matrix Test = Converter->IPToBinaryArray(&IPAddress);

    for(int i = 0; i < Test.size(); i++)
    {
        std::cout << "Division: " << i << std::endl;
        for(int j = 0; j < Test[i].size(); j++)
        {
            std::cout << Test[i][j] << std::endl;
        }
    }


    std::cout << "Escriba cualquier cosa y apriete enter para salir." << std::endl;
    std::cin >> hola3;

    return 0;
}

matrix IPCalculator::Calculations::IPToBinaryArray(IPCalculator::IP *IPToConvert)
{
    matrix ReturningArray (4, std::vector<int>(8, 0));

    int Dividend = 0;
    int Index = 7;

   for(int i = 0 ; i != 4 ; i++)
   {
        Index = 7;

        /* Select the correct octet */
        if(i == 0)
            Dividend = IPToConvert->_FirstQuarter();

        else if (i == 1)
            Dividend = IPToConvert->_SecondQuarter();

        else if (i == 2)
        Dividend = IPToConvert->_ThirdQuarter();

        else 
        Dividend = IPToConvert->_FourthQuarter();
        
        while(Dividend != 0)    
        {
            ReturningArray[i][Index] = Dividend % 2;
            Dividend = std::floor(Dividend / 2);

            Index--;
        }  

   }

    return ReturningArray;

}

matrix IPCalculator::Calculations::GetMaskFromSubnetID(IPCalculator::IP *SubnetID)
{
    
}
