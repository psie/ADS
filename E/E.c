// finding 2D intersection with maximal summaried value
// sweeping in one dimension and full binary tree in other (after compression)
#include <stdio.h>
#include <stdlib.h>

#define DATASIZE 100000
#define RANGE DATASIZE*2

typedef struct node node;
struct node { 
	int val;
	int max;
}; // 8B

node tree[4*RANGE*2]; // sould be next power of two larger then 2*n
						// but I want to keep an empty level below leaves
						// for simplicity reasons (less checking), thus
						// 4*RANGE

typedef struct {
	int *x1, *x2, w, y;
} pre;

pre data[DATASIZE*2]; // two for each rectangle
					  // one with begenning in y with positive value w
					  // second ending with -w

typedef struct {
	int x, *ptr;
} cmprs;

int xses[DATASIZE*2]; // to store actual x values
cmprs xcompression[DATASIZE*2]; // for sorting and later compressing

int leaves;

void update_upstream(int p)
{
	while(p>=1)
	{
		tree[p].max = tree[p].val + 
		((tree[2*p].max > tree[2*p+1].max)? tree[2*p].max:tree[2*p+1].max);

		p/=2;
	}
}

void insert(pre *i)
{
	int x1, x2, w;
	//assuming x1<x2
	x1 = leaves+*i->x1;
	x2 = leaves+*i->x2;
	w = i->w;

	// update leaves
	tree[x1].val += w;
	tree[x1].max += w;
	tree[x2].val += w;
	tree[x2].max += w;

	// identify all basic intervals and update them 
	while(x1/2 != x2/2)
	{
		if(x1 % 2 == 0) // left son
		{
			tree[x1+1].val += w;
			
			tree[x1+1].max = tree[x1+1].val + 
				((tree[(x1+1)*2].max > tree[(x1+1)*2+1].max)?
				 tree[(x1+1)*2].max : tree[(x1+1)*2+1].max);
		}
			
		if(x2 % 2 == 1) // right son
		{
			tree[x2-1].val += w;

			tree[x2-1].max = tree[x2-1].val + 
				((tree[(x2-1)*2].max > tree[(x2-1)*2+1].max)?
				 tree[(x2-1)*2].max : tree[(x2-1)*2+1].max);
		}

		x1/=2;
		x2/=2;
	}

	update_upstream(leaves+*i->x1);
	update_upstream(leaves+*i->x2);
}

int cmpx(const void *v1, const void *v2)
{
	return (((cmprs*)v1)->x > ((cmprs*)v2)->x )? 1:-1;
}

int cmpy(const void *v1, const void *v2)
{
	if( ((pre*)v1)->y > ((pre*)v2)->y )
		return 1;
	else if( ((pre*)v1)->y == ((pre*)v2)->y )
	{
		if( ((pre*)v1)->w < ((pre*)v2)->w )// not to miss any overlaps
			return 1; 					   // of rectangles only touching in y
		return -1;
	}
	else
		return -1;
}

int main()
{
	int n;
	int i, k;
	int max;

	scanf("%d", &n);

	for(i=0; i<2*n; i+=2)
	{	
		scanf("%d%d%d%d%d", &xses[i], &data[i].y, &xses[i+1],
				&data[i+1].y, &data[i].w);
		
		xcompression[i].x = xses[i];
		xcompression[i].ptr = &xses[i];
		xcompression[i+1].x = xses[i+1];
		xcompression[i+1].ptr = &xses[i+1];

		data[i].x1 = &xses[i];
		data[i].x2 = &xses[i+1];
		
		data[i+1].x1 = &xses[i];
		data[i+1].x2 = &xses[i+1];
		data[i+1].w  = -data[i].w;
	}

	// 'compress' rectangles in one dimension
	// to reduce space in my full binary interval tree
	qsort(xcompression, n*2, sizeof(cmprs), cmpx);
	
	k = 0;
	*xcompression[0].ptr=0;
	for(i=1; i<2*n; ++i)
	{
		if(xcompression[i].x > xcompression[i-1].x)
			k++;
		*xcompression[i].ptr=k;
	}
	
	// make k a power of 2
	i=1<<30;
	while(!(i&k))
		i>>=1;
	i<<=1;
	k=i;

	leaves = k;

	// sort by y to implement sweeping in y axis
	qsort(data, n*2, sizeof(pre), cmpy);
	
	max = 0;
	for(i=0; i<n*2; ++i)
	{
		insert(&data[i]);
		if(tree[1].max > max)
			max = tree[1].max;
	}

	printf("%d\n", max);

	return 0;
}
