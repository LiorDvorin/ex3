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
    //array that counts each brand's data received
    int brandCount[NUM_OF_BRANDS];

    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice) {
            case addOne: {
                int brandIndex, suvSales, sedanSales, coupeSales, gtSales;
                scanf("%d %d %d %d %d", &brandIndex, &suvSales, &sedanSales, &coupeSales, &gtSales);
                if(brandIndex > 4|| brandIndex < 0) {
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
                    //loop to print which brands are missing data
                    for(int i = 0 ; i<NUM_OF_BRANDS; i++){
                        if(brandCount[i] == 0) {
                            printf(" %s", brands[i]);
                        }
                    }
                    printf("\n");
                    printf("Please complete the data\n");
                    int brandIndex, suvSales, sedanSales, coupeSales, gtSales;
                    scanf("%d %d %d %d %d", &brandIndex, &suvSales, &sedanSales, &coupeSales, &gtSales);
                    // if to check if the brand number received can accept data
                    if(brandIndex > NUM_OF_BRANDS-1 || brandIndex < 0 || brandCount[brandIndex] > 0) {
                        printf("This brand is not valid\n");
                    }
                    else {
                        //setting the data in the right place
                        cube[day][brandIndex][SUV] = suvSales;
                        cube[day][brandIndex][SEDAN] = sedanSales;
                        cube[day][brandIndex][COUPE] = coupeSales;
                        cube[day][brandIndex][GT] = gtSales;
                        brandCount[brandIndex]++;
                        countCheck++;
                    }
                }while(countCheck != NUM_OF_BRANDS);
                //set all the counts back to 0 so i can check it in the next day
                for(int i = 0; i < NUM_OF_BRANDS; i++)
                    brandCount[i] = 0;
                //up the day count
                day++;
                break;
            }
            case stats: {
                int n;
                do {
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &n);
                    //check if the day is valid and didnt pass the current program's day
                    if(n >= DAYS_IN_YEAR || n > day || n == 0) {
                        printf("Please enter a valid day.\n");
                    }
                }while(n > DAYS_IN_YEAR || n > day|| n == 0);
                printf("In day number %d:\n", n);
                //call to various functions
                totalSales(cube, n-1, NUM_OF_BRANDS, NUM_OF_TYPES); //prints the sum of all sales in a day
                bestBrand(cube, n-1, NUM_OF_BRANDS, NUM_OF_TYPES); //prints the brand that sold the most in a day
                bestType(cube, n-1, NUM_OF_BRANDS, NUM_OF_TYPES); //prints the type that sold the most in a day
                break;
            }
            case print: {
                //prints the data cube
                printf("*****************************************\n\n");
                for(int i = 0 ; i < NUM_OF_BRANDS; i++) {
                    printf("Sales for %s:\n", brands[i]);
                    //checks if the value of a sale is equal to -1 (the default). if not then the program prints the data
                    if(salesCheck(cube, i, day-1, NUM_OF_TYPES)) {
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
                bestSellingBrand(cube, day, NUM_OF_BRANDS, NUM_OF_TYPES); //prints the best selling brand overall
                bestSellingType(cube, day, NUM_OF_BRANDS, NUM_OF_TYPES); //prints the best selling type overall
                mostProfitableDay(cube, day, NUM_OF_BRANDS, NUM_OF_TYPES); //prints the most profitable day overall
                break;
            }
            case deltas: {
                for(int i = 0 ; i < NUM_OF_BRANDS; i++) {
                    // checks how many days passed. if one then there is no average delta. else, it prints each brands average delta up until current day
                    if(day == 1)
                        printf("Brand: %s, Average Delta: %f\n", brands[i], (double)0);
                    else
                        //prints the average delta of each brand using the averageDelta function
                        printf("Brand: %s, Average Delta: %f\n", brands[i], averageDelta(cube, i, day, NUM_OF_TYPES));

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
int salesCheck(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int day, int numOfTypes) {
    //checks if the value of a sale is equal to -1 (the default). if it is, return 0, else 1
    for(int i = 0; i < numOfTypes; i++) {
        if(cube[day][brand][i] == -1)
            return 0;
    }
    return 1;
}
void totalSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int numOfBrands, int numOfTypes) {
    //sums up all sales of all brands in a specific day
    int sum = 0;
    for(int i = 0; i < numOfBrands; i++)
        for(int j = 0; j < numOfTypes; j++)
            sum += cube[day][i][j];
    printf("The sales total was %d\n", sum);
}
void bestBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int numOfBrands, int numOfTypes) {
    //creates an array of sales for each brand in a specific day and then checks which one sold the most and prints it's sales and brand
    int sales[numOfBrands];
    for(int i = 0 ; i < numOfBrands; i++)
        sales[i] = 0;
    for(int i = 0; i < numOfBrands; i++)
        for(int j = 0; j < numOfTypes; j++)
            sales[i] += cube[day][i][j];
    int bestBr = 0, bestSales = 0;
    for(int i = 0; i < numOfBrands; i++) {
        if(sales[i] > bestSales) {
            bestBr = i;
            bestSales = sales[i];
        }
    }
    printf("The best sold brand with %d sales was %s\n", bestSales, brands[bestBr]);
}
void bestType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int numOfBrands, int numOfTypes) {
    //creates an array of sales for each type of car in a specific day and then checks which one sold the most and prints it's sales and type
    int sales[numOfTypes];
    for(int i = 0 ; i < numOfTypes; i++)
        sales[i] = 0;
    for(int i = 0; i < numOfTypes; i++)
        for(int j = 0; j < numOfBrands; j++)
            sales[i] += cube[day][j][i];
    int bestTy = 0, bestSales = 0;
    for(int i = 0; i < numOfTypes; i++) {
        if(sales[i] > bestSales) {
            bestTy = i;
            bestSales = sales[i];
        }
    }
    printf("The best sold type with %d sales was %s\n\n", bestSales, types[bestTy]);
}
void bestSellingBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay,
int numOfBrands, int numOfTypes) {
    //creates an array of sales for each brand and then checks which one sold the most overall and prints it's brand and sales

    int brandSales[numOfBrands];
    for(int i = 0; i < numOfBrands; i++)
        brandSales[i] = 0;
    for(int i = 0; i < currentDay; i++)
        for(int j = 0; j < numOfBrands; j++)
            for(int k = 0; k < numOfTypes; k++)
                brandSales[j] += cube[i][j][k];
    int bestBr = 0, bestSales = 0;
    for(int i = 0; i < numOfBrands; i++) {
        if(brandSales[i] > bestSales) {
            bestBr = i;
            bestSales = brandSales[i];
        }
    }
    printf("The best-selling brand overall is %s: %d$\n", brands[bestBr], bestSales);
}
void bestSellingType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay,
int numOfBrands, int numOfTypes) {
    //creates an array of sales for each type of car and then checks which one sold the most overall and prints it's type and sales

    int typeSales[numOfTypes];
    for (int i = 0; i < numOfTypes; i++)
        typeSales[i] = 0;
    for(int i = 0; i < currentDay; i++)
        for(int j = 0; j < numOfBrands; j++)
            for(int k = 0; k < numOfTypes; k++)
                typeSales[k] += cube[i][j][k];
    int bestTy = 0, bestSales = 0;
    for(int i = 0; i < numOfTypes; i++) {
        if(typeSales[i] > bestSales) {
            bestTy = i;
            bestSales = typeSales[i];
        }
    }
    printf("The best-selling type of car is %s: %d$\n", types[bestTy], bestSales);
}
void mostProfitableDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay,
int numOfBrands, int numOfTypes) {
    //creates an array of sales for each day up until the current day and checks which one is the most profitable and prints the day number and the sum of the sales
    int daySum[currentDay];
    for(int i = 0; i < currentDay; i++)
        daySum[i] = 0;
    for(int i = 0; i < currentDay; i++)
        for(int j = 0; j < numOfBrands; j++)
            for(int k = 0; k < numOfTypes; k++)
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
double averageDelta(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int day, int numOfTypes) {
    //calculates the total change in the brand's sales up until current day and then return the average delta
    int change = 0;
    for(int j = 0; j < day - 1; j++) {
        change += dailyBrandSales(cube, brand, j+1, numOfTypes) - dailyBrandSales(cube, brand, j, numOfTypes);
    }
    return (double) change / (day-1);
}
int dailyBrandSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int day, int numOfTypes) {
    //return the sum of the specific brand's sales in a specific day
    int brandSales = 0;
    for(int k = 0; k < numOfTypes; k++)
        brandSales += cube[day][brand][k];
    return brandSales;
}

