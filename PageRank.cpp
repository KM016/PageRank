//impporting libraries 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>


//matrix class 
class matrix
{

    //creating variables to hold matrix rows, cols and elements 
    int num_rows;
    int num_cols;
    int *elements;

//public functions 
public:

    //function to get the rows/cols of a matrix
    int get_num_rows() { return num_rows; }
    int get_num_cols() { return num_cols; }


    //function to set the ij element of a matrix to value 
    void set_elem(int i, int j, int value){
            elements[i * num_cols + j] = value;
    }


    //function to return the ij element of a matrix
    int get_elem(int i, int j){
            return elements[i * num_cols + j];
    }


    //matrix constructor 
    matrix(int nrow, int ncol){
            num_rows = nrow;
            num_cols = ncol;

            printf("allocating memory for the matrix...\n");
            elements = (int *)malloc(num_rows * num_cols * sizeof(int));
    }


    //matrix deconstructor 
    ~matrix()
    {
        printf("freeing the matrix...\n");
        free(elements);
    }


    //function to print out elements of a matrix
    void print()
    {
        for (int i = 0; i < num_rows; i++){
            for (int j = 0; j < num_cols; j++){
                printf("%d ", get_elem(i, j));
            }
            printf("\n");
        }
    }

};






//algorithm class
class algorithm{

    matrix A;
    

    //public functions 
    public:

        //algorithm constrictor takes row/col num and makes a matrix
        algorithm(int num_rows, int num_cols): A(num_rows, num_cols){

            //matrix is defined as an array first 
            double matrix_data[] = {0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 
                        0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0,
                        1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0,
                        1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
                        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0,};



            //takes each element of the array and adds it to a matrix 
            for  (int i=0; i<7; i++) {
                for (int j = 0; j < 7; j++){
                    A.set_elem(i,j,matrix_data[i*7+j]);
                }
            }

        }



        //run function does the page rank calculations 
        void run(){

            //creating arrays for a, b, a old, and b old
            double a[7];
            double b[7];
            double a_old[7];
            double b_old[7];

            //variables to hold the max difference between a[i] and a_old[i] - used for terminating condition
            double max_diff_a;
            double max_diff_b;

            //esetting terminate to false and setting number of itterations to 0 
            bool terminate = false;
            int itterations = 0;


            //setting the initial elements of a and b 
            for(int i = 0; i < 7; i++){
                a[i] = 1.0;
                b[i] = 1.0;
            }


            //setting values for M and epsilon 
            int M = 100;
            double e = 1e-6;



            //big loop that will run for M itterations or until terminating condition is met 
            while(itterations<M && terminate == false){

                //setting elements of a old and b old to that of a and b 
                for(int i = 0; i < 7; i++){
                    a_old[i] = a[i];
                    b_old[i] = b[i];
                }


                //setting ai as the sum of Aji * bj
                for(int i=0; i<7; i++){
                    double ai_sum = 0.0;

                    for(int j=0; j<7; j++) {
                        ai_sum += A.get_elem(j,i) * b[j];
                    }

                    a[i] = ai_sum;      
                }



             //setting bi as the sum of Aij * aj
                for(int i=0; i<7; i++){
                    double bi_sum = 0.0;

                    for(int j=0; j<7; j++) {

                        bi_sum += A.get_elem(i,j) * a[j];

                    }
                        b[i] = bi_sum;      
                }




                //finding the norm of a and b  
                double norm_a = 0.0;
                double norm_b = 0.0;

                for(int i =0; i<7; i++){
                    norm_a += a[i] * a[i];
                    norm_b += b[i] * b[i];
                }

                norm_a = abs(sqrt(norm_a));
                norm_b = abs(sqrt(norm_b));


                //dividing a and b by their norms  
                for(int i =0; i<7; i++){
                    a[i] = a[i]/norm_a;
                    b[i] = b[i]/norm_b;
                }


                //setting the max difference between a[i] and a_old[i] to zero 
                max_diff_b = 0; 
                max_diff_b = 0; 


                //this loop will find the maximum difference between the elements of a/b and a_old/b_old
                for(int i =0; i<7; i++){

                    if( abs(a[i] - a_old[i]) > max_diff_a ){
                            max_diff_a = abs(a[i] - a_old[i]);
                    }

                    if( abs(b[i] - b_old[i]) > max_diff_b){
                             max_diff_b = abs(b[i] - b_old[i]);
                    }
                }

                //if both the max differences are less than epsilon terminating condition is met 
                if  (max_diff_a < e || max_diff_b < e) {
                    terminate = true;
                }


                //so long as the terminating condition is not met itterations increments 
                itterations += 1;
                
            }

            //prints how many itterations it took to break the loop (converge)
            printf("\nItterations to converge: %d\n\n", itterations);
            //calls print function 
            print_score(a,b,7);
            

        }



        //function that prints the contents of a (impact) and b(knowledge)
        void print_score(double a[], double b[], int len){

            for(int i=0; i<len; i++){
                printf("Paper %d:\n Impact: %.8f    Knowledge: %.8f\n\n",i+1, a[i], b[i]);
            }

        }
};







int main(){

    //creating a patrix B 
    matrix A(7,7);

    //creating an Algorithm B that works with the matrix defined and running it 
    algorithm pagerank(A.get_num_rows(),A.get_num_cols());
    pagerank.run();

}