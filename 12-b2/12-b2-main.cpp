//1850059 ��1�� ��־Զ

#include <iostream>
#include <iomanip>
#include "12-b2-linear_list_DL.cpp"
#include "12-b2-double1.h"
#include "12-b2-student.h"

using namespace std;

//�궨�������main�������Ե�ǰ���У��������ļ��еĴ����޹�
//#define ELEMTYPE_INT
//#define ELEMTYPE_STRING
//#define ELELTYPE_DOUBLE1
#define ELEMTYPE_STUDENT

#define INSERT_NUM		115		//��ʼ������е�Ԫ������
#define MAX_NUM_PER_LINE 	10		//ÿ����������Ԫ�ظ���

int line_count = 0;   //��ӡ����ʱ�ļ�����

/* ���ڱȽ�����ֵ�Ƿ���ȵľ��庯������LocateElem�еĺ���ָ�붨����ͬ������ʱ����
   int LocateElem(sqlist L, ElemType e, Status (*compare)(ElemType e1, ElemType e2)) */
template <class ElemType>
Status MyCompare(ElemType e1, ElemType e2)
{
	if (e1 == e2)
		return TRUE;
	else
		return FALSE;
}

/* ���ڷ���ĳ��Ԫ�ص�ֵ�ľ��庯������ListTraverse�еĺ���ָ�붨����ͬ������ʱ����
   Status ListTraverse(sqlist L, Status (*visit)(ElemType e)) */
template <class ElemType>
Status MyVisit(ElemType e)
{
#if defined ELEMTYPE_STUDENT
	cout << e << "->" << endl;
#else
	cout << setw(4) << e << "->";
	/* ÿ���MAX_NUM_PER_LINE������ӡһ������ */
	if ((++line_count) % MAX_NUM_PER_LINE == 0)
		cout << endl;
#endif
	return OK;
}

int main()
{
#if defined ELELTYPE_DOUBLE1
	LinkList<double1> L;
	double1 e1, e2;
	
#elif defined ELEMTYPE_STRING
	LinkList<string> L;
	string e1, e2;
#elif defined ELEMTYPE_STUDENT
	//student e[6];
	//e[0] = student(1001, "����", 'M', 76.5, "�Ϻ���������");	//������Բ������صȺ�
	//e[1] = student(1002, "����", 'F', 87, "�Ϻ���������");
	//e[2] = student(1003, "����", 'M', 80, "�㽭ʡ������");
	//e[3] = student(1004, "����", 'M', 54, "�㽭ʡ������");
	//e[4] = student(1005, "ţ��", 'F', 85, "����ʡ�Ͼ���");
	//e[5] = student(1006, "���", 'M', 60, "����ʡ������");
	LinkList<student> L;
	student e1, e2;
#else
	LinkList<int> L;
	int e1, e2;
#endif
	int i, pos, n = 0;

	cout << "�ձ�=" << ((L.ListEmpty() == TRUE) ? "TRUE" : "FALSE") << endl;
	cout << "��=" << L.ListLength() << endl;

	cout << "��Ҫ�����Ԫ�ظ�����";
	cin >> n;

	cout << "����" << n << "��Ԫ�أ�" << endl;

	for (i = 0; i < n; i++)
	{
		cin >> e1;
		L.ListInsert(L.ListLength() + 1, e1);
	}
	cin.clear();
	cin.ignore(9999, '\n');

	L.ListTraverse(MyVisit);//�˴�����MyVisit������

	cout << "�ձ�=" << ((L.ListEmpty() == TRUE) ? "TRUE" : "FALSE") << endl;
	cout << "��=" << L.ListLength() << endl;

	/* �ֱ�ȡ��1������Լ�С�ڵ�1����������4������µĵ�Ԫ��ֵ��ǰ��ֵ�����ֵ
	   ����ټ�һ����������ֵ */
	for (i = 0; i < 5; i++) {
		int pos;
		switch (i) {
			case 0:
				pos = 1;
				break;
			case 1:
				pos = L.ListLength();
				break;
			case 2:
				pos = -1;
				break;
			case 3:
				pos = L.ListLength() + 1;
				break;
			case 4:
				cout << "������ҪȡԪ�ص�λ��[1.." << L.ListLength() << "]��" << endl;
				cin >> pos;
				break;
		}

		if (L.GetElem(pos, e1) == OK) {
			cout << "��" << pos << "��Ԫ��=" << e1 << endl;

			/* ֻ��ȡ����ĳ��Ԫ�أ�����ȡǰ���ͺ�� */
			if (L.PriorElem(e1, e2) == OK)
				cout << "��" << pos << "��Ԫ��(" << e1 << ")��ǰ��=" << e2 << endl;
			else
				cout << "�޷�ȡ�õ�" << pos << "��Ԫ��(" << e1 << ")��ǰ��" << endl;

			if (L.NextElem(e1, e2) == OK)
				cout << "��" << pos << "��Ԫ��(" << e1 << ")�ĺ��=" << e2 << endl << endl;
			else
				cout << "�޷�ȡ�õ�" << pos << "��Ԫ��(" << e1 << ")�ĺ��" << endl << endl;
		}
		else
			cout << "�޷�ȡ�õ�" << pos << "��Ԫ��" << endl << endl;
	} // end of for

	cout << "������Ҫ���ҵ�Ԫ�أ�" << endl;
	cin >> e1;
	if ((pos = L.LocateElem(e1, MyCompare)) > 0)
		cout << "Ԫ��" << e1 << "��λ��=" << pos << endl;
	else
		cout << "�Ҳ���Ԫ��" << e1 << endl;
	cout << endl << "������Ҫ����Ԫ�ص�ֵ��" << endl;

	cin >> e1;
	cout << "������Ҫ����Ԫ�ص�λ��" << endl;
	cin >> pos;
	if (L.ListInsert(pos, e1) == OK) {
		cout << "��" << pos << "ǰ����Ԫ��" << e1 << "�ɹ�" << endl;
		cout << "�±�Ϊ��" << endl;
		L.ListTraverse(MyVisit);
	}
	else
		cout << "��" << pos << "ǰ����Ԫ��" << e1 << "ʧ��" << endl;

	cout << endl << "������Ҫɾ��Ԫ�ص�λ��" << endl;
	cin >> pos;
	if (L.ListDelete(pos, e1) == OK) {
		cout << "ɾ����" << pos << "Ԫ��=" << e1 << "�ɹ�" << endl;
		cout << "�±�Ϊ��" << endl;
		L.ListTraverse(MyVisit);
	}
	else
		cout << "ɾ����" << pos << "Ԫ��=" << e1 << "ʧ��" << endl;

	cout << endl << "��ձ�" << endl;
	L.ClearList();
	cout << "�ձ�=" << ((L.ListEmpty() == TRUE) ? "TRUE" : "FALSE") << endl;
	cout << "��=" << L.ListLength() << endl;

	return 0;
}