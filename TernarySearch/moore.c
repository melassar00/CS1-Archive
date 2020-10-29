/*  Muhamad Elassar
    CS1 Assignment 2: Moore Time
    9/30/2019                   
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EPS 1e-9
#define TRUE (1<2)
#define FALSE (!TRUE)

// gets the lowest total amount of years to wait
double getLowestTotal(int numStudents, double scalingFactor);

// this is the Mordon equation plus the number of years waited
double mordonize(int numStudents, double scalingFactor, double numYearsWaited);

// finds the best amount of years it would take to grade, so that the total years is the lowest
double findBestNumYears(int numStudents, double scalingFactor);

// ternary search function, taken from frame_while problem in notes
double ternarySearch(int numStudents, double scalingFactor, double low, double high);

// function that checks if two values are equal; taken from frame problem notes
int eq(double a, double b);

int main(){
    // take in how many cases
    int t;
    scanf("%d", &t);

    // k = number of students, H = scaling factor
    double k, H;

    // loop through to take in input for t cases, print lowest amount of years to wait
    int i;
    for(i=0; i<t; i++){
        scanf("%lf %lf", &k, &H);
        printf("%.6lf\n", getLowestTotal(k, H));
    }

    return 0;
    
}

double getLowestTotal(int numStudents, double scalingFactor){
    double totalYears;
    
    // we know that if the scale factor is less than or equal to 1, the best amount of years to wait is 0
    if(scalingFactor <= 1){
        totalYears = mordonize(numStudents, scalingFactor, 0);
        return totalYears;
    }

    // if there are no students to grade, then there are no years to wait
    if(numStudents == 0){
        totalYears = 0;
        return totalYears;
    }

    // search through all the possible values for the lowest amount of years to wait
    totalYears = findBestNumYears(numStudents, scalingFactor);

    return totalYears;
    
}


double findBestNumYears(int numStudents, double scalingFactor){
    //start at high point before dip
    double candidateTotalYears = mordonize(numStudents, scalingFactor, 0); 
    double hi = 1, lo = 0;

    // initialize a starting high bound by getting close to where the plot stops decreasing and begins to increase
    while(candidateTotalYears >= mordonize(numStudents, scalingFactor, hi)){
        candidateTotalYears = mordonize(numStudents, scalingFactor, hi);

        //shift bound to the right by increasing it by a factor of 25% after every iteration
        hi = hi * 1.25; 
    }

    // make low bound iteration before it started increasing
    lo = hi/1.5;
    
    // perform ternary search between bounds
    double totalYears = ternarySearch(numStudents, scalingFactor, lo, hi);
    return totalYears;
}

double ternarySearch(int numStudents, double scalingFactor, double low, double high){
    while(!eq(low, high)){
        // compute mid points by splitting it into thirds
        double m1 = (2 * low + high) / 3;
        double m2 = (low + 2 * high) / 3;
        
        // compute total amount of years using the mid points
        double totalYears1 = mordonize(numStudents, scalingFactor, m1);
        double totalYears2 = mordonize(numStudents, scalingFactor, m2);

        // check if totalYears1 is worse than totalYears2
        if(totalYears1 > totalYears2){
            // move up lower bound to the first midpoint
            low = m1;
        }
        else{
            // move down high bound to the second mid point
            high = m2;
        }
    }
    
    // once found the best number of years, stick the average of the bounds in Mordon function 
    double years = mordonize(numStudents, scalingFactor, (low+high)/2);
    return years;
}

double mordonize(int numStudents, double scalingFactor, double numYears){
    return (numStudents / (pow(scalingFactor, sqrt(numYears))) + numYears);
}

int eq(double a, double b){
    // Get the difference   
    double diff = a - b;    
    if (diff < 0)        
        diff = -diff; // absolute value of the difference    
    if (diff < EPS)        
        return TRUE; // ABSOLUTE ERROR CHECK PASSED    
    if (a < 0)        
        a = -a; // abs    
    if (b < 0)        
        b = -b; // abs    
    if (a < b)        
        a = b; // max    
    // Scale the error by the magnitude of the big value    
    // This will give a new relative error to check against    
    if (a * EPS > diff)        
        return TRUE; // RELATIVE ERROR CHECK PASSED  

    return FALSE; // Not equal values
}
