#include <iostream>
#include <armadillo>
#include <vector>	

using namespace std;
using namespace arma;



void cec14_test_func(double *, double *,int,int,int);
class Firefly{

	private:
			Mat<double> positions;
			int N; //Number of elements in the poblation
			Row<double> fitness;
			double best_fitness;
			Row<double> best_position;
			int max_iter;
			double valor_estudio=1;

			int dim=30;
			int minPos=-100;
			int maxPos=100;	


			int function; //Asignment in constructor

			
			
			double evaluationFunction(Row<double> r){
		    	
		    	double result=0;
		    	double *x;
		    	x = (double*)malloc(dim*sizeof(double)); 
		    	for(int i=0;i<dim;i++){
		    		x[i]=r(i);
		    	}

		    	cec14_test_func(x,&result,dim,1,function);
		    	
				free(x);
		    	return result;
		    }

    public:

    	Firefly(int size,int ef, int iter);
    	void initialize();
    	void algorithm();


};