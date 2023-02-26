games = input()

k_values = []

for k in range(1, 2001):
    a_score = 0
    b_score = 0
    a_wins = 0
    b_wins = 0
    for game in games:
        if game == 'A':
            a_score += 1
        if game == 'B':
            b_score += 1
        if a_score == k:
            a_wins += 1
            a_score = 0
            b_score = 0
        if b_score == k:
            b_wins += 1
            a_score = 0
            b_score = 0
    if a_wins > b_wins:
        k_values.append(k)

print(len(k_values))
if (len(k_values) > 0):
    for k in k_values:
        print(k, end=' ')
    print()
        
        
        
    


