#include "List.hpp"

#include <utility>
#include <vector>
#include <iostream>
#include <map>
#include <random>
#include <chrono>

List::List() :
    head(nullptr),
    tail(nullptr),
    count(0)
{
}

List::~List() {
    if(head == nullptr) {
        return;
    }

    auto* removedNode = head->next;
    while (removedNode != nullptr) {
        auto* nextNode = removedNode->next;
        delete removedNode;
        removedNode = nextNode;
    }
    delete head;
}

void List::Serialize(FILE* file) const {
    auto currNode = head;
    while (currNode != nullptr) {
        fprintf(file, "%llu %llu\n%s\n",
                reinterpret_cast<std::uintptr_t>(currNode),
                reinterpret_cast<std::uintptr_t>(currNode->rand),
                currNode->data.c_str());
        currNode = currNode->next;
    }
}

void List::Deserialize(FILE* file) {
    std::map<std::uintptr_t, ListNode*> nodesMap;
    nodesMap[reinterpret_cast<std::uintptr_t>(nullptr)] = nullptr;

    std::vector<std::uintptr_t> randKeys;

    std::uintptr_t keyNode, randKey;
    while (fscanf_s(file, "%llu %llu\n", &keyNode, &randKey) != EOF) {
        char bufferChar, buffer[256];
        int cursoreLineIndex = 0;

        while ((bufferChar = fgetc(file)) != '\n' ) {
            buffer[cursoreLineIndex++] = bufferChar;
        }
        buffer[cursoreLineIndex] = '\0';

        PushBack(buffer);
        nodesMap[keyNode] = tail;
        randKeys.push_back(randKey);
    }

    auto currNode = head;
    int keyIndex = 0;
    while (currNode != nullptr) {
        currNode->rand = nodesMap[randKeys[keyIndex]];
        currNode = currNode->next;
        keyIndex++;
    }
}

void List::PushFront(std::string newData) noexcept {
    auto* newNode = new ListNode{ nullptr, nullptr, nullptr, std::move(newData) };
    ListNode* oldHead = head;

    if (head != nullptr) {
        head->prev = newNode;
        newNode->next = head;
    }

    head = newNode;
    ++count;
    if (oldHead == nullptr) {
        tail = head;
    }
}

void List::PushBack(std::string newData) noexcept {
    auto* newNode = new ListNode{ nullptr, nullptr, nullptr, std::move(newData) };
    ListNode* oldTail = tail;

    if (tail != nullptr) {
        tail->next = newNode;
        newNode->prev = tail;
    }

    tail = newNode;
    ++count;
    if (oldTail == nullptr) {
        head = tail;
    }
}

void List::Print() const noexcept {
    auto currNode = head;
    while (currNode != nullptr) {
        std::cout << "Node: " << currNode->data <<
                     " Curr: " << currNode <<
                     " Next: " << currNode->next <<
                     " Prev: " << currNode->prev <<
                     " Rand: " << currNode->rand << std::endl;
        currNode = currNode->next;
    }
}

void List::UpdateRandPointers() {
    auto currPointer = head;

    while (currPointer != nullptr) {
        int randIndex = GetRandomNumber(count);

        currPointer->rand = GetListNode(randIndex);
        currPointer = currPointer->next;
    }
}

List::ListNode* List::GetListNode(int nodeIndex) const noexcept
{
    if (count > 0) {
        if (nodeIndex == count) {
            return nullptr;
        }

        int index = 0;
        ListNode* node = head;
        while (index < nodeIndex) {
            node = node->next;
            index++;
        }
        return node;
    }

    return nullptr;
}

int List::GetRandomNumber(int max) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<> dist(0, max);

    return dist(gen);
}
