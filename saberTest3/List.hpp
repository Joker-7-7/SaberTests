#ifndef LIST_HPP
#define LIST_HPP

#include <string>

/**
 * Data structure - List
 *
 * <p>
 * Consisting of elements containing,
 * in addition to their own data, links to
 * the next and / or previous element of the list
 * <p>
 *
 * Using example:
 * @code
 * std::unique_ptr<List> list = std::make_unique<List>();
 * list->PushBack("Second element");
 * list->PushFrond("First element");
 * @endcode
 *
 * @author Joker-7-7
 */
class List
{
public:
    /**
     * Elementary list node
     */
    struct ListNode
    {
        ListNode* prev;
        ListNode* next;
        ListNode* rand;
        std::string data;
    };

    /**
     * Constructs list
     */
    List();

    /**
     * Destructs list
     */
    ~List();

    /**
     * Serializing a list into a binary file
     *
     * @param file writable file
     * @attention  file open with <code>fopen(path, "wb")</code>
     */
    void Serialize(FILE* file) const;

    /**
     * Deserialization of a binary file into a list
     *
     * @param file read file
     * @attention  file open with <code>fopen(path, "rb")</code>
     */
    void Deserialize(FILE* file);

    /**
     * Pushing a new element at front
     *
     * @param newData data
     */
    void PushFront(std::string newData) noexcept;

    /**
     * Pushing a new element at back
     *
     * @param newData data
     */
    void PushBack(std::string newData) noexcept;

    /**
     * Print list
     */
    void Print() const noexcept;

    /**
     * Update random pointer for all list nodes
     */
    void UpdateRandPointers();

private:
    /**
     * Pointer to the beginning of the list
     *
     * @see #ListNode
     */
    ListNode* head;

    /**
     * Pointer to end of list
     *
     * @see #ListNode
     */
    ListNode* tail;

    /**
     * Number of nodes
     */
    int count;

    /**
     * Get list node by index
     *
     * @param nodeIndex index
     * @return          node pointer
     */
    [[nodiscard]] ListNode* GetListNode(int nodeIndex) const noexcept;

    /**
     * Get random number
     *
     * @param max upper generation limit
     * @return    random number
     */
    static int GetRandomNumber(int max);
};

#endif
