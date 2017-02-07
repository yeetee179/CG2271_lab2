#include <stdio.h>
#include <stdlib.h>


int main(void){
	int value;
	int remapped_value;
	int i=0;
	value = 600;
//	for (i = 0; i<601; i++){
		remapped_value = remapTouch(i);
		printf("%d\n", remapped_value);
//	}


}


int remapTouch(int value){
	double remappedValue;
	remappedValue = (double)value/600.0 *375.0 + 125;

	return remappedValue;	
}

