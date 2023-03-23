#include <vector>

#define matrix std::vector<std::vector<int>>

namespace IPCalculator
{
    struct IP
    {
        public:

            IP(int first, int second, int third, int fourth)
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

                this->FirstQuarter = first;
                this->SecondQuarter = second;
                this->ThirdQuarter = third;
                this->FourthQuarter = fourth;
            }

            

           int _FirstQuarter() const { return this->FirstQuarter; }
           int _SecondQuarter() const { return this->SecondQuarter; }
           int _ThirdQuarter() const { return this->ThirdQuarter; }
           int _FourthQuarter() const { return this->FourthQuarter; }

        private:

            int FirstQuarter = -1;
            int SecondQuarter = -1;
            int ThirdQuarter = -1;
            int FourthQuarter = -1;

        };


    class Calculations
    {
        public:

         matrix IPToBinaryArray(IPCalculator::IP *IPToConvert);
         matrix GetMaskFromSubnetID(IPCalculator::IP *SubnetID);

         /* 

         */
          

    };

}
