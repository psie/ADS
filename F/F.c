// finding a minimal edge in maximal spanning tree
// Kruskal's algorithm: heap + union find
#include <stdio.h>
#include <limits.h>

#define DATASIZE 1000000
#define HEAPSIZE 1048576 // 2^20

typedef struct {
	int a, b, w;
} edge; 

edge heap[HEAPSIZE+1]; 

int m;
int last;

void down_top_reheapify(int n)
{
	edge tmp;
	while(n!=1)
	{
		if(heap[n/2].w < heap[n].w)
		{
			tmp = heap[n/2];
			heap[n/2] = heap[n];
			heap[n] = tmp;
			n/=2;
		}
		else
			break;
	}
}

void top_down_reheapify(int n)
{
	edge tmp;
	while(n <= m/2)
	{
		if( heap[n*2].w > heap[n*2+1].w )
		{
			if( heap[n].w < heap[n*2].w )
			{
				tmp = heap[n*2];
				heap[n*2] = heap[n];
				heap[n] = tmp;
				n*=2;
			}
			else
				break;
		}
		else
		{
			if( heap[n].w < heap[n*2+1].w )
			{
				tmp = heap[n*2+1];
				heap[n*2+1] = heap[n];
				heap[n] = tmp;
				n=n*2+1;
			}
			else
				break;
		}
	}
}

void heap_insert(edge e)
{
	heap[last] = e;
	down_top_reheapify(last);
	last++;
}

void heap_delmax()
{
	heap[1].w = 0;
	top_down_reheapify(1);
}

int parent[DATASIZE+1];
int rank[DATASIZE+1];

// find with path compression
int find(int e)
{
	if(parent[e] != e)
		parent[e] = find(parent[e]);
	return parent[e];
}

// union with ranks to join smaller trees under bigger
int uni(int e1, int e2)
{
	int r1, r2;
	r1 = find(e1);
	r2 = find(e2);

	if(r1 == r2)
		return 0;

	if(rank[r1] < rank[r2])
		parent[r1] = r2;
	else if( rank[r1] > rank[r2] )
		parent[r2] = r1;
	else
	{
		parent[r2] = r1;
		rank[r1]++;
	}
	return 1;
}

int main()
{
	int n;
	int i, u, v, min;
	edge tmp;

	scanf("%d%d", &n, &m);

	last = 1;
	for(i=0; i<m; ++i)
	{
		scanf("%d%d%d", &tmp.a , &tmp.b, &tmp.w);

		parent[tmp.a] = tmp.a;
		parent[tmp.b] = tmp.b;

		heap_insert(tmp);
	}

	// make m a power of 2
	i=1<<30;
	while(!(i&m))
		i>>=1;
	i<<=1;
	m=i;

	// Kruskal's algorithm
	min = INT_MAX;
	i=1;
	while(i < n)
	{
		u = find(heap[1].a);
		v = find(heap[1].b);
		if(uni(u, v))
		{
			if(heap[1].w < min)
				min = heap[1].w;
			i++;
		}
		heap_delmax();
	}
	
	printf("%d\n", min);

	return 0;
}
