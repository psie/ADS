// printing first k maximal numbers from a multiplication table of
// size m - heap data structure implementation

#include <stdio.h>

//#define DEBUG

typedef struct element {
	int x,y;
} field;

field heap[1000000]; // 8MB

void addnext(int c, int *m)
{
	if(heap[c].y > heap[c].x)
		heap[c].y--;
	else
	{
		heap[c] = heap[*m-1];
		
		heap[*m-1].x=0;
		heap[*m-1].y=0; 

		if((*m+1)%2)
			m-=2;
	}

	#ifdef DEBUG
	printf("-[+] %d:%d:%ld-\n", heap[c].x, heap[c].y, (long long) heap[c].x*heap[c].y);
	#endif
	
}

void relax(int c, int *m)
{
	int g;
	field tmp;

	while((c+1)*2+1 <= *m)
	{
		if((long long)heap[(c+1)*2-1].x*heap[(c+1)*2-1].y > (long long)heap[(c+1)*2].x*heap[(c+1)*2].y)
			g = (c+1)*2-1;
		else
			g = (c+1)*2;

		if((long long)heap[c].x*heap[c].y < (long long)heap[g].x*heap[g].y)
		{
			tmp = heap[c];
			heap[c] = heap[g];
			heap[g] = tmp;
		}
		else
			return;
		c = g;
	}
}

#ifdef DEBUG
void printheap(int m)
{
	    int i;
		for(i=0;i<m;++i)
			printf("%d:%d:%ld ", heap[i].x, heap[i].y, (long long)heap[i].x*heap[i].y);
		printf("\n");
}
#endif

int main()
{
	int m,k;
	int i;
	long long last = 0;

	scanf("%d%d", &m, &k);

	for(i=1; i<=m; ++i)
	{
		heap[i-1].x = m-(i-1);
		heap[i-1].y = m;
	}
	

	while(k>0)
	{
		#ifdef DEBUG
		printheap(m);
		#endif

		if(last == (long long)heap[0].x*heap[0].y)
		{
			addnext(0, &m);
			relax(0, &m);
			continue;
		}

		printf("%lld\n", (long long)heap[0].x*heap[0].y);
		last = (long long)heap[0].x*heap[0].y;

		addnext(0, &m);
		relax(0, &m);
		k--;
	}

	return 0;
}
