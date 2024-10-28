
#define BLOCK_SIZE 512

__device__ unsigned int warpDistribution[33] = {0};

__device__ void countWarpDistribution(){

      unsigned int mask = __popc(__activemask());
      if(threadIdx.x % 32 == 0){
        atomicAdd(&warpDistribution[mask],1);
      }
}

__device__ void printWarpDistribution(){
    printf("\n Warp Distribution: \n");
    for(int i = 0; i < 33; i++){
        printf("W%d: %u, ",i,warpDistribution[i]);
    }
    printf("\n\n");
}

__global__ void naiveReduction(float *out, float *in, unsigned size)
{
    
    __shared__ float partialSum[2*BLOCK_SIZE];
    unsigned int t = threadIdx.x;
    
    unsigned int start= 2*blockIdx.x*blockDim.x;
    if((start + t)>size){
       partialSum[t] =  0;
    }
    else{
    partialSum[t] =in[start + t];
    }
    if((start + t + blockDim.x)>size){
      partialSum[t+blockDim.x] = 0;
    }
    else{
    partialSum[t+blockDim.x] =in[start + t + blockDim.x];
    }
    for(unsigned int stride = 1; stride<= blockDim.x;stride*=2){
      __syncthreads();
      if(t % stride == 0){
        partialSum[2*t] += partialSum[2*t+stride];
      }

    }
    
      out[t*blockDim.x+blockIdx.x] =partialSum[2*t];
 
}


__global__ void optimizedReduction(float *out, float *in, unsigned size){

   __shared__ float partialSum[2*BLOCK_SIZE];
    unsigned int t = threadIdx.x;
    
    unsigned int start= 2*blockIdx.x*blockDim.x;
    if((start + t)>size){
       partialSum[t] =  0;
    }
    else{
    partialSum[t] =in[start + t];
    }
    if((start + t + blockDim.x)>size){
      partialSum[t+blockDim.x] = 0;
    }
    else{
    partialSum[t+blockDim.x] =in[start + t + blockDim.x];
    }
    for(unsigned int stride = blockDim.x; stride>0 ;stride/=2){
      __syncthreads();
      if(t < stride ){
        partialSum[t] += partialSum[t+stride];
         
      }

    }
    
      out[t*blockDim.x+blockIdx.x] =partialSum[t];


  
}