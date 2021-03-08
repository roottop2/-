#include<stdio.h>
#include<math.h>
#include<memory.h>
#include"Forward.h"
#include"Inversion.h"

//double Forward(double x_0, double y_0, double z_0, double x_1, double y_1, double z_1, double x, double y, double M_1,double times)
//					��һ���ǵ���������				�ڶ����ǵ���������				�����������		�Ż�ǿ��     �ڼ����ʷֵ�Ԫ

#define dx 100	//x���
#define dy 100	//y���
#define M1 1	//A/m

#pragma warning(disable:4996)

//M��ģ�ͣ�N�����

int num = 6;
//�ڼ��ζ�ȡ�ǵ����꣬���һ�нǵ�����Ϊ���㱳����B_T������

int main()
{
	FILE* fp1, * fp2, * fp3, * fp4, * fp5;
	double x_0[2], y_0[2], z_0[2];
	double R_T[441] = { 0 };//d
	//R_Tģ�ʹ��쳣

	int line = 21, point = 21;	//���ߺͲ����
	int times = 0, part = 0;	
	//times ��ʾ��Ԫ�Ե�times�������쳣Ӱ�죬
	int i, j, x, y;				

	//double G[21 * 21][5 * 5 * 2 * 6];
	double* G = (double*)malloc(sizeof(double) * 441*4410);
	//�˾����������ݵ�һ���x�������Ԫ
	//���ݳ��ĺ˾���;���ú˾���ͱ������Ĵ�С����������쳣;
	
	//�������쳣
	double* B_T = (double*)malloc(sizeof(double) * 441);	
	//����̬����G��B_T��ʼ��Ϊ0;

	//����+���ݴ��쳣
	double* ALL_T = (double*)malloc(sizeof(double) * 441);
	//���ݳ���m
	double* m = (double*)malloc(sizeof(double) * 4410);

	memset(G, 0, sizeof(double) * 441 * 300);
	memset(B_T, 0, sizeof(double) * 441);
	memset(ALL_T, 0, sizeof(double) * 441);

	fp1 = fopen("C:\\Users\\wc\\Desktop\\̨�����ݲ���.txt", "rb+");
	fp2 = fopen("C:\\Users\\wc\\Desktop\\̨������.txt", "wb+");
	fp3 = fopen("C:\\Users\\wc\\Desktop\\�������쳣.txt", "wb+");
	fp4 = fopen("C:\\Users\\wc\\Desktop\\����+ģ�ʹ��쳣.txt", "wb+");
	fp5 = fopen("C:\\Users\\wc\\Desktop\\����.txt", "wb+");
	fprintf(fp2, "x\ty\tT\n");	
	fprintf(fp3, "x\ty\tT\n");	
	fprintf(fp4, "x\ty\tT\n");	
	do {
		int ret = fscanf_s(fp1, "%lf%lf%lf%lf%lf%lf", &x_0[0], &y_0[0], &z_0[0], &x_0[1], &y_0[1], &z_0[1]);		
		if (ret > 0){	
			times = 0;						
			for (i = 0; i < 21; i++){
				x = dx * i;
				for (j = 0; j < 21; j++){
					y = dy * j;																	//440
					if (part != num){
						R_T[times] += Forward(x_0[0], y_0[0], z_0[0], x_0[1], y_0[1], z_0[1], x, y, M1, times, G, part);
						times++;
					}
					else {
						B_T[times] += Forward(x_0[0], y_0[0], z_0[0], x_0[1], y_0[1], z_0[1], x, y, M1, times, G, part);
						fprintf(fp2, "%d\t%d\t%lf\n", x, y, R_T[times]);
						fprintf(fp3, "%d\t%d\t%lf\n", x, y, B_T[times]);
						ALL_T[times] = R_T[times] + B_T[times];
						fprintf(fp4, "%d\t%d\t%lf\n", x, y, ALL_T[times++]);
					}
				}
			}			
			part++;
		}
		if (feof(fp1)) break;
	}while(1);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	m = Inversion(G, ALL_T, 2, 1);
	fprintf(fp5, "T\n");
	for (i = 0; i < 4410; i++)
	{
		fprintf(fp5, "%lf\n", *(m + i));
	}

	fclose(fp5);
}