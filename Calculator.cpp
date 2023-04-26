#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

#include "Calculator.h"

#define Print(x) std::cout << x << std::endl;

//Masks that have a number diferent from 255, 254, 252, 248, 240, 224, 192, 178 or 0, are wrong.

int main()
{
    char Input;

    IPCalculator::Parser* Parser = new IPCalculator::Parser();


    Parser->ParseAndPassResults();


    std::cin >> Input;
    return 0;
}

void IPCalculator::Parser::ParseAndPassResults()
{
    std::cout << "Ingrese la ruta del archivo para leer:" << std::endl;
    std::string Path;
    std::cin >> Path;

    std::string Line;
    std::ifstream File(Path);

    std::map<std::string, matrix> AllocatedMatrices;
    std::map<std::string, IPCalculator::IP> AllocatedIPs;

    bool ForcefulTerminationFlag = false;
    bool RAVFlag = false;
    bool IsIP = true;
    std::string RAVVarName = "";

    while(getline(File, Line) && !ForcefulTerminationFlag)
    {

        if(Line.find("VAR") != std::string::npos) // Breaks when there is more than one space between different mods or params. Think of fix later.
        {

            std::string VarName = "";

            if(Line.find("M") != std::string::npos)  //found a matrix
            {
                VarName = this->ParseVarName(this->GetIndexOfFollowingSequence(Line.find("M"), Line), Line);

                AllocatedMatrices[VarName] = this->ParseMatrix(this->GetIndexOfFollowingSequence(Line.find(VarName), Line), Line);
            }

            else if (Line.find("I")) //found an IP
            {
                VarName = this->ParseVarName(this->GetIndexOfFollowingSequence(Line.find("I"), Line), Line);

                AllocatedIPs[VarName] = this->ParseIP(this->GetIndexOfFollowingSequence(Line.find(VarName), Line), Line);
            }

        }

        else if(Line.find ("RAV") != std::string::npos)
        {
            unsigned short int ParsingPosition = this->GetIndexOfFollowingSequence(Line.find("RAV"), Line);

            IsIP = (Line[ParsingPosition] == 'I') ? true : false;
            ParsingPosition = this->GetIndexOfFollowingSequence(ParsingPosition, Line);
            RAVFlag = (Line[ParsingPosition] == 'R') ? true : false;


            if(RAVFlag)
            {
                ParsingPosition = this->GetIndexOfFollowingSequence(ParsingPosition, Line);

                RAVVarName = this->ParseVarName(ParsingPosition, Line);
                continue;
            }

            else if(IsIP && !RAVFlag)
            {
                ParsingPosition = this->GetIndexOfFollowingSequence(ParsingPosition, Line);
                RAVVarName = this->ParseVarName(ParsingPosition, Line);

                AllocatedIPs[RAVVarName] = this->ParseIP(ParsingPosition, Line);
                RAVFlag = false;
                IsIP = false;
                RAVVarName = "";
            }

            else if(!IsIP && !RAVFlag)
            {
                ParsingPosition = this->GetIndexOfFollowingSequence(ParsingPosition, Line);
                RAVVarName = this->ParseVarName(ParsingPosition, Line);

                AllocatedMatrices[RAVVarName] = this->ParseMatrix(ParsingPosition, Line);
                RAVVarName = "";
            }

        }

        else if(Line.find("PRT") != std::string::npos)
        {
            unsigned short int ParsingPosition = Line.find("PRT");
            bool IsIP = false;
            ParsingPosition = this->GetIndexOfFollowingSequence(ParsingPosition, Line);

            IsIP = (Line[ParsingPosition] == 'I') ? true : false;
            ParsingPosition = this->GetIndexOfFollowingSequence(ParsingPosition, Line);

            std::string VarName = this->ParseVarName(ParsingPosition, Line);

            std::map<std::string, matrix>::iterator MatrixIterator;
            std::map<std::string, IPCalculator::IP>::iterator IPIterator;

            if(IsIP)
            {
                IPIterator = AllocatedIPs.find(VarName);
                if(IPIterator == AllocatedIPs.end())
                {
                    std::cout << "Variable of type IP named " << VarName << " hasn't been declared yet." << std::endl;
                    ForcefulTerminationFlag = true;
                    continue;
                }
                std::cout << "IP: " << VarName << " = ";
                IPCalculator::Calculations::PrintIP(&AllocatedIPs[VarName]);
            }
            else
            {
                MatrixIterator = AllocatedMatrices.find(VarName);
                if(MatrixIterator == AllocatedMatrices.end())
                {
                    std::cout << "Variable of type matrix named " << VarName << " hasn't been declared yet." << std::endl;
                    ForcefulTerminationFlag = true;
                    continue;
                }

                std::cout << "matrix: " << VarName << " = ";
                IPCalculator::Calculations::PrintBinaryArray(&AllocatedMatrices[VarName]);

            }

        }

        else if(Line.find("GSM") != std::string::npos)
        {
            unsigned int ParsingPosition = this->GetIndexOfFollowingSequence(Line.find("GSM"), Line);
            std::string Var1 = this->ParseVarName(ParsingPosition, Line);

            ParsingPosition = this->GetIndexOfFollowingSequence(ParsingPosition, Line);
            std::string Var2 = this->ParseVarName(ParsingPosition, Line);

            IPCalculator::Calculations *Calculator = new IPCalculator::Calculations();

            IPCalculator::IP Result(0,0,0,0);

            matrix Matrix1 = Calculator->IPToBinaryArray(&AllocatedIPs[Var1]);
            matrix Matrix2 = Calculator->IPToBinaryArray(&AllocatedIPs[Var2]);

            Result = Calculator->GetSubnetMask(&Matrix1, &Matrix2);
            std::cout << "Subnet Mask: ";
            Calculator->PrintIP(&Result);

            if(RAVFlag)
            {
                if(IsIP)
                {
                    AllocatedIPs[RAVVarName] = Result;
                    RAVFlag = false;
                    IsIP = false;
                    RAVVarName = "";
                }

                else
                {
                    AllocatedMatrices[RAVVarName] = Calculator->IPToBinaryArray(&Result);
                    RAVFlag = false;
                    RAVVarName = "";
                }
            }

            delete Calculator;
        }

        else if(Line.find("GFH") != std::string::npos)
        {
            unsigned short int ParsingPosition = this->GetIndexOfFollowingSequence(Line.find("GFH"), Line);

            std::string Var1 = this->ParseVarName(ParsingPosition, Line);

            IPCalculator::Calculations *Calculator = new IPCalculator::Calculations();

            IPCalculator::IP Temp(0,0,0,0);
            Temp = Calculator->GetFirstHost(&AllocatedIPs[Var1]);
            if(Temp.IsInvalidIP)
            {
                ForcefulTerminationFlag = true;
                continue;
            }

            if(RAVFlag)
            {
                if(IsIP)
                {
                    AllocatedIPs[RAVVarName] = Temp;
                    RAVVarName = "";
                    RAVFlag = false;
                    IsIP = false;
                }
                else
                {
                    AllocatedMatrices[RAVVarName] = Calculator->IPToBinaryArray(&Temp);
                    RAVVarName = "";
                    RAVFlag = false;
                    IsIP = false;
                }
            }

            delete Calculator;
        }

        else if(Line.find("GLH") != std::string::npos)
        {
            unsigned short int ParsingPosition = this->GetIndexOfFollowingSequence(Line.find("GLH"), Line);

            std::string Var1 = this->ParseVarName(ParsingPosition, Line);

            IPCalculator::Calculations *Calculator = new IPCalculator::Calculations();
            IPCalculator::IP Temp = Calculator->GetLastHost(&AllocatedIPs[Var1]);

            if(Temp.IsInvalidIP)
            {
                ForcefulTerminationFlag = true;
                continue;
            }

            if(RAVFlag)
            {
                if(IsIP)
                {
                    AllocatedIPs[RAVVarName] = Temp;
                    RAVVarName = "";
                    RAVFlag = false;
                    IsIP = false;
                }
                else
                {
                    AllocatedMatrices[RAVVarName] = Calculator->IPToBinaryArray(&Temp);
                    RAVVarName = "";
                    RAVFlag = false;
                    IsIP = false;
                }
            }

            delete Calculator;

        }


        else if (Line.find("GSI") != std::string::npos)
        {
            unsigned short int ParsingPosition = this->GetIndexOfFollowingSequence(Line.find("GSI"), Line);

            std::string Var1 = this->ParseVarName(ParsingPosition, Line);
            ParsingPosition = this->GetIndexOfFollowingSequence(ParsingPosition, Line);
            std::string Var2 = this->ParseVarName(ParsingPosition, Line);

            IPCalculator::Calculations *Calculator = new IPCalculator::Calculations();

            IPCalculator::IP Temp = Calculator->GetSubnetID(&AllocatedIPs[Var1], &AllocatedIPs[Var2]);

            if(RAVFlag)
            {
                if(IsIP)
                {
                    AllocatedIPs[RAVVarName] = Temp;
                    RAVVarName = "";
                    RAVFlag = false;
                    IsIP = false;
                }
                else
                {
                    AllocatedMatrices[RAVVarName] = Calculator->IPToBinaryArray(&Temp);
                    RAVVarName = "";
                    RAVFlag = false;
                    IsIP = false;
                }
        }

            delete Calculator;
        }

    }

}

