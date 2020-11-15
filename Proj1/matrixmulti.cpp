#include<iostream>
#include <chrono>
#include<time.h>
#include<cassert>
#include<omp.h>
#include <immintrin.h>
extern"C"
{
    #include"cblas.h"       
}
using namespace std;
#define TIME_START start=std::chrono::steady_clock::now();
#define TIME_END(NAME) end=std::chrono::steady_clock::now(); \
             duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();\
             cout<<(NAME)<<": duration = "<<duration<<"ms" \
             <<", result:"<<endl;\
            showMatrix(c);



struct Matrix{
    int num_rows;
    int num_colums;
    float *data;
    Matrix(int m, int n){
        num_rows = m;
        num_colums = n;
        data = new float[m*n];
    }

};

Matrix generator(int m, int n){
    Matrix myMatrix(m,n); 
    srand(time(NULL));
    for(int i=0 ; i<m*n; i++){
        myMatrix.data[i] = (rand()%100)/10.0f;     
    }
    return myMatrix;
    
}
void showMatrix(Matrix c){
    int m,n;
    m = c.num_rows;
    n = c.num_colums;
    float *data = c.data;
    assert((n>6&&m>6));
    cout << "\t"<<data[0] << " " << data[1] << " " << data[2] << " ... " 
    << data[n-3] << " " << data[n-2] << " " << data[n-1] << endl;
    cout << "\t\t\t\t"<< "..." << endl;
    cout << "\t"<< data[n*(m-1)] << " " << data[n*(m-1)+1] << " " << data[n*(m-1)+2] << " ... " 
    << data[m*n-3] << " " << data[m*n-2] << " " << data[m*n-1] << endl;
    cout << endl;
}
Matrix multiMatrix1(Matrix &a, Matrix &b){
    assert (a.num_colums == b.num_rows);
    Matrix result = Matrix(a.num_rows, b.num_colums);
    for(int i=0 ; i<a.num_rows; i++){
        for(int j=0 ; j<b.num_colums; j++){
            float sum = 0;
            for(int k=0 ; k<a.num_colums; k++){
                sum += a.data[i*a.num_colums+k]*b.data[k*b.num_colums+j];
            }
            result.data[i*b.num_colums+j] = sum;
        }      
    }

    return result;
}

Matrix multiMatrix2(Matrix &a, Matrix &b){
    assert (a.num_colums == b.num_rows);
    Matrix result = Matrix(a.num_rows, b.num_colums);
    for(int i=0 ; i<a.num_rows; i++){     
        for(int k=0 ; k<a.num_colums; k++){
            float s = a.data[i*a.num_colums+k];                
            for(int j=0 ; j<b.num_colums; j++){
                result.data[i*b.num_colums+j] += s*b.data[k*b.num_colums+j];
            }
        }         
    }

    return result;
}

Matrix multiMatrix3(Matrix &a, Matrix &b){
    assert (a.num_colums == b.num_rows);
    Matrix result = Matrix(a.num_rows, b.num_colums);
    float *data = new float[a.num_rows*b.num_colums];
    #pragma omp parallel for
    for(int i=0 ; i<a.num_rows; i++){
        for(int j=0 ; j<b.num_colums; j++){
            float sum = 0;
            for(int k=0 ; k<a.num_colums; k++){
                sum += a.data[i*a.num_colums+k]*b.data[k*b.num_colums+j];
            }
            data[i*b.num_colums+j] = sum;
        }      
    }
    result.data = data;

    return result;
}

Matrix multiMatrix4(Matrix &a, Matrix &b){
    assert (a.num_colums == b.num_rows);
    float* adata = a.data;
    float* bdata = b.data;
    Matrix result = Matrix(a.num_rows, b.num_colums);
    #pragma omp parallel for
    for(int i=0 ; i<a.num_rows; i++){     
        for(int k=0 ; k<a.num_colums; k++){
            float s = adata[i*a.num_colums+k];                
            for(int j=0 ; j<b.num_colums; j++){
                result.data[i*b.num_colums+j] += s*bdata[k*b.num_colums+j];
            }
        }         
    }

    return result;
}

