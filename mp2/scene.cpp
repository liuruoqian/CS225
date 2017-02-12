#include "scene.h"
#include "image.h"

#include <iostream>

using namespace std;

//constructor with given max, set max = maxSize

Scene::Scene (int maxSize): max(maxSize){
	//array of imaage ptrs of size max
	arr = new Image* [max]; 
	x = new int[max]; //initilize ptr x to array(dynamic)
	y = new int[max]; //initilize ptr y to array(dynamic)
    
    // initilize all of the ptrs in arr to NULL
	for (int i = 0; i < max; i++){
		arr[i] = NULL;
	}
}

void Scene::clear(){
	for (int i = 0; i < max; i++){
		if (arr[i] != NULL) {
			delete arr[i];
			arr[i] = NULL;
		}
	}

	if (x != NULL){
		delete [] x;
		x = NULL;
	}

	if (y != NULL){
		delete [] y;
		y = NULL; 
	}
}

Scene::~Scene(){
	clear();
}

Scene::Scene(const Scene & source){

    copy(source);
}

void Scene::copy(const Scene & source){
	max = source.max;
	arr = new Image*[max];
	x = new int[max];
	y = new int[max];
	for (int i = 0; i < max; i++){
		if (source.arr[i] == NULL){
			arr[i] = NULL;
		}
		else 
		arr[i] = new Image(*(source.arr[i])); // deep copy!!!!! 
		
		x[i] = source.x[i];
		y[i] = source.y[i];

	}
}


const Scene & Scene::operator=(const Scene & source){
	if (this != &source){
		clear();
		copy(source);
	}
	return *this;

}

void Scene::changemaxlayers (int newmax){

	// Should we use this? No!!
    // 
	// you may assume newmax > 0
	if (newmax < max){
		for (int i = newmax; i < max; i++){
			if (arr[i] != NULL){
				cout << "invalid index" << endl;
				return;
			}

		}
	}

    Image ** arr1 = new Image*[newmax];
	for (int i = 0; i < newmax; i++){
		arr1[i] = NULL;
	}
	int * x1 = new int[newmax];
	int * y1 = new int[newmax];
		
	for (int i = 0; i < max; i++){
		if (arr[i] != NULL){
			*arr1[i] = *(arr[i]);
			x1[i] = x[i];
			y1[i] = y[i];
		}
		
	}
	clear();

	x = x1;
	y = y1;
	max = newmax;
	arr = arr1;


}

void Scene::addpicture( const char * FileName, int index, int xVal, int yVal){

	if (index < 0 || index > (max -1)){
		cout << "index out of bounds" << endl;
		return;
	}
	if (arr[index] != NULL){
		delete arr[index];
	}
	Image * addpic = new Image();
	(*addpic).readFromFile(FileName);
	arr[index] = addpic;
	x[index] = xVal;
	y[index] = yVal;
	
}

void Scene::changelayer(int index, int newindex){  //revised
	if (index == newindex)
		return;
	if ((index >=0 && index < max) && (newindex >=0 && newindex < max)){ //...? !!!!!
		if (arr[newindex] != NULL)
			delete arr[newindex];
		arr[newindex] = arr[index];
		arr[index] = NULL;
        x[newindex] = x[index];
        y[newindex] = y[index];
        //x[index] = 0; ... well..
        //y[index] = 0; ... well..
	}
	else{
		cout << "invalid index" << endl;
		return;  // ...well..
	}
}

void Scene::translate(int index, int xcoord, int ycoord){
	if ((index < 0) || (index > (max-1)) || arr[index] == NULL){
		cout << "invalid index" << endl;
		return;
	}
	x[index] = xcoord;
	y[index] = ycoord;
}

void Scene::deletepicture (int index){
	if ((index < 0) || (index > (max-1)) || arr[index] == NULL){
		cout << "invalid index" << endl;
		return;
	}
	else{
	delete arr[index];
	arr[index] = NULL;
	//x[index] = 0; //...well..
	//y[index] = 0; //...well..
    }
}

Image * Scene::getpicture(int index) const{
	if (index < 0 || index > (max-1)){
		cout << "invalid index" << endl;
		return NULL;
	}
	Image * pic = arr[index];
	return pic; // ...well..
}


Image Scene::drawscene () const{
	size_t width = 0;
	size_t height = 0;
	for (int i = 0; i < max; i++){
		if (arr[i] != NULL){
		    if (width < ((*arr[i]).width() + x[i]))
			    width = (*arr[i]).width() + x[i];
		    if (height < ((*arr[i]).height() + y[i]))
			    height = (*arr[i]).height() + y[i];	
        }
	}
	Image draw;
	draw.resize(width, height);
	for (int i = 0; i < max; i++){
		if (arr[i] != NULL){
			for (size_t a = 0; a < (*arr[i]).width(); a++){  //..well..
				for (size_t b = 0; b < (*arr[i]).height(); b++){  
					*draw(a+x[i], b+y[i]) = *(*arr[i])(a,b);
				}
			}
			
		}
	}
	return draw;
}

//Done!

