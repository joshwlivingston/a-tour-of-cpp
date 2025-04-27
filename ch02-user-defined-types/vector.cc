/* Construct a vector piece by piece */
class Vector {
public:
  Vector(int s) : elements{new double[s]}, size_{s} {}

  double &operator[](int i) {return elements[i];}
  int    size()             {return size_;}
private:
  double *elements;
  int    size_;
};
