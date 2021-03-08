#pragma once
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
//�ʷ�������� 20*20*10
//����DX=DY=DZ=100;
//
double Matrix_multiplication(double* matrix_1, double* matrix_2, double* output_matrix, int line, int column)
{
	int s = 0, i, j;
	double sum = 0;
	do
	{
		for (i = 0; i < line; i++)
		{
			for (j = 0; j < column; j++)
				sum += *(matrix_1 + i * column + j) * *(matrix_2 + j * line + s);
			*(output_matrix + i * line + s) = sum;
			sum = 0;
		}
		s++;
	} while (s < line);
	return 0;
}
//A���ݾ���
//���ݳ�ֵm 0     
//��������k<N
//���򻯲���0.6<miu<0.9
//�۽�����e = 10e-10
//m = Wm��*We��*mw
//Aw = Wd*A*Wm��*We��
//dw = Wd*d
//mw = We*Wm*m
//Q = We���ƽ��*Aw��ת��*Aw+miu0*e*e*I
//q = We���ƽ��*Aw��ת��*dw 
//����mw0���ĵ���Ϊf0 = Q*mw-q
//��mw0�ĳ�ʼ��������ѡ��Ŀ�꺯���յ������½�����d0 = -f0
//��Ӧ��������t = (d0ת��*f0)/(d0ת��*Q*d0)
//����ģ��mb = a  , db = Amb  ,d = dobs+db

//���ݴŻ�ǿ��mc = 1A/m  �����Ż�ǿ��1A/m   Լ��M_min= 0 M_max = 2;

//����������
#define  Maximum_number_of_iterations 100

