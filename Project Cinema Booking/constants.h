#ifndef CONSTANTS_H
#define CONSTANTS_H

//Modify and/or uncomment the commented constants to have less success rate. The default success rate is 100%.


#define N_seat 10   // Number of seats per row
#define N_zoneA 10  // Number of rows in Zone A
#define N_zoneB 20  // Number of rows in Zone B
// #define N_seat 5        // Reduced seats per row for higher chance of failure
// #define N_zoneA 2       // Reduced number of rows in Zone A
// #define N_zoneB 3       // Reduced number of rows in Zone B
#define P_a 30  // Probability percentage for Zone A
#define C_zoneA 30 // Cost per seat in Zone A
#define C_zoneB 20 // Cost per seat in Zone B
#define N_low 1 // Minimum number of tickets a customer can request
// #define N_high 3        // Reduced maximum number of tickets for higher chance of failure
#define N_high 5 // Maximum number of tickets a customer can request
#define t_low 1 // Minimum time for serving a customer (in seconds)
// #define t_high 3        // Reduced maximum service time for higher chance of failure
#define t_high 5 // Maximum time for serving a customer (in seconds)

#endif // CONSTANTS_H
