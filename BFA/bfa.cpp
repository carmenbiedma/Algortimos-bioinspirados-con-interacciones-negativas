#include "bfa.h"
#include <algorithm>
#include <stdlib.h>
#include "functions.cpp"

BFA::BFA(int size,int function){

	this->function = function;
	S=size;
    positions.set_size(S,dim);
    fitness.set_size(S);
    best_position.set_size(dim);
    best_fitness=0;
    C= Lred; 
    Ccc=0.1; 
    Jhealth.resize(S);
    Nc = (dim*100)/23;
    Nre = (dim*100)/23;
    Ned = (dim*100)/23;
    Ns = (3*dim*100)/23;

}

void BFA::initialize(){

	srand(time(NULL));


	for(int i=0;i<S;i++){
		for(int j=0;j<dim;j++){
			positions(i,j)= rand()%(2*maxPos)-maxPos;

		}
	}

	for(int i=0;i<S;i++){
		fitness(i) = evaluationFunction(positions.row(i));
		Jhealth[i].first = Jhealth[i].second =0;
	}


	best_fitness = fitness.min(); 
	best_position = positions.row(fitness.index_min());

}

double BFA::Jcc(Mat<double> poblation, int actual){

	double result=0;
	double atraccion = 0;
	double repulsion = 0;
	double aux=0;

	for(int i=0;i<S;i++){
		if(actual!=i){
			for(int j = 0;j<dim;j++){
				aux+= pow (poblation(actual,j) - poblation(i,j), 2);
			}
		}	

		atraccion += -da * exp(-wa*aux);
		repulsion += -hr * exp(-wr*aux);
	}

	result = atraccion*1.5 + 0*repulsion;
	return result;
}

void BFA::chemotaxis(int actual){

	double lastfitness = fitness(actual) + Jcc(positions,actual);

	//Tumble

	Row<double> random;
	random.set_size(dim);

	for(int d1 = 0;d1<dim;d1++)
		 random(d1) = (rand()%(2*100)-100)* 0.01;
	

	positions.row(actual) = positions.row(actual) + C*random;

	fitness(actual) = evaluationFunction(positions.row(actual));

	double currentfitness = fitness(actual) + Jcc(positions,actual);

	//Run

	for( int a=0; a<Ns && currentfitness < lastfitness; a++){
		lastfitness = currentfitness;
		positions.row(actual) = positions.row(actual) + C*random;
		fitness(actual) = evaluationFunction(positions.row(actual));
		currentfitness = fitness(actual) + Jcc(positions,actual);

	}

}


void BFA::algorithm(){

	double jcurrent,jlast =0;

	for(int l=0; l<Ned;l++){
		for(int k=0; k<Nre;k++){
			for(int j=0;j<Nc;j++){
				for(int i=0;i<S;i++){
					chemotaxis(i);

				} //End for bacterium

				if(fitness.min()<=best_fitness){
					best_position=positions(fitness.index_min());
					best_fitness = fitness.min();
				}

			} //End for chemotaxis


			for(int a=0;a<S;a++){
				Jhealth[a].first += fitness(a);
				Jhealth[a].second = a;
				
			}
			
			sort(Jhealth.begin(),Jhealth.end());

			int aux = S/2;

			for(int a=0;a<S/2;a++){

				Jhealth[a+aux].first = Jhealth[a].first;

				positions(Jhealth[a+aux].second) = positions(Jhealth[a].second);
				fitness(Jhealth[a+aux].second) = fitness(Jhealth[a].second);
	
			}


		} //End of reproduction

		double p = rand()%100; //Pobabilidad de 0,25
		if(p<25){
			int aux = rand()%(S-1);
			for(int a=0;a<dim;a++){
				positions(aux,a)=rand()%(2*maxPos)-maxPos;
			}
		}

		C= Lred / ((l+1)/Ned);


	}

	cout<<best_fitness-function*100<<";";

}
