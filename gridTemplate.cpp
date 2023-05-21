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

#include "gridTemplate.h"

#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include <random>
using namespace std;
#define L 9

    void gridTemplate::checkedRefillCounter(){ 
       refillCounter++;
       if(refillCounter>100000)
           refillCounter = 0;
    }

    // Creates a full solved grid
    gridTemplate::gridTemplate(int dif){
        
        difficulty = dif;
        this->refillAll();
        
    };

    void gridTemplate::changeDifficulty(int dif){
        difficulty = dif;
    }

    // Creates an unsolved grid form a full grid
    void gridTemplate::refillUnsolvedGrid(){
        for(int k=0; k<L; k++){
            for(int i=0; i<L; i++){
                B[k][i] = A[k][i];
            }
        }
        for(int k=0; k<difficulty; k++){
            int i, j;
            do{
               srand(time(0)*refillCounter);
               i = rand()%9;
               j = rand()%9;
               refillCounter++;
            }while(B[i][j] == 0);
            B[i][j] = 0;
        }
    }

    // check the number in the rows and cols
    bool gridTemplate::check_value_rc(int a, int b, int value){
            
            if(A[a][b] == 0){
                for(int k=0; k<L; k++){
                   // with the cols
                    if((A[k][b] == value && k!=a)){
                        return false;
                    }
                    //with the rows
                    if((A[a][k] == value && k!=b)){
                        return false;
                    }       
                }
                return true;
            }
        return false;
    }

    // check the number in the square
    bool gridTemplate::check_value_sqr(int a, int b, int value){

       int start = a/3*3, startb = b/3*3;
       int finish = a/3*3+3, finishb = b/3*3+3;
       for(int k=start; k<finish; k++){
           for(int i=startb; i<finishb; i++){
               if(A[k][i] == value && (k!=a || i!=b))
                   return false;
           }
       }
       return true;
    }

    void gridTemplate::putRawValue(int i, int j, int value){
       B[i][j] = value;
    }

    // If the given value is the same as in the cell with the given coordinates in the solved grid then it places the value, else places -1
    void gridTemplate::putValue(int i, int j, int value){
       if(A[i][j] == value) 
           B[i][j] = value;
       else B[i][j] = -1;
    }
    
    // Returns a cell from the filled grid
    int gridTemplate::getCell(int i, int j){
       return B[i][j];
    }

    // Shuffle array
    void gridTemplate::shuffle_array(int arr[], int n, int k)
    {
        // Obtain a seed besed on time and the given k value (which will be different every time) to ensure the randomness
        unsigned seed = time(0)*k;
         // Shuffling our array
        shuffle(arr, arr + n, default_random_engine(seed));
    }

     void gridTemplate::fill_square(int ii, int jj, bool& validSquare){
         for(int k=0; k<L; k++){
            bool notFound = true;
            for(int i=ii; i<ii+3 && notFound; i++){
                for(int j=jj; j<jj+3 && notFound; j++){
                    if(check_value_rc(i, j, k+1)){
                        A[i][j] = k+1;
                        notFound = false;
                    }                       
                }
            }
            if(notFound)
                validSquare = false;
        }
    }

    void gridTemplate::printGrid(){
        for(int k=0; k<L; k++){
            for(int i=0; i<L; i++){
                cout<<A[k][i]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }

    void gridTemplate::printUnsolvedGrid(){
        for(int k=0; k<L; k++){
            for(int i=0; i<L; i++){
                cout<<B[k][i]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }

    void gridTemplate::refillGrid(){

        // Even if one square returns the bool validSquare as false the grid is invalid because it has zeros - unfilled cells
        bool validSquare;

        do{    
           
            validSquare = true;

            // delete all the previous values
            memset(A, 0, sizeof(A[0][0]) * L * L);
            int n[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

             // fill the 3 diagonal squares completely randomely
            for(int k=0; k<3; k++){
                shuffle_array(n, L, refillCounter);
                 for(int i=k*3; i<k*3+3; i++){
                    for(int j=k*3; j<k*3+3; j++){
                        A[i][j] = n[(i*3+j)%9];
                    }
                }
            }
            // fill the remaining squares
            fill_square(0, 3, validSquare);
            fill_square(0, 6, validSquare);
            fill_square(3, 6, validSquare);
            fill_square(3, 0, validSquare);
            fill_square(6, 0, validSquare);
            fill_square(6, 3, validSquare);

            refillCounter++;

        }while(!validSquare);

        checkedRefillCounter();

    }  

    void gridTemplate::refillAll(){
        this->refillGrid();
        this->refillUnsolvedGrid();
    }