//�۽�����
#define e 10e-10
//���� G �˾���  ALL_T�ܴ��쳣  Լ������M_min= 0 M_max = 2
double *Inversion(double* G, double* ALL_T, double M_max, double M_min)
{
	//��������
	int Iterations = 0;
	//ѭ������
	int i, j;
	//���򻯲���
	double miu = 0.6;//(0.6~0.9)

	double sum = 0;

	//���ݼ�Ȩ����Wd;�۽�Ȩ����We;ģ�ͼ�Ȩ����Wd;����ģ��mb(�Ż�ǿ�ȣ��˴�Ϊ1A/m),dΪ�۲�����;
	//Gm = d
	//�˾���G 441�� 4410��
	double* Wd, * We, * Wm, * Aw, t0, beta;
	Aw = (double*)malloc(sizeof(double) * 441*4410);
	Wd = (double*)malloc(sizeof(double) * 441);	
	We = (double*)malloc(sizeof(double) * 4410);
	Wm = (double*)malloc(sizeof(double) * 4410);
	//double Wd[441], We[4410], Wm[4410],mb,d;
	//We = diag(1/sqrt(m*m+e*e))
	//Wd = diag(sqrt(A*Aת��))
	//Wm = diag(sqrt(Aת��*A))

	double* G_T = (double*)malloc(sizeof(double) * 4410 * 441);

	double* Aw_T = (double*)malloc(sizeof(double) * 4410 * 441);

	double* Q = (double*)malloc(sizeof(double) * 4410 * 4410);

	double* q = (double*)malloc(sizeof(double) * 4410);

	double* m = (double*)malloc(sizeof(double) * 4410);

	double* dw = (double*)malloc(sizeof(double) * 441);

	double* mid = (double*)malloc(sizeof(double) * 4410);

	double* f0 = (double*)malloc(sizeof(double) * 4410);

	double* f1 = (double*)malloc(sizeof(double) * 4410);

	double* d0 = (double*)malloc(sizeof(double) * 4410);

	memset(m,1,sizeof(double)*4410);
	memset(dw,0,sizeof(double)*441);
	memset(mid,0,sizeof(double)*4410);
	memset(d0,0,sizeof(double)*4410);
	memset(Q,0,sizeof(double)*4410);
	memset(f1,0,sizeof(double)*4410);

	for (i = 0; i < 4410; i++)
		for (j = 0; j < 441; j++)
			*(G_T + 441 * i + j) = *(G + 4410 * j + i);

	//We Wm Wd����
	
	for (i = 0; i < 441; i++)
	{
		for (j = 0; j < 4410; j++)
			sum += *(G + i * 4410 + j) * *(G_T + j * 441 + i);
		*(Wd + i) = sqrt(sum);
		sum = 0;
	}
	for (i = 0; i < 4410; i++)
	{
		for (j = 0; j < 441; j++)
			sum += *(G_T + i * 441 + j) * *(G + j * 4410 + i);
		*(Wm + i) = sqrt(sum);
		sum = 0;
	}

	//m0w
	
	
	//Aw��Aw_T
	
	
	//����Q����
	
	//����dw  dw = Wd * d;   441 441   441 1  =441 1
	for (i = 0; i < 441; i++)
		*(dw + i) = *(ALL_T + i) * *(Wd + i);
	//����q
	

	//����f0 = Q*mw - q


	//����t0
	do {
		//����We �� mwk;
		for (i = 0; i < 4410; i++){
			We[i] = 1.0 / sqrt(m[i] * m[i] + e * e);
			m[i] = We[i] * Wm[i] * m[i];
		}
		//����Aw
		for (i = 0; i < 441; i++)
			for (j = 0; j < 4410; j++)
				*(Aw + i * 4410 + j) = *(G + i * 4410 + j) * *(Wd + i) * 1.0 / *(Wm + j) * 1.0 / *(We + j);
		for (i = 0; i < 4410; i++)
			for (j = 0; j < 441; j++)
				*(Aw_T + i * 441 + j) = *(Aw + j * 4410 + i);
		//����Q
		Matrix_multiplication(Aw_T, Aw, Q, 4410, 441);
		for (i = 0; i < 4410; i++)
			for (j = 0; j < 4410; j++) {
				*(Q + i * 4410 + j) *= 1.0 / *(We + i) * 1.0 / *(We + i);
				while (i == j)
					*(Q + i * 4410 + j) += miu * e * e;
			}
		//����q
		for (i = 0; i < 4410; i++) {
			for (j = 0; j < 441; j++)
				*(mid + i) += *(Aw_T + 441 * i + j) * *(dw + j);
			*(q + i) = 1.0 / *(We + i) * 1.0 / *(We + i) * *(mid + i);
		}
		//fk
		for (i = 0; i < 4410; i++)
			for (j = 0; j < 4410; j++)
				*(f1 + i) += *(Q + i * 4410 + j) * *(m + j) - *(q + i);
		double molecule = 0, denominator = 0;
		for (i = 0; i < 4410; i++) {
			if(Iterations == 0)
				*(d0 + i) = -*(f1 + i);
			else
				for (j = 0; j < 4410; j++)
				{
					molecule += *(f1 + j) * *(f1 + j);
					denominator += *(f0 + j) * *(f0 + j);
					beta = molecule / denominator;
					*(d0 + i) = -*(f1 + i) + beta * *(d0 + i);
				}
			molecule = 0, denominator = 0;
			molecule += *(d0 + i) * *(f0 + i);
			for (j = 0; j < 4410; j++)
				*(mid + i) += *(d0 + j) * *(Q + i * 4410 + j);
			denominator += *(mid + i) * *(d0 + i);
		}
		t0 = molecule / denominator;

		for (i = 0; i < 4410; i++)
			*(f0 + i) = *(f1 + i);

		Iterations++;
		for (i = 0; i < 4410; i++){
			*(m + i) = *(m + i) + t0 * *(d0 + i);
			*(m + i) = 1.0 / (*(Wm + i) * *(We + i)) * *(m + i);
			if (*(m + i) > M_max)
				*(m + i) = M_max;
			else if (*(m + i) < M_min)
				*(m + i) = M_min;
		}

	} while (Iterations < Maximum_number_of_iterations);
	for (i = 0; i < 4410; i++)
		*(m + i) -= 1;
	return m;
}


//ת�����ת�þ������
