#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vll vector<ll>
constexpr ll count_distinct_primes(ll n) {
	ll ret = 0;
	if (n % 2 == 0) ++ret;
	while (n % 2 == 0) {
		n /= 2;
	}
	for (ll i = 3; i * i <= n; i+=2) {
		if (n % i == 0) ++ret;
		while (n % i == 0) {
			n /= i;
		}
		if (n == 1) {
			break;
		}
	}
	if (n > 1) {++ret;}
	return ret;
}

const ll MAXN = 110;
ll prefix[MAXN];
vector<bool> is_prime(MAXN, true);
vll primes{2};

// only need to get prime number up to sqrt of MAXN
void populate_sieves() {
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= MAXN; ++i) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

template <typename T>
void deb(const vector<T>nums) {
    for (auto a : nums) {
        cout << a << " ";
    }
    cout << "\n";

}

void init() {
	memset(prefix, 0, sizeof(prefix));
    populate_sieves();
    for (ll i = 3; i < MAXN; i += 2) {
        if (is_prime[i]) {
            cout << i << "\n";
            primes.push_back(i);
        }
    }
    for (ll i = 0; i < primes.size(); ++i) {
        for (ll i = 0; i <)
    }
    for (ll i = 3; i < MAXN; ++i) {
        prefix[i] += prefix[i - 1];
    }
}

void solve() {
    ll l, r;
    while (cin >> l && cin >> r) {
        ll total = r - l + 1;
        ll even = prefix[r] - prefix[l - 1];
        cout << even - (total - even) << "\n";
    }
}


int main() {
    init();
    solve();
}
