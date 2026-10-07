#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int id;
    float value;
    float weight;
    float ratio;
    float fraction;
} Package;

void enterDetails(Package p[], int *n, float *capacity, int *hasDetails);
void displayDetails(Package p[], int n);
void calculateRatio(Package p[], int n, int *hasRatios);
void sortPackages(Package p[], int n, int *isSorted);
void findMaxValue(Package p[], int n, float capacity,
                  float *maxValue, float *totalWeightUsed,
                  int *isCalculated);
void displaySelected(Package p[], int n,
                     float maxValue, float totalWeightUsed);

int compareRatio(const void *a, const void *b) {
    Package *p1 = (Package *)a;
    Package *p2 = (Package *)b;

    if (p1->ratio < p2->ratio)
        return 1;
    else if (p1->ratio > p2->ratio)
        return -1;

    return 0;
}

int main() {
    Package p[MAX];

    int n = 0;
    int choice;

    float capacity = 0.0;
    float maxValue = 0.0;
    float totalWeightUsed = 0.0;

    int hasDetails = 0;
    int hasRatios = 0;
    int isSorted = 0;
    int isCalculated = 0;

    do {
        printf("\nSmart Delivery Planning\n");
        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                enterDetails(p, &n, &capacity, &hasDetails);

                hasRatios = 0;
                isSorted = 0;
                isCalculated = 0;
                break;

            case 2:
                if (hasDetails)
                    displayDetails(p, n);
                else
                    printf("\nPlease enter package details first.\n");
                break;

            case 3:
                if (hasDetails)
                    calculateRatio(p, n, &hasRatios);
                else
                    printf("\nPlease enter package details first.\n");
                break;

            case 4:
                if (hasRatios)
                    sortPackages(p, n, &isSorted);
                else
                    printf("\nPlease calculate the ratios first.\n");
                break;

            case 5:
                if (isSorted) {
                    findMaxValue(
                        p,
                        n,
                        capacity,
                        &maxValue,
                        &totalWeightUsed,
                        &isCalculated
                    );
                } else {
                    printf("\nPlease sort the packages first.\n");
                }
                break;

            case 6:
                if (isCalculated) {
                    displaySelected(
                        p,
                        n,
                        maxValue,
                        totalWeightUsed
                    );
                } else {
                    printf("\nPlease calculate the maximum value first.\n");
                }
                break;

            case 7:
                printf("\nExiting Smart Delivery Planning...\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}

void enterDetails(Package p[], int *n,
                  float *capacity, int *hasDetails) {

    printf("\nEnter number of packages: ");
    scanf("%d", n);

    printf("Enter maximum vehicle capacity: ");
    scanf("%f", capacity);

    for (int i = 0; i < *n; i++) {

        p[i].id = i + 1;

        printf("\nPackage %d\n", p[i].id);

        printf("Enter value: ");
        scanf("%f", &p[i].value);

        printf("Enter weight: ");
        scanf("%f", &p[i].weight);

        p[i].ratio = 0.0;
        p[i].fraction = 0.0;
    }

    *hasDetails = 1;

    printf("\nPackage details entered successfully.\n");
}

void displayDetails(Package p[], int n) {

    printf("\n%-8s %-12s %-12s %-12s\n",
           "ID", "Value", "Weight", "Ratio");

    for (int i = 0; i < n; i++) {

        printf("%-8d %-12.2f %-12.2f %-12.2f\n",
               p[i].id,
               p[i].value,
               p[i].weight,
               p[i].ratio);
    }
}

void calculateRatio(Package p[], int n, int *hasRatios) {

    for (int i = 0; i < n; i++) {
        p[i].ratio = p[i].value / p[i].weight;
    }

    *hasRatios = 1;

    printf("\nValue/Weight ratios calculated successfully.\n");
}

void sortPackages(Package p[], int n, int *isSorted) {

    qsort(p, n, sizeof(Package), compareRatio);

    *isSorted = 1;

    printf("\nPackages sorted by decreasing value/weight ratio.\n");
}

void findMaxValue(Package p[], int n,
                  float capacity,
                  float *maxValue,
                  float *totalWeightUsed,
                  int *isCalculated) {

    float remainingCapacity = capacity;

    *maxValue = 0.0;
    *totalWeightUsed = 0.0;

    for (int i = 0; i < n; i++) {

        p[i].fraction = 0.0;

        if (remainingCapacity <= 0)
            break;

        if (p[i].weight <= remainingCapacity) {

            p[i].fraction = 1.0;

            *maxValue += p[i].value;

            remainingCapacity -= p[i].weight;

            *totalWeightUsed += p[i].weight;
        }
        else {

            p[i].fraction =
                remainingCapacity / p[i].weight;

            *maxValue +=
                p[i].value * p[i].fraction;

            *totalWeightUsed += remainingCapacity;

            remainingCapacity = 0;
        }
    }

    *isCalculated = 1;

    printf("\nMaximum value calculated successfully.\n");
}

void displaySelected(Package p[], int n,
                     float maxValue,
                     float totalWeightUsed) {

    printf("\nSelected Packages\n");

    printf("%-8s %-12s %-12s %-12s %-15s\n",
           "ID",
           "Value",
           "Weight",
           "Ratio",
           "Fraction Taken");

    for (int i = 0; i < n; i++) {

        if (p[i].fraction > 0) {

            printf("%-8d %-12.2f %-12.2f %-12.2f %-15.2f\n",
                   p[i].id,
                   p[i].value,
                   p[i].weight,
                   p[i].ratio,
                   p[i].fraction);
        }
    }

    printf("\nTotal Weight Used: %.2f\n", totalWeightUsed);
    printf("Maximum Value Obtained: %.2f\n", maxValue);
}
