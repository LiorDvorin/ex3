/******************
Name: Lior Dvorin
ID: 215823469
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7
#define SUV  0
#define SEDAN  1
#define COUPE  2
#define GT  3
#define TOYOGA  0
#define HYUNNIGHT  1
#define MAZDUH  2
#define FOLKSVEGAN  3
#define KEYYUH  4

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};


void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

int salesCheck();
int dailyBrandSales();
double averageDelta();
void totalSales();
void bestBrand();
void bestType();
void bestSellingBrand();
void bestSellingType();
void mostProfitableDay();


int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    for (int i = 0; i < DAYS_IN_YEAR; i++)
        for (int j = 0; j < NUM_OF_BRANDS; j++)
            for (int k = 0; k < NUM_OF_TYPES; k++)
                cube[i][j][k] = -1;
    int day = 0;
    int brandCount[NUM_OF_BRANDS];

    //int days[NUM_OF_BRANDS] = {0};
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice) {
            case addOne: {
                int brandIndex, suvSales, sedanSales, coupeSales, gtSales;
                scanf("%d %d %d %d %d", &brandIndex, &suvSales, &sedanSales, &coupeSales, &gtSales);
                if(brandIndex >4 || brandIndex < 0) {
                    printf("This brand is not valid\n");
                    break;
                }
                cube[day+1][brandIndex][SUV] = suvSales;
                cube[day+1][brandIndex][SEDAN] = sedanSales;
                cube[day+1][brandIndex][COUPE] = coupeSales;
                cube[day+1][brandIndex][GT] = gtSales;

                break;
            }
            case addAll: {
                int countCheck = 0; //counter to see if all brands got data
                do {
                    printf("No data for brands");
                    for(int i = 0 ; i<NUM_OF_BRANDS; i++){
                        if(brandCount[i] == 0) {
                            printf(" %s", brands[i]);
                            /*if(i != NUM_OF_TYPES)
                                printf(",");*/
                        }
                    }
                    printf("\n");
                   // printf(".\n");
                    printf("Please complete the data\n");
                    int brandIndex, suvSales, sedanSales, coupeSales, gtSales;
                    scanf("%d %d %d %d %d", &brandIndex, &suvSales, &sedanSales, &coupeSales, &gtSales);
                    if(brandIndex > 4 || brandIndex < 0 || brandCount[brandIndex] > 0) {
                        printf("This brand is not valid\n");
                    }
                    else {
                        cube[day][brandIndex][SUV] = suvSales;
                        cube[day][brandIndex][SEDAN] = sedanSales;
                        cube[day][brandIndex][COUPE] = coupeSales;
                        cube[day][brandIndex][GT] = gtSales;
                        brandCount[brandIndex]++;
                        countCheck++;
                    }
                }while(countCheck != NUM_OF_BRANDS);
                for(int i = 0; i < NUM_OF_BRANDS; i++)
                    brandCount[i] = 0;
                day++;
                break;
            }
            case stats: {
                int n;
                do {
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &n);
                    if(n >= DAYS_IN_YEAR || n > day) {
                        printf("Please enter a valid day.\n");
                    }
                }while(n > DAYS_IN_YEAR || n > day);
                printf("In day number %d:\n", n);
                totalSales(cube, n-1);
                bestBrand(cube, n-1);
                bestType(cube, n-1);
                break;
            }
            case print: {
                printf("*****************************************\n\n");
                for(int i = 0 ; i < NUM_OF_BRANDS; i++) {
                    printf("Sales for %s:\n", brands[i]);
                    if(salesCheck(cube, i, day-1)) {
                        for(int j = 0; j < day; j++) {
                            printf("Day %d- ", j + 1);
                            for(int k = 0; k < NUM_OF_TYPES; k++) {
                                printf("%s: %d ", types[k], cube[j][i][k]);
                            }
                            printf("\n");
                        }
                    }
                }
                printf("\n\n*****************************************\n");
                break;
            }
            case insights: {
                bestSellingBrand(cube, day);
                bestSellingType(cube, day);
                mostProfitableDay(cube, day);
                break;
            }
            case deltas: {
                for(int i = 0 ; i < NUM_OF_BRANDS; i++) {
                    if(day == 1)
                        printf("Brand: %s, Average Delta: %f\n", brands[i], 0);
                    else
                        printf("Brand: %s, Average Delta: %f\n", brands[i], averageDelta(cube, i, day));
                }
                break;
            }
            default: {
                printf("Invalid input\n");
            }
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}
int salesCheck(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int day) {
    for(int i = 0; i < NUM_OF_TYPES; i++) {
        if(cube[day][brand][i] == -1)
            return 0;
    }
    return 1;
}
void totalSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    int sum = 0;
    for(int i = 0; i < NUM_OF_BRANDS; i++)
        for(int j = 0; j < NUM_OF_TYPES; j++)
            sum += cube[day][i][j];
    printf("The sales total was %d\n", sum);
}
void bestBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    int sales[NUM_OF_BRANDS] = {0};
    for(int i = 0; i < NUM_OF_BRANDS; i++)
        for(int j = 0; j < NUM_OF_TYPES; j++)
            sales[i] += cube[day][i][j];
    int bestBr = 0, bestSales = 0;
    for(int i = 0; i < NUM_OF_BRANDS; i++) {
        if(sales[i] > bestSales) {
            bestBr = i;
            bestSales = sales[i];
        }
    }
    printf("The best sold brand with %d sales was %s\n", bestSales, brands[bestBr]);
}
void bestType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    int sales[NUM_OF_TYPES] = {0};
    for(int i = 0; i < NUM_OF_TYPES; i++)
        for(int j = 0; j < NUM_OF_BRANDS; j++)
            sales[i] += cube[day][j][i];
    int bestTy = 0, bestSales = 0;
    for(int i = 0; i < NUM_OF_TYPES; i++) {
        if(sales[i] > bestSales) {
            bestTy = i;
            bestSales = sales[i];
        }
    }
    printf("The best sold type with %d sales was %s\n\n", bestSales, types[bestTy]);
}
void bestSellingBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay) {
    int brandSales[NUM_OF_BRANDS] = {0};
    for(int i = 0; i < currentDay; i++)
        for(int j = 0; j < NUM_OF_BRANDS; j++)
            for(int k = 0; k < NUM_OF_TYPES; k++)
                brandSales[j] += cube[i][j][k];
    int bestBr = 0, bestSales = 0;
    for(int i = 0; i < NUM_OF_BRANDS; i++) {
        if(brandSales[i] > bestSales) {
            bestBr = i;
            bestSales = brandSales[i];
        }
    }
    printf("The best-selling brand overall is %s: %d$\n", brands[bestBr], bestSales);
}
void bestSellingType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay) {
    int typeSales[NUM_OF_TYPES] = {0};
    for(int i = 0; i < currentDay; i++)
        for(int j = 0; j < NUM_OF_BRANDS; j++)
            for(int k = 0; k < NUM_OF_TYPES; k++)
                typeSales[k] += cube[i][j][k];
    int bestTy = 0, bestSales = 0;
    for(int i = 0; i < NUM_OF_TYPES; i++) {
        if(typeSales[i] > bestSales) {
            bestTy = i;
            bestSales = typeSales[i];
        }
    }
    printf("The best-selling type of car is %s: %d$\n", types[bestTy], bestSales);
}
void mostProfitableDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay) {
    int daySum[currentDay];
    for(int i = 0; i < currentDay; i++)
        daySum[i] = 0;
    for(int i = 0; i < currentDay; i++)
        for(int j = 0; j < NUM_OF_BRANDS; j++)
            for(int k = 0; k < NUM_OF_TYPES; k++)
                daySum[i] += cube[i][j][k];
    int bestDay = 0, bestSum = 0;
    for(int i = 0; i < currentDay; i++) {
        if(daySum[i] > bestSum) {
            bestDay = i;
            bestSum = daySum[i];
        }
    }
    printf("The most profitable day was day number %d: %d$\n", bestDay + 1, bestSum);
}
double averageDelta(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int day) {
    int change = 0;
    for(int j = 0; j < day - 1; j++) {
        change += dailyBrandSales(cube, brand, j+1) - dailyBrandSales(cube, brand, j);
    }
    return (double) change / (day-1);
}
int dailyBrandSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int day) {
    int brandSales = 0;
    for(int k = 0; k < NUM_OF_TYPES; k++)
        brandSales += cube[day][brand][k];
    return brandSales;
}

