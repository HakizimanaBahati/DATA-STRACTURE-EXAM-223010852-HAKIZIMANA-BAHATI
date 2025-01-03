
fitness_data = [
    {"name": "Morning Cardio", "type": "Exercise", "priority": 3},
    {"name": "Breakfast Plan", "type": "Meal", "priority": 1},
    {"name": "Strength Training", "type": "Exercise", "priority": 4},
    {"name": "Lunch Plan", "type": "Meal", "priority": 2},
]

def selection_sort(data, key):
   
    n = len(data)
    for i in range(n):
       
        min_index = i
        for j in range(i + 1, n):
            if data[j][key] < data[min_index][key]:
                min_index = j
     
        data[i], data[min_index] = data[min_index], data[i]

selection_sort(fitness_data, "priority")

print("Sorted Fitness Data by Priority:")
for entry in fitness_data:
    print(f"Name: {entry['name']}, Type: {entry['type']}, Priority: {entry['priority']}")
