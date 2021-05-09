#pragma once
struct StateElement
{
    StateElement* parent = nullptr;
    StateElement* children = nullptr;
    StateElement*   siblings = nullptr ;
    int number = 0;
};
