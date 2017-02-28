/* 在回溯法解决的前提下，尝试更加完善地使用二叉树实现，具体逻辑如下 
老师的提示是，将所有元素从大到小进行排序后，依次架构最大的元素放入待测数组中，直到接近c的最大值
这样子与c还有一定的差距，可以想到是一个小的值，下面就是要寻找到这个小的值，如果找到，就加入并且输出这个数组
如果查找不到便舍弃当前数组最后一个元素值，选取小于当前的元素的最大元素，接着重复上步。这一步即为递归调用 
一次找到满足条件的wi数组后， 
/*
具体逻辑设计：
     如果原始读取的数据已经有序排列好的话，那么可以利用结构体将每个序号的元素封装起来
	 先将所有元素存储到结构体数组中，并且按照wi列的值进行降序排序
	 开始 
*/ 

#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
#include <cstdlib>
#define N 1000 
using namespace std;

int x[1000];  //以0和1来表示数是否加入当前序列
int static count3=0; //用于记录满足条件的wi序列的组合数 
int static count=0,P[100]={0}; //在此题条件下进行添加，count用于计数，p[]记录满足条件的最大的pi序列组
//使用结构体封装每组数据，具体域为序号、wi值、pi值 
struct Row{
	int RowNum;    //序号 
	int WiValue;    //对应序号左域wi值 
	int PiValue;    //对应序号右域pi值 
};
/*
  设计一个ReadySet结构体用以存储每种满足条件的wi序列集合
  从根节点开始，依次附在下面
  每满足条件的一种情况输出后便销毁内存 
*/ 
struct ReadySet{
   struct Row *lchild;  //满足条件wi序列的左子树 
   struct Row *rchild;   	
};  
/*
设计一个子集类 
*/
class Subset{
	private:
		struct Row row01[N];   //测试使用并存储N组数据 
	    
		struct ReadySet *root=NULL; 
		//int count;   //用以统计满足条件的wi序列组合个数 
	public:
		int w[1000],p[1000];   //存储所有wi、pi的值 
		int sum;    //表示所有wi元素总和 
		
		 
		/*默认块*/
		Subset(); // 默认构造函数，读取.in文件，存入数据
		~Subset();  //析构函数 
		
		/*核心函数*/ 
		void SubsetSearch(int r[],int n);   //n为定值c 从大到小填充法 
		void SubsetSearch2(int s,int k,int r,int M);   // 回溯法 
		
        /*各种排序函数测试*/		
		void QuickSort(int r1[],int r2[],int first,int end);  //快速排序
		int Partition(int r1[],int r2[],int first,int end);  //快排第一次划分
		void ShellSort(int r1[],int r2[],int n);	 //希尔排序 
		void HeapSort(int r1[],int n);            //堆排序 
        void Sift(int r1[],int k,int m);   //调整为大根堆	
        void TimeTest(); 
		
		/*查找特定元素*/ 
		int BinSearch(int r[],int n,int k);   //零头元素简单采用二分查找
		//int GreatSearch(int r[],int n);   //特定查找 
		
		/**/ 
		void show1();   //展示读取的文件变更前后数据项 
};  
//构造函数读取.in文件的所有数据    
Subset::Subset() {
	    ifstream infile("D://软件/数据结构与算法/大二下学期数据结构实习/invest/1000/1000/test.01.in",ios::in);
		if(!infile)
		{
		   cout<<"Error opening file!"<<'\t';
		   exit(1);
	    }
	    else {
	    	cout<<"成功读取文件！测试文件为invest目录下test.01.in文件，共1000组数据！\n";
		}
	    sum=0;
	    int i=0;    //统计存入数据个数 
	    int num,wi,pi; //暂存每行数据
		while(infile.peek()!=EOF) {
			infile>>num>>wi>>pi;
			//按照字段存入到内存中 
			row01[i].RowNum=num;
			row01[i].WiValue=wi;
			row01[i].PiValue=pi;
			w[i]=wi; 
			p[i]=pi;
			i++;
		}
		
		//进行简单读取检测 
		cout<<"\n共存入数据"<<i-1<<"组\n";
		
		/*cout<<"输出前10组数据进行简单检测1:\n";
		for(int j=0;j<10;j++) {
		   cout<<row01[j].RowNum<<'\t'<<row01[j].WiValue<<'\t'<<row01[j].PiValue<<'\n';
		}*/
		w[0]=390; 
		p[0]=380;	
		for(int i=0;i<1000;i++)
		sum+=w[i];
	    cout<<"\nwi列所有元素总和为：\n";
	    cout<<sum<<'\n';	 
			 
}
Subset::~Subset() {
	
}

