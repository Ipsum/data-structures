/*-----DblLinkedList.cpp-----
by: David Tyler
    16.322 Data Structures
    ECE Dept.
    UMASS Lowell

PURPOSE
This file contains functions related to the DblLinkedList class

CHANGES
10-09-13 --- Passed in for homework 2 credit
*/

#include <cassert>
#include "DblLinkedList.h"

//Default Constructor
DblLinkedList::DblLinkedList()
{
    first = 0;
    last = 0;
    current = 0;
}
/*-----Empty()-----
PURPOSE
Check if list is empty

RETURN
true if empty, false otherwise */
bool DblLinkedList::Empty() const
{
    return first==0;
}
/*-----AtEnd()-----
PURPOSE
Check if list is past the end

RETURN
true if past end, false otherwise */
bool DblLinkedList::AtEnd() const
{
    return (!current);
}
/*-----Forward()-----
PURPOSE
Advance list one step */
void DblLinkedList::Forward()
{
    assert(!AtEnd() && !Empty());

    current=current->succ;
}
/*-----Backward()-----
PURPOSE
Step backwards one element in list */
void DblLinkedList::Backward()
{
    assert(!Empty());

    current=current->pred;
}
/*-----CurrentItem()-----
PURPOSE
Returns point data of current node
RETURN
NodeData - the x,y coords in current node
            as type Point                */
NodeData DblLinkedList::CurrentItem() const
{
    assert(current);

    return current->data;
}
/*-----FirstItem()-----
PURPOSE
Returns point data of first node
RETURN
NodeData - the x,y coords in first node
            as type Point                */
NodeData DblLinkedList::FirstItem() const
{
    assert(first);

    return first->data;
}
/*-----LastItem()-----
PURPOSE
Returns point data of last node
RETURN
NodeData - the x,y coords in lastnode
            as type Point                */
NodeData DblLinkedList::LastItem() const
{
    assert(last);

    return last->data;
}
/*-----InsertItem()-----
PURPOSE
Inserts a new node into list at current node
INPUT
d - The data to be put in the new node      */
void DblLinkedList::InsertItem(const NodeData &d)
{
    Node *newNode;
    //Insert into empty
    if(Empty())
    {
        newNode = new(nothrow) Node(d);
        assert(newNode != 0);
        first=newNode;
        last=newNode;
        return;
    }
    //Insert at end
    if(AtEnd())
    {
        newNode = new(nothrow) Node(d,last);
        assert(newNode != 0);
        last->succ=newNode;
        last=newNode;
        return;
    }
    //Insert at beginning
    if(current==first)
    {
        newNode = new(nothrow) Node(d,0,first);
        assert(newNode != 0);
        current->pred = newNode;
        first = newNode;
        return;
    }

    //Insert into middle of list
    newNode = new(nothrow) Node(d,current->pred,current);
    assert(newNode != 0);
    newNode->pred->succ = newNode;
    current->pred = newNode;
}
/*-----InsertItem()-----
PURPOSE
Removes current node from list   */
void DblLinkedList::DeleteItem()
{
    assert(current);
    //Delete only node
    if(first==last)
    {
        delete current;
        first=0;
        last=0;
        current=0;
        return;
    }
    //Delete first node
    if(current==first)
    {
        first = current->succ;
        first->pred = 0;
        delete current;
        current = first;
        return;
    }
    //Delete last node
    if(current==last)
    {
        current->pred->succ=0;
        last=current->pred;
        delete current;
        current=0;
        return;
    }
    
    //General case
    Node *newCurrent;
    current->pred->succ = current->succ;
    current->succ->pred = current->pred;
    newCurrent = current->succ;
    delete current;
    current = newCurrent;
}