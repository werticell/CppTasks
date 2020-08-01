#include "geometry.h"
using std::cout;
using std::endl;

/* Answer
 * iiiiii18.5
 * asdas166.5
 * r == 0.517454 R == 1.15244
 * wow6 6
 * 1 1 1 1
 * 0 1 1 0
 * 0 1 1 0
 * 1000110
 */

double distance(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool equals(double left, double right) {
    return fabs(right - left) < EPS;
}

int main() {
    try {
        const int ax = -2, ay = 2, bx = 1, by = 2,
                cx = 3, cy = -1, dx = -1, dy = -2,
                ex = 1, ey = -1, fx = 6, fy = 1;
        Point a(ax, ay);
        Point b(bx, by);
        Point c(cx, cy);
        Point d(dx, dy);
        Point e(ex, ey);
        if (!equals(distance(a, b), 3)) {
            throw 1;
        }
        Line ae(a, e);
        Line ea(e, a);
        Line line1(3, 5);
        Line line2(c, -1.5);
        for (unsigned i = 0; i < 1000000; ++i) {
            Shape *square = new Square(a, e);
            delete square;
        }
        Point f(fx, fy);
        Polygon abfcd(a, b, f, c, d);
        std::vector<Point> vec = {c, f, b, a, d};
        Polygon cfbad(vec);
        if (abfcd != cfbad) {
            throw 3;
        }
        if (!abfcd.isConvex()) {
            throw 4;
        }
        Polygon bfced(b, f, c, e, d);
        if (bfced.isConvex()) {
            throw 5;
        }
        Triangle abd(a, b, d);
        Polygon abfced(a, b, f, c, e, d);
        if (!equals(abd.area() + bfced.area(), abfced.area())) {
            throw 6;
        }

        if (abd.isSimilarTo(abfced)) {
            throw 7;
        }

        if (abfced.isCongruentTo(abd)) {
            throw 8;
        }
        Polygon newAbfced = abfced;
        newAbfced.rotate(Point(0, 0), 50);
        newAbfced.scale(Point(0,0),3);
        cout << "iiiiii" << abfced.area() << endl;
        cout << "asdas" << newAbfced.area() << endl;
        if (!equals(9 * abfced.area(), newAbfced.area())) {
//            cout << abfcd.area() << endl;
//            cout << newAbfced.area() << endl;
            throw 9; // if crashes, comment
        }
        if (!equals(3 * abfced.perimeter(), newAbfced.perimeter())) {
            cout << abfcd.perimeter() << endl;
            cout << newAbfced.perimeter() << endl;
            throw 10; // if crashes, comment
        }
        if (!abfced.isSimilarTo(newAbfced)) {
            throw 11;
        }
        newAbfced.scale(a, 1. / 3);
        newAbfced.reflex(line1);
        newAbfced.rotate(Point( 0.5, 1.2),49 );
        if (!abfced.isCongruentTo(newAbfced)) {
            throw 12;
        }

        if (newAbfced == abfced) {
            throw 13;
        }
        Point k(3, 1);

        Polygon bfkce(c, k, f, b, e);

        Rectangle rec_ae1(e, a, 1);

        Square sq_ae(a, e);

        if (rec_ae1 != sq_ae) {
            throw 14;
        }
        Circle b3(b, 3);

        Ellipse cf5(c, f, 5);

        std::vector<Shape *> shapes;
        shapes.push_back(&abfced);
        shapes.push_back(&abd);
        shapes.push_back(&sq_ae);
        shapes.push_back(&rec_ae1);
        shapes.push_back(&bfkce);
        shapes.push_back(&b3);
        shapes.push_back(&cf5);
        for (size_t i = 0; i < shapes.size(); ++i) {
            std::cerr << shapes[i]->containsPoint(
                    Point(2, 1)); //1000110
        }

        for (size_t i = 0; i < shapes.size(); ++i) {
            shapes[i]->scale(Point(5, 5), 0.5);
        }
        Circle incircle = abd.inscribedCircle();
        Circle circumcircle = abd.circumscribedCircle();
        Point inc = incircle.center();
        Point circ = circumcircle.center();
        double r = incircle.radius(), R = circumcircle.radius();
        std::cout << " r == " << r << " R == " << R << std::endl;
        bool ok = equals(distance(inc, circ), sqrt(R * R - 2 * R * r));
        ok = equals(distance(inc, circ), sqrt(R * R - 2 * R * r));
        if (!ok)
            throw 15;

        Circle eulerCircle = abd.ninePointsCircle();
        Line eulerLine = abd.EulerLine();
        Point orc = abd.orthocenter();
        ok = equals(distance(orc, eulerCircle.center()), distance(circ, eulerCircle.center()));
        if (!ok)
            throw 16;
        ok = equals(circumcircle.radius() / 2, eulerCircle.radius());
        if (!ok)
            throw 17;
        Circle anotherCircle = eulerCircle;
        anotherCircle.scale(orc, 2);

        Point centreeeeoid = abd.centroid();
        Point elllleeeer = eulerCircle.center();
        Line EulerLine = eulerLine;
        Line axxxx = Line(eulerCircle.center(), abd.centroid());

        ok = Line(eulerCircle.center(), abd.centroid()) == eulerLine;
        if (!ok)
            throw 18;
    }
    catch (int expr) {
        std::cerr << "Test " << expr << "failed\n";
    }
    cout << "wow";

    Point A( 1, 1), B(2,0), C(1, -1), D( -1, -1), E(-2, 0), F( -1, 1);
    Polygon pol( A, B, C, D, E, F);
    Polygon other( A, F, E,  D, C, B );
    cout << pol.area() << " " << other.area() << endl;
    cout << ( pol == other ) << " " << pol.isSimilarTo(other) << " " << other.isSimilarTo(pol) << " " << other.isCongruentTo( pol) << endl;
    other.rotate(Point(0,0), 50);
    other.scale( Point( 0, 0), 3);
    other.reflex( C );
    other.reflex( Line( Point(5,5), Point( 3, -4 ) ) );
    cout << ( pol == other ) << " " << pol.isSimilarTo(other) << " " << other.isSimilarTo(pol) << " " << other.isCongruentTo( pol) << endl;
    other.rotate( Point(-5,0.3), 48.9);
    cout << ( pol == other ) << " " << pol.isSimilarTo(other) << " " << other.isSimilarTo(pol) << " " << other.isCongruentTo( pol) << endl;

    Point a(-2, 2),  e(1, -1);

    return 0;
}

