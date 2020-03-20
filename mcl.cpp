#include <vector>
#include "particle.cpp"
#include "motion_model.cpp"
#include "measurement_model.cpp"

std::vector<particle> mcl (std::vector<particle> prevParticles, int control[2], robot&  r){
	
	 std::vector<particle> predictedParticleSet; 
	 particle p(0,0,0,0); 
	r.setX(r.getX()+control[0]);
	r.setY(r.getY()+control[1]);
	r.setT(r.getT()+control[2]);
	printf("X %d Y %d T %d", r.getX(), r.getY(), r.getT());
	for (int i =0; i < prevParticles.size(); i++){
		//sets x,y,theata
		motion_model(p, control, prevParticles.at(i));
		//sets weight value
		measurement_model(p,r ,prevParticles.at(i));
		//adds particle to predicted set
		predictedParticleSet.push_back(p);
	}

	int total=0; 
	for (int i =0; i < predictedParticleSet.size(); i++){
		total = total + predictedParticleSet.at(i).getW();
	}
	
	
	std::vector<particle> resample;
	srand(time(0));
	
	for (int i =0; i <predictedParticleSet.size() ; i++){
		int choose = rand()%total;
		int counter =0;
	  	for (int j=0; j < predictedParticleSet.size(); j++){
			  counter = counter + predictedParticleSet.at(j).getW();
			  if(counter > choose){
				  resample.push_back(predictedParticleSet.at(j));
				  break;
			  }
		  }
	}//end for

	printf("\n");
	plot(resample,r);
	return resample;
	
}