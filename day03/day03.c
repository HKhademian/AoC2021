#include <stdio.h>
#include <stdlib.h>

#define INP_COUNT 1000
#define INP_LEN 12
#define INP_FILE /*"./sample.txt"*/ "./input.txt"

int numbers[INP_COUNT] = {0};

void fputbin(void* sink, int x) {
  for (int z = (1<<INP_LEN-1); z>0; z >>= 1) {
    fprintf(sink, ((x & z) == z) ? "1" : "0");
  }
}

int readBin(FILE* file, int* number) {
  char buf[INP_LEN+1];
  if(fscanf(file, "%s", buf)>0) {
    *number = (int) strtol(buf, NULL, 2);
    return 1;
  } else {
    return 0;
  }
}

int calGamma(int start, int end) {
  int bitCount[INP_LEN] = {0};
  int gamma=0, count = end-start;

  for(int i=start; i<end; i++) {
    for(int j=0; j<INP_LEN; j++) {
      if((numbers[i] & (1<<j)) != 0)
        bitCount[j]++;
    }
  }

  for(int i=0; i<INP_LEN; i++) {
    if(bitCount[i] >= (count-bitCount[i])) {
      gamma |= (1<<i);
    }
  }

  return gamma;
}

int calLocalRate(int start, int end, int pos, int least) {
  int gamma = calGamma(start, end);

  // fprintf(stderr, "$$$ start: %d  end: %d  pos: %d gamma = %d = ", start, end, pos, gamma);
  // fputbin(stderr, gamma);
  // fputs("\n", stderr);
  
  if(end<=start+1)
    return numbers[start];

  if(pos<0) {
    fprintf(stderr, "o2 pos not correct!\n");
    exit(1);
  }

  while( least ^ ((numbers[start]&(1<<pos)) != (gamma & (1<<pos))) )
    start++;
  while( least ^ ((numbers[end-1]&(1<<pos)) != (gamma & (1<<pos))) )
    end--;
  
  return calLocalRate(start, end, pos-1, least);
}

int cmp(const void * a, const void * b) {
  return *(int*)a - *(int*)b;
}

int main(void) {
  int count = 0;
  FILE *file = fopen(INP_FILE, "r");
  while(readBin(file, numbers+count)>0) {
    count++;
  }
  fclose(file);

  qsort(numbers, count, sizeof(int), cmp);
  
  printf("count: %d\n", count);
  // for(int i=0; i<count; i++){
  //   printf("\n#%03d:\t%02d = ", i, numbers[i]);
  //   fputbin(stdout, numbers[i]);
  // }
  // puts("\n");

  int gamma = calGamma(0, count);
  int epsilon = gamma ^ ((1<<INP_LEN)-1);
  printf("\ngama:    %d\t= ", gamma);
  fputbin(stdout, gamma);
  printf("\nepsilon: %d\t= ", epsilon);
  fputbin(stdout, epsilon);
  printf("\npart1: %d\n", gamma*epsilon);

  int o2_rate  = calLocalRate(0, count, INP_LEN-1, 0);
  int co2_rate = calLocalRate(0, count, INP_LEN-1, 1);
  printf("o2_rate: %d\n"
    "co2_rate: %d\n"
    "part2: %d\n",
    o2_rate,
    co2_rate,
    o2_rate*co2_rate);

  return 0;
}
