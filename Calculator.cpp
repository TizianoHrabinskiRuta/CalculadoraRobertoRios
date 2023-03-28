#include <bits/stdc++.h>
#include <cmath>
#include "Calculator.h"

//Masks that have a number diferent from 255, 254, 252, 248, 240, 224, 192, 178 or 0, are wrong.
int main()
{
   int hola = 4;

    IPCalculator::Calculations *Calculator = new IPCalculator::Calculations();

   IPCalculator::IP IP(10, 10, 16, 0);
   matrix Binary = Calculator->IPToBinaryArray(&IP);

   Calculator->PrintBinaryArray(&Binary);

    delete Calculator;
    std::cin >> hola;
    return 0;
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

IPCalculator::IP IPCalculator::Calculations::GetSubnetMask(matrix *SubnetID, matrix *BroadcastID)
{
    int Marker = 0;
    bool MarkerFlag = false;

    int SubnetMarker = 0;
    bool SubnetMarkerFlag = false;


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

    for(int i = SubnetID[0].size() - 1; i >= 0; i--)
    {
        for(int j = SubnetID[0][i].size() - 1; j >= 0; j--)
        {
            if(SubnetID[0][i][j] == 1)
            {
                SubnetMarkerFlag = true;
                break;
            }
            SubnetMarker += 1;
        }
        if(SubnetMarkerFlag)
            break;
    }

    int RemainingBits = 32 - Marker;

    if(SubnetMarker < Marker)
        RemainingBits++;
    else if(Marker > SubnetMarker)
        RemainingBits--;

    bool FinishFlag = false;



  for(int i = 0; i < 4; i ++)
  {
      for(int j = 0; j < 8; j++)

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

    IPCalculator::Calculations *Calculator = new IPCalculator::Calculations();

    IPCalculator::IP ReturningIP = Calculator->BinaryArrayToIP(&MaskMatrix);
    delete Calculator;

    return ReturningIP;

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

IPCalculator::IP IPCalculator::Calculations::GetFirstHost(IPCalculator::IP *SubnetID)
{
    /* Tested, works correctly. */
    IPCalculator::IP ReturningIP(0, 0, 0, 0);

    if(SubnetID->_FourthQuarter() != 0)
    {
        std::cout << "Ha calculado mal la ID de subred, ya que el cuarto octeto no puede superar 0. " << std::endl;
        ReturningIP.IsInvalidIP = true;
        return ReturningIP;
    }

   ReturningIP = *(SubnetID);
   ReturningIP.AssignOctet(4, ReturningIP._FourthQuarter() + 1);

    return ReturningIP;
}

IPCalculator::IP IPCalculator::Calculations::GetLastHost(IPCalculator::IP *BroadcastID)
{
    /* Tested, works correctly. */
    IPCalculator::IP ReturningIP(0, 0, 0, 0);
    if(BroadcastID->_FourthQuarter() != 255)
    {
        std::cout << "La ip ingresada es invalida, ya que el cuarto octeto no puede ser otro valor que 255." << std::endl;
        ReturningIP.IsInvalidIP = true;
        return ReturningIP;
    }

    ReturningIP = *(BroadcastID);

    ReturningIP.AssignOctet(4, ReturningIP._FourthQuarter() - 1);
    return ReturningIP;

}

IPCalculator::IP IPCalculator::Calculations::GetBroadcastID(IPCalculator::IP *LastHost)
{
    /* Tested, works correctly. */
    IPCalculator::IP ReturningIP(0, 0, 0, 0);

    if(LastHost->_FourthQuarter() != 254)
    {
        std::cout << "La IP ingresada es invalida, ya que el cuarto octeto no puede ser diferente a 254." << std::endl;
        ReturningIP.IsInvalidIP = true;
        return ReturningIP;
    }

    ReturningIP = *(LastHost);

    ReturningIP.AssignOctet(4, ReturningIP._FourthQuarter() + 1);
    return ReturningIP;
}

IPCalculator::IP IPCalculator::Calculations::GetSubnetID(IPCalculator::IP *Subnetmask, IPCalculator::IP *BroadcastID)
{
    /* Tested, seems to works correctly. */
    IPCalculator::IP ReturningIP(0, 0, 0, 0);
    IPCalculator::Calculations* Calculator = new IPCalculator::Calculations();

    matrix BroadcastMatrix = Calculator->IPToBinaryArray(BroadcastID);
    matrix MaskMatrix = Calculator ->IPToBinaryArray(Subnetmask);
    matrix ANDResult(4, std::vector<int>(8, 0));

    for(int i = 0; i < BroadcastMatrix.size(); i++)
    {
        for(int j = 0; j < BroadcastMatrix[i].size(); j++)
        {
            if(MaskMatrix[i][j] == 1)
                ANDResult[i][j] = BroadcastMatrix[i][j];
            else
                ANDResult[i][j] = 0;
        }
    }

    ReturningIP = Calculator->BinaryArrayToIP(&ANDResult);
    delete Calculator;
    return ReturningIP;
}

IPCalculator::IP IPCalculator::Calculations::GetDecimalMask(int Mask)
{
    // WIP
    IPCalculator::IP ReturningIP(0, 0, 0, 0);
    matrix BinaryMask(4, std::vector<int>(8,0));
    bool StopFlag = false;

    for(int i = 0; i < BinaryMask.size(); i++)
    {
        for(int j = 0; j < BinaryMask[i].size(); j++)
        {
            if(Mask == 0)
            {
                StopFlag = true;
                break;
            }

            BinaryMask[i][j] = 1;
            Mask--;
        }

        if(StopFlag)
        break;
    }

    IPCalculator::Calculations *Calculator = new IPCalculator::Calculations();
    ReturningIP = Calculator->BinaryArrayToIP(&BinaryMask);

    delete Calculator;
    return ReturningIP;
}

IPCalculator::IP IPCalculator::Calculations::GetBroadcastID(IPCalculator::IP *SubnetID, IPCalculator::IP *SubnetMask)
{
    IPCalculator::IP ReturningIP(0, 0, 0, 0);

    matrix SubnetIDMatrix(4, std::vector<int>(8, 0));
    matrix SubnetMaskMatrix(4, std::vector<int>(8, 0));
    matrix ANDResult(4, std::vector<int>(8, 0));




}
