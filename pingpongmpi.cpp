#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  const int limite = 10;
  MPI_Init(NULL, NULL);
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  int my_size;
  MPI_Comm_size(MPI_COMM_WORLD, &my_size);
  if (my_size != 3) {
    fprintf(stderr, "El tamaño debe ser 3 para: %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int contador = 0;
  int partner_rank = (my_rank + 1) % 2;
  while (contador < limite) {
    if (my_rank == contador % 2) {
      MPI_Send(&contador, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
      printf("%d Contador enviado e incrementado %d a %d\n",
             my_rank, contador, partner_rank);
    } else {
      MPI_Recv(&contador, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      contador++;
      printf("%d Contador recibido %d desde %d\n",
             my_rank, contador, partner_rank);
    }
  }
  MPI_Finalize();
}
