#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMELEN 10			//姓名最大长度
#define MAX_COURSE 8			//课程数最大数量
#define MAX_STU 30				//学生最多人数


struct Data{
	int stuID;							//学号
	char Name[MAX_NAMELEN] = { 0 };		//姓名
	float TotalScore;					//总成绩
	float AVGScore;						//平均成绩
	float LScore[MAX_COURSE];			//单科成绩
};

typedef struct Node {			//链表结点
	struct Data data;
	struct Node* next;
} Student;

Student* head = NULL;			//全局定义链表head

int Menu();													//显示菜单
void AddData(int NumStudent, int NumCourse);				//添加学生数据
void ListInsert(Data data);									//链表插入功能
void DisplayStuData(int Course_Num, Student* p);			//显示学生数据
Student* SearchById(int Course_Num);						//按学号搜索
Student* SearchByName(int Course_Num);						//按姓名搜索
void CourseAverSum(int Student_Num, int Course_Num);		//计算单科平均成绩和成绩分布
void SaveFile(int Course_Num);								//储存到txt文件中
void ReadFile();											//从txt文件中读取数据
void Operating(int Course_Num);								//查找并修改删除学生数据
void EmptyList();											//清空所有数据
void List_Initi(int row, int Course_Num);					//链表初始化
void JudgeFile(int* row, int* column);						//获取txt文件的最大行列数

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
			printf("\t\t请输入学生数量:"); //输入学生数
			printf("\t\t");
			scanf_s("%d", &NumStu);
			SumStu += NumStu;
			printf("\t\t请输入课程数量:");//输入课程数
			printf("\t\t");

			scanf_s("%d", &NumCourse_Add);
			AddData(NumStu, NumCourse_Add);
			if (NumCourse_Add > NumCourse)//记录最大科目数
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
			printf("\t\t数据已清空\n ");
			printf("\t\t******************************************************************************\n");
			system("pause");
			system("cls");
			break;
		case 0:
			system("cls");
			printf("\n\n\n");
			printf("\t\t******************************************************************************\n");
			printf("\t\t感谢使用,程序已退出\n ");
			printf("\t\t******************************************************************************\n");
			return 0;						//程序退出
		default:
			system("cls");
			printf("\n\n\n");
			printf("\t\t******************************************************************************\n");
			printf("\t\t输入选项不存在。\n");
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
	system("title 学生成绩管理系统 by 1119096502@qq.com");
	printf("\n\n");
	printf("\t\t\t                         学生成绩管理系统\n");
	printf("\t\t******************************************************************************\n");
	printf("\t\t*                1.  添加学生信息                                            *\n");
	printf("\t\t*                2.  按默认顺序排出学生成绩表                                *\n");
	printf("\t\t*                3.  通过学号查询学生成绩                                    *\n");
	printf("\t\t*                4.  通过姓名查询学生成绩                                    *\n");
	printf("\t\t*                5.  计算每一学科的总分和平均分                              *\n");
	printf("\t\t*                6.  对学生数据进行删改                                      *\n");
	printf("\t\t*                7.  储存或更新到文件                                        *\n");
	printf("\t\t*                8.  读取文件数据                                            *\n");
	printf("\t\t*                9.  删除全部数据                                            *\n");
	printf("\t\t*                0.  退出                                                    *\n");
	printf("\t\t******************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t*****************请输入选项序号:");
	scanf_s("%d", &i);
	return i;
}

void List_Initi(int row, int Course_Num)//链表初始化
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
	Student* p;				//清空链表
	p = head;
	while (p)
	{
		head = p->next;
		free(p);
		p = head;
	}
	head = NULL;

	FILE* fp;				//清空txt文件
	fopen_s(&fp, ".//student.txt", "w");
	if (fp)
		fclose(fp);
}

