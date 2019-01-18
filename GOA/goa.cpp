#include "goa.h"
#include <stdlib.h>
#include "functions.cpp"


GOA::GOA(int size,int ef){
	N=size;
    positions.set_size(N,dim);
    fitness.set_size(N);
    best_position.set_size(dim);
    distances.resize(N);

   	for(int i=0;i<N;i++){
   		distances[i].resize(N);
   		for(int j=0;j<N;j++)
   			distances[i][j].resize(dim);
   }

   function = ef;

   valor_estudio = 1.5;

}

int GOA::get_poblation_size(){

	return N;
}

int GOA::get_max_iterations(){
	return maxIter;
}

void GOA::initialize(int cmax, int cmin, int maxIter){

	srand(time(NULL));

	this->cmax = cmax;
	this->cmin = cmin;
	this->maxIter=maxIter;

	for(int i=0;i<N;i++){
		for(int j=0;j<dim;j++){
			positions(i,j)= rand()%(2*maxPos)-maxPos;

		}

		fitness(i) = evaluationFunction(positions.row(i));	
	}

	//cout<<fitness<<endl;

	best_fitness = fitness.min();
	mejor1 = best_fitness;
	best_position = positions.row(fitness.index_min());

	//cout<<"INICIAL"<<best_fitness<<endl;
	//cout<<"POSICIONES INICIAL"<<positions<<endl;
}

void GOA::update_c(int l){

	c = cmax - l * (cmax-cmin)/maxIter;
}

void GOA::normalize_distances(){

	double max = 0;

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			for(int k=0;k<dim;k+=2){ 
				distances[i][j][k]=sqrt(pow(positions(j,k) - positions(i,k),2) + pow(positions(j,k+1) - positions(i,k+1),2)); 
				distances[i][j][k+1]=distances[i][j][k]; 
				if(distances[i][j][k] > max)
					max = distances[i][j][k];
			}
		}
	}

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			for(int k=0;k<dim;k++){ 
				distances[i][j][k]=(distances[i][j][k]*4)/max;

			}
		}
	}


	
}


void GOA::actualize_position(int l,int pos){

	double aux=0;
	double s=0;
	double r=0;

	for(int d=0;d<dim;d++){
		aux=0;
		for(int j=0;j<N;j++){
			if(j!=pos){
				if(dim%2==0){ //
					r = abs(positions(j,d) - positions(pos,d)); 
				}

				if(r==0) r=0.000001;
				s = f*exp( (-r) / l) - exp(-r);
				aux += c * (maxPos - minPos)/2 * s * r * valor_estudio* (positions(j,d)-positions(pos,d))/distances[pos][j][d];

			}

		}

		positions(pos,d) = c * aux + best_position(d);

		//bring back
		if(positions(pos,d) < minPos || positions(pos,d) > maxPos)
			positions(pos,d) = rand()%(2*maxPos)-maxPos;

	}

	fitness(pos)=evaluationFunction(positions.row(pos));


}

double GOA::actualize_best(int l){

	for(int d=0;d<N;d++){
		fitness(d) = evaluationFunction(positions.row(d));
	}

	if(fitness.min()<best_fitness){
		best_fitness = fitness.min();
		best_position = positions.row(fitness.index_min());
	}

	return best_fitness;

}




