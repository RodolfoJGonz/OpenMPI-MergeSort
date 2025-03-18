#include <iostream>
#include <vector>
#include <chrono>

void printArray(std::vector<int>& A);
void merge(std::vector<int>& arr, int left, int mid, int right);
void mergeSort(std::vector<int>& arr, int left, int right);

int main (int argc, char *argv[]) {
	std::vector<int> testArray;
	for(int i = 0; i < 1000000; i++){
		testArray.push_back(rand()%100);
	}
	int sz = testArray.size();
	
	//printf("Given array is: \n");
	//printArray(testArray);

	auto start = std::chrono::high_resolution_clock::now();
	mergeSort(testArray, 0, sz-1);
	auto stop = std::chrono::high_resolution_clock::now();

	//printf("\nSorted array is: \n");
	//printArray(testArray);
	
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
	return 0;
}

void printArray(std::vector<int>& A)
{
    for (int i = 0; i < A.size(); i++)
        printf("%d ", A[i]);
    printf("\n");
}


void merge(std::vector<int>& arr, int left, int mid, int right){
	int n1 = mid-left + 1;
	int n2 = right-mid;

	std::vector<int> L(n1), R(n2);

	for (int i = 0; i < n1; i++){
		L[i] = arr[left+i];
	}
	for (int j = 0; j < n2; j++){
		R[j] = arr[mid+1+j];
	}

	int i = 0, j = 0;
	int k = left;

	while(i < n1 && j < n2){
		if(L[i] <= R[j]){
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while(i < n1){
		arr[k] = L[i];
		i++;
		k++;
	}
	while(j < n2){
		arr[k] = R[j];
		j++;
		k++;
	}
}



void mergeSort(std::vector<int>& arr, int left, int right){
	if(left >= right)
		return;

	int mid = left + (right-left)/2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid+1, right);
	merge(arr, left, mid, right);
}
