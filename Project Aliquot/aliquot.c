#include <stdio.h>

const long long MAX_SUPPORTED_INTEGER = 10000000000000000LL;

/**
 * @brief Calculates the sum of the proper divisors of a number n.
 *
 * A proper divisor is any divisor of n, except n itself.
 * This version avoids using math.h by checking i*i <= n instead of i <=
 * sqrt(n).
 *
 * @param n The number for which to calculate the sum of divisors. Must be > 0.
 * @return The sum of the proper divisors of n.
 */
long long sum_proper_divisors(long long n) {
  if (n <= 1) {
    return 0;
  }

  long long sum = 1;  // 1 is a proper divisor for all n > 1.

  // Loop until i*i exceeds n, which is equivalent to i > sqrt(n).
  // This avoids using math.h and the sqrt function, offering a small speedup.
  // The check i*i does not overflow since n is up to 10^16, and long long
  // typically supports up to 9*10^18.
  for (long long i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      sum += i;
      long long other_divisor = n / i;
      if (i != other_divisor) {
        sum += other_divisor;
      }
    }
  }
  return sum;
}

int main() {
  long long start_num;
  long long max_len;
  char format_char;

  printf("Please give the number to start the aliquot sequence from: ");

  if (scanf("%lld", &start_num) != 1 || start_num <= 0) {
    return 1;
  }

  if (start_num >= MAX_SUPPORTED_INTEGER) {
    // fprintf(stderr, "Number exceeds maximum supported integer (%lld).
    // Stopping.\n", MAX_SUPPORTED_INTEGER);
    printf("Number exceeds maximum supported integer (%lld). Stopping.\n",
           MAX_SUPPORTED_INTEGER);
    return 1;
  }

  printf("Provide the max aliquot length to look for (0 for unlimited): ");
  if (scanf("%lld", &max_len) != 1 || max_len < 0) {
    return 1;
  }

  printf(
      "Do you want to print the full sequence ('f') or just the length "
      "('l')? ");

  if (scanf(" %c", &format_char) != 1 ||
      (format_char != 'f' && format_char != 'l')) {
    return 1;
  }

  // --- Sequence Generation ---
  long long current_num = start_num;
  long long length = 0;  // Length tracks the number of steps taken.

  if (format_char == 'f') {
    printf("%lld", current_num);
  }

  while (current_num > 0) {
    // The max_len variable now represents the maximum number of *terms* to
    // print. Since the first term is printed outside the loop, the loop should
    // only execute max_len - 1 times. It breaks when the number of steps
    // (length) reaches max_len - 1.
    if (max_len > 0 && length >= max_len) {
      break;
    }

    long long next_num = sum_proper_divisors(current_num);

    // Checks if the next number exceeds the supported limit.
    if (next_num >= MAX_SUPPORTED_INTEGER) {
      // fprintf(stderr, "Number exceeds maximum supported integer (%lld).
      // Stopping.\n", MAX_SUPPORTED_INTEGER);
      printf("Number exceeds maximum supported integer (%lld). Stopping.\n",
             MAX_SUPPORTED_INTEGER);
      return 1;
    }

    current_num = next_num;
    length++;

    // The sequence has terminated at 0.
    if (current_num == 0) {
      break;
    }

    if (format_char == 'f') {
      printf("\n%lld", current_num);
    }
  }

  if (format_char == 'f') {
    printf("\n");
  }

  if (format_char == 'l') {
    printf("Length of aliquot sequence: %lld\n", length);
  }

  return 0;
}