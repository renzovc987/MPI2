#include <mpi.h>

#include <stdio.h>


int main(int argc,char* argv[]){

    int id, total_proc;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&id);

    MPI_Comm_size(MPI_COMM_WORLD,&total_proc);

    printf("Hola Solvetic desde el proceso %d de un total de %d \n", id, total_proc);
    MPI_Finalize();

   return 0;
   

}