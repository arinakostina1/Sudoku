#pragma once

#define L 9

class gridTemplate{

    private:

     int A[L][L]; // filled grid
     int B[L][L]; // not filled - unsolved grid
     int difficulty;

     // refillCounter ensures that every grid is filled differentely and randomely
     // It is used in the shuffle method because the suffling based only on time 
     // isn't enough, because it doesn't change frequently enough
     int refillCounter;

     void checkedRefillCounter();

    public:

     // Creates a full solved grid
     gridTemplate(int dif);

    private:

     // Creates an unsolved grid form a full grid
     void refillUnsolvedGrid();


    public:

     // check the number in the rows and cols
     bool check_value_rc(int a, int b, int value);

     // check the number in the square
     bool check_value_sqr(int a, int b, int value);

     void putRawValue(int i, int j, int value);

     // If the given value is the same as in the cell with the given coordinates then it places the value, else places -1
     void putValue(int i, int j, int value);
     
     // Returns a cell from unsolved grid
     int getCell(int i, int j);


    private:

     // Shuffle array
     void shuffle_array(int arr[], int n, int k);
 
     void fill_square(int ii, int jj, bool& validSquare);


    public:

     void printGrid();

     void printUnsolvedGrid();

     void refillGrid();

     void refillAll();
};
