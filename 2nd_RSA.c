#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


long long mod_inverse(long long a, long long m)
{
    long long old_r = a;        
    long long r     = m;    
    long long old_s = 1;   
    long long s     = 0;  

    while (r != 0) {
        long long quotient= old_r / r;                 
        long long tmp_r = r;                      
        long long tmp_s = s;                              

        r     = old_r - quotient * r;           
        old_r = tmp_r;                               

        s     = old_s - quotient * s;            
        old_s = tmp_s;                                  
    }

    
    if (old_r != 1)          return -1;                
    if (old_s < 0) old_s += m;            
    return old_s;                                           
}


long long power_mod(long long base, long long exp, long long mod)
{
    long long result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        exp >>= 1;
        base = (base * base) % mod;
    }
    return result;
}




int main()
{
	
	
	long long N;
    long long x=0;
	long long i;
	long long r1=9999;
	long long r2=99999;
	int primeY=0;
    long long r22=(long long)sqrt(r2);
	int list_n=0; 
	
	
	long long primes[10000] = {0};
	
	clock_t start,end;
	start = clock();
	
	
	
	for (N=r1;N<=r2;N++){
		primeY=0; 
		for (i=2;i<=r22;i++){      
	        if(N%i == 0){
		        primeY=1;
			    break;
	        } 
			 
    	}	
    	
    	if (primeY==0){
    		primes[list_n]=N;
    		list_n ++;
    		
    		x++;
    		
		}
		
	}
    
   	end = clock();
   	double time_spent = (double)(end-start)/ CLOCKS_PER_SEC;
   	
	printf("\n%lld~%lld范围内的素数已查找完毕\n一共有%lld个素数\n耗时%.6fs\n", r1, r2 ,x,time_spent);	
	
	
    srand((unsigned)time(NULL));
	int idx_p = rand() % list_n;
	int idx_q = rand() % list_n;
	while (idx_p == idx_q){
		idx_q = rand() % list_n;
	}                                     //随机取pq 并保证两者不相等 		
	
	long long p=primes[idx_p];
	long long q=primes[idx_q];
	
    long long n=p*q;
    long long phi=(p-1)*(q-1);
    
    long long e = 65537;                  //随机取e 在此范围内无需考虑是否互质 
    long long d=mod_inverse(e,phi);
    
    printf("公钥:(%lld,%lld)\n",e,n);
	printf("私钥:(%lld,%lld)\n",d,n);
	
	long long M;
	printf("请输入需要加密的信息M:(0<M<%lld)\n",n);
	scanf("%lld",&M);
	
	long long C = power_mod(M,e,n);
	long long P = power_mod(C,d,n);
	
	
	printf("\n=========== 加解密过程 ============\n");
    printf("明文 M        = %lld\n", M);
    printf("加密 M^e mod n = %lld   ← 密文\n", C);
    printf("解密 C^d mod n = %lld   ← 还原\n", P);
    printf("还原结果: %s\n", (P == M) ? "成功" : "失败");
	

	
}
	


	
	

    
     
		
	





