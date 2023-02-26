from itertools import combinations

# MAXN = 10000010
MAXN = 110

is_prime = [True for _ in range(MAXN)]
for i in range(2, MAXN):
    if i * i > MAXN:
        break
    if is_prime[i]:
        for j in range(i*i, MAXN, i):
            is_prime[j] = False

primes = [i for i, is_primed in enumerate(is_prime) if is_primed and i > 1]
all_primes_count = len(primes)
is_even = [0 for _ in range(MAXN)]

def get_prod(nums):
    assert len(nums) > 1
    ret = 1
    for a in nums:
        ret *= a
        if ret > MAXN:
            return False, -1
    return True, ret

def f():
    for k in range(2, MAXN, 2):
        for nums in sorted(combinations(primes, k)):
            is_good, even_num = get_prod(nums)
            if is_good:
                print(even_num)
                is_even[even_num] = 1
            else:
                return
f()
for i in range(2, MAXN):
    is_even[i] += is_even[i - 1]

if __name__ == "__main__":
    l, r = map(int, input().split())
    total = r - l + 1
    count_even = is_even[r] - is_even[l - 1]
    print(count_even - (total - count_even))
