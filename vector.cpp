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


Vector::Vector(int s) : elements{new double[s]}, size_{s} {}

double &Vector::operator[](int i)
{
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
