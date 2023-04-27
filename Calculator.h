#include <vector>

typedef std::vector<std::vector<int>> matrix;

namespace IPCalculator
{
    struct IP
    {
        public:
            IP()
            {
                this->FirstQuarter = 0;
                this->SecondQuarter = 0;
                this->ThirdQuarter = 0;
                this->FourthQuarter = 0;
            }

            IP(int first, int second, int third, int fourth)
            {
                if(first > 255 || second > 255 || third > 255 || fourth > 255)
                {
                    std::cout << "Un octeto superó el limite de 255." << std::endl;
                    return;
                }

                if(first < 0 || second < 0 || third < 0 || fourth < 0)
                {
                    std::cout << "Un octeto fue inferior a 0." << std::endl;
                    return;
                }

                this->FirstQuarter = first;
                this->SecondQuarter = second;
                this->ThirdQuarter = third;
                this->FourthQuarter = fourth;
            }

            IP(int first, int second, int third, int fourth, bool _IsInvalidIP)
            {
                 if(first > 255 || second > 255 || third > 255 || fourth > 255)
                {
                    std::cout << "Un octeto superó el limite de 255." << std::endl;
                    return;
                }

                if(first < 0 || second < 0 || third < 0 || fourth < 0)
                {
                    std::cout << "Un octeto fue inferior a 0." << std::endl;
                    return;
                }

                this->FirstQuarter = first;
                this->SecondQuarter = second;
                this->ThirdQuarter = third;
                this->FourthQuarter = fourth;
                this->IsInvalidIP = _IsInvalidIP;
            }

            void operator = (IPCalculator::IP RightOperand)
            {
                this->AssignOctet(1, RightOperand._FirstQuarter());
                this->AssignOctet(2, RightOperand._SecondQuarter());
                this->AssignOctet(3, RightOperand._ThirdQuarter());
                this->AssignOctet(4, RightOperand._FourthQuarter());
            }

            void AssignOctet(int Octet, int Value)
            {
                if(Value > 255 || Value < 0) return;

                switch(Octet)
                {
                    case 1:
                        this->FirstQuarter = Value;
                        break;

                    case 2:
                        this->SecondQuarter = Value;
                        break;

                    case 3:
                        this->ThirdQuarter = Value;
                        break;

                    case 4:
                        this->FourthQuarter = Value;
                        break;

                    default:
                        std::cout << "Valor de parametro octeto tiene que ser entre 1 y 4 inclusive." << std::endl;
                        break;
                }

            }

           int _FirstQuarter() const { return this->FirstQuarter; }
           int _SecondQuarter() const { return this->SecondQuarter; }
           int _ThirdQuarter() const { return this->ThirdQuarter; }
           int _FourthQuarter() const { return this->FourthQuarter; }
           bool IsInvalidIP = false;

        private:

            int FirstQuarter = -1;
            int SecondQuarter = -1;
            int ThirdQuarter = -1;
            int FourthQuarter = -1;

        };


    class Calculations // this is not a flawless calculator. Some calculations are impossible, yet it completes them. Double check your results before writing them down.
    {
        public:

         matrix IPToBinaryArray(IPCalculator::IP *IPToConvert);

         IPCalculator::IP BinaryArrayToIP(matrix *BinaryArray);
         IPCalculator::IP GetSubnetMask(matrix *SubnetID, matrix *BroadcastID); //Most likely works 90% of the time. Not very fast
         IPCalculator::IP GetFirstHost(IPCalculator::IP *SubnetID);
         IPCalculator::IP GetLastHost(IPCalculator::IP *BroadcastID);
         IPCalculator::IP GetBroadcastID(IPCalculator::IP *LastHost);
         IPCalculator::IP GetSubnetID(IPCalculator::IP *Subnetmask, IPCalculator::IP *BroadcastID); // Most likely works 90% of the time. Good speed.
         IPCalculator::IP GetDecimalMask(int Mask);
         IPCalculator::IP GetBroadcastID(IPCalculator::IP *SubnetID, IPCalculator::IP *SubnetMask); // Prone to give errors when dealing with something like 1.1.0.0 or 1.0.0.0

         static void PrintIP(IPCalculator::IP *IPToPrint);
         static void PrintBinaryArray(matrix *MatrixToPrint);

    };

    class Parser
    {
        public:

         void ParseAndPassResults();

         IPCalculator::IP ParseIP(size_t StartIndex, const std::string &Line);
         matrix ParseMatrix(size_t StartIndex, const std::string &Line);
         std::string ParseVarName(size_t StartIndex, const std::string &Line);
         unsigned short int GetIndexOfFollowingSequence(size_t LastKnownCharPosition, const std::string &Line);


        private:

         struct RAVInfo
         {
            RAVInfo(std::string *RAVVarName, bool *IsIPFlag, bool *RAVFlag, std::map<std::string, matrix> *AllocatedMatrices)
            {
                this->VarName = RAVVarName;
                this->IsIP = IsIPFlag;
                this->RAVVarFlag = RAVFlag;

                this->AllocatedMatricesPtr = AllocatedMatrices;
            }

            RAVInfo(std::string *RAVVarName, bool *IsIPFlag, bool *RAVFlag, std::map<std::string, IPCalculator::IP> *AllocatedIPs)
            {
                this->VarName = RAVVarName;
                this->IsIP = IsIPFlag;
                this->RAVVarFlag = RAVFlag;
                this->AllocatedIPsPtr = AllocatedIPs;
            }


            std::string *VarName;
            bool *IsIP;
            bool *RAVVarFlag;

            std::map<std::string, matrix> *AllocatedMatricesPtr;
            std::map<std::string, IPCalculator::IP> *AllocatedIPsPtr;
         };

        private:
         void SolveRAV(RAVInfo &Data, const IPCalculator::IP &Value);


    };

}
