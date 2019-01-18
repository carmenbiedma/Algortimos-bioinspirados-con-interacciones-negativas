#include "firefly.h"
#include <stdlib.h>
#include "functions.cpp"


Firefly::Firefly(int size,int ef,int iter){
	N=size;
    positions.set_size(N,dim);
    fitness.set_size(N);
    best_position.set_size(dim);
    
   	function = ef;

   	max_iter = iter;

}

void Firefly::initialize(){

	srand(time(NULL));


	for(int i=0;i<N;i++){
		for(int j=0;j<dim;j++){
			positions(i,j)= rand()%(2*maxPos)-maxPos;

		}

		fitness(i) = evaluationFunction(positions.row(i));	
	}

	best_fitness = fitness.min();
	best_position = positions.row(fitness.index_min());
}

void Firefly::algorithm(){

	for(int i=0;i<max_iter;i++){
		for(int j=0;j<N;j++){
			for(int k=0;k<N;k++){
				if(fitness(k)<fitness(j)){
					double aux = 0;
					for(int d=0;d<dim;d++){
						aux += pow(positions(k,d)-positions(j,d),2);
					}

					double distance = aux * valor_estudio; //Le quito la raiz porque luego lo eleva al cuadrado

					Mat<double> random;
					random.set_size(1,dim);
					random.randn();
					positions(j) = positions(j) + exp(-distance)*(positions(k)-positions(j)) + 0.2 * random(0);


					for(int p= 0;p<dim;p++){	
						if(positions(j,p) < minPos || positions(j,p) > maxPos)
							positions(j,p) = rand()%(2*maxPos)-maxPos;
					}


					fitness(j) = evaluationFunction(positions.row(j));
				}
			}
		}
	}

	double sol = fitness.min();
	cout<<sol-function*100<<";";

}