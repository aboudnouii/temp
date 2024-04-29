#include<stdio.h>
#include<stdlib.h>

typedef struct pdt {
    int state; // 0-free 1-not free
    int size; // of partition
    int nom_p; // le nom de chaque processus
    int num;
} pdt;

typedef struct wq {
    int num_proc; // le nom de chaque process
    int size_proc; // size de chaque process
} wq;

void display_pdt(pdt s[40], int Npa) {
    int j;
    for(j = 0; j < Npa; j++) {
        printf("the partition nbr %d\n", s[j].num);
        printf("the size of partition is %d and the state is %d and the name of the process is %d \n", s[j].size, s[j].state, s[j].nom_p);
    }
}

void display_wq(wq l[10], int Npr) {
    int k;
    for(k = 0; k < Npr; k++) {
        printf("the name of the process nbr %d is %d and his size is %d \n", k+1, l[k].num_proc, l[k].size_proc);
    }
}
        int fragext = 0;
int fragmentation(int size,int psize,int name) {
    int fragint;
            fragint = size - psize;
            if(size !=0 && psize !=0 && name != 0 )
            printf("the fragmentation internal for the partition %d is %d \n",name , fragint);
            fragext += fragint;
    return fragext;
}
void f_f(pdt n[40], int NPa, wq p[10], int NPr) {
    int x;
    int j;
    int b;
    for(int i = 0; i < NPr; i++) {
        x = p[i].size_proc;
        j = 0;
        b = 0;
        while(j < NPa && b == 0) { 
            if(n[j].state != 0) {
                j++;
            } else {
                if(n[j].size < x) {
                    j++;
                } else {
                    n[j].state = 1;
                    n[j].nom_p = p[i].num_proc;
                    b = 1;
                    fragmentation(n[j].size,p[i].size_proc,n[j].nom_p);
                }
            }
        }
    }
    printf("External fregmantation is %d",fragmentation(0,0,0));
}
void bestFit(pdt P[],int n,wq Q[],int m)
{
    wq temp;
    int b=0;
    while(b==0)
    b=1;
    for(int i = 0; i < m-1)
    {
            if (Q[i].size_proc >= Q[i+1].size_proc && Q[i].num_proc != -1 )
            {
                temp = Q[i];
                Q[i]=Q[i+1];
                Q[i+1]=temp;
                b=0;
            }
    }
	for (int i = 0; i < m; i++)
	{
		int x = -1;
		for (int j = 0; j < n; j++)
		{
			if (P[j].size >= Q[i].size_proc && P[j].state==0 && Q[i].num_proc != -1 )
			{
				if (x == -1)
					x = j;
				else if (P[x].size > P[j].size)
					x = j;
			}
		}
		if (x != -1)
		{
        P[x].state =1;
        printf("Process %d is allocated in partition %d \n",Q[i].num_proc,P[x].num);
        P[x].nom_p=Q[i].num_proc;
        fragmentation(P[x].size,Q[i].size_proc,P[x].nom_p);
            Q[i].size_proc=-1;
            Q[i].num_proc=-1;
		}
	}
        printf("External fregmantation is %d",fragmentation(0,0,0));
}
void deallocation(pdt r[40]) {
    int z;
    printf("enter the number of partition that you want to delete: ");
    scanf("%d", &z);
    if(r[z-1].state != 0) {
        r[z-1].state = 0;
        r[z-1].nom_p = -1;
    } else {
        printf("Partition is already free.\n");
    }
}


int main() {
    int i;
    int npa; // nbr of partition
    int npr; // nmbr of processus
    int choix; // le menu
    
    
    
    printf("enter the number of partitions: \n");
    scanf("%d", &npa);
    pdt t[npa];
    for(i = 0; i < npa; i++) {
        printf("enter the size of partition %d: \n", i+1);
        scanf("%d", &t[i].size);
        t[i].state = 0; // Set state to free
        t[i].nom_p = -1; 
        t[i].num=i+1;
    }

    printf("enter the number of processes: \n");
    scanf("%d", &npr);
    wq s[npr];
    for(i = 0; i < npr; i++) {
        printf("enter the name of process %d: \n", i+1);
        scanf("%d", &s[i].num_proc);
        printf("enter the size of process %d: \n", i+1);
        scanf("%d", &s[i].size_proc);
    }

    do {
        printf("\t\t\t\t\t***** Menu *****\n");
        printf("\t\t\t\t\tfor allocation with best fit tap 1\n");
        printf("\t\t\t\t\tfor allocation with first fit tap 2\n");
        printf("\t\t\t\t\tfor deallocation tap 3\n");
        printf("\t\t\t\t\tfor display the PDT tap 4\n");
        printf("\t\t\t\t\tfor display the WQ tap 5\n");
        printf("\t\t\t\t\tto exit tap any other number\n");
        scanf("%d", &choix);
        
        switch(choix) {
            case 1: 
            bestFit(t, npa, s, npr);
            break;
            case 2:
                f_f(t, npa, s, npr);
                break;
            case 3:
                deallocation(t);
                break;
            case 4:
                display_pdt(t, npa);
                break;
            case 5:
                display_wq(s, npr);
                break;
            default:
                exit(0); // Exit the program
        }
    } while(1);

    return 0;
}
