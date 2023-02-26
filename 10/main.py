nums = list(map(int, input().split()))
nums.sort(reverse=True)
ret = 0
for j in range(nums[0] - 1, nums[1], -1):
    ret += j
for j in range(nums[1] - 1, nums[2], -1):
    ret += j
print(ret)
