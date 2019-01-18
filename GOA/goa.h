#include <iostream>
#include <armadillo>
#include <vector>	

using namespace std;
using namespace arma;



void cec14_test_func(double *, double *,int,int,int);

class GOA{

	private:
			Mat<double> positions;
			int N; //Number of elements in the poblation
			double cmax,cmin;
			int maxIter;
			Row<double> fitness;
			double best_fitness;
			Row<double> best_position;
			double c;
			double f = 0.5;
			vector<vector<vector<double>>> distances;

			int dim=30;
			int minPos=-100;
			int maxPos=100;	

			double mejor1;

			int function; //Asignment in constructor

			double valor_estudio;
			
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

    	GOA(int size,int ef);
    	int get_poblation_size();
		int get_max_iterations();
    	void initialize(int cmax, int cmin, int maxIter);
    	void update_c(int l);
    	void normalize_distances();
    	void actualize_position(int l,int pos);
    	double actualize_best(int l);



};