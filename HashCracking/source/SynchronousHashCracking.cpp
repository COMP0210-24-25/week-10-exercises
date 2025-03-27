#include <cstdio>
#include "RubbishHash.h"
#include <mpi.h>

enum MpiTags
{
    found_key,
    stop_work
};

int main()
{
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n_ranks;
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);

    unsigned long hash = 504981L;

    const int N = 12000;

    unsigned int x_min = N / n_ranks * rank;

    unsigned int x_max = (N / n_ranks) * (rank + 1);
    if(rank == (n_ranks - 1))
    {
        x_max = N;
    }

    unsigned int key = 0;
    int winner = 0;

    bool solved = false;
    bool* found = new bool[n_ranks];
    for(int i = 0; i < n_ranks; i++)
    {
        found[i] = false;
    }

    for(unsigned int i = x_min; i < x_max; i++)
    {

        if(rubbish_hash(i) == hash)
        {
            found[rank] = true;
            key = i;
        }
        
        MPI_Gather(&found[rank], 1, MPI_C_BOOL, found, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);

        if(rank == 0)
        {
            for (int r = 0; r < n_ranks; r++)
            {
                if (found[r])
                {
                    winner = r;
                    solved = true;
                }
            }
        }
        MPI_Bcast(&solved, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
        if(solved) break;
    }

    if(winner != 0)
    {
        if (rank == 0)
        {
            MPI_Recv(&key, 1, MPI_UNSIGNED, winner, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        else if (found[rank] == true)
        {
            MPI_Ssend(&key, 1, MPI_UNSIGNED, 0, 1, MPI_COMM_WORLD);
        }
    }

    if(rank == 0)
    {
        printf("Rank 0 was told that %d found x = %u\n", winner, key);
    }
    else
    {
        printf("Rank %d came to a graceful stop.\n", rank);
    }


    MPI_Finalize();

    return 0;
}