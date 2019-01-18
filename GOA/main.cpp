#include <iostream>
#include <armadillo>
#include "goa.h"

using namespace std;

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;

int main(int argc, char **argv){
	int dim = 10;
	int ef=1;

	if (argc > 1) {
		ef = atoi(argv[1]);
	}


	GOA prueba = GOA(10,ef);

	prueba.initialize(1,0.000001,dim*10000);
	double sol=0;

	for(int l=0;l<prueba.get_max_iterations();l++){
		prueba.update_c(l);
		for(int j=0;j<prueba.get_poblation_size();j++){
			prueba.normalize_distances();
			prueba.actualize_position(l,j);

		}
		sol=prueba.actualize_best(l);
		if(sol < pow(10,-8)){
			sol = 0;
			l = prueba.get_max_iterations(); //Termina
		}

		//if(l%1000 == 0){
			//cout<<"iter =  "<<l<<" " << sol-ef*100<<endl;
		//}
	}
	
	cout<<sol-ef*100<<";";

	return 0;
}