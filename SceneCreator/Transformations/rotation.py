from SceneCreator.utils import *


class Rotation:
    def __init__(self):
        self.name = "Rotation"
        self.angle_y = 0

        self.change_values = {
            "angle y": self.change_angle_y,
        }


    def change_angle_y(self):
        print("Current angle y value:", self.angle_y)
        while True:
            try:
                new_value = int(input(f"{YELLOW}Enter new angle y value: {RESET}"))
                self.angle_y = new_value
                print(f"{GREEN}Angle y value changed to: {self.angle_y}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")


    def display(self, tab=0):
        print(f"{' ' * tab}- Rotation:")
        print(f"{' ' * (tab + 4)}- Angle Y: {self.angle_y}")


    def add(self):
        start = False
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a rotation settings to change:")
            print("0 - Back to transformations menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the rotation")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                return False
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Rotation added.{RESET}")
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
            print("Choose a rotation settings to change:")
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
        file.write("            # Rotation transformation\n")
        file.write("            rotation = {\n")
        file.write(f"                angleY = {self.angle_y};\n")
        file.write("            };\n")
