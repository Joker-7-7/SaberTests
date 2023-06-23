#include "List.hpp"

#include <iostream>

int main()
{
    auto list = std::make_unique<List>();

    list->PushFront("2");
    list->PushBack("3");
    list->PushBack("4");
    list->PushFront("1");
    list->UpdateRandPointers();

    std::cout << "Before Serialization:" << std::endl;
    list->Print();

    FILE* file = fopen("testList.bin", "wb");
    if (file != nullptr) {
        list->Serialize(file);
        fclose(file);
    }

    file = fopen("testList.bin", "rb");
    if (file != nullptr) {
        auto deserializedList = std::make_unique<List>();
        deserializedList->Deserialize(file);
        fclose(file);

        std::cout <<  "\nAfter Deserialization:" << std::endl;
        deserializedList->Print();
    }

    return 0;
}
