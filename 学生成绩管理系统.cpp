#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMELEN 10			//������󳤶�
#define MAX_COURSE 8			//�γ����������
#define MAX_STU 30				//ѧ���������


struct Data{
	int stuID;							//ѧ��
	char Name[MAX_NAMELEN] = { 0 };		//����
	float TotalScore;					//�ܳɼ�
	float AVGScore;						//ƽ���ɼ�
	float LScore[MAX_COURSE];			//���Ƴɼ�
};

typedef struct Node {			//������
	struct Data data;
	struct Node* next;
} Student;

Student* head = NULL;			//ȫ�ֶ�������head

int Menu();													//��ʾ�˵�
void AddData(int NumStudent, int NumCourse);				//���ѧ������
void ListInsert(Data data);									//������빦��
void DisplayStuData(int Course_Num, Student* p);			//��ʾѧ������
Student* SearchById(int Course_Num);						//��ѧ������
Student* SearchByName(int Course_Num);						//����������
void CourseAverSum(int Student_Num, int Course_Num);		//���㵥��ƽ���ɼ��ͳɼ��ֲ�
void SaveFile(int Course_Num);								//���浽txt�ļ���
void ReadFile();											//��txt�ļ��ж�ȡ����
void Operating(int Course_Num);								//���Ҳ��޸�ɾ��ѧ������
void EmptyList();											//�����������
void List_Initi(int row, int Course_Num);					//�����ʼ��
void JudgeFile(int* row, int* column);						//��ȡtxt�ļ������������

