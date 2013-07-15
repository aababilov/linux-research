#include <mpi.h>
#include <stdio.h>

#define WORKTAG 1
#define DIETAG 2

typedef int unit_of_work_t;
typedef double unit_result_t;
/* Local functions */

static void master(void);
static void slave(void);
static unit_of_work_t get_next_work_item(void);
static void process_results(unit_result_t result);
static unit_result_t do_work(unit_of_work_t work);

static int myrank;

void parg(int argc, char **argv)
{
	int i;
	for (i = 0; i < argc; ++i) {
		printf("%d: %s\n", i, argv[i]);
	}
}

int main(int argc, char **argv)
{

	/* Initialize MPI */
	parg(argc, argv);
	MPI_Init(&argc, &argv);
	parg(argc, argv);
	/* Find out my identity in the default communicator */

	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	if (myrank == 0) {
		master();
	} else {
		slave();
	}

	/* Shut down MPI */
	printf("finr....\n");
	MPI_Finalize();
	return 0;
}

static void master(void)
{
	int ntasks, rank;
	unit_of_work_t work;
	unit_result_t result;
	MPI_Status status;
	char buf[2] = "w";
	/* Find out how many processes there are in the default
	 communicator */

	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
	printf("master ssend\n");
	fflush(stdout);
	MPI_Ssend(buf, 1, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
	printf("master ssend returned\n");
	fflush(stdout);
}

static void slave(void)
{
	unit_of_work_t work;
	unit_result_t result;
	MPI_Status status;
	char buf[2];
	int i;
	MPI_Request req;
	MPI_Irecv(buf, 2, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &req);
//	MPI_Wait(&req, &status);
	for (i = 0; i < 3; ++i) {
		printf("sleep #%d\n", i);
//		sleep(3);
	}
	MPI_Wait(&req, &status);
}