//搜寻最小值(零头)方法、按照从大到小填充 
void Subset::SubsetSearch(int r[],int n) {
	int static count=0;  //用于记录wi所有序列个数 
	int i,j;          //j用于记录不能再添加元素的最后一个元素位置
	int s1=0;       //已加进来前i个数的和
	for(i=0;i<N;i++) {
		s1+=w[i];
		//临界点条件 
		if(s1<n && (s1+w[i+1])>n) {
			j=i;              //记录最后一个位置
			//n-=s1;         //零头赋给n
			break; 
		}
	} 
	//寻找最小值
	int n2=n-s1;
	for(int k=j+1;k<N;k++) {
		if(n2>w[k]) break;
	    if(n==w[k]) {
	    	//count++; 
	    	cout<<"\n已找到满足条件的一种wi序列,其中序列元素个数唯一的元素为："<<w[k]<<",满足条件序列最多元素个数为："<<j+1<<'\n';
			return; 
		}	 
	} 
    //搜寻不到最小值
	for(int l=j;l>=0;l--) {
		n2=n-s1+w[l];    //逐步替换零头 
		int n3=n2/2,m;   //折取零头如合适并存储 
		for(int l2=j+1;l2<N;l2++) {
		    if(n3==w[l2] || (n3>w[l2] && n3<w[l2+1])) {
		    	m=l2;
			}	
			int m2=m-1;
			//从m分裂向两端进行检索 
			for(int l3=m2;l3>j;l3++) {
				for(int l4=m;l4<N;l4++) {
					if(w[l3]+w[l4]<n2) {
						//cout<<"当前情况未找到满足条件的wi序列!\n";
						break; 
					}
					if(w[l3]+w[l4]==n2) {
						//count++;
						cout<<"\n已找到满足条件的一种wi序列,其中序列元素个数唯一的元素为："<<w[l4]<<",满足条件序列最多元素个数为："<<j+1<<'\n';
					}
				}
			}	
		}
	}
	//cout<<count<<'\n';
	cout<<"未找到满足条件wi序列！\n";	 
}
void Subset::SubsetSearch2(int s,int k,int r,int M) {
	x[k]=1;
	if(s+w[k]==M)  //如果结果等于M,则输出结果
	{ 
	   count3++;
	   int count2=0,p2[100]={0}; 
	   int j=0;
	   for(int i=0;i<=k;i++) {
	   	//控制值输出x[i]=1,即已经加入数组的数 
	   	if(x[i]==1) 
		   {
		    cout<<w[i]<<'\t';
		    count2++;
		    p2[j++]=w[i];
		   } 
	   }
	   	cout<<'\n';
	   	if(count2>count) {
	   		count=count2;
	   		//count4=j;
	   		for(int l=0;l<count;l++)
	   		P[l]=p2[l];
		   } 
	} 
	else if(s+w[k]+w[k+1]<=M) //当往后添加两个元素时，结果仍然<=M,则将当前的第k个元素加入s,k取下一元素，继续递归
	{
		SubsetSearch2(s+w[k],k+1,r-w[k],M);
	} 
	if ((s+r-w[k])>=M && (s+w[k+1])<=M) //当包括w[k]时，全体元素>=M,并且s+下一个元素的和<=M,则舍弃当前第k个元素，继续下一个 
	{
	  x[k]=0;
	  SubsetSearch2(s,k+1,r-w[k],M);	
	}
}
//快排  
int  Subset::Partition(int r1[],int r2[],int first,int end)    //快速排序第一次划分 
{
	int i=first;       //初始化 
	int j=end;
	while(i<j)
	{
		while(i<j && r1[i]<=r1[j]) j--;     //右侧扫描
		if(i<j)
		{
			int temp=r1[i];
			r1[i]=r1[j];
			r1[j]=temp;
			int temp3=r2[i];
			r2[i]=r2[j];
			r2[j]=temp3;
			i++;
		} 
		while(i<j && r1[i]<=r1[j]) i++;     //左侧扫描
		{
			if(i<j)
			{
				int temp2;
				temp2=r1[i];
				r1[i]=r1[j];
				r1[j]=temp2;
				int temp4=r2[i];
				r2[i]=r2[j];
				r2[j]=temp4;
				j--;
			}
		} 
	}
	return i; 
}
void Subset::QuickSort(int r1[],int r2[],int first,int end)
{
	if(first<end)
	{
		int pivot;
		pivot=Partition(r1,r2,first,end);    //一次划分
		QuickSort(r1,r2,first,pivot-1);         //递归对左侧序列进行排序
		QuickSort(r1,r2,pivot+1,end);           //递归对右侧序列进行排序 
	}
}
//希尔排序
void Subset::ShellSort(int r1[],int r2[],int n) {
	int r3[n+1],r4[n+1];
	for(int i=0;i<n;i++) {
		r3[i+1]=r1[i];
		//r4[i+1]=r2[i];
	} 
	
	for(int d=n/2;d>=1;d--)  //0号单元用作暂存单元，增量d进行直插排序 
	{ 
		for(int j=d+1;j<n;j++)
		{
			r3[0]=r3[j];    //暂存被插记录
			//r4[0]=r4[j];
			int k; 
			for(k=j-d;k>=0 && r3[0]<r3[k];k-=d) 
			   r3[k+d]=r3[k];
			   r3[k+d]=r3[0];
			   //r4[k+d]=r4[k];
			   //r4[k+d]=r4[0];
		} 
	}
	for(int l=0;l<n;l++) {
		r1[l]=r3[l+1];
	}
	
} 
//堆排序
void Subset::HeapSort(int r1[],int n) {
	int r3[n+1];
	for(int k=0;k<1000;k++)
	r3[k+1]=r1[k];
	for(int i=n/2;i>=1;i--)
	Sift(r3,i,n);
	int temp;
	for(int j=1;j<n;j++)
	{
		temp=r3[1];
		r3[1]=r3[n-j+1];
		r3[n-j+1]=temp; 
		Sift(r3,1,n-j);
	}
	for(int l=0;l<1000;l++)
	r1[l]=r3[l+1];
} 
void Subset::Sift(int r1[],int k,int m) {
	int i=k;
	int j=2*i;
	while(j<=m)
	{
		if(j<m && r1[j]<r1[j+1]) j++;
		if(r1[i]>r1[j]) break;
		else 
		{
			int temp;
			temp=r1[i];
			r1[i]=r1[j];
			r1[j]=temp;
			i=j;
			j=2*i;
		}
	}
}

