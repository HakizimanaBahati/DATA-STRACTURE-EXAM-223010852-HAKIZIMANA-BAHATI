class Order:

    def __init__(self, order_id, meal_plan, exercise_plan):
        self.order_id = order_id
        self.meal_plan = meal_plan
        self.exercise_plan = exercise_plan

class TreeNode:

    def __init__(self, order):
        self.order = order
        self.left = None
        self.right = None

class OrderBinaryTree:

    def __init__(self):
        self.root = None
        self.count = 0
        self.max_orders = 10  

    def add_order(self, order):
       
        if self.count >= self.max_orders:
            print("Cannot add more orders. Maximum limit reached.")
            return

        if self.root is None:
            self.root = TreeNode(order)
        else:
            self._add_to_tree(self.root, order)

        self.count += 1

    def _add_to_tree(self, node, order):
       
        if order.order_id < node.order.order_id:
            if node.left is None:
                node.left = TreeNode(order)
            else:
                self._add_to_tree(node.left, order)
        else:
            if node.right is None:
                node.right = TreeNode(order)
            else:
                self._add_to_tree(node.right, order)

    def print_orders(self):

        if self.root is None:
            print("No orders to display.")
        else:
            self._in_order_traversal(self.root)

    def _in_order_traversal(self, node):
        if node is not None:
            self._in_order_traversal(node.left)
            print(f"Order ID: {node.order.order_id}, Meal Plan: {node.order.meal_plan}, Exercise Plan: {node.order.exercise_plan}")
            self._in_order_traversal(node.right)

if __name__ == "__main__":
    tree = OrderBinaryTree()

    tree.add_order(Order(3, "Salad", "Yoga"))
    tree.add_order(Order(1, "Chicken Breast", "KWIRUKA"))
    tree.add_order(Order(2,"Protein Shake", "Strength Training"))
    tree.add_order(Order(5, "Pasta", "swiming"))
    tree.add_order(Order(4, "potatoes", "Cycling"))

    print("\nALL FIXED NUMBER OF ORDERS:")
    tree.print_orders()
