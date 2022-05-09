class complex_number{
private:
    double Re = 0, Im = 0; 
    
public:
    complex_number(double);
    complex_number(double, double);
    double rez();
    double imz();
    friend complex_number convpol(int i, float rad, float phi);
    complex_number& operator+=(const complex_number &);
    complex_number& operator-=(const complex_number &);
    complex_number operator*=(const complex_number &);
    friend complex_number operator+(const complex_number &, const complex_number &);
    friend complex_number operator-(const complex_number &, const complex_number &);
    friend complex_number operator*(const complex_number &, const complex_number &);
    friend std::ostream& operator<<(std::ostream &out, const complex_number &z);
};

complex_number operator+(const complex_number &, const complex_number &);
complex_number operator-(const complex_number &, const complex_number &);
complex_number operator*(const complex_number &, const complex_number &);
std::ostream& operator<<(std::ostream &out, const complex_number &z);

complex_number convpol(int i, float rad, float phi);
