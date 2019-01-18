#include "da.h"
#include <math.h>

#include "functions.cpp"

DragonFly::DragonFly(int size, int ef){
	//________________________
    n=size;
    positions.set_size(n,dim);
    velocity.set_size(n,dim);
    fitness.set_size(n);
    A.set_size(n,dim);
    S.set_size(n,dim);
    C.set_size(n,dim);
    F.set_size(n,dim);
    E1.set_size(n,dim);
    food_pos.set_size(dim);
    enemy_pos.set_size(dim);
    isBestNeighbour.set_size(n);

    food = 100000000000;

    function = ef;
}

void DragonFly::initialize(int dimension){

	dim = dimension;

	srand(time(NULL));

	for(int i=0;i<n;i++){
		for(int j=0;j<dim;j++){
			positions(i,j)= rand()%maxPos; //Between 0 and positive limit of the function
			double random = rand() % 200;
			velocity(i,0) = -1 + random/100;
		}
	}
	
	A.zeros();
	S.zeros();
	C.zeros();
	F.zeros();
	E1.zeros();
	food_pos.zeros();
	enemy_pos.zeros();

}

void DragonFly::calculateFitness(){
	Row<double> aux;
	aux.set_size(1,dim);
	aux.zeros();
	for(int i=0;i<n;i++){
		fitness(i)= evaluationFunction(positions.row(i));
	}

	//cout<<"FITNESS"<<endl<<fitness<<endl; 
}

vector<int> DragonFly::calculateNeighbours(int num, int iter,int maxIter){

	//cout<<"ITER"<<iter<<endl;
	r= (maxPos-minPos)/4 + (iter/maxIter)*(maxPos-minPos)*2;
	vector<int> vecinos;
	bool esVecino;

	for(int i=0;i<n;i++){
		esVecino=true;
		if(i!=num){
			for(int j=0;j<dim && esVecino==true;j++){
				double dist = positions(num,j) - positions(i,j);

				//cout<<dist<<" DIST "<<endl;
				if(abs(dist) > r)
					esVecino=false;

				if(positions(num,j)-food_pos(j) < r)
					isBestNeighbour(num)=true;
				else
					isBestNeighbour(num)=false;
			}

			if(esVecino) vecinos.push_back(i);

		}
	}

	return vecinos;
}

void DragonFly::calculateValues(int iter, int maxIter){ //con los vecinos)
	vector<bool> has_neighbors(n);

	//Calculate the food with the best fitness
	if(fitness.min()<food){
		food=fitness.min();
		food_pos=positions.row(fitness.index_min());
	}
	enemy=fitness.max();
	
	enemy_pos=positions.row(fitness.index_max());

	for(int i=0; i < n; i++){ //Recorremos la poblacion
		//calculamos los vecinos
		vector<int> neighbours = calculateNeighbours(i,iter, maxIter);

		//Calculate separation
		
		Row<double> posAct = positions.row(i);
		for(unsigned j=0;j<neighbours.size();j++){
			S.row(i) += posAct - positions.row(neighbours[j]);
		}

		S.row(i) *=-1;
		

		//calculate alignment

		Row<double> aux(dim);
		
		aux.zeros();

		for(unsigned j=0;j<neighbours.size();j++){
			aux+=velocity.row(neighbours[j]);
		}
		A.row(i) = aux/n;

		

		//Calculate cohesion
		aux.zeros();
		for(unsigned j=0;j<neighbours.size();j++){
			aux += positions.row(neighbours[j]);
		}		

		C.row(i)=aux/n-posAct;
		

		//Calculate F and E
	
		F.row(i) = food_pos - posAct;
		E1.row(i) = enemy_pos + posAct;
		has_neighbors[i] = (neighbours.size() > 1);


	}			

		//ACtualize position and velocity
	for(int i=0;i<n;i++){
		if(isBestNeighbour(i) == false) {
			if(has_neighbors[i]){
				actualizeVelocity(iter,maxIter,i,0,0);
				actualizePositionWithNeighbours(i);
			}
			else{
				actualizePositionWithoutNeighbours(i);
			}
		}
		else{
			actualizeVelocity(iter,maxIter,i,1,1);
			actualizePositionWithNeighbours(i);
		}
	}
	
}


void DragonFly::actualizeVelocity(int iter,int iterMax,int pos, double fvalue ,double evalue){

	f=fvalue;
	e=evalue;
	Mat<double> velocityAnt = velocity;

	w=0.9 - iter/iterMax*(0.9-0.4);

	velocity(pos,0)= s*S(pos,0) + a*A(pos,0) + c*C(pos,0) + atraccion*f*F(pos,0) + repulsion*e*E1(pos,0) + w*velocityAnt(pos,0);

	if(velocity(pos,0) < -1 || velocity(pos,0)>1){
		double random = rand() % 200;
		velocity(pos,0) = -1 + random/100;
	}
}

void DragonFly::actualizePositionWithNeighbours(int pos){

	Row<double> positionAnt = positions.row(pos);

	positions.row(pos)=positionAnt + velocity(pos,0);
	for(int j=0;j<dim;j++){
		if(positions(pos,j) < minPos)
			positions(pos,j)= maxPos;
		if(positions(pos,j) > maxPos)
			positions(pos,j) = minPos;
	}

}

void DragonFly::actualizePositionWithoutNeighbours(int pos){

	Row<double> positionAnt = positions.row(pos);

	double beta = 1.5;
	double sigma = (tgamma(1+beta) * sin( (3.141592653589793*beta) / 2) ) / tgamma( (1+beta)/2)*beta*pow(2, (beta-1)/2);
	double r1 = rand()%100; 
	double r2 = rand()%100; 
	r1 = r1/100;
	r2=r2/100;
	double levy = 0.01 * ((r1*sigma) / pow(r2,1/beta));

	positions.row(pos) = positionAnt - levy*positionAnt;

	for(int j=0;j<dim;j++){
		if(positions(pos,j) < minPos)
			positions(pos,j)= maxPos;
		if(positions(pos,j) > maxPos)
			positions(pos,j) = minPos;
	}

}

pair<Row<double>,double> DragonFly::bestSolution(){

	pair<Row<double>,double> solution;
	solution.first=food_pos;
	solution.second=food;
	return solution;
}
