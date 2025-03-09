#include "../include/Runway_Schedule.hpp"
#include "../include/defines.hpp"

Runway_Schedule::~Runway_Schedule()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

void Runway_Schedule::push_back(Aircraft aircraft, int landing_time)
{
    Node *newNode = new Node(aircraft, landing_time);

    if (tail == nullptr)
        head = tail = newNode;

    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    
    size++;
}

void Runway_Schedule::print() const
{
    Node *current = head;
    while (current != nullptr)
    {
        cout << "Aircraft " << current->aircraft.plane_index
                  << " landed at " << endl;
        current = current->next;
    }
}

size_t Runway_Schedule::getSize() const
{
    return size;
}

Node *Runway_Schedule::getHead() const
{
    return head;
}

Node *Runway_Schedule::getTail() const
{
    return tail;
}

void Runway_Schedule::remove(Node *node)
{
    if (node == nullptr)
        return;

    if (node == head)
        head = node->next;

    if (node == tail)
        tail = node->prev;

    if (node->prev != nullptr)
        node->prev->next = node->next;

    if (node->next != nullptr)
        node->next->prev = node->prev;

    delete node;
    size--;
}

void Runway_Schedule::insert(Node *node, Aircraft aircraft, int landing_time)
{
    Node *newNode = new Node(aircraft, landing_time);

    if (node == nullptr){
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    if (node == head)
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else
    {
        newNode->next = node;
        newNode->prev = node->prev;
        node->prev->next = newNode;
        node->prev = newNode;
    }

    size++;
}