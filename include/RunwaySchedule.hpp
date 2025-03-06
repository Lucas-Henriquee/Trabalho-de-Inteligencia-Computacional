#ifndef RUNWAY_SCHEDULE_HPP
#define RUNWAY_SCHEDULE_HPP

#include "Aircraft_Struct.hpp"
#include "defines.hpp"

struct Node
{
    Aircraft aircraft;
    int landing_time;
    Node *prev;
    Node *next;

    Node(Aircraft a, int time) : aircraft(a), landing_time(time), prev(nullptr), next(nullptr) {}
};

class RunwaySchedule
{
public:
    RunwaySchedule() : head(nullptr), tail(nullptr), size(0) {}
    ~RunwaySchedule();

    void push_back(Aircraft aircraft, int landing_time);
    void print() const;
    
    size_t getSize() const;
    Node *getHead() const;
    Node *getTail() const;

private:
    Node *head;
    Node *tail;
    size_t size;
};

#endif // RUNWAY_SCHEDULE_HPP