Matrix multiMatrix5(Matrix &a, Matrix &b){
    assert (a.num_colums == b.num_rows);
    int ii = a.num_rows;
    int kk = a.num_colums;
    int jj = b.num_colums;
    assert(ii%8==0 && jj%8==0);
    Matrix result = Matrix(ii,jj);
    float* colums = new float[kk*jj];
    for(int i=0; i<kk*jj; i++){
        int row = i/jj;
        int colum = i%jj;
        colums[colum*kk+row] = b.data[i];
    }
    #pragma omp parallel for
    for(int i=0; i<ii; i++){
        for(int j=0 ; j<jj; j++){
            float sum[8] = {0};
            __m256 z = _mm256_setzero_ps();
            for(int k=0; k<kk; k+=8){
                __m256 x = _mm256_load_ps(colums+j*kk+k);
                __m256 y = _mm256_load_ps(a.data+i*kk+k);
                z =  _mm256_add_ps(z, _mm256_mul_ps(x, y));
            }
            _mm256_store_ps(sum,z);
            result.data[i*jj+j] = sum[0]+sum[1]+sum[2]+sum[3]+sum[4]+sum[5]+sum[6]+sum[7];
        }
    }

    return result;
}
Matrix multiMatrix6(Matrix &a, Matrix &b){
    assert (a.num_colums == b.num_rows);
    int ii = a.num_rows;
    int kk = a.num_colums;
    int jj = b.num_colums;
    Matrix result = Matrix(ii,jj);
    float* colums = new float[kk*jj];
    for(int i=0; i<kk*jj; i++){
        int row = i/jj;
        int colum = i%jj;
        colums[colum*kk+row] = b.data[i];
    }
    #pragma omp parallel for
    for(int i=0; i<ii; i++){
        for(int j=0 ; j<jj; j++){
            float sum = 0;
            for(int k=0; k<kk; k++){
                sum += colums[j+kk]*a.data[i*kk+k];
            }
    
            result.data[i*jj+j] = sum;
        }
    }

    return result;
}
Matrix multiMatrix7(Matrix &a, Matrix &b){
    assert (a.num_colums == b.num_rows);
    int ii = a.num_rows;
    int kk = a.num_colums;
    int jj = b.num_colums;
    assert(ii%4==0 && jj%4==0);
    Matrix result = Matrix(ii,jj);
    float* colums = new float[kk*jj];
    
    for(int i=0; i<kk*jj; i++){
        int row = i/jj;
        int colum = i%jj;
        colums[colum*kk+row] = b.data[i];
    }
    #pragma omp parallel for
    for(int i=0; i<ii; i+=4){
        for(int j=0 ; j<jj; j+=4){           
            register float t0(0),t1(0),t2(0),t3(0),t4(0),t5(0),t6(0),t7(0),
                    t8(0),t9(0),t10(0),t11(0),t12(0),t13(0),t14(0),t15(0);
            float *a0(a.data+i*kk) ,*a1(a.data+(i+1)*kk), *a2(a.data+(i+2)*kk), *a3(a.data+(i+3)*kk);
            float *b0(b.data+j*kk) ,*b1(b.data+(j+1)*kk) , *b2(b.data+(j+2)*kk), *b3(b.data+(j+3)*kk);
            for(int k=0; k<kk; k+=1){
                t0+=*(a0)**(b0);
                t1+=*(a0)**(b1);
                t2+=*(a0)**(b2);
                t3+=*(a0++)**(b3);
                t4+=*(a1)**(b0);
                t5+=*(a1)**(b1);
                t6+=*(a1)**(b2);
                t7+=*(a1++)**(b3);
                t8+=*(a2)**(b0);
                t9+=*(a2)**(b1);
                t10+=*(a2)**(b2);
                t11+=*(a2++)**(b3);
                t12+=*(a3)**(b0++);
                t13+=*(a3)**(b1++);
                t14+=*(a3)**(b2++);
                t15+=*(a3++)**(b3++);
            }
            result.data[i*jj+j] = t0;
            result.data[i*jj+j+1] = t1;
            result.data[i*jj+j+2] = t2;
            result.data[i*jj+j+3] = t3;
            result.data[(i+1)*jj+j] = t4;
            result.data[(i+1)*jj+j+1] = t5;
            result.data[(i+1)*jj+j+2] = t6;
            result.data[(i+1)*jj+j+3] = t7;
            result.data[(i+2)*jj+j] = t8;
            result.data[(i+2)*jj+j+1] = t9;
            result.data[(i+2)*jj+j+2] = t10;
            result.data[(i+2)*jj+j+3] = t11;
            result.data[(i+3)*jj+j] = t12; 
            result.data[(i+3)*jj+j+1] = t13; 
            result.data[(i+3)*jj+j+2] = t14; 
            result.data[(i+3)*jj+j+3] = t15;      
        }
    }

    return result;
}
//for 100 and 1000
void testSmall(int x, int y, int z){
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto duration = 0L;
    Matrix a = generator(x,y);
    Matrix b = generator(y,z);
    Matrix c = Matrix(x,z);

    TIME_START
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,x,z,y,1.0,a.data,y,b.data,z,0.0,c.data,z);
    TIME_END("Cblas")

    TIME_START
    c = multiMatrix1(a,b);
    TIME_END("V1(naive)1")

    TIME_START
    c = multiMatrix1(a,b);
    TIME_END("V1(naive)2")

    TIME_START
    c = multiMatrix2(a,b);
    TIME_END("V2(change_to_ikj)")

    TIME_START
    c = multiMatrix3(a,b);
    TIME_END("V3(naive+openmp)")

    TIME_START
    c = multiMatrix4(a,b);
    TIME_END("V4(ikj+omp)")

    TIME_START
    c = multiMatrix5(a,b);
    TIME_END("V5(tanspose+SIMD)")

    TIME_START
    c = multiMatrix6(a,b);
    TIME_END("V6(transpose)")

    TIME_START
    c = multiMatrix7(a,b);
    TIME_END("V7(16registers+omp)")

}
void testLarge(int x, int y, int z){
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto duration = 0L;
    Matrix a = generator(x,y);
    Matrix b = generator(y,z);
    Matrix c = Matrix(x,z);

    TIME_START
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,x,z,y,1.0,a.data,y,b.data,z,0.0,c.data,z);
    TIME_END("Cblas")

    TIME_START
    c = multiMatrix4(a,b);
    TIME_END("V4(ikj+omp)")

    TIME_START
    c = multiMatrix5(a,b);
    TIME_END("V5(tanspose+SIMD)")
}

int main(){
    cout << "Test for two 400*400 matrix:" << endl;
    testSmall(400,400,400);
    cout << "Test for two 1000*1000 matrix:" << endl;
    testSmall(1000,1000,1000);
    cout << "Test for two 2000*2000 matrix:" << endl;
    testSmall(2000,2000,2000);
    cout << "Test for two 10000*10000 matrix:" << endl;
    testLarge(10000,10000,10000);
    
    return 0;
}