void AddData(int Student_Num, int Course_Num)
{
	printf("\t\t请输入学生的学号，姓名，和各科目成绩：（请按XX XX XX的格式输入）\n");
	printf("\t\t******************************************************************************\n");
	printf("\t\t学号	姓名");
	for (int k = 0; k < Course_Num; k++)
	{
		printf("	科目%d", k + 1);
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
	Student* p_new = (Student*)malloc(sizeof(Student)), * pf = head;//分配一段大于申请空间的内存，返回其地址，并使p指向它，p中的地址变量仍指向原位置
	if (p_new)		//若p分配成功，可进行该操作。有可能内存分配失败，导致p_new==NULL，警告
	{
		p_new->data = data;
		if (head == NULL)
		{
			head = p_new;
			p_new->next = NULL;		//head指针变量存放了p的地址，当*p改变，p未改变，head从地址访问的一样改变
			return;
		}
		while (pf->next != NULL)
		{
			pf = pf->next;
		}
		pf->next = p_new;
		p_new->next = NULL;			//p_new申请的空间被head存储，会被free(head)释放
	}
}

void DisplayStuData(int Course_Num, Student* p)
{
	if (p == NULL)
	{
		printf("\t\t******************************************************************************\n");
		printf("\t\t系统未录入数据\n");
		printf("\t\t******************************************************************************\n");
		return;
	}
	printf("\t\t******************************************************************************\n");
	printf("\t\t    学号    姓名  平均分    总分");

	for (int k = 0; k < Course_Num; k++)
	{
		printf("   科目%d", k + 1);
	}
	printf("\n\t\t******************************************************************************\n");


	while (p)
	{
		printf("\t\t%8d%8s%8.2f%8.2f",p->data.stuID, p->data.Name, p->data.AVGScore, p->data.TotalScore);
		for (int i = 0; i < Course_Num; i++)
		{
			if (p->data.LScore[i] >= 0) //数据存在显示，数据不存在在txt中为-1
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
	printf("\t\t请输入学生学号：\t");
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
	printf("\n\t\t    学号    姓名  平均分    总分");

	for (int k = 0; k < Course_Num; k++)
	{
		printf("   科目%d", k + 1);
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
		printf("\t\t此ID不存在");
	}
	printf("\n\t\t******************************************************************************\n");
	return p;
}

Student* SearchByName(int Course_Num)
{
	Student* p = (Student*)malloc(sizeof(Student));
	char StuName[MAX_NAMELEN] = { 0 };
	printf("\t\t******************************************************************************\n");
	printf("\t\t请输入学生姓名：\t");
	scanf_s("%s", StuName, MAX_NAMELEN);
	printf("\t\t******************************************************************************\n");
	p = head;
	int i = 0;
	while (p)
	{
		if (strcmp(p->data.Name, StuName) == 0)//(p->data.Name == StuName)不可行，对比的是两个地址
		{
			i = 1;
			break;
		}
		p = p->next;
	}
	printf("\n\t\t    学号    姓名  平均分    总分");

	for (int k = 0; k < Course_Num; k++)
	{
		printf("   科目%d", k + 1);
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
		printf("\t\t此学生姓名不存在");
	}
	printf("\n\t\t******************************************************************************\n");
	return p;
}

void Operating(int Course_Num)//指针q，h，p，p = head.next,h = head.next.next,q = head; q.next = h;
{
	printf("\n\n");
	printf("\t\t******************************************************************************\n");
	printf("\t\t*                1.  通过学号搜索学生并操作                                  *\n");
	printf("\t\t*                2.  通过姓名搜索学生并操作                                  *\n");
	printf("\t\t*                0.  返回菜单                                                *\n");
	printf("\t\t******************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t*****************请输入选项序号:");
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
		printf("\t\t输入选项不存在。\n");
		printf("\t\t******************************************************************************\n");
		break;
	}

	if (Op && p)
	{
		printf("\n\n");
		printf("\t\t******************************************************************************\n");
		printf("\t\t*                1.  修改学号                                                *\n");
		printf("\t\t*                2.  修改姓名                                                *\n");
		printf("\t\t*                3.  修改单科成绩                                            *\n");
		printf("\t\t*                4.  删除该学生数据                                          *\n");
		printf("\t\t*                0.  返回菜单                                                *\n");
		printf("\t\t******************************************************************************\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\t\t*****************请输入选项序号:");
		scanf_s("%d", &i);
		printf("\n");
		float bf, af;
		switch (i)
		{
		case 1:
			printf("\t\t请输入更改后的学号:\t");
			scanf_s("%d", &p->data.stuID);
			break;

		case 2:
			printf("\t\t请输入更改后的姓名:\t");
			scanf_s("%s", p->data.Name, MAX_NAMELEN);
			break;

		case 3:
			printf("\t\t请输入需要更改的科目:\t");
			scanf_s("%d", &i);
			bf = p->data.LScore[i - 1];				//修改前该科成绩
			printf("\t\t请输入该科目更改后的成绩:\t");
			scanf_s("%f", &af);
			p->data.LScore[i - 1] = af;					//修改后该科成绩
			af -= bf;
			p->data.TotalScore += af;				//修改后该学生总分
			p->data.AVGScore += af / Course_Num;	//修改后该学生平均分
			break;

		case 4:
			if (p == head && p->next != NULL)		//有头结点利于简化删除，没有头结点操作很麻烦
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
			printf("\n\t\t删除成功");
			break;
		case 0:
			break;
		default:
			Op = 0;
			system("cls");
			printf("\n\n\n");
			printf("\t\t输入选项不存在。\n");
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
					fprintf(fp, " %d", -1); //该科无成绩则存储-1到txt
			}
			p = p->next;
			fprintf(fp, "\n");
		}
		printf("\t\t存储成功");
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

	errno_t t = fopen_s(&fp, ".//student.txt", "r");		//文件存在返回errno_t类型值0
	printf("\t\t******************************************************************************\n");

	if (!t && fp)
	{
		if (!row && p)
		{
			printf("\t\t该文件为空, 可能是文件未更新引起的\n");
		}
		
		else if (!row)
		{
			printf("\t\t该文件为空\n");
		}

		else
		{
			rewind(fp);
			printf("\t\t    学号    姓名  平均分    总分");
			for (int k = 0; k < Course_Num; k++)
			{
				printf("   科目%d", k + 1);
			}
			printf("\n\t\t******************************************************************************\n");
			for (int i = 0; i < row; i++)
			{
				fscanf_s(fp, "%d%s%f%f", &p->data.stuID, p->data.Name, MAX_NAMELEN, &p->data.AVGScore, &p->data.TotalScore);
				printf("\t\t%8d%8s%8.2f%8.2f", p->data.stuID, p->data.Name, p->data.AVGScore, p->data.TotalScore);
				for (int j = 0; j < Course_Num; j++)
				{
					fscanf_s(fp, "%f", &p->data.LScore[j]);
					if (p->data.LScore[j] >= 0)  //若txt中不为-1，即成绩存在
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
		printf("\t\t文件不存在\n");
	}
	printf("\t\t******************************************************************************\n");
}

void JudgeFile(int* row, int* column)
{
	FILE* fpRow;							//获取txt文件中的行数，即学生数量
	fopen_s(&fpRow, "student.txt", "r+");
	char line[1024];
	if (fpRow)
	{
		while (fgets(line, sizeof(line), fpRow))
		{
			if (line[0] == '\n' || line[0] == '\r') // 判断空行
			{
				break; // 跳出
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
					*column = *column + 1;//列数为空格数+1，求出列与列的空格数
				else
					continue;
			}
			if (maxcol < *column)        //求出最大列数
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
	printf("\t\t    课程  平均分    总分\n");
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
		printf("\t\t   科目%d%8.2f%8.2f\n", i + 1, aver, sum);
	}
	free(p);
	printf("\t\t******************************************************************************\n");
}