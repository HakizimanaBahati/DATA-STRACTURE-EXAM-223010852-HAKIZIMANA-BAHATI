class TreeNode:
    def __init__(self, name, data=None):
        
        self.name = name
        self.data = data
        self.children = []

    def add_child(self, child_node):
     
        self.children.append(child_node)

    def display(self, level=0):
       
        indent = "  " * level
        print(f"{indent}{self.name}: {self.data}")
        for child in self.children:
            child.display(level + 1)



if __name__ == "__main__":
   
    fitness_tree = TreeNode("Fitness Plan")


    day1 = TreeNode("Day 1")
    day2 = TreeNode("Day 2")
    fitness_tree.add_child(day1)
    fitness_tree.add_child(day2)

    breakfast_day1 = TreeNode("Breakfast", "bread, Banana, Coffee")
    lunch_day1 = TreeNode("Lunch", "potetoes, meat, salad")
    dinner_day1 = TreeNode("Dinner", "ibirayi, Sweet Potato,  Vegetables")
    day1.add_child(breakfast_day1)
    day1.add_child(lunch_day1)
    day1.add_child(dinner_day1)

  
    exercise_day1 = TreeNode("Exercise", "30 min Jogging, 20 min Strength Training")
    day1.add_child(exercise_day1)

    
    breakfast_day2 = TreeNode("Breakfast", "Smoothie, Butter Toast")
    lunch_day2 = TreeNode("Lunch", " Sandwich, Indimu")
    dinner_day2 = TreeNode("Dinner", "beans, Rice, meat")
    day2.add_child(breakfast_day2)
    day2.add_child(lunch_day2)
    day2.add_child(dinner_day2)


    exercise_day2 = TreeNode("Exercise", "40 min Cycling, 10 min Yoga")
    day2.add_child(exercise_day2)
    print("IMPLEMENTATION OF TREE TO REPRESENT HIERARCHICAL DATA")

    fitness_tree.display()
