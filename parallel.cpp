#include <cstdlib>
#include <mpi.h>
#include <iostream>
#include <ostream>
#include <chrono>

//void printArray(int A[], int size);
void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);

int main (int argc, char** argv) {
	//Number of integers that will be sorted
	const int ARR_SIZE = 1000000;
	MPI_Init(&argc, &argv);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	//Use dynamic memory allocation since using stack allocation
	//Results in segmentation fault if the ARR_SIZE is too large
	//i.e. when testing from 100,000 stack allocation was fine
	//but when testing 1,000,000 segmentation fault occured
	int* testArray = new int[ARR_SIZE];
	const int elements_per_proc = (ARR_SIZE/world_size);
	int* recv_buffer = new int[elements_per_proc];
	
	//Root processor assigns random number to arrays
	if(world_rank == 0){
		for(int i = 0; i < ARR_SIZE; i++){
			testArray[i] = rand()%100;
		}
	}

	//Start timer
	auto start = std::chrono::high_resolution_clock::now();

	//Send partitioned data from test Array to processors
	MPI_Scatter(testArray, elements_per_proc, MPI_INT, recv_buffer, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

	//Merge on every processor
	mergeSort(recv_buffer, 0, elements_per_proc-1);
	
	//Gather all of the sorted "Sub-arrays" back into the root
	MPI_Gather(recv_buffer, elements_per_proc, MPI_INT, testArray, elements_per_proc,MPI_INT, 0, MPI_COMM_WORLD);

	if(world_rank == 0){
		//After gathering "Sub-arrays" into root, perform final merges
		for( int i = 1; i < world_size; i++){
			merge(testArray, 0, i * elements_per_proc-1, (i + 1) * elements_per_proc -1);
		}

		//End timer
		auto stop = std::chrono::high_resolution_clock::now();
		
		//Calculate time taken
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
	}
	
	//De-allocate memory
	delete[] testArray;
	delete[] recv_buffer;

	
	MPI_Finalize();
	return 0;
}


//void printArray(int A[], int size)
//{
//    for (int i = 0; i < size; i++)
//        printf("%d ", A[i]);
//    printf("\n");
//}


//Just normal merge sort
void merge(int arr[], int left, int mid, int right){
	int n1 = mid-left + 1;
	int n2 = right-mid;

	int L[n1], R[n2];

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



void mergeSort(int arr[], int left, int right){
	if(left >= right)
		return;

	int mid = left + (right-left)/2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid+1, right);
	merge(arr, left, mid, right);
}
