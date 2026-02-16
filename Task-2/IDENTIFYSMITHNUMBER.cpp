int sum_of_digits(int num) {
 

int sum = 0;
while (num > 0) {
   sum += num % 10;
   num /= 10;
}
return sum;
}
int sum_of_prime_factors_digits(int num) {
 

int sum = 0;
int factor = 2;
while (num > 1) {
  
   while (num % factor == 0) {
       sum += sum_of_digits(factor);
       num /= factor;
   }
   factor++;
   if (factor * factor > num) {
       break;
   }
}

if (num > 1) {
   sum += sum_of_digits(num);
}
return sum;
}
 
int solve(int n) {
   if (n < 4) {
   return 0;
}
 

int sum_num_digits = sum_of_digits(n);
 

int sum_factors_digits = sum_of_prime_factors_digits(n);
 

if (sum_num_digits == sum_factors_digits) {
   return 1; 
} else {
   return 0; 
}
 
}
 