//二分查找 
int Subset::BinSearch(int r[],int n,int k)
{
	int low=1,high=n;           //设置查找区间，low为表最低位，high为最高位
	while(low<=high)
	{
		int mid;
		mid=(low+high)/2;
		if(k<r[mid]) high=mid-1;           //若待查找数小于中间数，查找区间压缩为左半边
		else if(k>r[mid]) low=mid+1;           //若待查找数大于中间数，查找区间压缩为右半边
		else return mid; 
    }
}
void Subset::TimeTest() {
	int i;
	cout<<"\n1、2、3依次表示快速排序、希尔排序、堆排序，选择其中一种来进行原始数据排序：\n";
	cin>>i;
	double start,end;
	switch(i) {
		case 1:
			start=clock();
			QuickSort(w,p,0,999);
			end=clock();
			cout<<"排序完成，使用快速排序共花费时间为："<<(end-start)<<"ms。\n";
			break;
		case 2: 
			start=clock();
			ShellSort(w,p,1000);
			end=clock();
			cout<<"wi列排序完成，使用希尔排序共花费时间为："<<(end-start)<<"ms。\n";
			break;
		case 3:
			start=clock();
			HeapSort(w,999);
			end=clock();
			cout<<"wi列排序完成，使用堆排序共花费时间为："<<(end-start)<<"ms。\n";
			break;
		default: 
		    cout<<"请按照要求进行输入！\n";
		    TimeTest();
	}
	
} 
void Subset::show1() {
    //QuickSort(obj.w,obj.p,0,999);
    //cout<<'\n';
	for(int i=0;i<10;i++)
	//cout<<row01[i].RowNum<<'\t'<<row01[i].WiValue<<'\t'<<row01[i].PiValue<<'\n';
	cout<<w[i]<<'\t'<<p[i]<<'\n';

}

int main()
{
	Subset test;
	cout<<"\n输出前10组数据进行简单测试，判断是否存储成功:\n";
	test.show1();
	//cout<<"\n测试快排后按照wi列从小到大前10组数据：\n";
	//test.QuickSort(test.w,test.p,0,999);
	test.TimeTest();
	//test.QuickSort(test.w,test.p,0,999); 
	cout<<"\n检测排序后的wi、pi序列：\n";
	test.show1(); 
    float r; 
	cout<<"\n请输入指定在0-1范围内的一个r："<<'\n';
	cin>>r;
	int c=r*test.sum;
	cout<<"根据所给r确定的c为："<<c<<'\n'; 
    cout<<"\n选择核心算法1运算结果如下：\n";
	cout<<"\n所有可能序列元素之为"<<c<<"的具体组合如下：\n"; 
	double start=clock(); 
	test.SubsetSearch2(0,0,test.sum,c);
	double end=clock();
	cout<<"核心算法1处理test.01.in的1000组数据共花费时间："<<(end-start)<<"ms。\n"; 
	cout<<"\n共有这样的组合"<<count3<<"组\n"; 
	cout<<"\n满足条件的wi组合对应的pi组合其和最大的序列为：\n";
	for(int j=0;j<count;j++)
	cout<<P[j]+10<<'\t';
	cout<<'\n';
    cout<<"\n选择核心算法2运算结果如下：\n";
    start=clock();
    test.SubsetSearch(test.w,c);
    end=clock();
	cout<<"\n核心算法2处理test.01.in的1000组数据共花费时间："<<(end-start)<<"ms。";
	return 0;
}
