//�˳���ΪJXL��д��C++���Եĳ��򣬿������쳲��������У��ص��ǲ������Ա�����ݽṹ����ӷ����㣬��ÿһλ���������㣬����λ�����������int��long int����unsigned long int(0~2^32-1=4294967295)�ľ��ȷ�Χ���ƣ����㷨�ľ��ȷ�Χ��Ҫ������n(int)�ķ�Χ(1~2^31-1=2147483647)Ӱ��
#include<iostream>
using namespace std;
#define MAX 10240//���е�λ�����ֵ

class number
{
public:
	number()
	{
		data = '0';
		next = NULL;
	}
	unsigned char data;//Ϊ��ʡ�ռ俪����0~9����Ϊֻռһ��Byte��unsigned char�ͱ���
	number *next;
	void show()
	{
		number *p = this;
		number *(q[MAX]);//q�洢p������nextָ�룬��p��������
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
number *add(number *a, number *b)//aΪ��һ�������ͷָ�룬bΪ�ڶ��������ͷָ��
{
	number *c = new number;//cΪ�ӷ�����������ͷָ��
	number *p = new number;
	number *q = new number;
	number *r = new number;
	p = a;//pΪa��������˳���ƶ�����ʱָ��
	q = b;//qΪb��������˳���ƶ�����ʱָ��
	r = c;//rΪc��������˳���ƶ�����ʱָ��
	unsigned char temp = 0;//temp���ڴ洢�Ƿ��λ
	while (p || q || temp)
	{
		if (p&&q)//���������ж�Ӧλ����
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
			r->next = new number;//�˴���ѭ�������һ�β�����һ�����õ�number�����ɹ��캯����data=0
			r = r->next;
		}
		else if (p)//p���λ����q���λ����
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
			r->next = new number;//�˴���ѭ�������һ�β�����һ�����õ�number�����ɹ��캯����data=0
			r = r->next;
		}
		else if (q)//q���λ����p���λ����
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
			r->next = new number;//�˴���ѭ�������һ�β�����һ�����õ�number�����ɹ��캯����data=0
			r = r->next;
		}
		else//temp=1&&p=NULL&&q=NULL
		{
			r->data = temp + 48;
			temp = 0;
			r->next = new number;//�˴���ѭ�������һ�β�����һ�����õ�number�����ɹ��캯����data=0
			r = r->next;
		}
	}
	for (r = c; r->next->next != NULL; r = r->next){};//ɾ��������whileѭ�������һ�β���������number��
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
	cout << "��ΪJXL��ĸ߾���쳲����������㷨С����������Ҫ�����ǰn�������n:(��Χ1~2147483647)\nn=";//2^31-1=2147483647
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cout << "��" << i << "�";
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
