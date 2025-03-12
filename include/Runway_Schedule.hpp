#ifndef RUNWAY_SCHEDULE_HPP
#define RUNWAY_SCHEDULE_HPP

#include "Aircraft_Struct.hpp"
#include "defines.hpp"

struct Node
{
    Aircraft aircraft;
    Node *prev;
    Node *next;
    int landing_time;

    Node(Aircraft a, int time) : aircraft(a), prev(nullptr), next(nullptr), landing_time(time) {}
    ~Node() {}
};

class Runway_Schedule
{
public:
    Runway_Schedule() : head(nullptr), tail(nullptr), size(0) {}
    ~Runway_Schedule();

    void push_back(Aircraft aircraft, int landing_time);
    void insert(Node *node, Aircraft aircraft, int landing_time);
    void insert(size_t pos, Aircraft aircraft, int landing_time);
    void remove(Node *node);
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