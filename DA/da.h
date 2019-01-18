#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

void cec14_test_func(double *, double *,int,int,int);

class DragonFly{

	private:
			const double s=0.1;
			const double atraccion = 0.75;
			const double repulsion = 1.25;
			const double a=0.1;
			const double c=0.7;
			double f=1;
			double e=1;
			int n; //Number of members in the population
		    Mat<double> positions; //Position 
		    Mat<double> velocity; //Step vectors
		    Row<double> fitness; //Value of goodness calculate with the evaluation function
		    Row<bool> isBestNeighbour;
		    Row<double> food_pos,enemy_pos;
		    double food,enemy;
		    Mat<double> S,A,C,E1,F;
		    double w;
		    double r;

		    //Se introduce manualmente
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

    		DragonFly(int size,int ef); //Number of elements in the poblation
    		void initialize(int dimension);
    		void calculateFitness(); //Euclidean distance member-food
    		vector<int> calculateNeighbours(int num, int iter,int maxIter);
    		void calculateValues(int iter, int iterMax); //Calculate the value of food,enemy,S,A,C,F,E
    		void actualizeVelocity(int iter,int iterMax,int pos,double fvalue, double evalue);
    		void actualizePositionWithNeighbours(int pos);
    		void actualizePositionWithoutNeighbours(int pos);
    		pair<Row<double>,double> bestSolution();

    		virtual ~DragonFly(){}

};