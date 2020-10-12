#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  //Se inicializa el entorno MPI
  const int limite = 10;
  MPI_Init(NULL, NULL);
    //Se define my_rank y my_size  que serán los ids y el número de procesos

  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  int my_size;
  MPI_Comm_size(MPI_COMM_WORLD, &my_size);
  //Se emplean paramatros que se deben cumplir en este caso el numero de procesos no debe ser mayor a 3
  if (my_size != 3) {
    fprintf(stderr, "El tamaño debe ser 3 para: %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  // Posteriormente se realizan las operaciones de envío y recibimiento utilizando las instrucciones
  // MPI_Send y MPI_Recv
  int contador = 0;
  int rank_p = (my_rank + 1) % 3;
  while (contador < limite) {
    if (my_rank == contador % 3) {
      contador++;
      MPI_Send(&contador, 1, MPI_INT, rank_p, 0, MPI_COMM_WORLD);
      printf("%d Contador enviado e incrementado %d a %d\n",
             my_rank, contador, rank_p);
    } else {
      contador++;
      MPI_Recv(&contador, 1, MPI_INT, rank_p, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      printf("%d Contador recibido %d desde %d\n",
             my_rank, contador, rank_p);
    }
  }
  MPI_Finalize();
}
