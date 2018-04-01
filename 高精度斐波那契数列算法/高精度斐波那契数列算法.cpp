//此程序为JXL编写的C++语言的程序，可以输出斐波那契数列，特点是采用线性表的数据结构处理加法运算，对每一位数进行运算，并进位，解决了由于int或long int甚至unsigned long int(0~2^32-1=4294967295)的精度范围限制，此算法的精度范围主要受项数n(int)的范围(1~2^31-1=2147483647)影响
#include<iostream>
using namespace std;
#define MAX 10240//数列的位数最大值

class number
{
public:
	number()
	{
		data = '0';
		next = NULL;
	}
	unsigned char data;//为节省空间开销将0~9定义为只占一个Byte的unsigned char型变量
	number *next;
	void show()
	{
		number *p = this;
		number *(q[MAX]);//q存储p的链表next指针，将p链表逆序
		int i = 0;
		while (p)
		{
			q[i] = p;
			p = p->next;
			i++;
		}
		for (i--; i >= 0; i--)    cout << (q[i])->data;
	}
	~number()
	{
		number *p = this, *q;
		while (p)
		{
			q = p;
			p = p->next;
			delete q;
		}
	}
};
number *add(number *a, number *b)//a为第一个链表的头指针，b为第二个链表的头指针
{
	number *c = new number;//c为加法运算后链表的头指针
	number *p = new number;
	number *q = new number;
	number *r = new number;
	p = a;//p为a所在链表按顺序移动的临时指针
	q = b;//q为b所在链表按顺序移动的临时指针
	r = c;//r为c所在链表按顺序移动的临时指针
	unsigned char temp = 0;//temp用于存储是否进位
	while (p || q || temp)
	{
		if (p&&q)//两个链表都有对应位的数
		{
			temp += (p->data - 48) + (q->data - 48);
			if (temp<10)
			{
				r->data = temp + 48;
				temp = 0;
			}
			else if (temp >= 10)
			{
				r->data = temp - 10 + 48;
				temp = 1;
			}
			p = p->next;
			q = q->next;
			r->next = new number;//此处在循环的最后一次产生了一个无用的number，且由构造函数得data=0
			r = r->next;
		}
		else if (p)//p表的位数比q表的位数多
		{
			temp += p->data - 48;
			if (temp<10)
			{
				r->data = temp + 48;
				temp = 0;
			}
			else if (temp >= 10)
			{
				r->data = temp - 10 + 48;
				temp = 1;
			}
			p = p->next;
			r->next = new number;//此处在循环的最后一次产生了一个无用的number，且由构造函数得data=0
			r = r->next;
		}
		else if (q)//q表的位数比p表的位数多
		{
			temp += q->data - 48;
			if (temp<10)
			{
				r->data = temp + 48;
				temp = 0;
			}
			else if (temp >= 10)
			{
				r->data = temp - 10 + 48;
				temp = 1;
			}
			q = q->next;
			r->next = new number;//此处在循环的最后一次产生了一个无用的number，且由构造函数得data=0
			r = r->next;
		}
		else//temp=1&&p=NULL&&q=NULL
		{
			r->data = temp + 48;
			temp = 0;
			r->next = new number;//此处在循环的最后一次产生了一个无用的number，且由构造函数得data=0
			r = r->next;
		}
	}
	for (r = c; r->next->next != NULL; r = r->next){};//删除由于在while循环中最后一次产生的无用number类
	r->next = NULL;
	return c;
}

int main()
{
	number *a = new number;
	number *b = new number;
	number *c = new number;
	int i, n;
	a->data = '1';
	b->data = '1';
	cout << "此为JXL编的高精度斐波那契数列算法小程序，请输入要输出的前n项的项数n:(范围1~2147483647)\nn=";//2^31-1=2147483647
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cout << "第" << i << "项：";
		if (i % 2)
		{
			a->show();
			cout << '\n';
			a = add(a, b);
		}
		else
		{
			b->show();
			cout << "\n";
			b = add(a, b);
		}
	}
	cout << endl;
	system("pause");
	return 0;
}
