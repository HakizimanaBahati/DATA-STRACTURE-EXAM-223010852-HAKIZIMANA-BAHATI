import heapq

class User:
    def __init__(self, user_id, name, weight, height):
        self.user_id = user_id
        self.name = name
        self.weight = weight
        self.height = height

class ExercisePlan:
    def __init__(self, name, duration, calories_burned):
        self.name = name
        self.duration = duration  # in minutes
        self.calories_burned = calories_burned

class MealPlan:
    def __init__(self, name, calories):
        self.name = name
        self.calories = calories

class AVLNode:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.height = 1
        self.left = None
        self.right = None

class AVLTree:
    def __init__(self):
        self.root = None

    def _get_height(self, node):
        return node.height if node else 0

    def _get_balance(self, node):
        return self._get_height(node.left) - self._get_height(node.right)

    def _rotate_right(self, y):
        x = y.left
        T2 = x.right
        x.right = y
        y.left = T2
        y.height = 1 + max(self._get_height(y.left), self._get_height(y.right))
        x.height = 1 + max(self._get_height(x.left), self._get_height(x.right))
        return x

    def _rotate_left(self, x):
        y = x.right
        T2 = y.left
        y.left = x
        x.right = T2
        x.height = 1 + max(self._get_height(x.left), self._get_height(x.right))
        y.height = 1 + max(self._get_height(y.left), self._get_height(y.right))
        return y

    def insert(self, key, value):
        self.root = self._insert(self.root, key, value)

    def _insert(self, node, key, value):
        if not node:
            return AVLNode(key, value)
        if key < node.key:
            node.left = self._insert(node.left, key, value)
        elif key > node.key:
            node.right = self._insert(node.right, key, value)
        else:
            return node

        node.height = 1 + max(self._get_height(node.left), self._get_height(node.right))
        balance = self._get_balance(node)

        # Left Heavy
        if balance > 1 and key < node.left.key:
            return self._rotate_right(node)

        # Right Heavy
        if balance < -1 and key > node.right.key:
            return self._rotate_left(node)

        # Left Right Case
        if balance > 1 and key > node.left.key:
            node.left = self._rotate_left(node.left)
            return self._rotate_right(node)

        # Right Left Case
        if balance < -1 and key < node.right.key:
            node.right = self._rotate_right(node.right)
            return self._rotate_left(node)

        return node

    def search(self, key):
        return self._search(self.root, key)

    def _search(self, node, key):
        if not node or node.key == key:
            return node
        if key < node.key:
            return self._search(node.left, key)
        return self._search(node.right, key)

class BinaryTreeNode:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.left = None
        self.right = None

class BinaryTree:
    def __init__(self):
        self.root = None
        self.size = 0
        self.max_size = 15  # Fixed number of orders

    def insert(self, key, value):
        if self.size >= self.max_size:
            print("Binary tree is full. Cannot add more orders.")
            return
        self.root = self._insert(self.root, key, value)
        self.size += 1

    def _insert(self, node, key, value):
        if not node:
            return BinaryTreeNode(key, value)
        if key < node.key:
            node.left = self._insert(node.left, key, value)
        else:
            node.right = self._insert(node.right, key, value)
        return node

    def print_tree(self):
        def in_order_traversal(node):
            if not node:
                return
            in_order_traversal(node.left)
            print(f"Key: {node.key}, Value: {node.value}")
            in_order_traversal(node.right)
        in_order_traversal(self.root)

