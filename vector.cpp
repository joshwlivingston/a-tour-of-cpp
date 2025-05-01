import std;

export module Vector;

export class Vector {
public:
  Vector(int);

  double &operator[](int);
  int    size();
private:
  double *elements;
  int    size_;
};


Vector::Vector(int s) {
  if (s < 0)
    throw std::length_error { "Vector constructor: negative size" };
  elements  = new double[s];
  size_ = s;
}

double &Vector::operator[](int i)
{
  if (i < 0 || i >= size())
    throw std::out_of_range { "Vector::operator[]" };
  return elements[i];
}

int size()
{
  return size_;
}

export bool operator==(const Vector &lhs, const Vector &rhs)
{
  if (lhs.size() != rhs.size())
    return false;
  for (int i = 0; i != rhs.size(); ++i)
    if (rhs[i] != lhs[i])
      return false;
  return true;
}

void test_vector(int n)
{
  try {
    Vector v(n);
  }
  catch (std::length_error &err) {
    std::cerr << "test failed: length error\n";
    throw;
  }
  catch (std::bad_allod &err) {
    std::terminate();
  }
}

void run_test_vector()
{
  test(-27);               // throws length_error
  test(1'000'000'000'000); // may throw bad_alloc
  test(10);                // OK
}