unsigned short int IPCalculator::Parser::GetIndexOfFollowingSequence(size_t LastKnownCharPosition, const std::string &Line)
{
    unsigned short int ReturningIndex = LastKnownCharPosition;

    while(Line[ReturningIndex] != ' ')
        ReturningIndex++;
    while(Line[ReturningIndex] == ' ')
        ReturningIndex++;

    return ReturningIndex;
}

matrix IPCalculator::Parser::ParseMatrix(size_t StartIndex, const std::string &Line) // Both value parsers always assume that the input will be a valid length. Fix later.
{
    matrix ReturningMatrix(4, std::vector<int>(8,0));

    unsigned short int CurrentOctet = 0;
    unsigned short int ParsingPosition = StartIndex;
    unsigned short int AllocationIndex = 0;

    while(CurrentOctet <= 3)
    {
        if(Line[ParsingPosition] == '.' || ParsingPosition == Line.size())
        {
            CurrentOctet++;
            AllocationIndex = 0;
            ParsingPosition++;
            continue;
        }


        if(Line[ParsingPosition] - '0' == 0 || Line[ParsingPosition] - '0' == 1)
        {
            ReturningMatrix[CurrentOctet][AllocationIndex] = Line[ParsingPosition] - '0';
            AllocationIndex++;
            ParsingPosition++;
        }

        else
        {
            std::cout << "IP binaria en el octeto " << CurrentOctet + 1 << " tiene un bit que no es 0 ni 1." << std::endl;
            exit(1);
        }

    }

    return ReturningMatrix;

}

