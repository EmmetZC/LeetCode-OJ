#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <unordered_set>
#include <limits>
using namespace std;

struct Vertice {
	double x;
	double y;

	Vertice(double _x, double _y) :x(_x), y(_y) {}

	double getDistance(Vertice v2) {
		return sqrt(pow(x - v2.x, 2) + pow(y - v2.y, 2));
	}
};

class Solution {
public:
	int times = 0;
	vector<Vertice> Cities;
	vector<vector<double>> Distance;
	unsigned N;
	unsigned START_CITY = 0;
	vector<unsigned> sPath;
	double sPathLen;

	vector<unsigned> InitWithRandomOrder() {
		vector<unsigned> result;
		for (unsigned i = 0; i < N; ++i) {
			if (i == START_CITY) {
				continue;
			}
			result.push_back(i);
		}
		auto left = result.size();
		while (left > 0) {
			unsigned i = rand() % left;
			auto tmp = result[left - 1];
			result[left - 1] = result[i];
			result[i] = tmp;
			left--;
		}
		result.insert(result.begin(), START_CITY);
		result.push_back(START_CITY);
		return result;
	}

	double CountPathLen(vector<unsigned> p) {
		double result = 0;
		for (unsigned i = 0; i < p.size() - 1; ++i) {
			result += Distance[p[i]][p[i + 1]];
		}
		return result;
	}
	
	double GetMinSpanTreeLen(vector<unsigned> g) {
		double result = .0;
		auto v = g[g.size() - 1];
		g.pop_back();
		while (!g.empty()) {
			unsigned closestIndex;
			auto closestDist = numeric_limits<double>::max();
			for (unsigned i = 0; i < g.size(); ++i) {
				auto v2 = g[i];
				auto dist = Distance[v][v2];
				if (dist < closestDist) {
					closestIndex = i;
					closestDist = dist;
				}
			}
			v = g[closestIndex];
			g.erase(g.begin() + closestIndex);
			result += closestDist;
		}

		return result;
	}

	double Node2GraphDist(unsigned n, vector<unsigned> g) {
		double result = numeric_limits<double>::max();
		for (auto i : g) {
			auto d = Distance[n][i];
			result = (d < result ? d : result);
		}
		return result;
	}

	void Try(vector<unsigned> tracked, vector<unsigned> untracked, double len) {
		++times;
		if (untracked.size()==1) {
			auto first = tracked[0];
			auto last = tracked[tracked.size() - 1];
			auto last_untracked = *untracked.begin();

			tracked.push_back(last_untracked);
			tracked.push_back(first);
			untracked.clear();
			
			len += Distance[last][last_untracked];
			len += Distance[last_untracked][first];
			if (len < sPathLen) {
				sPathLen = len;
				sPath = tracked;
			}
			return;
		}
		for (auto it = untracked.begin(); it != untracked.end();++it) {
			auto toTrack = *it;
			auto first = tracked[0];
			auto last = tracked[tracked.size() - 1];
			auto deltaLen = Distance[last][toTrack];
			last = toTrack;
			
			len += deltaLen;
			it = untracked.erase(it);
			double eval = len + Node2GraphDist(last, untracked) +GetMinSpanTreeLen(untracked) + Node2GraphDist(first, untracked);
			if (eval >= sPathLen) {
				// Pruning
			} else {
				tracked.push_back(toTrack);
				Try(tracked, untracked, len);
				tracked.pop_back();
			}
			it = untracked.insert(it, toTrack);
			len -= deltaLen;
		}
	}

	Solution(vector<Vertice> cities) :Cities(cities), N(cities.size()) {
		for (unsigned i = 0; i < N; ++i) {
			vector<double> dist;
			for (unsigned j = 0; j < N; ++j) {
				if (i == j) {
					dist.push_back(.0);
				} else if (i > j) {
					dist.push_back(Distance[j][i]);
				} else {
					dist.push_back(Cities[i].getDistance(Cities[j]));
				}
			}
			Distance.push_back(dist);
		}
		sPath = InitWithRandomOrder();
		sPathLen = CountPathLen(sPath);
	}

	vector<unsigned> ShortestPath() {
		vector<unsigned> tracked{START_CITY};
		vector<unsigned> untracked;
		for (unsigned i = 0; i < N; ++i) {
			if (i == START_CITY) {
				continue;
			}
			untracked.push_back(i);
		}
		Try(tracked, untracked, 0);
		return sPath;
	}
};

void main() {
	vector<Vertice> V;
	ifstream fin("Input.txt");
	int N;
	fin >> N;
	for (int i = 0; i < N; ++i) {
		double a, b;
		fin >> a >> b;
		V.emplace_back(a, b);
	}
	Solution s(V);
	auto p = s.ShortestPath();
	for (auto i : p) {
		cout << i << endl;
	}
	cout << s.times << endl;
	ofstream fout("Output.txt");
	fout << N << endl;
	for (auto i:p) {
		fout << V[i].x << " " << V[i].y << endl;
	}
}