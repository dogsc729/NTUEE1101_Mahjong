#include "iostream"
#include "vector"
#include "time.h"

using namespace std;

int main(){ 
    srand(time(NULL));
    std::vector<int> positionSequence(36,0);
	std::vector<int> oneTo36(36,0);
	for(int i = 0; i < 36; i++)
		oneTo36[i] = i+1;
	int size = 36;
	int index;
    for(int i = 0; i < 6; i++){
        std::vector<int> pickedIndex(36,0);
        //cout << "fuck" << endl;
        for(int j = 0; j < 36; j++){
            //cout << "hoho" << endl;
            do{
                index = rand() % 36;
            } while (pickedIndex[index] != 0);
            pickedIndex[index] = 1;
            positionSequence[j] = oneTo36[index]; 
	    }
        for(int j = 0; j < 36; j++){
            std::cout << positionSequence[j] << " ";
        }
        cout << endl;
    }
    return 0;
}