// Has the  ----FULL CLASS----  random working grid generator !!
#include <iostream>
#include <fstream>
#include <cstring>
#include <bits/stdc++.h>
#include <random>
using namespace std;
#define L 9

class gridTemplate{

    private:

     int A[L][L]; // filled grid
     int B[L][L]; // not filled - unsolved grid
     int difficulty;

     // refillCounter ensures that every grid is filled differentely and randomely
     int refillCounter;

     void checkedRefillCounter(){
        refillCounter++;
        if(refillCounter>100000)
            refillCounter = 0;
     }

    public:

     // creates a full solved grid
     gridTemplate(int dif){
         
         difficulty = dif;
         this->refillAll();

     };

     // Makes an unsolved grid form a full grid
     void refillUnsolvedGrid(){

        memset(B, 0, sizeof(B[0][0]) * L * L);

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



     // check the number in the row and cols
     bool check_value_rc(int a, int b, int value){
             
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
     bool check_value_sqr(int a, int b, int value){

        // in the square
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

     void putRawValue(int i, int j, int value){
        B[i][j] = value;
     }

     // If the given value is the same as in the cell with the given coordinates then it places the value, else places -1
     void putValue(int i, int j, int value){
        if(A[i][j] == value) 
            B[i][j] = value;
        else B[i][j] = -1;
     }
     
     // Returns a cell from unsolved grid
     int getCell(int i, int j){
        return B[i][j];
     }


    private:

     // Shuffle array
     void shuffle_array(int arr[], int n, int k)
     {
         // To obtain a time-based seed
         unsigned seed = time(0)*k;
 
         // Shuffling our array
         shuffle(arr, arr + n, default_random_engine(seed));

     }

 
     void fill_square(int ii, int jj, bool& validSquare){
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


    public:

     void printGrid(){
         for(int k=0; k<L; k++){
             for(int i=0; i<L; i++){
                 cout<<A[k][i]<<" ";
             }
             cout<<"\n";
         }
         cout<<"\n";
     }

     void printUnsolvedGrid(){
         for(int k=0; k<L; k++){
             for(int i=0; i<L; i++){
                 cout<<B[k][i]<<" ";
             }
             cout<<"\n";
         }
         cout<<"\n";
     }


     void refillGrid(){
         // the counter is used in the shuffle method because the suffling based only on time(seed) isn't enough, because it changes with a delay
 
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
             //printGrid();
 
             refillCounter++;
 
         }while(!validSquare);
 
         checkedRefillCounter();
 
     }  

     void refillAll(){
         this->refillGrid();
         this->refillUnsolvedGrid(); 
     }


     int getRefillCounter(){
        return refillCounter;
     }

     
     
};


int main()
{   
    gridTemplate templ(40);

    //templ.printGrid();
    
    //templ.refillGrid();
    for(int k=0; k<L; k++){
        templ.printUnsolvedGrid();
        templ.refillAll();
    }

    cout<<templ.getRefillCounter()<<"\n";
    
    return 0;
}
