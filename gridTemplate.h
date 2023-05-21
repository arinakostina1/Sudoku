/*

MIT License

Copyright (c) 21/02/2023 arinakostina-exe

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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

     //changes difficulty
     void changeDifficulty(int dif);

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
