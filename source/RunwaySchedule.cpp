#include "../include/RunwaySchedule.hpp"
#include "../include/defines.hpp"

RunwaySchedule::~RunwaySchedule()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

void RunwaySchedule::push_back(Aircraft aircraft, int landing_time)
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

void RunwaySchedule::print() const
{
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << "Aircraft " << current->aircraft.plane_index
                  << " landed at " << current->landing_time << std::endl;
        current = current->next;
    }
}

size_t RunwaySchedule::getSize() const
{
    return size;
}

Node *RunwaySchedule::getHead() const
{
    return head;
}

Node *RunwaySchedule::getTail() const
{
    return tail;
}