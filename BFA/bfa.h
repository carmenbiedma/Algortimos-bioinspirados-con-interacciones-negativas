#include <iostream>
#include <armadillo>
#include <vector>	

using namespace std;
using namespace arma;

void cec14_test_func(double *, double *,int,int,int);

class BFA{

	private:
			Mat<double> positions;
			int Ned = 0;
			int Nre = 0;
			int Nc = 0;
			int Ns = 0;
			int S; 
			double C; //Size of the step
			double Lred = 0.1;
			Row<double> fitness; //J
			Row<double> best_position;
			double best_fitness;
			double Ccc; //Atraction factor
			vector<pair<int,double>> Jhealth;

			double da=0.1;
			double wa=0.2;
			double hr=0.1;
			double wr=10;

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

    	BFA(int size,int function); 
    	void initialize();
    	void algorithm();
    	double Jcc(Mat<double> poblation,int actual);
    	void chemotaxis(int actual);





};