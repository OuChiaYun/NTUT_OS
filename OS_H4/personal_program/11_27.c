
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

#define DISKS 5000
#define REQUESTS 1000

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
int getHeadPos(int upperBound, int input)
{
    int head = INT_MIN;
    head = input;
    return head;
}

int getDistance(int start, int end)
{
    return abs(end - start);
}

void generateRequests(int *cylinders, int upperLimit, int num)
{
    srand(time(0));

    // printf("\n==================================================\n\n");
    // printf("ref :\n");
    for (int i = 0; i < num; i++)
    {
        cylinders[i] = rand() % upperLimit;

        // printf("%d ", cylinders[i]);
    }
    // printf("\n==================================================\n\n");
}

int FCFS(int cylinders[], int head)
{
    int distance = 0;

    // printf("%d ", (head));
    for (int i = 0; i < REQUESTS; i++)
    {
        distance += getDistance(cylinders[i], head);
        head = cylinders[i];

        // printf("%d ", (head));
    }
    // printf("\n| distance : %8d |\n", distance);
    return distance;
}

int SCAN(int cylinders[], int head)
{
    int distanceTraveled = 0;
    int leftSize = 0, rightSize = 0;
    int leftVals[REQUESTS], rightVals[REQUESTS]; // Declare arrays to store sorted values to the left and right of head
    for (int i = 0; i < REQUESTS; i++)
    {
        if (cylinders[i] > head)
            rightVals[rightSize++] = cylinders[i];
        else
            leftVals[leftSize++] = cylinders[i];
    }
    qsort(leftVals, leftSize, sizeof(*leftVals), cmpfunc);
    qsort(rightVals, rightSize, sizeof(*rightVals), cmpfunc);

    // printf("%d ", (head));
    for (int i = leftSize - 1; i >= 0; i--)
    {
        distanceTraveled += getDistance(leftVals[i], head);
        head = leftVals[i];

        // printf("%d ", (head));
    }

    if (leftSize != 0)

    {
        distanceTraveled += getDistance(0, head);
        head = 0;

        // printf("%d ", (head));
    }
    for (int i = 0; i < rightSize; i++)
    {
        // printf("%d ", (rightVals[i]));
        distanceTraveled += getDistance(rightVals[i], head);
        head = rightVals[i];

        // printf("%d ", (head));
    }
    // printf("\n| distance : %8d |\n", distanceTraveled);
    return distanceTraveled;
}

int CSCAN(int cylinders[], int head)
{
    int distanceTraveled = 0;
    int leftSize = 0, rightSize = 0;
    int leftVals[REQUESTS], rightVals[REQUESTS];
    for (int i = 0; i < REQUESTS; i++)
    {
        if (cylinders[i] >= head)
        {
            rightVals[rightSize++] = cylinders[i];
        }
        else
        {
            leftVals[leftSize++] = cylinders[i];
        }
    }

    qsort(leftVals, leftSize, sizeof(*leftVals), cmpfunc);
    qsort(rightVals, rightSize, sizeof(*rightVals), cmpfunc);

    // Move from head to the end of the right
    // printf("%d ", (head));
    for (int i = 0; i < rightSize; i++)
    {
        // printf("%d ", rightVals[i]);

        distanceTraveled += getDistance(rightVals[i], head);
        head = rightVals[i];
        // printf("%d ", (head));
    }

    // Move from end to start (0)
    if (leftSize > 0)
    {
        if (head != 4999)
        {
            distanceTraveled += getDistance(4999, head);
            head = 4999;
            // printf("%d ", head); // back to start position
        }
        distanceTraveled += getDistance(0, head);
        head = 0;
        // printf("%d ", head); // back to start position
    }

    for (int i = 0; i < leftSize; i++)
    {
        distanceTraveled += getDistance(leftVals[i], head);
        head = leftVals[i];

        // printf("%d ", (head));
    }

    // printf("\n| distance : %8d |\n", distanceTraveled);
    return distanceTraveled;
}

void printResults(int *cylinders, int head)
{

    // printf("| FCFS | \n");
    int fcfs = FCFS(cylinders, head);

    // printf("\n");

    // printf("| SCAN | \n");
    int scan = SCAN(cylinders, head);

    // printf("\n");

    // printf("| CSCAN | \n");
    int cscan = CSCAN(cylinders, head);

    // printf("\n");
    printf("\n_____________________________\n");
    printf("| Algorithm | Head Movement |\n");
    printf("|___________|_______________|\n");
    printf("| FCFS:     | % 13d |\n", fcfs);
    printf("| SCAN:     | % 13d |\n", scan);
    printf("| CSCAN:    | % 13d |\n", cscan);
    printf("|___________|_______________|\n");
}

int main(int argc, char *argv[])
{
    int input = 0;
    if (argc == 1)
    {
        printf("para error!\n");
        return 0;
    }
    else
    {
        input = atoi(argv[1]);

        if (!(0 < input && input < DISKS))
        {
            printf("\nEnter valid starting position for Head (in the range of 0 to %d): !", DISKS - 1);
            return 0;
        }
    }

    int cylinders[REQUESTS], head = getHeadPos(DISKS, input);
    generateRequests(cylinders, DISKS, REQUESTS);
    printResults(cylinders, head);

    printf("head : %d \n", input);
    return 0;
}
