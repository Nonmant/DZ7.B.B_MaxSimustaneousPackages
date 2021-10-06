//https://contest.yandex.ru/contest/29396/problems/

#include "funcs.h"
#include <bits/stdc++.h>

enum Event : short int{
    Arrive = 1,
    Processed = 0
};

void parseInput(std::istream & input,
                 std::vector<std::pair<int,Event>> & events){
    int n;
    input>>n;
    events.reserve(2*n);
    int arrive,len;
    for(int i = 0; i<n; ++i){
        input>>arrive>>len;
        if(len > 0){
            events.emplace_back(arrive + len,Processed);
            events.emplace_back(arrive,Arrive);
        }
    }
}

void parseFile(std::istream & input, std::ostream & output){
    std::vector<std::pair<int,Event>> events;
    parseInput(input,events);

    std::sort(events.begin(), events.end());

    int curNumberOfPackages = 0, maxNumberOfPackages = 0;
    for(const auto & event:events){
        curNumberOfPackages += event.second == Arrive ? 1 : -1;
        if(curNumberOfPackages>maxNumberOfPackages)
            maxNumberOfPackages = curNumberOfPackages;
    }
    output<<maxNumberOfPackages<<std::endl;
}