class FitnessTracker:
    def __init__(self):
        self.users = AVLTree()
        self.exercise_plans = AVLTree()
        self.meal_plans = AVLTree()
        self.daily_logs = BinaryTree()  # Binary tree to store daily logs
        self.exercise_heap = []  # Heap for most calorie-intensive exercises
        self.meal_heap = []  # Heap for most calorie-intensive meals

    def add_user(self, user_id, name, weight, height):
        user = User(user_id, name, weight, height)
        self.users.insert(user_id, user)

    def add_exercise_plan(self, name, duration, calories_burned):
        plan = ExercisePlan(name, duration, calories_burned)
        self.exercise_plans.insert(name, plan)
        heapq.heappush(self.exercise_heap, (-calories_burned, plan))  # Max-heap by calories burned

    def add_meal_plan(self, name, calories):
        plan = MealPlan(name, calories)
        self.meal_plans.insert(name, plan)
        heapq.heappush(self.meal_heap, (-calories, plan))  # Max-heap by calories

    def get_user(self, user_id):
        node = self.users.search(user_id)
        return node.value if node else None

    def get_exercise_plan(self, name):
        node = self.exercise_plans.search(name)
        return node.value if node else None

    def get_meal_plan(self, name):
        node = self.meal_plans.search(name)
        return node.value if node else None

    def log_daily_activity(self, user_id, exercises, meals):
        user = self.get_user(user_id)
        if not user:
            return "User not found."
        log = {
            "user_id": user_id,
            "exercises": exercises,
            "meals": meals
        }
        self.daily_logs.insert(user_id, log)

    def get_daily_summary(self, user_id):
        logs = []
        def collect_logs(node):
            if not node:
                return
            collect_logs(node.left)
            if node.key == user_id:
                logs.append(node.value)
            collect_logs(node.right)
        collect_logs(self.daily_logs.root)

        total_calories_burned = sum(
            sum(exercise.calories_burned for exercise in log["exercises"])
            for log in logs
        )
        total_calories_consumed = sum(
            sum(meal.calories for meal in log["meals"])
            for log in logs
        )
        return total_calories_burned, total_calories_consumed

    def get_top_exercises(self, n=5):
        return [heapq.heappop(self.exercise_heap)[1] for _ in range(min(n, len(self.exercise_heap)))]

    def get_top_meals(self, n=5):
        return [heapq.heappop(self.meal_heap)[1] for _ in range(min(n, len(self.meal_heap)))]

    def print_all_data(self):
        # Print all users
        print("Users:")
        def print_users(node):
            if not node:
                return
            print_users(node.left)
            user = node.value
            print(f"ID: {user.user_id}, Name: {user.name}, Weight: {user.weight}kg, Height: {user.height}cm")
            print_users(node.right)
        print_users(self.users.root)

        # Print all exercise plans
        print("\nExercise Plans:")
        def print_exercises(node):
            if not node:
                return
            print_exercises(node.left)
            plan = node.value
            print(f"Name: {plan.name}, Duration: {plan.duration} mins, Calories Burned: {plan.calories_burned} kcal")
            print_exercises(node.right)
        print_exercises(self.exercise_plans.root)

        # Print all meal plans
        print("\nMeal Plans:")
        def print_meals(node):
            if not node:
                return
            print_meals(node.left)
            plan = node.value
            print(f"Name: {plan.name}, Calories: {plan.calories} kcal")
            print_meals(node.right)
        print_meals(self.meal_plans.root)

        # Print all daily logs
        print("\nDaily Logs:")
        self.daily_logs.print_tree()
        print("\n")

# Example Usage
tracker = FitnessTracker()

# Add users
tracker.add_user(1, "Alice", 70, 165)
tracker.add_user(2, "Bob", 85, 180)
tracker.add_user(3, "Charlie", 68, 170)
tracker.add_user(4, "Diana", 75, 160)
tracker.add_user(5, "Eve", 60, 155)

# Add exercise plans
tracker.add_exercise_plan("Running", 30, 300)
tracker.add_exercise_plan("Cycling", 45, 400)
tracker.add_exercise_plan("Swimming", 60, 500)
tracker.add_exercise_plan("Yoga", 30, 150)
tracker.add_exercise_plan("Strength Training", 40, 350)

# Add meal plans
tracker.add_meal_plan("Salad", 150)
tracker.add_meal_plan("Chicken Breast", 300)
tracker.add_meal_plan("Protein Shake", 200)
tracker.add_meal_plan("Pasta", 400)
tracker.add_meal_plan("Smoothie", 250)

# Log daily activity
tracker.log_daily_activity(1, [tracker.get_exercise_plan("Running"), tracker.get_exercise_plan("Yoga")], [tracker.get_meal_plan("Salad"), tracker.get_meal_plan("Chicken Breast")])
tracker.log_daily_activity(2, [tracker.get_exercise_plan("Cycling")], [tracker.get_meal_plan("Pasta"), tracker.get_meal_plan("Smoothie")])
tracker.log_daily_activity(3, [tracker.get_exercise_plan("Swimming")], [tracker.get_meal_plan("Protein Shake"), tracker.get_meal_plan("Salad")])
tracker.log_daily_activity(4, [tracker.get_exercise_plan("Strength Training")], [tracker.get_meal_plan("Chicken Breast"), tracker.get_meal_plan("Smoothie")])
tracker.log_daily_activity(5, [tracker.get_exercise_plan("Yoga"), tracker.get_exercise_plan("Cycling")], [tracker.get_meal_plan("Pasta"), tracker.get_meal_plan("Protein Shake")])

# Print summaries
print("IMPLEMENTATION OF HEAPS IN FITNESS SYSTEM PROCESSING")
for user_id in range(1, 6):
    total_burned, total_consumed = tracker.get_daily_summary(user_id)
    print(f"User {user_id} - Calories Burned: {total_burned}, Calories Consumed: {total_consumed}")

# Get top exercises and meals
print("\nTop Exercises:")
for exercise in tracker.get_top_exercises():
    print(f"{exercise.name} - {exercise.calories_burned} kcal")

print("\nTop Meals:")
for meal in tracker.get_top_meals():
    print(f"{meal.name} - {meal.calories} kcal")
