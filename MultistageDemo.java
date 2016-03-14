//MULTISTAGE
import java.io.*;
import java.util.*;
class Multistage
{
public int stages,stage_vertices[],c[][];
public int cost[],p[],n;
public Multistage(int MAX)
{
c=new int[MAX][MAX];
stage_vertices=new int[MAX];
cost=new int[MAX];
p=new int[MAX];
}
public int Get_min(int s,int n)
{
int min=9999;//equal to infinity
int min_vertex=0;
for(int i=0;i<n;i++)
{
if(min>(c[s][i]+cost[i]))
{
min=c[s][i]+cost[i];
min_vertex=i;
}}
return min_vertex;
}
public void Forward(int n)
{
int i,r;
int d[];
d=new int[20];
for(i=0;i<n;i++)
cost[i]=0;//initalize graph by cost 0
for(i=n-2;i>=0;i--)
{
r=Get_min(i,n);
cost[i]=c[i][r]+cost[r];
d[i]=r;
}
p[0]=0;
p[stages-1]=n-1;
for(i=1;i<stages-1;i++)
p[i]=d[p[i-1]];
}
public void display( )
{
int i;
System.out.print(" Shortest path is...\n");
for(i=0;i<stages-1;i++)
System.out.print(" -- "+(p[i]+1));
System.out.print(" -- "+(p[i]+1));;//printing target node
}}
class MultistageDemo
{
public static void main (String[] args )throws IOException,NullPointerException
{
Multistage obj=new Multistage(20);

int n=0;
int i,j,m,p;
Scanner input=new Scanner(System.in);
System.out.print("\nEnter no of vertices: ");
n=input.nextInt();
System.out.print("\nEnter no of stages : ");
obj.stages=input.nextInt();
for(i=0;i<n;i++)
for(j=0;j<n;j++)
obj.c[i][j]=9999;//initialization
for(i=0;i<obj.stages;i++)
{

System.out.print("\nEnter no of vertices in stage "+(i+1)+": ");
obj.stage_vertices[i]=input.nextInt();
}
i=0;
j=obj.stage_vertices[0];
for(m=0;m<obj.stages;m++)
{
j=i+obj.stage_vertices[m];
for(;i<j;i++)
{
for(p=0;p<obj.stage_vertices[m+1];p++)
{
	
System.out.print("\nEnter cost for "+(i+1)+" to "+(p+j+1)+": ");
obj.c[i][p+j]= input.nextInt();//entering the corresponding cost
}}}
obj.Forward(n);
obj.display( );
}//end main
}
