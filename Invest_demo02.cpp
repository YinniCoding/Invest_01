//first try
//1、在解决了第一个Subset的基础上，后面的Strong和Invest还是比较容易想到解决办法

/*
题意分析：
    Invest的每个元素对应的域pi比wi多10；
	如果每个满足条件的wi序列集合和为c的话，那么wi的元素个数越多，其对应的pi值便就越大
*/

/*
思路整理：
    在每次记录一组满足条件的wi序列集合时，添加count计数；

*/
#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
using namespace std;
int w[1000];  //存储已经给定的若干个数
int x[1000];  //以0和1来表示数是否加入当前序列
int M,sum=0; //sum为所有元素总和
//int p4,p5[100]={0}; //在此题条件下进行添加，count用于计数，p[]记录满足条件的最大的pi序列组
int static count=0,p[100];
/*
void Subset(int s,int k,int r，int M)

s表示当前选中的w[i]*x[i]的值，
k表示当前选择的第几个数，
r为所给元素之和，起到临时变量的作用
M为所给定值
*/

void Readfile() //读取.in文件,并求取所有元素的和
{
   ifstream infile("D://软件/数据结构与算法/大二下学期数据结构实习/invest/1000/1000/test.01.in",ios::in);
		if(!infile)
		{
		   cout<<"Error opening file!"<<'\t';
		   //exit(1);
	    }
	    int num,wi,pi;
	    //ofstream fout("D://软件/数据结构与算法/大二下学期数据结构实习/subset/1000/1000/test.01.in",ofstream::out);
	    int i=0;
	    while(infile.peek()!=EOF)
		{
			infile>>num>>wi>>pi;
			//cout<<wi<<'\t'<<pi<<'\n';
			w[i]=wi;
			sum+=w[i++];
		}
}
int Partition(int r[],int first,int end)    //快速排序第一次划分
{
	int i=first;       //初始化
	int j=end;
	while(i<j)
	{
		while(i<j && r[i]<=r[j]) j--;     //右侧扫描
		if(i<j)
		{
			int temp=r[i];
			r[i]=r[j];
			r[j]=temp;
			i++;
		}
		while(i<j && r[i]<=r[j]) i++;     //左侧扫描
		{
			if(i<j)
			{
				int temp2;
				temp2=r[i];
				r[i]=r[j];
				r[j]=temp2;
				j--;
			}
		}
	}
	return i;
}
void QuickSort(int r[],int first,int end)
{
	if(first<end)
	{
		int pivot;
		pivot=Partition(r,first,end);    //一次划分
		QuickSort(r,first,pivot-1);         //递归对左侧序列进行排序
		QuickSort(r,pivot+1,end);           //递归对右侧序列进行排序
	}
}
void Subset(int s,int k,int r,int M) {
	
	x[k]=1;
	if(s+w[k]==M)  //如果结果等于M,则输出结果
	{
	   int count2,p2[1000];
	   for(int i=0;i<=k;i++) {
	   	//控制值输出x[i]=1,即已经加入数组的数
	   	//添加进count进行计数，一旦遇到更大的count，便进行p[]数组覆盖
		count2=0,p2[1000]={0};   //临时计数以及临时数组
	   	if(x[i]==1)
		{
		  p2[count2++]=w[i];
		  cout<<w[i]<<'\t';
		}
	   }
	   	cout<<'\n';
	   	if(count2>=count) {
	   	   	count=count2;
	   	   	for(int j=0;j<count2;j++)
	   	   	p[j]=p2[j];
		}
	}
	else if(s+w[k]+w[k+1]<=M) //当往后添加两个元素时，结果仍然<=M,则将当前的第k个元素加入s,k取下一元素，继续递归
	{ 
		Subset(s+w[k],k+1,r-w[k],M);
	}
	if ((s+r-w[k])>=M && (s+w[k+1])<=M) //当包括w[k]时，全体元素>=M,并且s+下一个元素的和<=M,则舍弃当前第k个元素，继续下一个
	{
	  x[k]=0;
	  Subset(s,k+1,r-w[k],M);
	}
}
int main() {
	//for(int i=0;i<10;i++)
	//w[i]=i+1;
	//w[10]={1,2,3,4,5,6,7,8,9,10};
	float r;
	cout<<"请输入指定在0-1范围内的一个r："<<'\n';
	cin>>r;
	Readfile();
	cout<<"所有wi总和为："<<sum<<'\n';
	int c=r*sum;
	cout<<"根据所给r确定的c为："<<c<<'\n';
	QuickSort(w,0,999);
	cout<<"测试使用快排后的前10个数据："<<'\n';
	for(int i=0;i<10;i++)
	cout<<w[i]<<'\t';
	cout<<'\n';
	cout<<"所有可能序列元素之为"<<c<<"的具体组合如下：\n";
	Subset(0,0,sum,c);
	cout<<"invest中满足条件的对应pi序列组合为:\n";
	for(int j=0;j<count;j++)
	cout<<p[j]+10<<'\t';
	cout<<'\n';
	return 0;
}
