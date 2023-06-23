#include <iostream>
#include <vector>

void BinaryPrint(int number) {
    int absNumber = number;
    std::vector<int> result;
    if (number < 0) {
        result.push_back(1);
        absNumber *= -1;
    } else {
        result.push_back(0);
    }

    int remainder = absNumber;
    int quotient = absNumber;
    while(quotient >= 0) {
        quotient /= 2;
        remainder %= 2;
        result.push_back(remainder);
        remainder = quotient;

        if(quotient == 0) {
            break;
        }
    }

    std::reverse(std::begin(result) + 1, std::end(result));

    for (auto element : result) {
        std::cout << element;
    }
}

int main()
{
    for(int i = -10; i <= 10; ++i){
        BinaryPrint(i);
        std::cout << std::endl;
    }
}
