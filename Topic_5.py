class Node:
    def __init__(self, date, meals=None, exercises=None):
        self.date = date 
        self.meals = meals or [] 
        self.exercises = exercises or []  
        self.prev = None 
        self.next = None


class DoublyLinkedList:
    def __init__(self):
        self.head = None  
        self.tail = None

    def add_day(self, date, meals=None, exercises=None):
        
        new_node = Node(date, meals, exercises)
        if not self.head:  
            self.head = self.tail = new_node
        else:
            self.tail.next = new_node
            new_node.prev = self.tail
            self.tail = new_node

    def remove_day(self, date):
       
        current = self.head
        while current:
            if current.date == date:
                if current.prev:
                    current.prev.next = current.next
                if current.next:
                    current.next.prev = current.prev
                if current == self.head: 
                    self.head = current.next
                if current == self.tail: 
                    self.tail = current.prev
                return f"Day {date} removed."
            current = current.next
        return f"Day {date} not found."

    def update_day(self, date, meals=None, exercises=None):
    
        current = self.head
        while current:
            if current.date == date:
                if meals is not None:
                    current.meals = meals
                if exercises is not None:
                    current.exercises = exercises
                return f"Day {date} updated."
            current = current.next
        return f"Day {date} not found."

    def display(self):
   
        current = self.head
        if not current:
            print("No data available.")
            return
        while current:
            print(f"Date: {current.date}")
            print(f"  Meals: {', '.join(current.meals) if current.meals else 'No meals'}")
            print(f"  Exercises: {', '.join(current.exercises) if current.exercises else 'No exercises'}")
            current = current.next


if __name__ == "__main__":
    tracker = DoublyLinkedList()
    
 
    tracker.add_day("2024-12-26", meals=["Breakfast", "Lunch", "Dinner"], exercises=["Running", "Yoga"])
    tracker.add_day("2024-12-28", meals=["Brunch", "Dinner"], exercises=["kunyonga akagare", "Stretching"])
   
    print("IMPLEMENTATION OF DOUBLY LINKED LIST TO TRACK DATA DYNAMICALLY")
    
    print("Starting Data:")
    tracker.display()
    
    
    tracker.update_day("2024-12-26", meals=["Breakfast", "Snack", "Dinner"])
    tracker.update_day("2024-12-28", meals=["lunch", "potetoes", "Dinner"])
    
    print("\nAfter Update:")
    tracker.display()
    
   
    tracker.remove_day("2024-12-26")
    
  
    print("\nAfter Removing a Day:")
    tracker.display()
