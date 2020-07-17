#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
 
int main(void)
{
    /* Prepare an array of f-p values. */
    #define SIZE 8
    double A[SIZE] = {1.,2.,3.,4.,5.,6.,7.,8.};
    /* Write array to a file. */
    FILE * fp = fopen("test.bin", "wb");
    fwrite(A,sizeof(double),SIZE,fp);
    fclose (fp);
 
    /* Read the f-p values into array B. */
    double B[SIZE];
    fp = fopen("test.bin","rb");
 
    /* Set the file position indicator in front of third f-p value. */
    if (fseek(fp,sizeof(double)*2L,SEEK_SET) != 0)
    {
        perror("fseek()");
        fprintf(stderr,"fseek() failed in file %s at line # %d\n", __FILE__,__LINE__-5);
        exit(EXIT_FAILURE);
    }
 
    int ret_code = fread(B,sizeof(double),1,fp);   /* read one f-p value  */
    printf("%.1f\n", B[0]);                        /* print one f-p value */
    
    /* seek again after fread. */
    if (fseek(fp,sizeof(double)*3L,SEEK_SET) != 0)
    {
        perror("fseek()");
        fprintf(stderr,"fseek() failed in file %s at line # %d\n", __FILE__,__LINE__-5);
        exit(EXIT_FAILURE);
    }
 
    ret_code = fread(B+1,sizeof(double),1,fp);   /* read one f-p value  */
    printf("2nd: %.1f\n", B[1]);                        /* print one f-p value */
    
    struct stat stats;
    if( fstat( fileno( fp ), &stats ) != 0 )
    {
        perror( "CFile fstat failed" );
    }
    printf("file szie: %ld\n", stats.st_size);
    
    /* Write array again */
    FILE * fpw = fopen("test.bin", "wb");
    fwrite(A,sizeof(double),SIZE,fpw);
    fclose (fpw);
    
    if( fstat( fileno( fp ), &stats ) != 0 )
    {
        perror( "CFile fstat failed" );
    }
    printf("file szie: %ld\n", stats.st_size);
    
 
    fclose(fp);
    return EXIT_SUCCESS;
}
