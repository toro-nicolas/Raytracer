from SceneCreator.utils import *


class Translation:
    def __init__(self):
        self.name = "Translation"
        self.x = 0
        self.y = 0
        self.z = 0

        self.change_values = {
            "x": self.change_x,
            "y": self.change_y,
            "z": self.change_z,
        }


    def change_x(self):
        print("Current x value:", self.x)
        while True:
            try:
                new_value = int(input(f"{YELLOW}Enter new x value: {RESET}"))
                self.x = new_value
                print(f"{GREEN}X value changed to: {self.x}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")


    def change_y(self):
        print("Current y value:", self.y)
        while True:
            try:
                new_value = int(input(f"{YELLOW}Enter new y value: {RESET}"))
                self.y = new_value
                print(f"{GREEN}Y value changed to: {self.y}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")


    def change_z(self):
        print("Current z value:", self.z)
        while True:
            try:
                new_value = int(input(f"{YELLOW}Enter new z value: {RESET}"))
                self.z = new_value
                print(f"{GREEN}Z value changed to: {self.z}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")


    def display(self, tab=0):
        print(f"{' ' * tab}- Translation:")
        print(f"{' ' * (tab + 4)}- X: {self.x}")
        print(f"{' ' * (tab + 4)}- Y: {self.y}")
        print(f"{' ' * (tab + 4)}- Z: {self.z}")


    def add(self):
        start = False
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a translation settings to change:")
            print("0 - Back to transformations menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the translation")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                return False
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Translation added.{RESET}")
                return True
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key]()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")



    def edit(self):
        start = False
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a translation settings to change:")
            print("0 - Back to transformations menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key]()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def write(self, file):
        file.write("            # Translation transformation\n")
        file.write("            translation = {\n")
        file.write("                offset = {\n")
        file.write(f"                    x = {self.x};\n")
        file.write(f"                    y = {self.y};\n")
        file.write(f"                    z = {self.z};\n")
        file.write("                };\n")
        file.write("            };\n")
