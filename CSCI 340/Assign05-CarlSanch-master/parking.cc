// Carlos Sanchez
// z1729554
// CSCi 340
//
// I certify that this is my own work and where appropriate an extension of the starter code provided for the assignment

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <deque>
#include <stack>

using namespace std;

#define MAX_CAPACITY 10

typedef struct 
{ 
    int id;         // id starts at 1
    string lp;      // license plate of car
    int no_mv;      // number times the car has been moved
}CAR; 

int ID = 1;
void get_input_vals(const string &line, char &act, string &lp);
void arrival(const CAR &car, deque<CAR> &D);
void departure(const string &lp, deque<CAR> &D, stack<CAR> &S);

int main(){

    string line; 
    
    deque<CAR> car_queue;
    stack<CAR> car_stack;

    while(getline(cin, line)){
    	char act;
    	string lp;
    	get_input_vals(line, act, lp);
    	if(act=='A'){
    		CAR c = {ID++, lp, 0};
    		arrival(c, car_queue);
		}else if(act == 'D'){
			departure(lp, car_queue, car_stack);
		}else{
			cout<<"'"<<act<<"': invalid action!"<<endl;
		}
		cout<<endl;
    }  
  
    return 0; 
}



void get_input_vals(const string &line, char &act, string &lp){
	act = line[0];
	lp = line.substr(2,line.length()-3);

}

void arrival(const CAR &car, deque<CAR> &D){
	cout<<"Car "<<car.id<<" with license plate \""<<car.lp<<"\" is arrived."<<endl;

	if(D.size() < MAX_CAPACITY){
		D.push_back(car);
	}else{
		cout<<"    But the garage is full!"<<endl;
	}
	//cout<<"Arrival: "<<car.id<<" "<<car.lp<<" "<<car.no_mv<<endl;
}

void departure(const string &lp, deque<CAR> &D, stack<CAR> &S){
	int found = 0;

	CAR car;
	while(!D.empty()){
		if(lp.compare(D.front().lp)==0){
			found = 1;
			car = D.front();
			D.pop_front();
			break;
		}else{
			S.push(D.front());
			D.pop_front();
		}
	}
	if(found==1){
		cout<<"Car "<<car.id<<" with license plate \""<<car.lp<<"\" is departed,"<<endl;
		if(car.no_mv == 0)
			cout<<"    car was moved "<<(car.no_mv+1)<<" time in the garage."<<endl;
		else 
			cout<<"    car was moved "<<(car.no_mv+1)<<" times in the garage."<<endl;

	}else{
		cout<<"No car with license plate \""<<lp<<"\" in garage."<<endl;
	}
	while(!S.empty()){
		car = S.top();
		car.no_mv++; 
		S.pop();
		D.push_front(car);
	}
}
