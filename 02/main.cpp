#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y) == tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross (P a, P b) const { return (a-*this).cross(b-*this); }
	T dot(P p) const { return x*p.x + y*p.y; }
};

typedef Point<double> Pd;

template<class T>
T polygonArea(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	rep(i,0,sz(v)-1) {
		a += v[i].cross(v[i+1]);
	}
	//cout << endl;
	return a;
}

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
		 oc = a.cross(b, c), od = a.cross(b, d);
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {all(s)};
}

const double E = 0.0000001;

pair<double, double> area(vector<Pd> points, vector<pair<Pd, Pd>> edges, double a, Pd minp, Pd maxp) {
	pair<Pd, Pd> a_line_seg = {Pd(minp.x, a), Pd(maxp.x, a)};
	vector<Pd> intersections;
	vector<Pd> top;
	vector<Pd> bottom;
	for (auto edge : edges) {
		auto inters = segInter(a_line_seg.first, a_line_seg.second, edge.first, edge.second);
		if (inters.size() == 0) continue;
		if (inters.size() > 1) {
			if (abs(inters[0].y - minp.y) < E && abs(inters[1].y - minp.y) < E) {

				return {1 , 0};
			} else {
				return {0, 1};
			}
		}
        auto inter = inters[0];
		intersections.push_back(inter);
	}
	if (intersections.size() > 1) {
		if (intersections[0].x > intersections[1].x) {
			swap(intersections[0], intersections[1]);
		}
	}
	for (auto inter : intersections) {
		top.push_back(inter);
		bottom.push_back(inter);
	}
	for (auto point : points) {
		if (point.y > a) {
			top.push_back(point);
		} else {
			bottom.push_back(point);
		}
	}
	if (top.size() > 3) {
		if (top[2].x < top[3].x) {
			swap(top[2], top[3]);
		}
	}
	if (bottom.size() > 3) {
		if (bottom[2].x < bottom[3].x) {
			swap(bottom[2], bottom[3]);
		}
	}
	/*
	for (auto point : top) {
		cout << "top has: " << point.x << ", " << point.y << endl;
	}
	for (auto point : bottom) {
		cout << "bottom has: " << point.x << ", " << point.y << endl;
	}
	*/
	double top_area = abs(polygonArea(top));
	double bottom_area = abs(polygonArea(bottom));
//	cout << "bottom area: " << bottom_area << " top_area: " << top_area << endl;
	return {top_area, bottom_area};
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	Pd p1, p2, p3;

	try {
		while (cin >> p1.x && cin >> p1.y && cin >> p2.x && cin >> p2.y && cin >> p3.x && cin >> p3.y) {
			vector<pair<Pd, Pd>> edges(3);
			vector<Pd> points = {p1, p2, p3};
			edges[0] = {p1, p2};
			edges[1] = {p2, p3};
			edges[2] = {p1, p3};
			Pd minp(min(min(p1.x, p2.x), p3.x), min(min(p1.y, p2.y), p3.y));
			Pd maxp(max(max(p1.x, p2.x), p3.x), max(max(p1.y, p2.y), p3.y));
			//cout << areas.first << " " << areas.second << endl;
			double start = minp.y, end = maxp.y;
		//	cout << start << " " << end << endl;
			while (abs(start - end) > 0.0000001) {
				double h = start + (end - start)/2;
				//cout << "  h = " << h << endl;
				auto areas = area(points, edges, h, minp, maxp);
				if (areas.first > areas.second) {
					start = h + 0.0000001;
					//cout << "  top bigger" << endl;
				} else {
					end = h;
					//cout << "  bottom bigger" << endl;
				}
				//cout << "ok: " << start << " " << end << endl;
			}
			cout << fixed << setprecision(5) << start << endl;
		}
	} catch (...) {
		return 0;
	}
	return 0;

}
