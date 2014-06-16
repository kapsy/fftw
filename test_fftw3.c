/*
 *	How to use FFTW 
 *
 *	2007.10.31 A.Date
 *
 *  % gcc test_fftw3.c -lm -lfftw3
 *
 * */

#include<stdio.h>
#include<math.h>
#include<fftw3.h>

#define MAX 10000000

int main ()
{
	FILE *fp;
	int i;
	int N;
	double *Y; 
	double s,t,u,v;
	fftw_complex *in, *out;
	fftw_plan p;

	fp = fopen("ohayo57.txt", "r");
	if (fp == NULL){
			fprintf(stderr, "Can't open data file.\n");
			exit(-1);
	} 
	if(  ( Y=(double *)malloc(MAX) ) == NULL) {
			fprintf(stderr, "Can't allocate memory.\n");
			exit(-1);
	}

	i=0;
	while ( fscanf(fp,"%lf",&Y[i]) != EOF  &&  i < MAX ){
//				printf("%3d: %15.10lf\n",i, Y[i]);
		i++;
	}
	N=i;
	fclose(fp);


	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
	
	/* Set input data; N is the number of data.  */
	for(i=0; i<N; i++){
		in[i][0]=Y[i];
		in[i][1]=0.0;
	}

	p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE); 
	fftw_execute(p); 
	

	/* output the result */ 
	for(i=0; i<N; i++){
		s = out[i][0];		
		t = out[i][1];		
		u = sqrt(s*s + t*t);
		v = atan2(s,t);
		printf("%d \t %.5lf \t %.5lf \t %.5lf \t %.5lf \n", i, s,t,u,v);
	}

	fftw_destroy_plan(p);
	fftw_free(in); 
	fftw_free(out);

	free(Y);
}

