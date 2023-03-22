#include <vector>

namespace IPCalculator
{
    struct IP
    {
        public:
            IP(int first, int second, int third, int fourth, int _SubnetMask)
            {
                if(first > 255 || second > 255 || third > 255 || fourth > 255)
                this->FirstQuarter = first;
                this->SecondQuarter = second;
                this->ThirdQuarter = third;
                this->FourthQuarter = fourth;
                this->SubnetMask = _SubnetMask;

            }

            int FirstQuarter = -1;
            int SecondQuarter = -1;
            int ThirdQuarter = -1;
            int FourthQuarter = -1;

            int SubnetMask = -1;
        };


    class Conversions
    {
        public:

          std::vector<std::vector<int>> IPToBinaryArray(IPCalculator::IP *IPToConvert);

    };

}
