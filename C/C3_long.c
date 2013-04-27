// estimating possible values of coins given a sum of its weights
// - an unbounded knapsack problem with exact weight 
// a dynamic programming solution in O(n*W) time

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//#define DEBUG

typedef struct coin{int value, weight, i;} coin;
typedef struct best{int weight, id;} best;
coin C[100];

int chosen[100]; //400B
best best_minimal[100001]; //800kB
best best_maximal[100001]; //800kB
long long minimal[100001]; //800kB
long long maximal[100001]; //800kB

int cmp(const void *p1, const void *p2)
{
	if(((coin*)p1)->weight > ((coin*)p2)->weight)
		return 1;
	if(((coin*)p1)->weight == ((coin*)p2)->weight)
	{
		if(((coin*)p1)->value > ((coin*)p2)->value)
			return 1;
		else
			return -1;
	}
	return -1;
}

int main()
{
	int total, coins;
	int i, j;

	scanf("%d%d", &total, &coins);
	for(i=0; i<coins; ++i)
	{
		scanf("%d%d", &C[i].value, &C[i].weight);
		C[i].i=i;
	}

	qsort(C, coins, sizeof(coin), cmp);

	#ifdef DEBUG
		for(i=0; i<coins; ++i)
			printf("%d %d\n", C2[i].value, C2[i].weight);
	#endif

	for(i=0; i<=total; ++i)
		minimal[i] = LLONG_MAX; 

	//for(i=0; i<=total; ++i)
	//	maximal[i] = 0;
	
	j = 0;
	for(i=0; i<coins; ++i)
	{
		if(C[i].weight == j)
			continue;
		j = C[i].weight;
		minimal[j] = C[i].value;
		best_minimal[j].id = C[i].i;
		best_minimal[j].weight = j;
	}

	j = 0;
	for(i=coins-1; i>=0; --i)
	{
		if(C[i].weight == j)
			continue;
		j = C[i].weight;
		maximal[j] = C[i].value;
		best_maximal[j].id = C[i].i;
		best_maximal[j].weight = j;
	}


	for(i=0; i<coins; ++i)
	{
		for(j=C[i].weight+1; j<=total; ++j)
		{ 	
			if(minimal[j-C[i].weight] != LLONG_MAX)
			{
				if(minimal[j] > minimal[j-C[i].weight] + C[i].value) 
				{
					minimal[j] = minimal[j-C[i].weight] + C[i].value; 
					best_minimal[j].id = C[i].i;
					best_minimal[j].weight = C[i].weight;
				}
			}
			
			if(maximal[j-C[i].weight] != 0)
			{
				if(maximal[j] < maximal[j-C[i].weight] + C[i].value)
				{
					maximal[j] = maximal[j-C[i].weight] + C[i].value;
					best_maximal[j].id = C[i].i;
					best_maximal[j].weight = C[i].weight;
				}
			}
		}
	}

	/* MINIMAL */

	if(minimal[total] == LLONG_MAX)
	{
		printf("NIE\n"); // not possible to match given weight
		#ifndef DEBUG
			return 0;
		#endif
	}
	else
		printf("TAK\n");

	/*for(i=0; i<total; ++i)
		chosen[i]=0;*/
	i=total;
	while(i>0)
	{
		chosen[best_minimal[i].id]++;
		i -= best_minimal[i].weight;
	}
	
	printf("%lld\n", minimal[total]);
	for(i=0; i<coins; ++i)
		printf("%d ", chosen[i]);

	printf("\n");

	/* MAXIMAL */
	
	for(i=0; i<total; ++i)
		chosen[i]=0;
	i=total;
	while(i>0)
	{
		chosen[best_maximal[i].id]++;
		i -= best_maximal[i].weight;
	}
	
	printf("%lld\n", maximal[total]);
	for(i=0; i<coins; ++i)
		printf("%d ", chosen[i]);
		
	return 0;
}
