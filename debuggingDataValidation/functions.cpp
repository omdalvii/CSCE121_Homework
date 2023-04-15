#include <stdexcept>
#include <iostream>

int Largest(int a, int b, int c)
{
  int largest = a;
  largest = (b > largest) ? b : largest;
  largest = (c > largest) ? c : largest;

  return largest;
}

bool SumIsEven(int a, int b)
{
  if ((a + b) % 2)
  {
    return false;
  }
  else
  {
    return true;
  }
}

int BoxesNeeded(int apples)
{
  if (apples > 0)
  {
    int out = apples / 20;
    out += (apples % 20 > 0) ? 1 : 0;
    return out;
  }
  else
  {
    return 0;
  }
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total)
{
  if (A_correct > A_total || B_correct > B_total)
  {
    throw std::invalid_argument("Total number must be greater than correct number.");
  }
  else if (A_total <= 0 || A_correct < 0 || B_total <= 0 || B_correct < 0)
  {
    std::cout << A_correct << " " << A_total << " " << B_correct << " " << B_total << std::endl;
    throw std::invalid_argument("All inputs must be greater than zero.");
  }

  return A_correct / (A_total * 1.0) > B_correct / (B_total * 1.0);
}

bool GoodDinner(int pizzas, bool is_weekend)
{
  if (pizzas >= 10 && pizzas <= 20)
  {
    return true;
  }
  else if (pizzas >= 10 && is_weekend)
  {
    return true;
  }
  return false;
}


/* ADDITION OVERFLOW
*
*  case: value and n both positive
*  occurs when --> value + n > INT32_MAX
*  rewrite     --> value > INT32_MAX - n
*
*  logic statement --> if (value > 0) and (n > 0) and (value > INT32_MAX), then positive overflow
*                  --> if ((value > 0) && (n > 0) && (value > INT32_MAX)) {throw std::overflow_error("positive overflow");}
*
*
*  case: value and n both negative
*  occurs when --> (-)value + (-)n < INT32_MIN
*  rewrite     --> value > INT32_MAX - n
*
*  logic statement --> if (value > 0) and (n > 0) and (value > INT32_MAX), then positive overflow
*                  --> if ((value > 0) && (n > 0) && (value > INT32_MAX)) {throw std::overflow_error("positive overflow");}
*/
int SumBetween(int low, int high)
{
  // DEBUGGING
  std::cout << low << " -> " << high << std::endl;

  if (low > high)
  {
    throw std::invalid_argument("First input must be lower than second input.");
  }

  int value = 0;
  for (int n = low; n <= high; n++)
  { 
    // Skip over any part of range that consists of positive/negative counterparts
    // (eg -3 -> 3 would = 0, so we can just skip it by changing n = -3 to n = 3 and continuing)
    if (n < 0 && -n <= high)
    {
      n = -n;
    }

    // Regular execution if not skipping compliment range
    else
    {
      if (value > INT32_MAX - n && value > 0 && n > 0)
      { // Check for positive overflow 
        throw std::overflow_error("positive overflow");
      }
      else if (value < INT32_MIN - n && value < 0 && n < 0)
      { // Check for negative overflow
        throw std::overflow_error("negative overflow");
      }
      else
      { // If no overflow, add n to value and move on
        value += n;
      }
    }
  }

  return value;
}

/*  MULTIPLICATION OVERFLOW
 *
 *   if a and b are positive:
 *   occurs when --> a * b > INT32_MAX
 *   rewrite     --> a > INT32_MAX / b
 *
 *   logic statement --> if (a > 0) and (b > 0) and (a > INT32_MAX / b), then positive overflow
 *                   --> if ((a > 0) && (b > 0) && (a > INT32_MAX / b)) {throw std::overflow_error("positive overflow");}
 *
 *
 *   if a and b are negative:
 *   occurs when --> (-)a * (-)b > INT32_MAX
 *   rewrite     --> (-)a < INT32_MAX / (-)b <-- {equality flip for division by a negative number}
 *
 *   logic statement --> if (a < 0) and (b < 0) and (a < INT32_MAX / b), then positive overflow
 *                   --> if ((a < 0) && (b < 0) && (a < INT32_MAX / b)) {throw std::overflow_error("positive overflow");}
 *
 *
 *   if a is positive and b is negative:
 *   occurs when --> a * (-)b < INT32_MIN
 *   rewrite     --> a > INT32_MIN / (-)b <-- {equality flip for division by a negative number}
 *
 *   logic statement --> if (a > 0) and (b < 0) and (a > INT32_MIN / b), then negative overflow
 *                   --> if ((a > 0) && (b < 0) && (a > INT32_MIN / b)) {throw std::overflow_error("negative overflow");}
 *
 *
 *   if a is negative and b is positive:
 *   occurs when --> (-)a * b < INT32_MIN
 *   rewrite     --> a < INT32_MIN / b
 *
 *   logic statement --> if (a < 0) and (b > 0) and (a < INT32_MIN / b), then negative overflow
 *                   --> if ((a < 0) && (b > 0) && (a < INT32_MIN / b)) {throw std::overflow_error("negative overflow");}
 */
int Product(int a, int b)
{
  if (((a > 0) && (b > 0)) && (a > INT32_MAX / b))
  {
    throw std::overflow_error("positive overflow");
  }
  else if (((a < 0) && (b < 0)) && (a < INT32_MAX / b))
  {
    throw std::overflow_error("positive overflow");
  }
  else if ((a > 0) && (b < 0) && (a > INT32_MIN / b))
  {
    throw std::overflow_error("negative overflow");
  }
  else if ((a < 0) && (b > 0) && (a < INT32_MIN / b))
  {
    throw std::overflow_error("negative overflow");
  }

  return a * b;
}