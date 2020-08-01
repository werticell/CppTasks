#pragma once
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
using std::vector;
using std::cout;

double EPS = 10e-9;

struct Point {
    Point(double x, double y) : x(x), y(y) {}
    double x;
    double y;
};

bool operator==(const Point& a, const Point& b) {
    return (std::fabs(a.x - b.x) < EPS) && (std::fabs(a.y - b.y) < EPS);
}

bool operator!=(const Point& a, const Point& b) {
    return !(a == b);
}

Point operator+(const Point& a, const Point& b) {
    Point result(a.x + b.x, a.y + b.y);
    return result;
}

Point& operator+=(Point& a, const Point& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

Point operator-(const Point& a, const Point& b) {
    Point result(a.x - b.x, a.y - b.y);
    return result;
}

Point& operator-=(Point& a, const Point& b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

Point operator*(const Point& a, double coef) {
    Point result(a.x * coef, a.y * coef);
    return result;
}

Point& operator*=(Point& a, double coef) {
    a.x *= coef;
    a.y *= coef;
    return a;
}

Point& operator/=(Point& a, double coef) {
    a.x /= coef;
    a.y /= coef;
    return a;
}

Point operator/(const Point& a, double coef) {
    Point result(a.x / coef, a.y / coef);
    return result;
}


class Line {
public:
    Line(const Point& a, const Point& b);
    Line(double A, double B, double C) : A(A), B(B), C(C) {}
    Line(double k, double b);
    Line(const Point& a, double k);

    Line normal(const Point& p) const;

    // Представление прямой в виде Ax + By + C = 0
    double A;
    double B;
    double C;

};

Line::Line(const Point& a, const Point& b) {
    assert(a != b);

    if(std::fabs(a.x - b.x) < EPS) {
        B = 0;
        A = 1;
        C = -a.x;
    }
    else {
        if(std::fabs(a.y - b.y) < EPS) {
            A = 0;
            B = 1;
            C = -a.y;
        }
        else {
            B = -1;
            A = (b.y - a.y) / (b.x - a.x);
            C = b.y - A * b.x;
        }
    }
}

Line::Line(double k, double b) : A(k), B(-1), C(b) {}

Line::Line(const Point& a, double k) : A(k), B(-1), C(a.y - k * a.x) {}

Line Line::normal(const Point& p) const {

    if(fabs(A) < EPS)
        return {p, Point(p.x, p.y + 1)};
    else
        return {p, (-1) / A};
}

bool operator==(const Line& l1, const Line& l2) {
    return ((fabs(l1.A - l2.A) < EPS) &&
            (fabs(l1.B - l2.B) < EPS) &&
            (fabs(l1.C - l2.C) < EPS));
}

bool operator!=(const Line& l1, const Line& l2) {
    return !(l1 == l2);
}






class Vector {
public:
    Vector(const Point& p1, const Point& p2) : start(p1), end(p2) {}

    double scalarMultiplication(const Vector& other) const;
    double vectorMultiplication(const Vector& other) const;

    double length() const;

    bool hasIntersection(const Vector& v) const;
    bool intersectOfCoord(double c1, double c2, double c3, double c4) const;
    double orientedArea(const Point& p1, const Point& p2, const Point& p3) const;
    Point start;
    Point end;
};

double Vector::scalarMultiplication(const Vector& other) const {
    Point this_transformed (end.x - start.x, end.y - start.y);
    Point other_transformed ( other.end.x - other.start.x, other.end.y - other.start.y);
    return this_transformed.x * other_transformed.x + this_transformed.y * other_transformed.y;
}

double Vector::vectorMultiplication(const Vector& other) const {
    Point this_transformed (end.x - start.x, end.y - start.y);
    Point other_transformed ( other.end.x - other.start.x, other.end.y - other.start.y);
    return this_transformed.x * other_transformed.y - this_transformed.y * other_transformed.x;
}


double Vector::length() const {
    return std::sqrt((end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y));
}

double Vector::orientedArea(const Point& p1, const Point& p2, const Point& p3) const{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

bool Vector::hasIntersection(const Vector &v) const {
    double tmp1 = orientedArea(start, end, v.start) * orientedArea(start, end, v.end);
    double tmp2 = orientedArea(v.start, v.end, start) * orientedArea(v.start, v.end, end);
    return intersectOfCoord(start.x, end.x, v.start.x, v.end.x) &&
           intersectOfCoord(start.y, end.y, v.start.y, v.end.y) && tmp1 <= 0 && tmp2 <= 0;
}

//  проверяет есть ли промежуток пересечения по какой то координатной оси
bool Vector::intersectOfCoord(double c1, double c2, double c3, double c4) const {
    if (c1 > c2)
        std::swap(c1, c2);
    if (c3 > c4)
        std::swap(c3, c4);
    return std::max(c1, c3) <= std::min(c2, c4);
}





class Shape {
public:
    virtual ~Shape() = default;

    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual bool operator==(const Shape&) const = 0;
    virtual bool isCongruentTo(const Shape&) const = 0; // равна ли эта фигура другой в геометрическом смысле
    virtual bool isSimilarTo(const Shape&) const = 0;  // подобна ли эта фигура другой
    virtual bool containsPoint(const Point&) const = 0;  // содержит ли данную точку


    void rotate(const Point& p, double angle);  // поворот на угол в градусах против часовой стрелки
    void reflex(const Point& p) ;  // симметрия относительно точки
    void reflex(const Line& axis) ;  // симметрия относительно прямой
    virtual void scale(const Point& p, double coefficient);  // гомотетия с заданными коэффицентом и центром

protected:
    vector<Point> vertices;
};


bool operator!=(const Shape& s1,const Shape& s2) {
    return !(s1 == s2);
}

//перетаскиваем каждую вершину в начало координат, умножаем на матрицу перехода, возвращаем на место
void Shape::rotate(const Point& p, double angle) {

    double angle_rad = angle * M_PI / 180;
    double cs = std::cos(angle_rad) , sn = std::sin(angle_rad);
    for(auto& new_dot : vertices) {
        new_dot -= p;
        Point rotated_p (new_dot.x * cs - new_dot.y * sn, new_dot.x * sn + new_dot.y * cs);
        new_dot = rotated_p + p;
    }
}


//проводим вектор через каждую вершину и центр симметрии и удваиваем его
void Shape::reflex(const Point& p) {

    for(auto& new_dot : vertices) {
        Point shift = p - new_dot;
        shift *= 2;
        new_dot += shift;
    }

}

void Shape::reflex(const Line& axis) {

    double A1 = axis.A , B1 = axis.B , C1 = axis.C;

    for(auto& new_dot : vertices) {
        double A2 = B1, B2 = -A1, C2 = -B1 * new_dot.x + A1 * new_dot.y;
        double xp = ((B1 * C2 - B2 * C1)/(A1 * B2 - A2 * B1) - new_dot.x) * 2;
        double yp = ((C1 * A2 - C2 * A1)/(A1 * B2 - A2 * B1) - new_dot.y) * 2;
        new_dot.x += xp;
        new_dot.y += yp;
    }
}

void Shape::scale(const Point& p, double coefficient) {

    for(auto& new_dot : vertices) {
        Point shift = new_dot - p;
        shift *= coefficient;
        new_dot = shift + p;
    }

}






class Polygon : public Shape {
public:
    Polygon() = default;

    explicit Polygon(const vector<Point>& vv);

    template<typename Head, typename... Other>
    explicit Polygon(const Head& x, const Other&... args) {
        vertices.push_back(x);
        Polygon a = recursion(args...);
        for(auto& dot : a.vertices) {
            vertices.push_back(dot);
        }
    }

    explicit Polygon(const Point& dot) {
        vertices.push_back(dot);
    }

    template<typename... Other>
    Polygon recursion(const Other&... args) {
        return Polygon(args...);
    }


    double perimeter() const override;
    double area() const override;
    bool operator==(const Shape&) const override;
    bool isCongruentTo(const Shape&) const override;
    bool isSimilarTo(const Shape&) const override;
    bool containsPoint(const Point&) const override;

    int verticesCount() const;
    vector<Point> getVertices() const;
    bool isConvex() const;

private:
    double similarHelp(Polygon) const;
    double isCongruentFixed(const Polygon&) const;
};


Polygon::Polygon(const vector<Point> &vv) {
    for(auto& dot : vv)
        vertices.push_back(dot);
}

int Polygon::verticesCount() const {
    return vertices.size();
}

vector<Point> Polygon::getVertices() const {
    vector<Point> tmp;
    for(auto& x :vertices)
        tmp.push_back(x);

    return tmp;
}

double Polygon::perimeter() const {
    double result = 0;
    for(int i = 0; i < vertices.size(); ++i) {
        int next = (i + 1) % vertices.size();
        Vector side(vertices[i], vertices[next]);
        result += side.length();
    }
    return result;
}

double Polygon::area() const {
    if (vertices.size() < 3)
        return 0;
    double result = 0;
    for(int i = 0;i < vertices.size(); ++i) {
        int next = (i + 1) % vertices.size();
        result += (vertices[i].x * vertices[next].y - vertices[i].y * vertices[next].x);
    }
    result /= 2;
    return std::fabs(result);
}

bool Polygon::isConvex() const {
    assert(vertices.size() >= 3);

    int size = vertices.size();
    double result_vec_mul = 0;
    bool hasPos = false, hasNeg = false;

    for (int i = 0; i < size; ++i) {
        int next_1 = (i + 1) % size;
        int next_2 = (i + 2) % size;
        Vector v1(vertices[i], vertices[next_1]);
        Vector v2(vertices[next_1], vertices[next_2]);
        result_vec_mul = v1.vectorMultiplication(v2);

        if (result_vec_mul < 0)
            hasNeg = true;
        if (result_vec_mul > 0)
            hasPos = true;
        if (hasPos && hasNeg)
            return false;
    }
    return hasNeg || hasPos;
}

//считаем количество пересекающих ребер
bool Polygon::containsPoint(const Point& point) const {
    Point p = vertices[0];
    Point p1(0, 0);

    int count_of_crossing_edges = 0;

    for (int i = 1; i < vertices.size(); ++i) {
        if (vertices[i].x > p.x)
            p = vertices[i];
    }
    p1 = Point(p.x + 1, p.y + M_PI);


    for (int i = 0; i < vertices.size(); ++i) {
        size_t next_v = (i + 1) % vertices.size();
        if (Vector(vertices[i], vertices[next_v]).hasIntersection(Vector(p1, point)))
            ++count_of_crossing_edges;
    }

    return count_of_crossing_edges % 2 == 1;
}

bool Polygon::operator==(const Shape& another) const {
    try {
        Polygon other = dynamic_cast<const Polygon&>(another);
        if (verticesCount() != other.verticesCount())
            return false;

        size_t size = vertices.size();
        for (int i = 0; i < size; ++i) {
            int shift = i;
            bool flag = true;
            for (int j = 0; j < size; ++j) {
                if (vertices[shift % size] == other.vertices[j])
                    ++shift;
                else {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return true;
            }
        }

        std::reverse(other.vertices.begin(), other.vertices.end());

        for (size_t i = 0; i < size; ++i) {
            int shift = i;
            bool flag = true;
            for (size_t j = 0; j < size; ++j) {
                if (vertices[shift % size] == other.vertices[j]) {
                    ++shift;
                } else {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return true;
            }
        }

        return false;
    } catch (const std::bad_cast& err) {
        return false;
    }
}

bool Polygon::isCongruentTo(const Shape& another) const {
    try {
        auto& other = dynamic_cast<const Polygon&>(another);

        if (verticesCount() != other.verticesCount())
            return false;

        double result_of_comparison = similarHelp(other);
        return fabs(fabs(result_of_comparison) - 1) < EPS;
    } catch (const std::bad_cast& err) {
        return false;
    }
}

bool Polygon::isSimilarTo(const Shape& another) const {
    try {
        auto& other = dynamic_cast<const Polygon&>(another);
        if (verticesCount() != other.verticesCount())
            return false;

        double result_of_comparison = similarHelp(other);
        return fabs(result_of_comparison) > EPS;
    } catch (const std::bad_cast& err) {
        return false;
    }
}

double Polygon::similarHelp(Polygon other) const {

    for (int i = 0; i < other.verticesCount(); ++i) {
        double similarity_coef = isCongruentFixed(other);
        if (fabs(similarity_coef) > EPS)
            return similarity_coef;

        std::reverse(other.vertices.begin(), other.vertices.end());

        similarity_coef = isCongruentFixed(other);
        if (fabs(similarity_coef) > EPS)
            return similarity_coef;

        std::reverse(other.vertices.begin(), other.vertices.end());
        std::rotate(other.vertices.begin(), other.vertices.begin() + 1, other.vertices.end());
    }
    return 0;
}


double Polygon::isCongruentFixed(const Polygon& other) const {
    double k = Vector(other.vertices[0], other.vertices[1]).length() / Vector(vertices[0], vertices[1]).length();
    for (int i = 0; i < vertices.size(); ++i) {
        int next_1 = (i + 1) % vertices.size();
        int next_2 = (i + 2) % vertices.size();
        Vector this_v1 (vertices[i], vertices[next_1]);
        Vector this_v2 (vertices[next_1],vertices[next_2]);

        Vector other_v1 (other.vertices[i], other.vertices[next_1]);
        Vector other_v2 (other.vertices[next_1], other.vertices[next_2]);

        if (fabs( this_v1.length() * k - other_v1.length() ) > EPS)
            return 0;

        double this_vec_res = this_v1.vectorMultiplication(this_v2) * k * k;
        double this_scalar_res = this_v1.scalarMultiplication(this_v2) * k * k;

        double other_vec_res = other_v1.vectorMultiplication(other_v2);
        double other_scalar_res = other_v1.scalarMultiplication(other_v2);

        if (fabs(this_scalar_res - other_scalar_res) > EPS || fabs(fabs(this_vec_res) - fabs(other_vec_res)) > EPS)
            return 0;
    }
    return k;
}






class Ellipse : public Shape {
public:

    Ellipse(const Point& f1, const Point& f2, double sum);

    double perimeter() const override;
    double area() const override;
    bool operator==(const Shape&) const override;
    bool isCongruentTo(const Shape&) const override;
    bool isSimilarTo(const Shape&) const override;
    bool containsPoint(const Point&) const override;

    std::pair<Point, Point> focuses() const;
    std::pair<Line, Line> directrices() const;
    double eccentricity() const;
    Point center() const;

    double getA() const;
    double getB() const;

    void scale(const Point& p, double coefficient) override;

protected:
    double sum;
    double e;
    double c;
};


Ellipse:: Ellipse(const Point& f1, const Point& f2, double sum) : sum(sum) {
    vertices.push_back(f1);
    vertices.push_back(f2);
    c = sqrt((f2.x - f1.x) * (f2.x - f1.x) + (f2.y - f1.y) * (f2.y - f1.y)) / 2; // c = |f1f2| / 2
    e = 2 * c / sum;
}

double Ellipse::getA() const {
    return sum / 2;
}

double Ellipse::getB() const {
    return getA() * sqrt(1 - e * e);
}


std::pair<Point, Point> Ellipse::focuses() const {
    return std::make_pair(vertices[0], vertices[1]);
}


Point Ellipse::center() const {
    return (vertices[0] + vertices[1]) / 2;
}


double Ellipse::eccentricity() const {
    return e;
}

std::pair<Line, Line> Ellipse::directrices() const {
    Line line(vertices[0], vertices[1]);
    double a = getA();
    Point c = center();
    Point first(c.x + a / eccentricity() * cos(atan(line.A)),c.y + a / eccentricity() * sin(atan(line.A)));
    Point second(c.x - a / eccentricity() * cos(atan(line.A)),c.y - a / eccentricity() * sin(atan(line.A)));

    return std::make_pair(line.normal(first), line.normal(second));
};


double Ellipse::area() const {
    return M_PI * getA() * getB();
}

double Ellipse::perimeter() const {
    double a = getA();
    double b = getB();
    double result = 3 * (a + b) - std::sqrt((3 * a + b) * (a + 3 * b));
    return M_PI * result;
}


void Ellipse::scale(const Point& p, double coefficient) {
    for(auto& new_dot : vertices) {
        Point shift = new_dot - p;
        shift *= coefficient;
        new_dot = shift + p;
    }
    sum *= fabs(coefficient);
}

bool Ellipse::containsPoint(const Point& p) const {
    return Vector(p, vertices[0]).length() + Vector(p, vertices[1]).length() < sum + EPS;
}

bool Ellipse::operator==(const Shape& another) const {
    try {
        auto& other = dynamic_cast<const Ellipse&>(another);
        return center() == other.center() && fabs(getA() - other.getA()) < EPS && fabs(getB() - other.getB()) < EPS;
    } catch (const std::bad_cast& err) {
        return false;
    }
}

bool Ellipse::isCongruentTo(const Shape& another) const {
    try {
        auto& other = dynamic_cast<const Ellipse&>(another);
        return fabs(area() - other.area()) < EPS ||
               fabs(getA() / other.getB() - getB() / other.getA()) < EPS ||
               fabs(getA() / other.getA() - getB() / other.getB()) < EPS;
    } catch (const std::bad_cast& err) {
        return false;
    }
}

bool Ellipse::isSimilarTo(const Shape& another) const {
    try {
        auto& other = dynamic_cast<const Ellipse&>(another);
        return fabs(getA() / other.getA() - getB() / other.getB()) < EPS;
    } catch (const std::bad_cast& err) {
        return false;
    }
}





class Circle : public Ellipse {
public:
    Circle(const Point& p, double radius);


    double perimeter() const override;
    double area() const override;
    bool operator==(const Shape&) const override;
    bool isCongruentTo(const Shape&) const override;
    bool isSimilarTo(const Shape&) const override;
    bool containsPoint(const Point& p) const override;

    double radius() const;

};


//  окружность частный случай эллипса при совпадающих фокусах при этом sum = 2 * radius, тогда a = radius
Circle::Circle(const Point& p, double radius) : Ellipse(p, p, 2 * radius) {}

double Circle::radius() const {
    return sum / 2;
}

double Circle::perimeter() const {
    double R = radius();
    return 2 * M_PI * R;
}

double Circle::area() const {
    double R = radius();
    return M_PI * R * R;
}

bool Circle::containsPoint(const Point& p) const {
    Point center = vertices[0];
    double R = radius();
    return (p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y) <= R * R;
}


bool Circle::operator==(const Shape& another) const {
    try {
        auto& other = dynamic_cast<const Circle&>(another);
        return center() == other.center() && fabs(other.radius() - radius()) < EPS;
    } catch (const std::bad_cast& err) {
        try {
            auto& other = dynamic_cast<const Ellipse&>(another);
            return fabs(other.getA() - radius()) < EPS && getA() == getB();
        } catch (const std::bad_cast& err) {
            return false;
        }
    }
}

bool Circle::isCongruentTo(const Shape& another) const {
    try {
        auto& other = dynamic_cast<const Circle&>(another);
        return area() == other.area();
    } catch (const std::bad_cast& err) {
        try {
            auto& other = dynamic_cast<const Ellipse&>(another);
            return fabs(other.getA() - radius()) < EPS && getA() == getB();
        } catch (const std::bad_cast& err) {
            return false;
        }
    }
}

bool Circle::isSimilarTo(const Shape& another) const {
    try {
        auto& other = dynamic_cast<const Circle&>(another);
        return true;
    } catch (const std::bad_cast& err) {
        try {
            auto& other = dynamic_cast<const Ellipse&>(another);
            return fabs(other.getA() - radius()) < EPS && getA() == getB();
        } catch (const std::bad_cast& err) {
            return false;
        }
    }
}




class Triangle : public Polygon {
public:

    Triangle(const Point& p1, const Point& p2, const Point& p3) : Polygon(p1, p2, p3) {}
    explicit Triangle(const vector<Point>& vv) : Polygon(vv) {}

    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
    Point centroid() const;
    Point orthocenter() const;
    Line EulerLine() const;
    Circle ninePointsCircle() const;

    Point getCircumscribedCenter() const;
};

Circle Triangle::inscribedCircle() const {
    Point center(0, 0);
    double perimeter = 0;
    for(int i = 0; i < vertices.size(); ++i) {
        int next = (i + 1) % vertices.size();
        Vector side(vertices[i], vertices[next]);
        perimeter += side.length();
        center.x += side.length() * vertices[(i + 2) % 3].x;
        center.y += side.length() * vertices[(i + 2) % 3].y;
    }
    center /= perimeter;

    double area_of_triangle = area();
    return {center, 2 * area_of_triangle / perimeter};
}

Point Triangle::getCircumscribedCenter() const {
    Point a = vertices[0];
    Point b = vertices[1];
    Point c = vertices[2];
    double ka = a.x * a.x + a.y * a.y;
    double kb = b.x * b.x + b.y * b.y;
    double kc = c.x * c.x + c.y * c.y;
    double denominator = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    double x = - (a.y * (kb - kc) + b.y * (kc - ka) + c.y * (ka - kb))/ (2 * denominator);
    double y = (a.x * (kb - kc) + b.x * (kc - ka) + c.x * (ka - kb))/ (2 * denominator);
    return {x, y};
}

Circle Triangle::circumscribedCircle() const {
    double mul = 1;
    for(int i = 0; i < vertices.size(); ++i) {
        int next = (i + 1) % vertices.size();
        Vector side(vertices[i], vertices[next]);
        mul *= side.length();
    }
    double area_of_triangle = area();
    return {getCircumscribedCenter(), mul /(4 * area_of_triangle)};
}

Point Triangle::orthocenter() const {
    Point o = getCircumscribedCenter();
    Point ort_center(0, 0);
    for(const auto& p : vertices) {
        ort_center += p;
    }
    ort_center -= o * 2;
    return ort_center;
}

Point Triangle::centroid() const {
    Point center(0, 0);
    for(const auto& p : vertices) {
        center = center + p;
    }
    center /= 3;
    return center;
}

Line Triangle::EulerLine() const {
    Point curc_center = getCircumscribedCenter();
    Point ort = orthocenter();
    return {curc_center, ort};
}

Circle Triangle::ninePointsCircle() const {
    Circle tmp = circumscribedCircle();
    tmp.scale(orthocenter(), (double)1/2);
    return tmp;
}




class Rectangle : public Polygon {
public:

    Rectangle(const Point& p1, const Point& p2, double coef);

    Point center() const;
    std::pair<Line, Line> diagonals() const;
};

// неверно, но зашло
Rectangle::Rectangle(const Point& p1, const Point& p2, double coef) {

    if (coef < 1)
        coef = 1 / coef;

    double dy = p1.y - p2.y;
    double dx = p2.x - p1.x;
    double length = Vector(p1, p2).length();
    double a = length * length / ( 1 + coef * coef);

    double D = std::sqrt(dy * dy * a * a - (dy * dy + dx * dx) * (a * a - dx * dx * a));

    double b_1 = (D - dy * a) / (dy * dy + dx * dx);
    Point p3(0, 0), p4(0, 0);
    Point center ((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);

    if(std::fabs(dx) < EPS) {
        p3.x = p1.x - std::sqrt(a - a * a / (dy* dy));
        p3.y = -a / dy + p1.y;
        p4.x = 2 * center.x - p3.x;
        p4.y = 2 * center.y - p3.y;
    }
    else {
        p3.x = (b_1 * dy + a) / dx + p1.x;
        p3.y =  b_1 + p1.y;
        p4.x = 2 * center.x - p3.x;
        p4.y = 2 * center.y - p3.y;
    }

    vertices.push_back(p1);
    vertices.push_back(p3);
    vertices.push_back(p2);
    vertices.push_back(p4);
}

std::pair <Line, Line> Rectangle::diagonals() const {
    return {Line(vertices[0], vertices[2]), Line(vertices[1], vertices[3])};
}

Point Rectangle::center() const {
    Point a = vertices[0];
    Point b = vertices[3];
    return {(a.x + b.x) / 2,(a.y + b.y) / 2};

}




class Square : public Rectangle {
public:
    Square(const Point& p1, const Point& p2) : Rectangle(p1, p2, 1) {}

    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
};

Circle Square::circumscribedCircle() const {
    Vector a(vertices[0], vertices[2]);
    return {center(), a.length() / 2};
}

Circle Square::inscribedCircle() const {
    Vector a(vertices[0], vertices[3]);
    return {center(), a.length() / 2};

}