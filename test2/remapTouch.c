#include <stdio.h>
#include <stdlib.h>


int main(void){
	int value;
	int remapped_value;
	value = 600;
	remapped_value = remapTouch(600);
	printf("%d\n", remapped_value);

}


int remapTouch(int value){
	double remappedValue;
	remappedValue = (double)value/600.0 *375.0 + 125;

	return remappedValue;	
}

