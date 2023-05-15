#include<stdio.h>
#include<limits.h>
#include <stdbool.h>
#include <stdlib.h>

// state space tree node
struct BranchNode
{
	// stores parent of present node
	// helps in tracing path
	struct BranchNode* parent;

	// stores cost of the root to present node
	int pathCost;

	// stores least promising cost
	int cost;

	// store worker number
	int workerID;

	// store Job ID
	int jobID;

	// Boolean array assigned will contains
	// info about available jobs
	bool *assigned;
	struct BranchNode* next;
};

// Function to allocate a new search tree node
// Here Person p is assigned to job
struct BranchNode* newNode(int p, int job, bool assigned[],
	struct BranchNode* parent, int N)
{
    //allocate memory to the node variable
	struct BranchNode* node = malloc(sizeof(struct BranchNode));
	//allocate memory to the assigned variable of node
	node->assigned = malloc(N);
	//assign assigned array to  assigned array of node
	for (int j = 0; j < N; j++)
		node->assigned[j] = assigned[j];
	node->assigned[job] = true;
    //set parent,workerID and jobID
	node->parent = parent;
	node->workerID = p;
	node->jobID = job;

    //return node
	return node;
}

// Function to find the least optional cost
// of node after person p is assigned to job.
int findCost(int N, int costMatrix[N][N], int p,
	int job, bool assigned[])
{
	int cost = 0;

	// to store unavailable jobs
	bool *available = malloc(N);

	for (int i = 0; i < N; i++)
		available[i] = true;

	// start from next worker
	for (int i = p + 1; i < N; i++)
	{
		int min = INT_MAX, minIndex = -1;
		// do for each job
		for (int j = 0; j < N; j++)
		{
			// if job is unassigned
			if (!assigned[j] && available[j] &&
				costMatrix[i][j] < min)
			{
				// store job number
				minIndex = j;

				// store cost
				min = costMatrix[i][j];
			}
		}

		// add cost of next worker
		cost += min;

		// job becomes unavailable
		available[minIndex] = false;
	}
	return cost;
}



// print job assigned to each person
void printPersonWithJob(struct BranchNode *min)
{
    //check parent is NULL or not
	if (min->parent == NULL)
		return;
    //recursive call of the function
	printPersonWithJob(min->parent);
	//print Person id with job Id
	printf("%c:%d ", (min->workerID + 'a'), (min->jobID + 1));

}

// Finds minimum cost using Branch and Bound.
void findMinCost(int N, int costMatrix[N][N])
{
	// Create a priority queue to store live nodes of
	// search tree;
	struct BranchNode* minHeapRoot = NULL;

	// initialize heap to dummy node with cost 0
	bool *assigned = malloc(N);

	for (int i = 0; i < N; i++)
		assigned[i] = false;
	struct BranchNode* root = newNode(-1, -1, assigned, NULL, N);
	root->pathCost = root->cost = 0;
	root->workerID = -1;

	// Add dummy node to list of live nodes;
	minHeapRoot = root;

	// Finds a live node with least cost,
	// add its childrens to list of live nodes and
	// finally deletes it from the list.
	while (minHeapRoot != NULL)
	{

		// Find a live node with least estimated cost
		struct BranchNode* min = minHeapRoot;

		// The found node is deleted from the list of
		// live nodes
		minHeapRoot = minHeapRoot->next;

		// i stores next worker
		int i = min->workerID + 1;

		// if all workers are assigned a job
		if (i == N)
		{
		    //print  optional cost
			printf("%d\n", min->cost);
			//call the function to print Person id with job Id  
			printPersonWithJob(min);
			return;
		}

		// do for each job
		for (int j = 0; j < N; j++)
		{

			// If unassigned
			if (!min->assigned[j])
			{
				// create a new tree node
	struct BranchNode* child = newNode(i, j, min->assigned, min, N);

		// cost for ancestors nodes including current node
		child->pathCost = min->pathCost + costMatrix[i][j];

				// calculate its lower bound
				child->cost = child->pathCost +
					findCost(N, costMatrix, i, j, child->assigned);

				// Add child to list of live nodes;
				if (minHeapRoot == NULL)
					minHeapRoot = child;
				else
				{
				    //
					if (minHeapRoot->cost > child->cost)
					{
						child->next = minHeapRoot;
						minHeapRoot = child;
					}
					else
					{
						struct BranchNode* t = minHeapRoot->next;
						struct BranchNode* p = minHeapRoot;
						while (t != NULL && t->cost < child->cost)
						{
							p = t;
							t = t->next;
						}
						child->next = t;
						p->next = child;
					}
				}


			}
		}
	}
}

// Driver code
int main()
{
	//declaring to store number of persons/jobs
	int N;
	//declaring varibles for loops
	int i, j;
	//read number of persons/jobs
	scanf("%d", &N);
    //declare cost matrix
	int costMatrix[N][N];

	//read matrix
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			scanf("%d", &costMatrix[i][j]);

	//call function to find min cost
	findMinCost(N, costMatrix);

	return 0;
}