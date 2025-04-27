/* Construct a vector piece by piece */
class Vector {
public:
  Vector(int);

  double &operator[](int);
  int    size();
private:
  double *elements;
  int    size_;
};

