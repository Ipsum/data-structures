/*-----DblLinkedList.h-----
by: David Tyler
    16.322 Data Structures
    ECE Dept.
    UMASS Lowell

PURPOSE
This file contains the DblLinkedList class definition

CHANGES
10-09-13 --- Passed in for homework 2 credit
*/

#include "Point.h"

//Make a type for a node's data item
typedef Point NodeData;

//----- c l a s s    D b l L i n k e d L i s t -----//

class DblLinkedList
{
private:
    // List node class definition
    struct Node
    {
        NodeData data; // The contents of the node
        Node *pred; // Link to predecessor node
        Node *succ; // Link to successor node
        // Node Constructors
        Node() {}
        Node(const NodeData &theData, Node *const prd = 0, Node *const suc= 0) :
        data(theData), pred(prd), succ(suc) {}
    };
public:
    // Constructor
    DblLinkedList();
    // True if list is empty
    bool Empty() const;
    // True if current position is beyond last item.
    bool AtEnd() const;
    // Rewind the current item to the beginning of the list.
    void Rewind() { current = first; }
    // Advance to the next item in the list
    void Forward();
    // Move back to the previous entry
    void Backward();
    // Get the contents of the current list item.
    NodeData CurrentItem() const;
    // Get the contents of the first list item.
    NodeData FirstItem() const;
    // Get the contents of the last list item.
    NodeData LastItem() const;
    // Insert a new list item before the current item.
    void InsertItem(const NodeData &d);
    // Delete the current item.
    // The new current item was the successor of the deleted item.
    void DeleteItem();
private:
    Node *first; // Points to first node in list
    Node *last; // Points to last node in list
    Node *current; // Points to current node in list
};