int main()
{
	int row = 0, column = 1;
	JudgeFile(&row, &column);							
	int i, NumStu = 0, NumCourse = column - 4, SumStu = row, NumCourse_Add = 0;
	List_Initi(row, NumCourse);
	while (true)
	{
		i = Menu();
		switch (i)
		{
		case 1:
			system("cls");
			printf("\t\t******************************************************************************\n");
			printf("\t\t������ѧ������:"); //����ѧ����
			printf("\t\t");
			scanf_s("%d", &NumStu);
			SumStu += NumStu;
			printf("\t\t������γ�����:");//����γ���
			printf("\t\t");

			scanf_s("%d", &NumCourse_Add);
			AddData(NumStu, NumCourse_Add);
			if (NumCourse_Add > NumCourse)//��¼����Ŀ��
			{
				NumCourse = NumCourse_Add;
			}
			system("pause");
			system("cls");
			break;
		
		case 2:
			system("cls");
			if (NumCourse > NumCourse_Add)
				DisplayStuData(NumCourse, head);
			else
				DisplayStuData(NumCourse_Add, head);
			system("pause");
			system("cls");
			break;
		
		case 3:
			system("cls");
			SearchById(NumCourse);
			system("pause");
			system("cls");
			break;

		case 4:
			system("cls");
			SearchByName(NumCourse);
			system("pause");
			system("cls");
			break;
		
		case 5:
			system("cls");
			CourseAverSum(NumStu, NumCourse);
			system("pause");
			system("cls");
			break;
		
		case 6:
			system("cls");
			Operating(NumCourse);
			system("pause");
			system("cls");
			break;
		case 7:
			system("cls");
			SaveFile(NumCourse);
			system("pause");
			system("cls");
			break;

		case 8:
			system("cls");
			ReadFile();
			system("pause");
			system("cls");
			break;
		
		case 9:
			system("cls");
			EmptyList();
			NumStu = 0;
			SumStu = 0;
			NumCourse = 0;
			printf("\t\t******************************************************************************\n");
			printf("\t\t���������\n ");
			printf("\t\t******************************************************************************\n");
			system("pause");
			system("cls");
			break;
		case 0:
			system("cls");
			printf("\n\n\n");
			printf("\t\t******************************************************************************\n");
			printf("\t\t��лʹ��,�������˳�\n ");
			printf("\t\t******************************************************************************\n");
			return 0;						//�����˳�
		default:
			system("cls");
			printf("\n\n\n");
			printf("\t\t******************************************************************************\n");
			printf("\t\t����ѡ����ڡ�\n");
			printf("\t\t******************************************************************************\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

int Menu()
{
	int i;
	system("title ѧ���ɼ�����ϵͳ by 1119096502@qq.com");
	printf("\n\n");
	printf("\t\t\t                         ѧ���ɼ�����ϵͳ\n");
	printf("\t\t******************************************************************************\n");
	printf("\t\t*                1.  ���ѧ����Ϣ                                            *\n");
	printf("\t\t*                2.  ��Ĭ��˳���ų�ѧ���ɼ���                                *\n");
	printf("\t\t*                3.  ͨ��ѧ�Ų�ѯѧ���ɼ�                                    *\n");
	printf("\t\t*                4.  ͨ��������ѯѧ���ɼ�                                    *\n");
	printf("\t\t*                5.  ����ÿһѧ�Ƶ��ֺܷ�ƽ����                              *\n");
	printf("\t\t*                6.  ��ѧ�����ݽ���ɾ��                                      *\n");
	printf("\t\t*                7.  �������µ��ļ�                                        *\n");
	printf("\t\t*                8.  ��ȡ�ļ�����                                            *\n");
	printf("\t\t*                9.  ɾ��ȫ������                                            *\n");
	printf("\t\t*                0.  �˳�                                                    *\n");
	printf("\t\t******************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t*****************������ѡ�����:");
	scanf_s("%d", &i);
	return i;
}

void List_Initi(int row, int Course_Num)//�����ʼ��
{
	FILE* fp;
	fopen_s(&fp, "student.txt", "r+");
	if (fp)
	{
		for (int i = 0; i < row; i++)
		{
			Student* q = (Student*)malloc(sizeof(Student));
			if (q)
			{
				fscanf_s(fp, "%d%s%f%f", &q->data.stuID, q->data.Name, MAX_NAMELEN, &q->data.AVGScore, &q->data.TotalScore);
				for (int j = 0; j < Course_Num; j++)
				{
					fscanf_s(fp, "%f", &q->data.LScore[j]);
				}
				ListInsert(q->data);
			}
			else
			{
				exit(1);
			}
		}
		fclose(fp);
	}
}

void EmptyList()
{
	Student* p;				//�������
	p = head;
	while (p)
	{
		head = p->next;
		free(p);
		p = head;
	}
	head = NULL;

	FILE* fp;				//���txt�ļ�
	fopen_s(&fp, ".//student.txt", "w");
	if (fp)
		fclose(fp);
}

void AddData(int Student_Num, int Course_Num)
{
	printf("\t\t������ѧ����ѧ�ţ��������͸���Ŀ�ɼ������밴XX XX XX�ĸ�ʽ���룩\n");
	printf("\t\t******************************************************************************\n");
	printf("\t\tѧ��	����");
	for (int k = 0; k < Course_Num; k++)
	{
		printf("	��Ŀ%d", k + 1);
	}
	printf("\n\t\t******************************************************************************\n");
	Student *stu = (Student*)malloc(sizeof(Student));
	for (int i = 0; i < Student_Num; i++)
	{
		printf("\t\t");
		if (stu)
		{
			scanf_s("%d %s", &stu->data.stuID, stu->data.Name, MAX_NAMELEN);
			stu->data.TotalScore = 0;
			stu->data.AVGScore = 0;

			for (int j = 0; j < Course_Num; j++)
			{
				scanf_s("%f", &stu->data.LScore[j]);
				stu->data.TotalScore += stu->data.LScore[j];
			}
			stu->data.AVGScore = stu->data.TotalScore / Course_Num;
			ListInsert(stu->data);
		}
	}
	printf("\t\t******************************************************************************\n");
}

void ListInsert(Data data)
{
	Student* p_new = (Student*)malloc(sizeof(Student)), * pf = head;//����һ�δ�������ռ���ڴ棬�������ַ����ʹpָ������p�еĵ�ַ������ָ��ԭλ��
	if (p_new)		//��p����ɹ����ɽ��иò������п����ڴ����ʧ�ܣ�����p_new==NULL������
	{
		p_new->data = data;
		if (head == NULL)
		{
			head = p_new;
			p_new->next = NULL;		//headָ����������p�ĵ�ַ����*p�ı䣬pδ�ı䣬head�ӵ�ַ���ʵ�һ���ı�
			return;
		}
		while (pf->next != NULL)
		{
			pf = pf->next;
		}
		pf->next = p_new;
		p_new->next = NULL;			//p_new����Ŀռ䱻head�洢���ᱻfree(head)�ͷ�
	}
}

void DisplayStuData(int Course_Num, Student* p)
{
	if (p == NULL)
	{
		printf("\t\t******************************************************************************\n");
		printf("\t\tϵͳδ¼������\n");
		printf("\t\t******************************************************************************\n");
		return;
	}
	printf("\t\t******************************************************************************\n");
	printf("\t\t    ѧ��    ����  ƽ����    �ܷ�");

	for (int k = 0; k < Course_Num; k++)
	{
		printf("   ��Ŀ%d", k + 1);
	}
	printf("\n\t\t******************************************************************************\n");


	while (p)
	{
		printf("\t\t%8d%8s%8.2f%8.2f",p->data.stuID, p->data.Name, p->data.AVGScore, p->data.TotalScore);
		for (int i = 0; i < Course_Num; i++)
		{
			if (p->data.LScore[i] >= 0) //���ݴ�����ʾ�����ݲ�������txt��Ϊ-1
				printf("%8.2f", p->data.LScore[i]);
		}
		p = p->next;
		printf("\n");
	}
	printf("\t\t******************************************************************************\n");
}

Student* SearchById(int Course_Num)
{
	Student* p = (Student*)malloc(sizeof(Student));
	Student* pf = (Student*)malloc(sizeof(Student));

	int StuId;
	printf("\t\t******************************************************************************\n");
	printf("\t\t������ѧ��ѧ�ţ�\t");
	scanf_s("%d", &StuId);
	printf("\t\t******************************************************************************\n");
	p = head;
	int i = 0;
	while (p)
	{
		if (p->data.stuID == StuId)
		{
			i = 1;	
			break;
		}
		p = p->next;
	}
	printf("\n\t\t    ѧ��    ����  ƽ����    �ܷ�");

	for (int k = 0; k < Course_Num; k++)
	{
		printf("   ��Ŀ%d", k + 1);
	}
	printf("\n\t\t******************************************************************************\n");

	if (i)
	{
		printf("\t\t%8d%8s%8.2f%8.2f", p->data.stuID, p->data.Name, p->data.AVGScore, p->data.TotalScore);
		for (int i = 0; i < Course_Num; i++)
		{
			if (p->data.LScore[i] >= 0)
				printf("%8.2f", p->data.LScore[i]);
		}
	}
	else
	{
		printf("\t\t��ID������");
	}
	printf("\n\t\t******************************************************************************\n");
	return p;
}

Student* SearchByName(int Course_Num)
{
	Student* p = (Student*)malloc(sizeof(Student));
	char StuName[MAX_NAMELEN] = { 0 };
	printf("\t\t******************************************************************************\n");
	printf("\t\t������ѧ��������\t");
	scanf_s("%s", StuName, MAX_NAMELEN);
	printf("\t\t******************************************************************************\n");
	p = head;
	int i = 0;
	while (p)
	{
		if (strcmp(p->data.Name, StuName) == 0)//(p->data.Name == StuName)�����У��Աȵ���������ַ
		{
			i = 1;
			break;
		}
		p = p->next;
	}
	printf("\n\t\t    ѧ��    ����  ƽ����    �ܷ�");

	for (int k = 0; k < Course_Num; k++)
	{
		printf("   ��Ŀ%d", k + 1);
	}
	printf("\n\t\t******************************************************************************\n");
	if (i)
	{
		printf("\t\t%8d%8s%8.2f%8.2f", p->data.stuID, p->data.Name, p->data.AVGScore, p->data.TotalScore);
		for (int i = 0; i < Course_Num; i++)
		{
			if (p->data.LScore[i] >= 0)
				printf("%8.2f", p->data.LScore[i]);
		}
	}
	else
	{
		printf("\t\t��ѧ������������");
	}
	printf("\n\t\t******************************************************************************\n");
	return p;
}

void Operating(int Course_Num)//ָ��q��h��p��p = head.next,h = head.next.next,q = head; q.next = h;
{
	printf("\n\n");
	printf("\t\t******************************************************************************\n");
	printf("\t\t*                1.  ͨ��ѧ������ѧ��������                                  *\n");
	printf("\t\t*                2.  ͨ����������ѧ��������                                  *\n");
	printf("\t\t*                0.  ���ز˵�                                                *\n");
	printf("\t\t******************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t*****************������ѡ�����:");
	int i, Op = 1;
	scanf_s("%d", &i);
	system("cls");

	Student* p = (Student*)malloc(sizeof(Student));
	Student* pre = (Student*)malloc(sizeof(Student));
	pre = head;
	switch (i)
	{
	case 1:
		p = SearchById(Course_Num);
		break;
	
	case 2:
		p = SearchByName(Course_Num);
		break;
	case 0:
		Op = 0;
		break;
	default:
		Op = 0;
		system("cls");
		printf("\n\n\n");
		printf("\t\t******************************************************************************\n");
		printf("\t\t����ѡ����ڡ�\n");
		printf("\t\t******************************************************************************\n");
		break;
	}

	if (Op && p)
	{
		printf("\n\n");
		printf("\t\t******************************************************************************\n");
		printf("\t\t*                1.  �޸�ѧ��                                                *\n");
		printf("\t\t*                2.  �޸�����                                                *\n");
		printf("\t\t*                3.  �޸ĵ��Ƴɼ�                                            *\n");
		printf("\t\t*                4.  ɾ����ѧ������                                          *\n");
		printf("\t\t*                0.  ���ز˵�                                                *\n");
		printf("\t\t******************************************************************************\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\t\t*****************������ѡ�����:");
		scanf_s("%d", &i);
		printf("\n");
		float bf, af;
		switch (i)
		{
		case 1:
			printf("\t\t��������ĺ��ѧ��:\t");
			scanf_s("%d", &p->data.stuID);
			break;

		case 2:
			printf("\t\t��������ĺ������:\t");
			scanf_s("%s", p->data.Name, MAX_NAMELEN);
			break;

		case 3:
			printf("\t\t��������Ҫ���ĵĿ�Ŀ:\t");
			scanf_s("%d", &i);
			bf = p->data.LScore[i - 1];				//�޸�ǰ�ÿƳɼ�
			printf("\t\t������ÿ�Ŀ���ĺ�ĳɼ�:\t");
			scanf_s("%f", &af);
			p->data.LScore[i - 1] = af;					//�޸ĺ�ÿƳɼ�
			af -= bf;
			p->data.TotalScore += af;				//�޸ĺ��ѧ���ܷ�
			p->data.AVGScore += af / Course_Num;	//�޸ĺ��ѧ��ƽ����
			break;

		case 4:
			if (p == head && p->next != NULL)		//��ͷ������ڼ�ɾ����û��ͷ���������鷳
			{
				head = p->next;
				free(p);
				p = NULL;
			}
			else if (p == head && p->next == NULL)
			{
				free(head);
				head = NULL;
			}
			else
			{
				while (pre->next != p)
				{
					pre = pre->next;
				}
				pre->next = p->next;
				free(p);
				p = NULL;
			}
			printf("\n\t\tɾ���ɹ�");
			break;
		case 0:
			break;
		default:
			Op = 0;
			system("cls");
			printf("\n\n\n");
			printf("\t\t����ѡ����ڡ�\n");
			break;
		}
	printf("\n\t\t******************************************************************************\n");
	}
}

void SaveFile(int Course_Num)
{
	Student* p = (Student*)malloc(sizeof(Student));
	p = head;
	FILE* fp;
	fopen_s(&fp, ".//student.txt", "w");
	printf("\t\t******************************************************************************\n");

	if (fp)
	{
		while (p)
		{
			fprintf(fp, "%d %s %.2f %.2f", p->data.stuID, p->data.Name, p->data.AVGScore, p->data.TotalScore);
			for (int i = 0; i < Course_Num; i++)
			{
				if (p->data.LScore[i] >= 0)
					fprintf(fp, " %.2f", p->data.LScore[i]);
				else
					fprintf(fp, " %d", -1); //�ÿ��޳ɼ���洢-1��txt
			}
			p = p->next;
			fprintf(fp, "\n");
		}
		printf("\t\t�洢�ɹ�");
		fclose(fp);
	}
	printf("\n\t\t******************************************************************************\n");
	free(p);
}

void ReadFile()
{
	int row = 0, column = 1;
	JudgeFile(&row, &column);
	int Course_Num = column - 4;
	FILE* fp;
	Student* p = (Student*)malloc(sizeof(Student));
	p = head;

	errno_t t = fopen_s(&fp, ".//student.txt", "r");		//�ļ����ڷ���errno_t����ֵ0
	printf("\t\t******************************************************************************\n");

	if (!t && fp)
	{
		if (!row && p)
		{
			printf("\t\t���ļ�Ϊ��, �������ļ�δ���������\n");
		}
		
		else if (!row)
		{
			printf("\t\t���ļ�Ϊ��\n");
		}

		else
		{
			rewind(fp);
			printf("\t\t    ѧ��    ����  ƽ����    �ܷ�");
			for (int k = 0; k < Course_Num; k++)
			{
				printf("   ��Ŀ%d", k + 1);
			}
			printf("\n\t\t******************************************************************************\n");
			for (int i = 0; i < row; i++)
			{
				fscanf_s(fp, "%d%s%f%f", &p->data.stuID, p->data.Name, MAX_NAMELEN, &p->data.AVGScore, &p->data.TotalScore);
				printf("\t\t%8d%8s%8.2f%8.2f", p->data.stuID, p->data.Name, p->data.AVGScore, p->data.TotalScore);
				for (int j = 0; j < Course_Num; j++)
				{
					fscanf_s(fp, "%f", &p->data.LScore[j]);
					if (p->data.LScore[j] >= 0)  //��txt�в�Ϊ-1�����ɼ�����
						printf("%8.2f", p->data.LScore[j]);
				}
				printf("\n");
				p = p->next;
			}
		}
		fclose(fp);	
	}
	
	else
	{
		printf("\t\t�ļ�������\n");
	}
	printf("\t\t******************************************************************************\n");
}

void JudgeFile(int* row, int* column)
{
	FILE* fpRow;							//��ȡtxt�ļ��е���������ѧ������
	fopen_s(&fpRow, "student.txt", "r+");
	char line[1024];
	if (fpRow)
	{
		while (fgets(line, sizeof(line), fpRow))
		{
			if (line[0] == '\n' || line[0] == '\r') // �жϿ���
			{
				break; // ����
			}
			else
			{
				*row = *row + 1;
			}
		}
		rewind(fpRow);
		int maxcol = 0;
		while (fgets(line, sizeof(line), fpRow))
		{
			int len = strlen(line);
			for (int i = 0; i < len; i++)
			{
				if (line[i] == ' ')
					*column = *column + 1;//����Ϊ�ո���+1����������еĿո���
				else
					continue;
			}
			if (maxcol < *column)        //����������
			{
				maxcol = *column;
			}
			*column = 0;
		}
		*column = maxcol;
		fclose(fpRow);
	}
}

void CourseAverSum(int Student_Num, int Course_Num)
{
	float sum, aver;
	Student* p = (Student*)malloc(sizeof(Student));
	printf("\n\t\t******************************************************************************\n");
	printf("\t\t    �γ�  ƽ����    �ܷ�\n");
	printf("\t\t******************************************************************************\n");
	for (int i = 0; i < Course_Num; i++)
	{
		sum = 0, aver = 0;
		p = head;
		while (p)
		{
			sum += p->data.LScore[i];
			p = p->next;
		}
		aver = sum / Student_Num;
		printf("\t\t   ��Ŀ%d%8.2f%8.2f\n", i + 1, aver, sum);
	}
	free(p);
	printf("\t\t******************************************************************************\n");
}