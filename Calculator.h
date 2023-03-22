#include <vector>

namespace IPCalculator
{
    struct IP
    {
        public:

            IP(int first, int second, int third, int fourth, int _SubnetMask)
            {
                if(first > 255 || second > 255 || third > 255 || fourth > 255)
                {
                    std::cout << "Un octeto superó el limite de 255." << std::endl;
                    return;
                }

                if(first <= 0 || second <= 0 || third <= 0 || fourth <= 0)
                {
                    std::cout << "Un octeto fue inferior a 0." << std::endl;
                    return;
                }

                if(_SubnetMask > 30 || _SubnetMask < 8)
                {
                    std::cout << "Mascara de subred fuera de rango admisible"<< std::endl;
                    return;
                }


                this->FirstQuarter = first;
                this->SecondQuarter = second;
                this->ThirdQuarter = third;
                this->FourthQuarter = fourth;
                this->SubnetMask = _SubnetMask;

            }

        public:
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
