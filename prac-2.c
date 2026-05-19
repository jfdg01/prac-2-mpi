#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    int num, rango;
    MPI_Comm_size(MPI_COMM_WORLD, &num);
    MPI_Comm_rank(MPI_COMM_WORLD, &rango);

    if (num % 2 != 0) {
        if (rango == 0)
            printf("Se necesita un número par de procesos.\n");
        MPI_Finalize();
        return 0;
    }

    int es_par;
    if (rango % 2 == 0)
        es_par = 1;
    else
        es_par = 0;
    int mi_pareja;

    if (es_par)
        mi_pareja = rango+1;
    else
        mi_pareja = rango-1;

    int valor = 0;
    int contador = 0;

    while (contador < 3) {
        if (es_par) {
            printf("Soy el proceso %d y juego con el proceso %d. Recibo %d y envío %d\n", rango, mi_pareja, valor, valor+1);
            valor++;
            MPI_Send(&valor, 1, MPI_INT, mi_pareja, 0, MPI_COMM_WORLD);
            MPI_Recv(&valor, 1, MPI_INT, mi_pareja, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        else {
            MPI_Recv(&valor, 1, MPI_INT, mi_pareja, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Soy el proceso %d y juego con el proceso %d. Recibo %d y envío %d\n", rango, mi_pareja, valor, valor + 1);
            valor++;
            MPI_Send(&valor, 1, MPI_INT, mi_pareja, 0, MPI_COMM_WORLD);
        }
        contador++;
    }

    MPI_Finalize();
    return 0;
}