std::string IPCalculator::Parser::ParseVarName(size_t StartIndex, const std::string &Line)
{
    std::string ReturningString = "";
    unsigned short int ParsingPosition = StartIndex;

    while(Line[ParsingPosition] != ' ' &&  Line[ParsingPosition] != '\n' && Line[ParsingPosition] != '\r' && Line[ParsingPosition] != ',' && ParsingPosition < Line.size())
    {
        ReturningString += Line[ParsingPosition];
        ParsingPosition++;
    }

    return ReturningString;
}

IPCalculator::IP IPCalculator::Parser::ParseIP(size_t StartIndex, const std::string &Line)
{
    IPCalculator::IP ReturningIP(0,0,0,0);
    size_t ParsingPosition = StartIndex;

    unsigned short int CurrentOctet = 1;
    std::string OctetValue = "";

    while(CurrentOctet <= 4)
    {

        if(Line[ParsingPosition] == '.' || ParsingPosition == Line.size())
        {
            ReturningIP.AssignOctet(CurrentOctet, std::stoi(OctetValue));
            CurrentOctet++;
            OctetValue = "";
            ParsingPosition++;
            continue;
        }

        OctetValue += Line[ParsingPosition];
        ParsingPosition++;

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


    std::string ConvertedMatrix = "";

    for(int i = 0; i < MatrixToPrint[0].size(); i++)
    {
        for(int j = 0; j < MatrixToPrint[0][i].size(); j++)
        {
            ConvertedMatrix += (char)MatrixToPrint[0][i][j] + '0';
        }

        ConvertedMatrix += '.';
    }

    ConvertedMatrix.pop_back();
    std::cout << ConvertedMatrix << std::endl;
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

    /* Tested, seems to work correctly*/
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


    IPCalculator::IP ReturningIP = this->BinaryArrayToIP(&MaskMatrix);

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
    /* Tested, seems to work correctly */
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
   IPCalculator::IP ReturningIP = *(SubnetID);
   IPCalculator::Calculations *Calculator = new IPCalculator::Calculations();

   matrix SubnetMaskMatrix = Calculator->IPToBinaryArray(SubnetMask);
   int LeftoverValue = 0;
   int Step = 1;
   int Ceroes = 0;

   if(SubnetMask->_FourthQuarter() == 0)
   {
       for(int i = 0; i < 8; i++)
       {
           if( SubnetMaskMatrix[2][i] == 0)
                Ceroes++;
       }

       while(Ceroes != 0)
       {
           LeftoverValue += Step;
           Step *= 2;
           Ceroes--;
       }

       ReturningIP.AssignOctet(3, SubnetID->_ThirdQuarter() + LeftoverValue);
       ReturningIP.AssignOctet(4, 255);

   }

   else if( SubnetMask->_FourthQuarter() != 0)
   {
       for(int i = 0; i < 8; i++)
       {
           if( SubnetMaskMatrix[3][i] == 0)
                Ceroes++;
       }

       while(Ceroes != 0)
       {
           LeftoverValue += Step;
           Step *= 2;
           Ceroes--;
       }

       ReturningIP.AssignOctet(4, SubnetID->_FourthQuarter() + LeftoverValue);
   }

   delete Calculator;
   return ReturningIP;
}
