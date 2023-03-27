#include <bits/stdc++.h>
#include <cmath>
#include "Calculator.h"


int main()
{
   int hola = 4;


    IPCalculator::Calculations *Calculator = new IPCalculator::Calculations();

    IPCalculator::IP Broadcast1(10, 10, 31, 255);
    matrix Pollo = Calculator->IPToBinaryArray(&Broadcast1);

    IPCalculator::IP SubnetMask = Calculator->GetSubnetMask(&Pollo);
    Calculator->PrintIP(&SubnetMask);



    std::cin >> hola;
    return 0;
}


 IPCalculator::IP IPCalculator::Calculations::GetSubnetMask(matrix *BroadcastID)
{

//broken :( (maybe has something to do with the bit it detects as 0 not coinciding with the SubnetID?)
    int Marker = 0;
    bool MarkerFlag = false;


    matrix MaskMatrix(4, std::vector<int>(8, 0));


    for(int i = BroadcastID[0].size() - 1; i >= 0; i--)
    {
        for(int j = BroadcastID[0][i].size() - 1; j >= 0; j--)
        {
            if(BroadcastID[0][i][j] == 0)
            {
                MarkerFlag = true;
                break;
            }
            Marker += 1;
        }

        if(MarkerFlag)
            break;
    }

    int RemainingBits = 32 - Marker;
    bool FinishFlag = false;



  for(int i = 0; i < 4; i ++)
  {
      for(int j = 0; j < 8; j++)//allocating at unimplemented space, initialize matrix with standard IP bounds.

      {
        MaskMatrix[i][j] = 1;
        RemainingBits--;
        if(RemainingBits == 0)
        {
            FinishFlag = true;
            break;
        }
      }

      if(FinishFlag)
        break;
  }

    IPCalculator::Calculations *Calculator = new IPCalculator::Calculations(); // Memory leak?

    IPCalculator::IP ReturningIP = Calculator->BinaryArrayToIP(&MaskMatrix);
    delete Calculator;

    return ReturningIP;

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
    /* Tested, works correctly. */
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
