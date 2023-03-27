#include <bits/stdc++.h>
#include <cmath>
#include "Calculator.h"


int main()
{
   int hola = 4;

   IPCalculator::IP Test(140, 200, 120, 79);

   IPCalculator::Calculations* Calculator = new IPCalculator::Calculations();

  
    std::cin >> hola;
    return 0;
}




matrix IPCalculator::Calculations::IPToBinaryArray(IPCalculator::IP *IPToConvert)
{
    /* Tested, works correctly. */
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

IPCalculator::IP IPCalculator::Calculations::BinaryArrayToIP(matrix *BinaryArray)
{
    /* Tested, works */
    IPCalculator::IP ReturningIP(0, 0, 0, 0);

    int CalculatedOctetValue = 0;
    int StepValue = 1;
        

    for(int i = 0; i < BinaryArray[0].size() ; i++)
    {
    
        for(int j = BinaryArray[0][i].size() - 1 ; j >= 0 ; j--)
        {
            if( BinaryArray[0][i][j] == 1)
                CalculatedOctetValue += StepValue;

            StepValue *= 2;
        }

        ReturningIP.AssignOctet(i + 1, CalculatedOctetValue);
        CalculatedOctetValue = 0;
        StepValue = 1;
    }

   

    return ReturningIP;
}

void IPCalculator::Calculations::PrintIP(IPCalculator::IP *IPToPrint)
{
    /* Tested, works correctly. */
    std::cout << IPToPrint->_FirstQuarter() << "." << IPToPrint->_SecondQuarter() << "." << IPToPrint->_ThirdQuarter() << "." << IPToPrint->_FourthQuarter() << std::endl;
}

void IPCalculator::Calculations::PrintBinaryArray(matrix *MatrixToPrint)
{
    /* Tested, works correctly. */

    std::vector<char> Buffer;

    for( int i = 0; i < MatrixToPrint[0].size(); i++)
    {
        for( int j = 0; j < MatrixToPrint[0][i].size(); j++ )
        {
            if(MatrixToPrint[0][i][j] == 0)
                Buffer.push_back('0');

            else if(MatrixToPrint[0][i][j] == 1)
                Buffer.push_back('1');
        }        

        /* Avoids placing a lone point at the end of the buffer when all the bits have been added */
        if(i < MatrixToPrint[0].size() - 1)
            Buffer.push_back('.');
    }

 
    for(int i = 0; i < Buffer.size(); i++)
        std::cout <<  Buffer[i] << std::endl;

}

















