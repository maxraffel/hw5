#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    vector<size_t>& shiftsScheduled,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    size_t worker,
    size_t shifts
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    vector<size_t> shiftsScheduled(avail[0].size(), 0);
    return scheduleHelper(avail, shiftsScheduled, dailyNeed, maxShifts, sched, 0, 0, 0);

}



bool scheduleHelper(
    const AvailabilityMatrix& avail,
    vector<size_t>& shiftsScheduled,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    size_t worker,
    size_t shifts
)
{
    if (day == avail.size()){ // we did it!!!
        return true;
    }
    if (day >= sched.size()){
        sched.push_back(vector<Worker_T>());
    }
    if (worker >= avail[day].size()){
        if (shifts == dailyNeed){
            return scheduleHelper(avail, shiftsScheduled, dailyNeed, maxShifts, sched, day + 1, 0, 0);
        } else {
            return false;
        }
    }
    if (avail[day][worker] == false || shiftsScheduled[worker] >= maxShifts) {
        return scheduleHelper(avail, shiftsScheduled, dailyNeed, maxShifts, sched, day, worker + 1, shifts);
    } else {
        sched[day].push_back(worker);
        shiftsScheduled[worker]++;
        if (scheduleHelper(avail, shiftsScheduled, dailyNeed, maxShifts, sched, day, worker + 1, shifts + 1)) {
            return true;
        } else {
            sched[day].pop_back();
            shiftsScheduled[worker]--;
            return scheduleHelper(avail, shiftsScheduled, dailyNeed, maxShifts, sched, day, worker + 1, shifts);
        }
    }
}
