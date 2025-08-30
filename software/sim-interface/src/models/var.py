class Var:
    def __init__(self, var_id, value):
        self.id = var_id
        self.value = value

    def toggle(self):
        self.value = self.value ^ 1